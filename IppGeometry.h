#pragma once

#include "IppImage.h"

void IppTransLate(IppByteImage& imgSrc, IppByteImage& imgDst, int sx, int sy);
void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);
void IppResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);

