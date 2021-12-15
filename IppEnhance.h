#pragma once

#include "IppImage.h"

void IppInverse(IppByteImage& img);
void IppBrightness(IppByteImage& img, int n);
void IppContrast(IppByteImage& img, int n);
void IppGamma(IppByteImage& img, float fgamma);
void IppGammaCorrection(IppByteImage& img, float fgamma);
void IppHistogram(IppByteImage& img, double histo[256]);
void IppHistogramStrectch(IppByteImage& img);
void IppHistogramEQ(IppByteImage& img);