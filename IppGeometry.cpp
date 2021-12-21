#include "pch.h"
#include "IppGeometry.h"

void IppTransLate(IppByteImage& imgSrc, IppByteImage& imgDst, int sx, int sy)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, x, y;

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			x = i - sx;
			y = j - sy;

			if (x >= 0 && x < w && y >= 0 && y < h)
				pDst[j][i] = pSrc[y][x];

		}
	}

}

void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, x, y;
	double rx, ry;

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			// ¿øº» ¿µ»ó ÂüÁ¶ ÁÂÇ¥
			rx = static_cast<double>(w - 1) * i / (nw - 1);
			ry = static_cast<double>(h - 1) * j / (nh - 1);

			//ÃÖ±Ù¹æ ÀÌ¿ô º¸°£
			x = static_cast<int>(rx + 0.5);
			y = static_cast<int>(ry + 0.5);

			if (x >= w) x = w - 1;
			if (y >= h) y = h - 1;

			pDst[j][i] = pSrc[y][x];

		}
	}
}

void IppResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, x1, y1, x2, y2;
	double rx, ry, p , q, value;

	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			// ¿øº» ¿µ»ó ÂüÁ¶ ÁÂÇ¥
			rx = static_cast<double>(w - 1) * i / (nw - 1);
			ry = static_cast<double>(h - 1) * j / (nh - 1);

			//ÃÖ±Ù¹æ ÀÌ¿ô ÁÂÇ¥
			x1 = static_cast<int>(rx);
			y1 = static_cast<int>(ry);

			//ÃÖ±Ù¹æ ÀÌ¿ô ´ÙÀ½ ÁÂÇ¥
			x2 = x1 + 1;
			if (x2 == w) x2 = w - 1;

			y2 = y1 + 1;
			if (y2 == h) y2 = h - 1;

			p = rx - 1;
			q = ry - 1;

			//¾ç¼±Çü º¸°£¹ý
			value = (1.0 - p) * (1.0 - q) * pSrc[y1][x1] + p * (1.0 - q) * pSrc[y1][x1] + (1.0 - p) * q * pSrc[y2][x1] + p * q * pSrc[y2][x2];

			pDst[j][i] = static_cast<BYTE>(limit(value + 5.0));

		}
	}
}
