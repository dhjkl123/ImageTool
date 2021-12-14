#pragma once

#include "IppImage.h"

void IppInverse(IppByteImage& img);
void IppBrightness(IppByteImage& img, int n);
void IppContrast(IppByteImage& img, int n);
void IppGamma(IppByteImage& img, float fgamma);
void IppGammaCorrection(IppByteImage& img, float fgamma);