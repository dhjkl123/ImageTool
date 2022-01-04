#include "pch.h"
#include "IppFourier.h"

#include <math.h>
#include <algorithm>

const double PI = 3.14159265358979323846;

IppFourier::IppFourier()
	:m_nWidth(0), m_nHeight(0)
{

}

void IppFourier::SetImage(IppByteImage& img)
{
	m_nWidth = img.GetWidth();
	m_nHeight = img.GetHeight();

	m_Real.Convert(img, 1);
	m_Imag.CreateImage(m_nWidth, m_nHeight);

}

void IppFourier::GetImage(IppByteImage& img)
{
	if (!m_Real.IsValid())
		return;

	img.CreateImage(m_nWidth, m_nHeight);

	double* pRe = m_Real.GetPixels();
	BYTE* ptr = img.GetPixels();

	int size = m_Real.GetSize();
	for (int i = 0; i < size; i++)
		ptr[i] = static_cast<BYTE>(limit(pRe[i] + 0.5));


}

void IppFourier::GetSpectrumImage(IppByteImage& img)
{
	register int i, j;
	img.CreateImage(m_nWidth, m_nHeight);
	BYTE** ptr = img.GetPixels2D();

	double** pRe = m_Real.GetPixels2D();
	double** pIm = m_Imag.GetPixels2D();

	IppDoubleImage spectrum(m_nWidth, m_nHeight);
	double** pSpec = spectrum.GetPixels2D();

	// ���Ҽ� ���� ������ �α׷� ��ȯ�Ͽ� ����
	// ����ȭ�� ��� �̓G ������ ���Ͽ� ����Ʈ���� �ִ� ���
	double mag, max_value = 0;
	for (j = 0; j < m_nHeight; j++)
	{
		for (i = 0; i < m_nWidth; i++)
		{
			mag = sqrt(pRe[j][i] * pRe[j][i] + pIm[j][i] * pIm[j][i]);
			pSpec[j][i] = log(mag + 1);

			if (pSpec[j][i] > max_value)
				max_value = pSpec[j][i];
		}
	}

	//��� ���� ����. Ǫ���� ��ȯ ����� Shift�ϰ�, ��� ������ �ִ��� 255�� �ǵ��� �׷��̽����� ���� ����ȭ
	int x, y;
	for (j = 0; j < m_nHeight; j++)
	{
		for (i = 0; i < m_nWidth; i++)
		{
			x = i + m_nWidth / 2;
			y = j + m_nHeight / 2;

			if (x >= m_nWidth) x -= m_nWidth;
			if (y >= m_nHeight) y -= m_nHeight;

			ptr[j][i] = static_cast<BYTE>(limit(pSpec[y][x] * 255 / max_value));
		}
	}

}

void IppFourier::GetPhaseImage(IppByteImage& img)
{
	register int i, j;

	img.CreateImage(m_nWidth, m_nHeight);
	BYTE** ptr = img.GetPixels2D();

	double** pRe = m_Real.GetPixels2D();
	double** pIm = m_Imag.GetPixels2D();

	IppDoubleImage phase(m_nWidth, m_nHeight);
	double** pPhase = phase.GetPixels2D();

	//���Ҽ� ���� ������ ����. atan2 �Լ��� ��ȯ���� -PI ~ PI �̴�.

	for (j = 0; j < m_nHeight; j++)
	{
		for (i = 0; i < m_nWidth; i++)
		{
			pPhase[j][i] = atan2(pIm[j][i], pRe[j][i]);
		}
	}

	//��� ���� ����. Ǫ���� ��ȯ ����� SHIFT �ϰ�, ��� ������ �ִ��� 255�� �ǵ��� �׷��̽����� ���� ����ȭ

	int x, y;
	for (j = 0; j < m_nHeight; j++)
	{
		for (i = 0; i < m_nWidth; i++)
		{
			x = i + m_nWidth / 2;
			y = j + m_nHeight / 2;

			if (x >= m_nWidth) x -= m_nWidth;
			if (y >= m_nHeight) y -= m_nHeight;

			ptr[j][i] = static_cast<BYTE>(limit(pPhase[y][x] * 128 / PI + 128));
		}
	}


}

