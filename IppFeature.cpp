#include "pch.h"
#include "IppFeature.h"
#include "IppFilter.h"

#include <vector>

const double PI = 3.1415926535897;
const float PI_F = 3.1415926535897;

#define CHECK_WEAK_EDGE(x,y)\
	if(pEdge[y][x] == WEAK_EDGE){\
		pEdge[y][x] = STRONG_EDGE; \
		strong_edges.push_back(IppPoint(x,y));\
	}

void IppEdgeRoberts(IppByteImage& img, IppByteImage& imgEdge)
{
	int w = img.GetWidth();
	int h = img.GetHeight();

	imgEdge.CreateImage(w, h);

	BYTE** p1 = img.GetPixels2D();
	BYTE** p2 = imgEdge.GetPixels2D();

	int i, j, h1, h2;
	double hval;

	for (j = 1; j < h; j++)
	{
		for (i = 1; i < w - 1; i++)
		{
			h1 = p1[j][i] - p1[j - 1][i - 1];
			h2 = p1[j][i] - p1[j - 1][i + 1];

			hval = sqrt(static_cast<double>(h1 * h1 + h2 * h2));

			p2[j][i] = static_cast<BYTE>(limit(hval + 0.5));

		}
	}


}
void IppEdgePrewitt(IppByteImage& img, IppByteImage& imgEdge)
{
	int w = img.GetWidth();
	int h = img.GetHeight();

	imgEdge.CreateImage(w, h);

	BYTE** p1 = img.GetPixels2D();
	BYTE** p2 = imgEdge.GetPixels2D();

	int i, j, h1, h2;
	double hval;

	for (j = 1; j < h - 1; j++)
	{
		for (i = 1; i < w - 1; i++)
		{
			h1 = -p1[j - 1][i - 1] - p1[j - 1][i] - p1[j - 1][i + 1]
				+ p1[j + 1][i - 1] + p1[j + 1][i] + p1[j + 1][i + 1];
			h2 = -p1[j - 1][i - 1] - p1[j][i - 1] - p1[j + 1][i + 1]
				+ p1[j - 1][i + 1] + p1[j][i + 1] + p1[j + 1][i + 1];

			hval = sqrt(static_cast<double>(h1 * h1 + h2 * h2));

			p2[j][i] = static_cast<BYTE>(limit(hval + 0.5));

		}
	}

}
void IppEdgeSobel(IppByteImage& img, IppByteImage& imgEdge)
{
	int w = img.GetWidth();
	int h = img.GetHeight();

	imgEdge.CreateImage(w, h);

	BYTE** p1 = img.GetPixels2D();
	BYTE** p2 = imgEdge.GetPixels2D();

	int i, j, h1, h2;
	double hval;

	for (j = 1; j < h - 1; j++)
	{
		for (i = 1; i < w - 1; i++)
		{
			h1 = -p1[j - 1][i - 1] - 2 * p1[j - 1][i] - p1[j - 1][i + 1]
				+ p1[j + 1][i - 1] + 2 * p1[j + 1][i] + p1[j + 1][i + 1];
			h2 = -p1[j - 1][i - 1] - 2 * p1[j][i - 1] - p1[j + 1][i + 1]
				+ p1[j - 1][i + 1] + 2 * p1[j][i + 1] + p1[j + 1][i + 1];

			hval = sqrt(static_cast<double>(h1 * h1 + h2 * h2));

			p2[j][i] = static_cast<BYTE>(limit(hval + 0.5));

		}
	}
}

