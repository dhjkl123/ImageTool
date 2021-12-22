#include "pch.h"
#include <assert.h>
#include "IppConvert.h"

void IppDibToImage(IppDib& dib, IppByteImage& img)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 8);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws = (w + 3) & ~3; // ���� ������ �����ϱ� ���� �ʿ��� ����Ʈ �� (4���)
	BYTE* pDIBits = dib.GetDIBitsAddr();

	img.CreateImage(w, h);
	BYTE** pixels = img.GetPixels2D();

	for (int i = 0; i < h; i++)
	{
		memcpy(pixels[i], &pDIBits[(h - 1 - i) * ws], w); // (h - 1 - i) ������ �����̱� ������ �Ųٷ� ����
	}
}

void IppDibToImage(IppDib& dib, IppRGBBYTEImage& img)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 24);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws = (w * 3 + 3) & ~3; // ���� ������ �����ϱ� ���� �ʿ��� ����Ʈ �� (4���)
	BYTE* pDIBits = dib.GetDIBitsAddr();

	img.CreateImage(w, h);
	RGBBYTE** pixels = img.GetPixels2D();

	for (int i = 0; i < h; i++)
	{
		memcpy(pixels[i], &pDIBits[(h - 1 - i) * ws], w * 3); // (h - 1 - i) ������ �����̱� ������ �Ųٷ� ����
	}

}

void IppImageToDib(IppByteImage& img, IppDib& dib)
{
	assert(img.IsValid());
	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w + 3) & ~3; // ���� ������ �����ϱ� ���� �ʿ��� ����Ʈ �� (4���)
	BYTE** pixels = img.GetPixels2D();

	dib.CreatGrayBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	for (int i = 0; i < h; i++)
	{
		memcpy(&pDIBits[(h - 1 - i) * ws], pixels[i], w); // (h - 1 - i) ������ �����̱� ������ �Ųٷ� ����
	}

}
void IppImageToDib(IppFloatImage& img, IppDib& dib)
{
	assert(img.IsValid());
	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w + 3) & ~3; // ���� ������ �����ϱ� ���� �ʿ��� ����Ʈ �� (4���)
	float** pixels = img.GetPixels2D();

	dib.CreatGrayBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			pDIBits[(h - 1 - j) * ws + i] = static_cast<BYTE>(limit(pixels[j][i] + 0.5f)); // (h - 1 - i) ������ �����̱� ������ �Ųٷ� ����
		}
	}
}

void IppImageToDib(IppRGBBYTEImage& img, IppDib& dib)
{
	assert(img.IsValid());
	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w * 3+3) & ~3; // ���� ������ �����ϱ� ���� �ʿ��� ����Ʈ �� (4���)
	RGBBYTE** pixels = img.GetPixels2D();

	dib.CreatGrayBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	for (int i = 0; i < h; i++)
	{
		memcpy(&pDIBits[(h - 1 - i) * ws], pixels[i], w * 3); // (h - 1 - i) ������ �����̱� ������ �Ųٷ� ����
	}
}