void IppFourier::DFT(int dir)
{
	if (!m_Real.IsValid())
		return;

	//real, imag ���纻 ����

	IppDoubleImage real_cpy = m_Real;
	IppDoubleImage imag_cpy = m_Imag;

	double** pRe = m_Real.GetPixels2D();
	double** pIm = m_Imag.GetPixels2D();

	double** pReCpy = real_cpy.GetPixels2D();
	double** pImCpy = imag_cpy.GetPixels2D();

	// �̻� Ǫ���� ��ȯ
	register int i, j, x, y;
	double sum_re, sum_im, temp;

	for (j = 0; j < m_nHeight; j++)
	{
		for (i = 0; i < m_nWidth; i++)
		{
			sum_re = sum_im = 0;

			for (y = 0; y < m_nHeight; y++)
			{
				for (x = 0; x < m_nWidth; x++)
				{
					temp = 2 * dir * PI * (static_cast<double>(i) * x / m_nWidth + static_cast<double>(j) * y / m_nHeight);
					sum_re += (pReCpy[y][x] * cos(temp) - pImCpy[y][x] * sin(temp));
					sum_im += (pReCpy[y][x] * sin(temp) + pImCpy[y][x] * sin(temp));
				}
			}

			pRe[j][i] = sum_re;
			pIm[j][i] = sum_im;

			if (dir == -1)
			{
				pRe[j][i] /= (m_nWidth * m_nHeight);
				pIm[j][i] /= (m_nWidth * m_nHeight);
			}

		}
	}

}

void IppFourier::DFTRC(int dir)
{
	if (!m_Real.IsValid())
		return;

	//�� ���� �̻� Ǫ���� ��ȯ (�Ǵ� ����ȯ)

	IppDoubleImage real_tmp, imag_tmp;

	real_tmp.CreateImage(m_nWidth, 1);
	imag_tmp.CreateImage(m_nWidth, 1);

	double* pReTmp = real_tmp.GetPixels();
	double* pImTmp = imag_tmp.GetPixels();

	double** pRe = m_Real.GetPixels2D();
	double** pIm = m_Imag.GetPixels2D();


	// �̻� Ǫ���� ��ȯ
	register int i, j;

	for (j = 0; j < m_nHeight; j++)
	{
		for (i = 0; i < m_nWidth; i++)
		{			
			pReTmp[i] = pRe[j][i];
			pImTmp[i] = pRe[j][i];
			
		}

		DFT1d(pReTmp, pImTmp, m_nWidth, dir);

		for (i = 0; i < m_nWidth; i++)
		{
			pRe[j][i] = pReTmp[i];
			pIm[j][i] = pImTmp[i];

		}
	}

	//�� ���� �̻� Ǫ���� ��ȯ (�Ǵ� ����ȯ)

	real_tmp.CreateImage(m_nHeight, 1);
	imag_tmp.CreateImage(m_nHeight, 1);

	pReTmp = real_tmp.GetPixels();
	pImTmp = imag_tmp.GetPixels();

	memset(pReTmp, 0, sizeof(double) * m_nHeight);
	memset(pImTmp, 0, sizeof(double) * m_nHeight);

	// �̻� Ǫ���� ��ȯ
	for (i = 0; i < m_nWidth; i++)
	{
		for (j = 0; j < m_nHeight; j++)
		{
			pReTmp[j] = pRe[j][i];
			pImTmp[j] = pRe[j][i];

		}

		DFT1d(pReTmp, pImTmp, m_nHeight, dir);

		for (j = 0; j < m_nHeight; j++)
		{
			pRe[j][i] = pReTmp[j];
			pIm[j][i] = pImTmp[j];

		}
	}

}

