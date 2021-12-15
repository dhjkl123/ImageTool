#include "pch.h"
#include "IppEnhance.h"
#include <math.h>

void IppInverse(IppByteImage& img)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();
	for (int i = 0; i < size; i++)
	{
		p[i] = 255 - p[i];
	}

}

void IppBrightness(IppByteImage& img, int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();
	for (int i = 0; i < size; i++)
	{
		p[i] = limit(p[i] + n);
	}

}

void IppContrast(IppByteImage& img , int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();
	for (int i = 0; i < size; i++)
	{
		p[i] = static_cast<BYTE>(limit(p[i] + (p[i] - 128) * n / 100));
	}

}

void IppGamma(IppByteImage& img, float fgamma)
{
	float inv_gamma = 1.f / fgamma;

	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = static_cast<BYTE>(limit((pow(p[i] / 255, inv_gamma) * 255 + 0.5f)));
	}

}

void IppGammaCorrection(IppByteImage& img, float fgamma)
{
	float inv_gamma = 1.f / fgamma;

	float gamma_table[256];
	for (int i = 0; i < 256; i++)
		gamma_table[i] = pow((i / 255.f), inv_gamma);

	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = static_cast<BYTE>(limit(gamma_table[p[i]] * 255 + 0.5f));
	}

}

void IppHistogram(IppByteImage& img, double histo[256])
{

	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	int cnt[256];
	memset(cnt, 0, sizeof(int) * 256);
	for (int i = 0; i < size; i++)
		cnt[p[i]]++;

	for (int i = 0; i < 256; i++)
	{
		histo[i] = static_cast<double>(cnt[i]) / size;
	}

}

void IppHistogramStrectch(IppByteImage& img)
{

	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	BYTE gray_max, gray_min;
	gray_max = gray_min = p[0];
	
	for (int i = 1; i < size; i++)
	{
		if (gray_max < p[i])gray_max = p[i];
		if (gray_min > p[i])gray_min = p[i];
	}

	if (gray_max == gray_min)
		return;

	for (int i = 0; i < size; i++)
	{
		p[i] = (p[i] - gray_min) * 255 / (gray_max - gray_min);
	}

}

void IppHistogramEQ(IppByteImage& img)
{

	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	double histo[256] = { 0, };
	IppHistogram(img, histo);

	double cdf[256] = { 0, };
	cdf[0] = histo[0];
	for (int i = 1; i < 256; i++)
		cdf[i] = cdf[i - 1] + histo[i];

	for (int i = 0; i < size; i++)
	{
		p[i] = static_cast<BYTE>(limit(cdf[p[i]] * 255));
	}

}