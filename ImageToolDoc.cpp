﻿
// ImageToolDoc.cpp: CImageToolDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#pragma region Image header

#include "IppImage.h"
#include "IppConvert.h"
#include "IppEnhance.h"
#include "IppFilter.h"
#include "IppGeometry.h"
#include "BrightContrast.h"
#include "IppFeature.h"

#pragma endregion

#include "ImageToolDoc.h"


#pragma region Dlg header

#include "HistogramDlg.h"
#include "ImageLogicalDlg.h"
#include "GaussianDlg.h"
#include "NoiseDlg.h"
#include "DiffDlg.h"
#include "TranslateDlg.h"
#include "FileNewDlg.h"
#include "GammaDlg.h"
#include "ResizeDlg.h"
#include "RotateDlg.h"

#pragma endregion

#include "MainFrm.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)\
	IppByteImage img;\
	IppDibToImage(m_Dib, img);

#define CONVERT_IMAGE_TO_DIB(img, dib)\
	IppDib dib;\
	IppImageToDib(img, dib);

// CImageToolDoc

IMPLEMENT_DYNCREATE(CImageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPUCATE, &CImageToolDoc::OnWindowDupucate)
	ON_COMMAND(ID_EDIT_COPY, &CImageToolDoc::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CImageToolDoc::OnEditPaste)
	ON_COMMAND(ID_IMAGE_INVERSE, &CImageToolDoc::OnImageInverse)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_INVERSE, &CImageToolDoc::OnUpdateImageInverse)
	ON_COMMAND(ID_BRIGHTCONTRAST, &CImageToolDoc::OnBrightcontrast)
	ON_COMMAND(ID_GAMMA, &CImageToolDoc::OnGamma)
	ON_COMMAND(ID_HISTOGRAM, &CImageToolDoc::OnHistogram)
	ON_COMMAND(ID_HISTOGRAM_STRETCH, &CImageToolDoc::OnHistogramStretch)
	ON_COMMAND(ID_HISTOGRAM_EQ, &CImageToolDoc::OnHistogramEq)
	ON_COMMAND(ID_LOGICAL, &CImageToolDoc::OnLogical)
	ON_COMMAND(ID_BITPLAIN, &CImageToolDoc::OnBitplain)
	ON_COMMAND(ID_FILTER_MEAN, &CImageToolDoc::OnFilterMean)
	ON_COMMAND(ID_FILTER_WHIGHTED_MEAN, &CImageToolDoc::OnFilterWhightedMean)
	ON_COMMAND(ID_FILTER_GAUSSIAN, &CImageToolDoc::OnFilterGaussian)
	ON_COMMAND(ID_FILTER_LAPLACIAN, &CImageToolDoc::OnFilterLaplacian)
	ON_COMMAND(ID_FILTER_UNSHARP_MASK, &CImageToolDoc::OnFilterUnsharpMask)
	ON_COMMAND(ID_FILTER_HIGHBOOST, &CImageToolDoc::OnFilterHighboost)
	ON_COMMAND(ID_NOISE, &CImageToolDoc::OnNoise)
	ON_COMMAND(ID_MEDIAN, &CImageToolDoc::OnMedian)
	ON_COMMAND(ID_DIFF, &CImageToolDoc::OnDiff)
	ON_COMMAND(ID_TRANSLATE, &CImageToolDoc::OnTranslate)
	ON_COMMAND(ID_RESIZE, &CImageToolDoc::OnResize)
	ON_COMMAND(ID_ROTATE, &CImageToolDoc::OnRotate)
	ON_COMMAND(ID_FLIP0, &CImageToolDoc::OnFlip0)
	ON_COMMAND(ID_FLIP1, &CImageToolDoc::OnFlip1)
	ON_COMMAND(ID_ROBERTS, &CImageToolDoc::OnRoberts)
	ON_COMMAND(ID_PREWITT, &CImageToolDoc::OnPrewitt)
	ON_COMMAND(ID_SOBEL, &CImageToolDoc::OnSobel)
END_MESSAGE_MAP()


