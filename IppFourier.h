#pragma once

#include "IppImage.h"

class IppFourier
{
public: 
	int m_nWidth;
	int m_nHeight;
	IppDoubleImage m_Real;
	IppDoubleImage m_Imag;

public:
	IppFourier();

	void SetImage(IppByteImage& img);
	void GetImage(IppByteImage& img);
	void GetSpectrumImage(IppByteImage& img);
	void GetPhaseImage(IppByteImage& img);

	void DFT(int dir);
	void DFTRC(int dir);
	void FFT(int dir);

	void LowPassIdeal(int cutoff);
	void HighPassIdeal(int cutoff);
	void LowPassGaussian(int cutoff);
	void HighPassGaussian(int cutoff);


};

void DFT1d(double* re, double* im, int N, int dir);
void FFT1d(double* re ,double* im, int N, int dir);
bool IsPowerof2(int n);

