#include "pch.h"
#include "IppFourier.h"

#include <math.h>

const double PI = 3.14159265358979323846;

void DFT1d(double* re, double* im, int N, int dir)
{
	double* tr = new double[N];
	double* ti = new double[N];
	memcpy(tr, re, sizeof(double) * N);
	memcpy(ti, im, sizeof(double) * N);

	register int i, x;
	double sum_re, sum_im, temp;

	for (i = 0; i < N; i++)
	{
		sum_re = sum_im = 0;

		for (x = 0; x < N; x++)
		{
			temp = 2 * dir * PI * ((double)i * x / N);

			sum_re += (tr[x] * cos(temp) + ti[x] * sin(temp));
			sum_im += (ti[x] * cos(temp) - tr[x] * sin(temp));

		}

		re[i] = sum_re;
		im[i] = sum_im;
	}

	if (dir == -1)
	{
		for (i = 0; i < N; i++)
		{
			re[i] /= (double)N;
			im[i] /= (double)N;
		}
	}

	delete[] tr;
	delete[] ti;

}