// CImageToolDoc 생성/소멸

CImageToolDoc::CImageToolDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageToolDoc::~CImageToolDoc()
{
}

BOOL CImageToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	BOOL ret = FALSE;


	if (theApp.m_pNewDib == NULL)
	{
		CFileNewDlg Dlg;
		if (Dlg.DoModal() == IDOK)
		{
			if (Dlg.m_nType == 0)
				ret = m_Dib.CreatGrayBitmap(Dlg.m_nWidth, Dlg.m_nHeight);
			else
				ret = m_Dib.CreatRgbBitmap(Dlg.m_nWidth, Dlg.m_nHeight);
		}
		else
		{
			ret = FALSE;
		}
	}
	else
	{
		m_Dib = *(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
		ret = TRUE;
	}


	return ret;
}




// CImageToolDoc serialization

void CImageToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageToolDoc 진단

#ifdef _DEBUG
void CImageToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageToolDoc 명령


BOOL CImageToolDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	BOOL  res = m_Dib.Load(CT2A(lpszPathName));
	if (res)
	{
		CMainFrame* pMain = (CMainFrame * )AfxGetMainWnd();
		CString str; str.Format(_T("[파일 열기] 파일경로 : %s, 가로 크기 : %d픽셀, 세로 크기: %d픽셀, 색상수: %d"), 
			lpszPathName, m_Dib.GetWidth(), m_Dib.GetHeight(), 0x01 << m_Dib.GetBitCount());
		pMain->m_wndOutput.AddString(str);
	}
	return res;
}


BOOL CImageToolDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return m_Dib.Save(CT2A(lpszPathName));
}


void CImageToolDoc::OnWindowDupucate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxNewBitmap(m_Dib);
}


void CImageToolDoc::OnEditCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_Dib.IsValid())
		m_Dib.CopyToClipboard();
}


void CImageToolDoc::OnEditPaste()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IppDib dib;
	if (dib.PasteFromClipboard())
		AfxNewBitmap(dib);
}


void CImageToolDoc::OnImageInverse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib,img)
	IppInverse(img);

	CONVERT_IMAGE_TO_DIB(img, dib)

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnUpdateImageInverse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(m_Dib.GetBitCount() == 8);
}


void CImageToolDoc::OnBrightcontrast()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CBrightContrast dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppBrightness(img, dlg.m_nBright);
		IppContrast(img, dlg.m_nContrast);
		CONVERT_IMAGE_TO_DIB(img, dib)

		AfxNewBitmap(dib);

	}
}


void CImageToolDoc::OnGamma()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGammaDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
			IppGammaCorrection(img, dlg.m_fGamma);
		CONVERT_IMAGE_TO_DIB(img, dib)

			AfxNewBitmap(dib);

	}
}


void CImageToolDoc::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CHistogramDlg dlg;
	dlg.SetImage(&m_Dib);
	dlg.DoModal();
}


void CImageToolDoc::OnHistogramStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppHistogramStrectch(img);
	CONVERT_IMAGE_TO_DIB(img, dib)

		AfxNewBitmap(dib);
}


void CImageToolDoc::OnHistogramEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppHistogramEQ(img);
	CONVERT_IMAGE_TO_DIB(img, dib)

		AfxNewBitmap(dib);
}


void CImageToolDoc::OnLogical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageLogicalDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
		CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;

		CONVERT_DIB_TO_BYTEIMAGE(pDoc1->m_Dib, img1);
		CONVERT_DIB_TO_BYTEIMAGE(pDoc2->m_Dib, img2);

		IppByteImage img3;

		bool ret = false;

		switch (dlg.m_nFunc)
		{
		case 0:ret = IppAdd(img1, img2, img3); break;
		case 1:ret = IppSub(img1, img2, img3); break;
		case 2:ret = IppAvg(img1, img2, img3); break;
		case 3:ret = IppDiff(img1, img2, img3); break;
		case 4:ret = IppAND(img1, img2, img3); break;
		case 5:ret = IppOR(img1, img2, img3); break;

		defaut:
			break;
		}

		if (ret)
		{
			CONVERT_IMAGE_TO_DIB(img3, dib);

			AfxNewBitmap(dib);

		}

	}
}


