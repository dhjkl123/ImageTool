#pragma once

#include "IppImage.h"

void IppInverse(IppRGBBYTEImage& img);
void RGB_TO_HSI(double R, double G, double B, double& H, double& S, double& I);
void HSI_TO_RGB(double H, double S, double I, double& R, double& G, double& B);
void RGB_TO_YUV(BYTE R, BYTE G, BYTE B, BYTE& Y, BYTE& U, BYTE& V);
void YUV_TO_RGB(BYTE Y, BYTE U, BYTE V, BYTE& R, BYTE& G, BYTE& B);
void IppColorSplitRGB(IppRGBBYTEImage& imgColor, IppByteImage& imgR, IppByteImage& imgG, IppByteImage& imgB);
void IppColorSplitHSI(IppRGBBYTEImage& imgColor, IppByteImage& imgH, IppByteImage& imgS, IppByteImage& imgI);
void IppColorSplitYUV(IppRGBBYTEImage& imgColor, IppByteImage& imgY, IppByteImage& imgU, IppByteImage& imgV);
bool IppColorCombineRGB(IppByteImage& imgR, IppByteImage& imgG, IppByteImage& imgB, IppRGBBYTEImage& imgColor);
bool IppColorCombineHSI(IppByteImage& imgH, IppByteImage& imgS, IppByteImage& imgI, IppRGBBYTEImage& imgColor);
bool IppColorCombineYUV(IppByteImage& imgY, IppByteImage& imgU, IppByteImage& imgV, IppRGBBYTEImage& imgColor);


template<typename T>
inline T limit(const T& value, const T& lower, const T& upper)
{
	return ((value > upper) ? upper : ((value < lower) ? lower : value));
}
