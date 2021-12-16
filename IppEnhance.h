#pragma once

#include "IppImage.h"

// 6°­
void IppInverse(IppByteImage& img);
void IppBrightness(IppByteImage& img, int n);
void IppContrast(IppByteImage& img, int n);

void IppGamma(IppByteImage& img, float fgamma);
void IppGammaCorrection(IppByteImage& img, float fgamma);

void IppHistogram(IppByteImage& img, double histo[256]);
void IppHistogramStrectch(IppByteImage& img);
void IppHistogramEQ(IppByteImage& img);

//7°­
bool IppAdd(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppSub(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppAvg(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppDiff(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

bool IppAND(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppOR(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
