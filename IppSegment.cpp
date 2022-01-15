#include "pch.h"

#include "IppSegment.h"
#include "IppEnhance.h"


void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold)
{
	imgDst.CreateImage(imgSrc.GetWidth(), imgSrc.GetHeight());

	int size = imgSrc.GetSize();
	BYTE* pSrc = imgSrc.GetPixels();
	BYTE* pDst = imgDst.GetPixels();

	for (int i = 0; i < size; i++)
	{
		pDst[i] = (pSrc[i] <= threshold) ? 0 : 255;
	}
}

int IppBinarizationIterative(IppByteImage& imgSrc)
{
	double hist[256] = { 0, };
	IppHistogram(imgSrc, hist);

	int i, T, Told;

	double sum = 0.f;
	for (i = 0; i < 256; i++)
		sum += (i * hist[i]);

	T = static_cast<int>(sum + .5f);

	double a1, b1, u1, a2, b2, u2;

	do {
		Told = T;

		a1 = b1 = u1 = 0.f;

		for (i = 0; i <= Told; i++)
		{
			a1 += (i * hist[i]);
			b1 += hist[i];
		}

		if (b1 != 0.f)
			u1 = a1 / b1;

		a2 = b2 = u2 = 0.0;

		for (i = Told+1; i < 256; i++)
		{
			a2 += (i * hist[i]);
			b2 += hist[i];
		}

		if (b2 != 0.f)
			u2 = a2 / b2;

		T = static_cast<int>((u1 + u2) / 2 + 0.5f);
	} while (T != Told);

	return T;

}

int IppLabeling(IppByteImage& imgSrc, IppIntImage& imgDst, std::vector<IppLabelInfo>& labels)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetWidth();

	BYTE** pSrc = imgSrc.GetPixels2D();

	//임시로 레이블을 저장할 메모리 공간과 등가 테이블 생성

	IppIntImage imgMap(w, h);
	int** pMap = imgMap.GetPixels2D();

	const int MAX_LABEL = 100000;
	int eq_tbl[MAX_LABEL][2] = { {0,}, };

	//첫번째 스캔
	register int i, j;
	int label = 0, maxl, minl, min_eq, max_eq;

	for (i = 1; i < h; i++)
	{
		for (j = 1; j < w; j++)
		{
			if (pSrc[j][i] != 0)
			{
				if ((pMap[j - 1][i] != 0) && (pMap[j][i - 1] != 0))
				{
					if (pMap[j - 1][i] == pMap[j][i - 1])
					{
						pMap[j][i] = pMap[j - 1][i];
					}
					else
					{
						maxl = __max(pMap[j - 1][i], pMap[j][i - 1]);
						minl = __min(pMap[j - 1][i], pMap[j][i - 1]);

						pMap[j][i] = minl;

						//등가 테이블 조정
						min_eq = __min(eq_tbl[maxl][1], eq_tbl[minl][1]);
						max_eq = __max(eq_tbl[maxl][1], eq_tbl[minl][1]);

						eq_tbl[eq_tbl[max_eq][1]][1] = min_eq;
					}
				}
				else if (pMap[j - 1][i] != 0)
				{
					pMap[j][i] = pMap[j - 1][i];
				}
				else if (pMap[j][i - 1] != 0)
				{
					pMap[j][i] = pMap[j][i - 1];
				}
				else
				{
					label++;
					pMap[j][i] = label;
					eq_tbl[label][0] = label;
					eq_tbl[label][1] = label;
				}
			}

			

		}
	}

	//등가 테이블 정리
	int temp;
	for (i = 1; i <= label; i++)
	{
		temp = eq_tbl[i][1];
		if (temp != eq_tbl[i][0])
			eq_tbl[i][1] = eq_tbl[temp][1];
	}

	//등가 테이블의 레이블을 1부터 차례대로 증가시키기
	int* hash = new int[label + 1];
	memset(hash, 0, sizeof(int) * (label + 1));

	for (i = 1; i < label; i++)
		hash[eq_tbl[i][1]] = eq_tbl[i][1];

	int label_cnt = 1;
	for (i = 1; i <= label; i++)
		if (hash[i] != 0)
			hash[i] = label_cnt++;

	for (i = 1; i <= label; i++)
		eq_tbl[i][1] = hash[eq_tbl[i][1]];

	delete[] hash;

	//두번째 스캔 - 등가 테이블을 이용하여 모든 픽셀에 고유의 레이블 부여
	imgDst.CreateImage(w, h);
	int** pDst = imgDst.GetPixels2D();

	int idx;
	for (j = 1; j < h; j++)
	{
		for (i = 1; i < w; i++)
		{
			if (pMap[j][i] != 0)
			{
				idx = pMap[j][i];
				pDst[j][i] = eq_tbl[idx][1];
			}
		}
	}

	//IppLabelInfo 정보 작성
	labels.resize(label_cnt - 1);

	IppLabelInfo* pLabel;
	for (j = 1; j < h; j++)
	{
		for (i = 1; i < w; i++)
		{
			if (pDst[j][i] != 0)
			{
				pLabel = &labels.at(pDst[j][i] - 1);
				pLabel->pixels.push_back(IppPoint(i, j));
				pLabel->cx += i;
				pLabel->cy += j;

				if (i < pLabel->minx) pLabel->minx = i;
				if (i > pLabel->maxx) pLabel->maxx = i;
				if (j < pLabel->miny) pLabel->miny = j;
				if (j > pLabel->maxy) pLabel->maxy = j;
			}
		}
	}

	for (IppLabelInfo& label : labels)
	{
		label.cx /= label.pixels.size();
		label.cy /= label.pixels.size();
	}

	return (label_cnt - 1);

}

void IppContourTracing(IppByteImage& imgSrc, int sx, int sy, std::vector<IppPoint>& cp)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	BYTE** pSrc = imgSrc.GetPixels2D();

	cp.clear();

	if (pSrc[sy][sx] != 255)
		return;

	int x, y, nx, ny;
	int d, cnt;
	int dir[8][2] = {
		{1,0},
		{1,1},
		{0,1},
		{-1,1},
		{-1,0},
		{-1,-1},
		{0,-1},
		{1,-1}
	};

	x = sx;
	y = sy;
	d = cnt = 0;

	while (1)
	{
		nx = x + dir[d][0];
		ny = y + dir[d][1];

		if (nx < 0 || nx >= w || ny < 0 || ny >= h || pSrc[ny][nx] == 0)
		{
			if (++d > 7) d = 0;
			cnt++;

			if (cnt >= 8)
			{
				cp.push_back(IppPoint(x, y));
				break;
			}
		}
		else
		{
			cp.push_back(IppPoint(x, y));

			x = nx;
			y = ny;

			cnt = 0;
			d = (d + 6) % 8;
		}

		if (x == sx && y == sy && d == 0)
			break;
	}

}