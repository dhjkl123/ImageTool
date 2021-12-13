#include "pch.h"
#include "IppImage.h"
#include "memory.h"



template<typename T>
IppImage<T>::IppImage(int w, int h) :m_nWidth(w), m_nHeight(h), m_tPixels(NULL)
{
	m_tPixels = new T * [sizeof(T*) * m_nHeight];
	m_tPixels[0] = new T[sizeof(T) * m_nWidth * heght];

	for (int i = 1; i < m_nHeight; i++)
		m_tPixels[i] = m_tPixels[i - 1] + m_nWidth;

	memset(m_tPixels[0], 0, sizeof(T) * m_nWidth * heght);
}

template<typename T>
IppImage<T>::IppImage(const IppImage<T>& img) :m_nWidth(img.m_nWidth), m_nHeight(img.m_nHeight), m_tPixels(NULL)
{
	if (img.IsValid())
	{
		m_tPixels = new T * [sizeof(T*) * m_nHeight];
		m_tPixels[0] = new T[sizeof(T) * m_nWidth * m_nHeight];
		for (int i = 1; i < m_nHeight; i++)
			m_tPixels[i] = m_tPixels[i - 1] + m_nWidth;

		memcpy(m_tPixels[0], img.m_tPixels[0], sizeof(T) * m_nWidth * m_nHeight);
	}
}



//template<typename T>
//void IppImage<T>::CreateImage(int w, int h)
//{
//	DestroyImage();
//
//	m_nWidth = w;
//	m_nHeight = h;
//
//	m_tPixels = new T * [sizeof(T*) * m_nHeight];
//	m_tPixels[0] = new T[sizeof(T) * m_nWidth * m_nHeight];
//
//	for (int i = 1; i < m_nHeight; i++)
//		m_tPixels[i] = m_tPixels[i - 1] + m_nWidth;
//
//	memset(m_tPixels[0], 0, sizeof(T) * m_nWidth * m_nHeight);
//}

//template<typename T>
//void IppImage<T>::DestroyImage()
//{
//	if (pixels != NULL)
//	{
//		delete[] pixels[0];
//		delete[] pixels;
//		pixels = NULL;
//	}
//
//	width = height = 0;
//}

template<typename T>
IppImage<T>& IppImage<T>::operator=(const IppImage<T>& img)
{
	if (this == &img)
		return *this;

	CreateImage(img.m_nWidth, img.m_nHeight);
	memcpy(pixels[0], img.GetPixels[0], sizeof(T) * width * height);

	return *this;

}

template<typename T> template<typename U>
void IppImage<T>::Convert(const IppImage<U>& img, bool use_limit) //이미지 형변환 복사
{
	CreateImage(img.GetWidth(), img.GetHeight());

	int size = GetSize();
	T* p1 = GetPixels();
	U* p2 = img.GetPixels();

	if (use_limit)
		for (int i = 0; i < size; i++)
			p1[i] = static_cast<T>(limit(p2[i]));
	else
		for (int i = 0; i < size; i++)
			p1[i] = static_cast<T>(p2[i]);
}