void IppFourier::FFT(int dir)
{
	if (!m_Real.IsValid())
		return;

	if (!IsPowerof2(m_nWidth) || !IsPowerof2(m_nHeight))
		return;

	//����� �̻� Ǫ���� ��ȯ

	IppDoubleImage real_tmp, imag_tmp;

	real_tmp.CreateImage(m_nWidth, 1);
	imag_tmp.CreateImage(m_nWidth, 1);

	double* re = real_tmp.GetPixels();
	double* im = imag_tmp.GetPixels();

	double** pRe = m_Real.GetPixels2D();
	double** pIm = m_Imag.GetPixels2D();

	register int i, j;
	// �� ���� �̻� Ǫ���� ��ȯ
	for (j = 0; j < m_nHeight; j++)
	{
		for (i = 0; i < m_nWidth; i++)
		{
			re[i] = pRe[j][i];
			im[i] = pIm[j][i];
		}

		FFT1d(re, im, m_nWidth,  dir);

		for (i = 0; i < m_nWidth; i++)
		{
			pRe[j][i] = re[i];
			pIm[j][i] = im[i];
		}

	}

	//�� ���� �̻�Ǫ���� ��ȯ
	real_tmp.CreateImage(m_nHeight, 1);
	imag_tmp.CreateImage(m_nHeight, 1);

	re = real_tmp.GetPixels();
	im = imag_tmp.GetPixels();

	memset(re, 0, sizeof(double) * m_nHeight);
	memset(im, 0, sizeof(double) * m_nHeight);

	// �̻� Ǫ���� ��ȯ
	for (i = 0; i < m_nWidth; i++)
	{
		for (j = 0; j < m_nHeight; j++)
		{
			re[j] = pRe[j][i];
			im[j] = pRe[j][i];

		}

		FFT1d(re, im, m_nHeight, dir);

		for (j = 0; j < m_nHeight; j++)
		{
			pRe[j][i] = re[j];
			pIm[j][i] = im[j];

		}
	}
}


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

void FFT1d(double* re, double* im, int N, int dir)
{
	register int i, j, k;

	//�Է� ������ ���� �ٲٱ�

	int n2 = N >> 1;
	int nb = 0;

	while (N != (1 << nb))
		nb++;

	for (i = 0, j = 0; i < N - 1; i++)
	{
		if (i < j)
		{
			std::swap(re[i], re[j]);
			std::swap(im[i], im[j]);
		}

		k = n2;

		while (k <= j)
		{
			j -= k;
			k >>= 1;
		}

		j += k;

	}

	//�����ö��� �˰���

	int i1, l, l1, l2;
	double c1, c2, t1, t2, u1, u2, z;

	c1 = -1.0;
	c2 = 0.0;
	l2 = 1;

	for (l = 0; l < nb; l++)
	{
		l1 = l2;
		l2 <<= 1;
		u1 = 1.0;
		u2 = 0.0;

		for (j = 0; j < l1; j++)
		{
			for (i = j; i < N; i += l2)
			{
				i1 = i + l1;
				t1 = u1 * re[i1] - u2 * im[i1];
				t2 = u1 * im[i1] + u2 * re[i1];
				re[i1] = re[i] - t1;
				im[i1] = im[i] - t2;
				re[i] += t1;
				im[i] += t2;
			}

			z = u1 * c1 - u2 * c2;
			u2 = u1 * c2 + u2 * c1;
			u1 = z;

		}

		c2 = sqrt((1.0 - c1) / 2.0);
		if (dir == 1) //forward
			c2 = -c2;

		c1 = sqrt((1.0 + c1) / 2.0);

	}

	if (dir == -1) //IDFT
	{
		for (i = 0; i < N; i++)
		{
			re[i] /= static_cast<double>(N);
			im[i] /= static_cast<double>(N);
		}
	}


}

bool IsPowerof2(int n)
{
	int ref = 1;

	while (ref < n)
		ref <<= 1;

	if (ref == n)
		return true;
	else
		return false;

}
