#pragma once

#include "IppImage.h"
#include "IppDib.h"

void IppDibToImage(IppDib& dib, IppByteImage& img);
void IppDibToImage(IppDib& dib, IppRGBBYTEImage& img);

void IppImageToDib(IppByteImage& img,IppDib& dib);
void IppImageToDib(IppFloatImage& img, IppDib& dib);
void IppImageToDib(IppRGBBYTEImage& img, IppDib& dib);
