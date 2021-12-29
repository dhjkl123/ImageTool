#pragma once

#include "IppImage.h"
#include <vector>


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

class IppLineParam
{
public:
	double rho;
	double ang;
	int vote;

public:
	IppLineParam() : rho(0), ang(0), vote(0) {}
	IppLineParam(double rho, double ang, int vote) :rho(rho), ang(ang), vote(vote) {}
};

inline bool operator< (const IppLineParam& lhs, const IppLineParam& rhs)
{
	return lhs.vote > rhs.vote;
}

void IppHoughLine(IppByteImage& img, std::vector<IppLineParam>& lines, int threshold = 60);
void IppDrawLine(IppByteImage& img, IppLineParam line, BYTE c);
void IppDrawLine(IppByteImage& img, int x1, int y1, int x2, int y2, BYTE c);

void IppHarrisCorner(IppByteImage& img, std::vector<IppPoint>& corners, double th);