void CImageToolDoc::OnBitplain()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgPlane;

	for (int i = 0 ;i < 8; i++)
	{
		IppBitPlane(img, imgPlane, i);
		CONVERT_IMAGE_TO_DIB(imgPlane, dib)
			AfxNewBitmap(dib);
	}
}


void CImageToolDoc::OnFilterMean()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppFilterMean(imgSrc, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnFilterWhightedMean()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppFilterWeightedMean(imgSrc, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnFilterGaussian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGaussianDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
			IppByteImage imgDst;
		IppFilterGaussian(imgSrc, imgDst,dlg.m_fSigma);
		CONVERT_IMAGE_TO_DIB(imgDst, dib);

		AfxNewBitmap(dib);
	}
}


void CImageToolDoc::OnFilterLaplacian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppFilterLaplacian(imgSrc, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnFilterUnsharpMask()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppFilterUnsharpMask(imgSrc, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnFilterHighboost()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	float alpha = 1.2f;
	IppFilterHighboost(imgSrc, imgDst, alpha);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnNoise()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CNoiseDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
			IppByteImage imgDst;

		if (dlg.m_nNoiseType == 0)
			IppNoiseGaussian(imgSrc, imgDst, dlg.m_nAmount);
		else
			IppNoiseSaltPepper(imgSrc, imgDst, dlg.m_nAmount);

		CONVERT_IMAGE_TO_DIB(imgDst, dib);

		AfxNewBitmap(dib);
	}
}


void CImageToolDoc::OnMedian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppFilterMedian(imgSrc, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnDiff()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDiffDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
			IppFloatImage imgDst;
		IppFilterDiffusion(imgSrc, imgDst,dlg.m_fLambda,dlg.m_fK,dlg.m_nIter);
		CONVERT_IMAGE_TO_DIB(imgDst, dib);

		AfxNewBitmap(dib);
	}

}


void CImageToolDoc::OnTranslate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CTranslateDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
			IppByteImage imgDst;
		IppTransLate(imgSrc, imgDst, dlg.m_nX, dlg.m_nY);
		CONVERT_IMAGE_TO_DIB(imgDst, dib);

		AfxNewBitmap(dib);
	}
}


void CImageToolDoc::OnResize()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CResizeDlg dlg;
	dlg.m_nOldHeight = m_Dib.GetHeight();
	dlg.m_nOldWidth = m_Dib.GetWidth();
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
			IppByteImage imgDst;
		
		switch (dlg.m_nSel)
		{
		case 0:
			IppResizeNearest(imgSrc, imgDst, dlg.m_nNewWidth, dlg.m_nNewHeight);
			break;
		case 1:
			IppResizeBilinear(imgSrc, imgDst, dlg.m_nNewWidth, dlg.m_nNewHeight);
			break;
		case 2:
			IppResizeCubic(imgSrc, imgDst, dlg.m_nNewWidth, dlg.m_nNewHeight);
			break;

		}

		CONVERT_IMAGE_TO_DIB(imgDst, dib);

		AfxNewBitmap(dib);
	}

}


void CImageToolDoc::OnRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CRotateDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
			IppByteImage imgDst;
		IppRotate(imgSrc, imgDst, dlg.m_dbAngle);
		CONVERT_IMAGE_TO_DIB(imgDst, dib);

		AfxNewBitmap(dib);
	}
}


void CImageToolDoc::OnFlip0()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppFlip(imgSrc, imgDst,1);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnFlip1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppFlip(imgSrc, imgDst, 0);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnRoberts()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppEdgeRoberts(imgSrc, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnPrewitt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppEdgePrewitt(imgSrc, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);
	
	AfxNewBitmap(dib);
}


void CImageToolDoc::OnSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppEdgeSobel(imgSrc, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib);

	AfxNewBitmap(dib);
}
