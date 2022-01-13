#pragma once

#include "IppImage.h"

void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold);
int IppBinarizationIterative(IppByteImage& imgSrc);