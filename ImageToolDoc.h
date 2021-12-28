﻿
// ImageToolDoc.h: CImageToolDoc 클래스의 인터페이스
//


#pragma once

#include "IppDib.h"

class CImageToolDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageToolDoc() noexcept;
	DECLARE_DYNCREATE(CImageToolDoc)

// 특성입니다.
public:

// 작업입니다.
public:
	IppDib m_Dib;
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnWindowDupucate();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnImageInverse();
	afx_msg void OnUpdateImageInverse(CCmdUI* pCmdUI);
	afx_msg void OnBrightcontrast();
	afx_msg void OnGamma();
	afx_msg void OnHistogram();
	afx_msg void OnHistogramStretch();
	afx_msg void OnHistogramEq();
	afx_msg void OnLogical();
	afx_msg void OnBitplain();
	afx_msg void OnFilterMean();
	afx_msg void OnFilterWhightedMean();
	afx_msg void OnFilterGaussian();
	afx_msg void OnFilterLaplacian();
	afx_msg void OnFilterUnsharpMask();
	afx_msg void OnFilterHighboost();
	afx_msg void OnNoise();
	afx_msg void OnMedian();
	afx_msg void OnDiff();
	afx_msg void OnTranslate();
	afx_msg void OnResize();
	afx_msg void OnRotate();
	afx_msg void OnFlip0();
	afx_msg void OnFlip1();
	afx_msg void OnRoberts();
	afx_msg void OnPrewitt();
	afx_msg void OnSobel();
	afx_msg void OnCanny();
	afx_msg void OnHough();
};
