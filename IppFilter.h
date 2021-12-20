#pragma once

#include "IppImage.h"

void IppFilterMean(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppFilterWeightedMean(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppFilterGaussian(IppByteImage& imgSrc, IppByteImage& imgDst, double sigma);

void IppFilterLaplacian(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppFilterUnsharpMask(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppFilterHighboost(IppByteImage& imgSrc, IppByteImage& imgDst, float alpha);

void IppNoiseGaussian(IppByteImage& imgSrc, IppByteImage& imgDst, int amount);
void IppNoiseSaltPepper(IppByteImage& imgSrc, IppByteImage& imgDst, int amount);

void IppFilterMedian(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppFilterDiffusion(IppByteImage& imgSrc, IppFloatImage& imgDst, float lambda, float k, int iter);