#pragma once

#include "IppImage.h"

void IppEdgeRoberts(IppByteImage& img, IppByteImage& imgEdge);
void IppEdgePrewitt(IppByteImage& img, IppByteImage& imgEdge);
void IppEdgeSobel(IppByteImage& img, IppByteImage& imgEdge);


class IppPoint
{
public:
	int x;
	int y;

public:
	IppPoint() : x(0),y(0){}
	IppPoint(int _x, int _y) : x(_x), y(_y) {}
};

void IppEdgeCanny(IppByteImage& imgSrc, IppByteImage& imgEdge, float sigma, float th_low, float th_high);