void IppEdgeCanny(IppByteImage& imgSrc, IppByteImage& imgEdge, float sigma, float th_low, float th_high)
{
	register int i, j;

	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	// 1. 가우시안 필터링
	IppFloatImage imgGaussian(w, h);
	IppFilterGaussian(imgSrc, imgGaussian, sigma);

	//2. 그래디언트 구하기 (크기 & 방향)
	IppFloatImage imgGx(w, h); // x 의 그래디언트
	IppFloatImage imgGy(w, h); // y 의 그래디언트
	IppFloatImage imgMag(w, h); // 그래디언트 의 매그니튜드

	float** pGauss = imgGaussian.GetPixels2D();
	float** pGx = imgGx.GetPixels2D();
	float** pGy = imgGy.GetPixels2D();
	float** pMag = imgMag.GetPixels2D();

	for (j = 1; j < h - 1; j++)
	{
		for (i = 1; i < w - 1; i++)
		{
			pGx[j][i] = -pGauss[j - 1][i - 1] - 2 * pGauss[j][i - 1] - pGauss[j + 1][i - 1]
				+ pGauss[j - 1][i + 1] + 2 * pGauss[j][i + 1] + pGauss[j + 1][i + 1];
			pGy[j][i] = -pGauss[j - 1][i - 1] - 2 * pGauss[j - 1][i] - pGauss[j - 1][i + 1]
				+ pGauss[j + 1][i - 1] + 2 * pGauss[j + 1][i] + pGauss[j + 1][i + 1];

			pMag[j][i] = sqrt(pGx[j][i] * pGx[j][i] + pGy[j][i] * pGy[j][i]);

		}
	}

	//3. 비최대 억제
	// 국지적 최대를 구함과 동시에 이중 임계값을 적용하여  strong edge 와 week edge를 구한다

	imgEdge.CreateImage(w, h);
	BYTE** pEdge = imgEdge.GetPixels2D();

	enum DISTRICT 
	{
		AREA0 = 0,
		AREA45, 
		AREA90, 
		AREA135,
		NOAREA
	};

	const BYTE STRONG_EDGE = 255;
	const BYTE WEAK_EDGE = 128;

	std::vector<IppPoint> strong_edges;

	float ang;
	int district;
	bool local_max;

	for (j = 1; j < h - 1; j++)
	{
		for (i = 1; i < w - 1; i++)
		{
			if (pMag[j][i] > th_low)
			{
				if (pGx[j][i] != 0.f)
				{
					ang = atan2(pGy[j][i], pGx[j][i]) * 180 / PI_F;

					if (((ang >= -22.5f) && (ang < 22.5f)) || (ang >= -157.5f) || (ang < -157.5f))
						district = AREA0;
					else if (((ang >= 22.5f) && (ang < 67.5f)) || ((ang >= -157.5f) && (ang < -112.5f)))
						district = AREA45;
					else if (((ang >= 67.5) && (ang < 112.5)) || ((ang >= -112.5) && (ang < -67.5)))
						district = AREA90;
					else
						district = AREA135;
				}
				else
					district = AREA90;

				local_max = false;

				switch (district)
				{
				case AREA0:
					if ((pMag[j][i] >= pMag[j][i - 1]) && (pMag[j][i] > pMag[j][i + 1]))
						local_max = true;
					break;
				case AREA45:
					if ((pMag[j][i] >= pMag[j - 1][i - 1]) && (pMag[j][i] > pMag[j + 1][i + 1]))
						local_max = true;
					break;
				case AREA90:
					if ((pMag[j][i] >= pMag[j - 1][i]) && (pMag[j][i] > pMag[j + 1][i]))
						local_max = true;
					break;
				case AREA135:
				default:
					if ((pMag[j][i] >= pMag[j - 1][i + 1]) && (pMag[j][i] > pMag[j + 1][i - 1]))
						local_max = true;
					break;
				}

				//강한 엣지와 약한 엣지 구분
				if (local_max)
				{
					if (pMag[j][i] > th_high)
					{
						pEdge[j][i] = STRONG_EDGE;
						strong_edges.push_back(IppPoint(i, j));
					}
					else
						pEdge[j][i] = WEAK_EDGE;
				}

			}
		}

	}

	//4. 히스테리시스 엣지 트래킹
	while (!strong_edges.empty())
	{
		IppPoint p = strong_edges.back();
		strong_edges.pop_back();

		int x = p.x, y = p.y;

		// 강한 엣지 주변의 약한 엣지는 최종 엣지(강한 엣지)로 설정

		CHECK_WEAK_EDGE(x + 1, y);
		CHECK_WEAK_EDGE(x + 1, y + 1);
		CHECK_WEAK_EDGE(x, y + 1);
		CHECK_WEAK_EDGE(x - 1, y + 1);
		CHECK_WEAK_EDGE(x - 1, y);
		CHECK_WEAK_EDGE(x - 1, y - 1);
		CHECK_WEAK_EDGE(x, y - 1);
		CHECK_WEAK_EDGE(x + 1, y - 1);

	}

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			if (pEdge[j][i] == WEAK_EDGE) pEdge[j][i] = 0;
		}
	}


}