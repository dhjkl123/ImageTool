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