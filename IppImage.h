#pragma once

#include "RGBBYTE.h"

template<typename T>
class IppImage
{
protected:
	int m_nWidth;
	int m_nHeight;
	T** m_tPixels;

public:

	//template<typename T>
	IppImage<T>::IppImage() :m_nWidth(0), m_nHeight(0), m_tPixels(NULL)
	{

	}

	IppImage(int w, int h);
	IppImage(const IppImage<T>& img);

	//template<typename T>
	IppImage<T>::~IppImage()
	{
		if (m_tPixels != NULL)
		{
			delete[] m_tPixels[0];
			delete[] m_tPixels;
		}
	}

	void CreateImage(int w, int h) // template 사용시 cpp h 분리 X
	{
		DestroyImage();

		m_nWidth = w;
		m_nHeight = h;

		m_tPixels = new T * [sizeof(T*) * m_nHeight];
		m_tPixels[0] = new T[sizeof(T) * m_nWidth * m_nHeight];

		for (int i = 1; i < m_nHeight; i++)
			m_tPixels[i] = m_tPixels[i - 1] + m_nWidth;

		memset(m_tPixels[0], 0, sizeof(T) * m_nWidth * m_nHeight);
	}

	void DestroyImage()
	{	
		if (m_tPixels != NULL)
		{
			delete[] m_tPixels[0];
			delete[] m_tPixels;
			m_tPixels = NULL;
		}

		m_nWidth = m_nHeight = 0;	
	}

	T* GetPixels() const {
		if (m_tPixels) return m_tPixels[0];
		else return NULL;
	}

	T** GetPixels2D() const { return m_tPixels; }

	IppImage<T>& operator=(const IppImage<T>& img);
	template<typename U> IppImage<T>& operator=(const IppImage<U>& img);

	template<typename U> void Convert(const IppImage<U>& img, bool use_limit); // ??

	int GetWidth() const { return m_nWidth; }
	int GetHeight() const { return m_nHeight; }
	int GetSize() const { return m_nWidth * m_nHeight; }
	bool IsValid() const { return (m_tPixels != NULL); }



};

typedef IppImage<BYTE> IppByteImage;
typedef IppImage<int> IppIntImage;
typedef IppImage<float> IppFloatImage;
typedef IppImage<double> IppDoubleImage;
typedef IppImage<RGBBYTE> IppRGBBYTEImage;

