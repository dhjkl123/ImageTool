
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
#include "IppFourier.h"
#include "IppColor.h"

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
#include "CannyDlg.h"
#include "CornerDlg.h"
#include "FreqFilterDlg.h"
#include "ColorCombineDlg.h"
#include "IppSegment.h"
#include "BinaryDlg.h"


#pragma endregion

#include "MainFrm.h"

#include <algorithm>
#include <functional>
#include <vector>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

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

#define SHOW_SOECTRUM_PHASE_IMAGE

#define CONVERT_DIB_TO_RGBIMAGE(m_Dib,img)\
IppRGBBYTEImage img;\
IppDibToImage(m_Dib,img);
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
	ON_COMMAND(ID_CANNY, &CImageToolDoc::OnCanny)
	ON_COMMAND(ID_HOUGH, &CImageToolDoc::OnHough)
	ON_COMMAND(ID_CORNER, &CImageToolDoc::OnCorner)
	ON_COMMAND(ID_DFT, &CImageToolDoc::OnDft)
	ON_COMMAND(ID_DRTRC, &CImageToolDoc::OnDrtrc)
	ON_COMMAND(ID_FOURIERFFT, &CImageToolDoc::OnFourierfft)
	ON_COMMAND(ID_FRQ_FILTER, &CImageToolDoc::OnFrqFilter)
	ON_COMMAND(ID_RGB2GRAY, &CImageToolDoc::OnRgb2gray)
	ON_COMMAND(ID_RGB, &CImageToolDoc::OnRgb)
	ON_UPDATE_COMMAND_UI(ID_RGB, &CImageToolDoc::OnUpdateRgb)
	ON_COMMAND(ID_HSI, &CImageToolDoc::OnHsi)
	ON_UPDATE_COMMAND_UI(ID_HSI, &CImageToolDoc::OnUpdateHsi)
	ON_COMMAND(ID_YUV, &CImageToolDoc::OnYuv)
	ON_UPDATE_COMMAND_UI(ID_YUV, &CImageToolDoc::OnUpdateYuv)
	ON_COMMAND(ID_RGB_COMBINE, &CImageToolDoc::OnRgbCombine)
	ON_COMMAND(ID_HSI_COMBINE, &CImageToolDoc::OnHsiCombine)
	ON_COMMAND(ID_YUV_COMBINE, &CImageToolDoc::OnYuvCombine)
	ON_COMMAND(ID_EDGE_COLOR, &CImageToolDoc::OnEdgeColor)
	ON_UPDATE_COMMAND_UI(ID_EDGE_COLOR, &CImageToolDoc::OnUpdateEdgeColor)
	ON_COMMAND(ID_BINARY, &CImageToolDoc::OnBinary)
	ON_COMMAND(ID_LABEL, &CImageToolDoc::OnLabel)
	ON_COMMAND(ID_CONTUOR, &CImageToolDoc::OnContuor)
	ON_COMMAND(ID_EROSION, &CImageToolDoc::OnErosion)
	ON_COMMAND(ID_DILATION, &CImageToolDoc::OnDilation)
	ON_COMMAND(ID_OPENING, &CImageToolDoc::OnOpening)
	ON_COMMAND(ID_CLOSING, &CImageToolDoc::OnClosing)
	ON_COMMAND(ID_GRAY_EROSION, &CImageToolDoc::OnGrayErosion)
	ON_COMMAND(ID_GRAY_DILATION, &CImageToolDoc::OnGrayDilation)
	ON_COMMAND(ID_GRAY_OPENING, &CImageToolDoc::OnGrayOpening)
	ON_COMMAND(ID_GRAY_CLOSING, &CImageToolDoc::OnGrayClosing)
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
	if (m_Dib.GetBitCount() == 8)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
			IppInverse(img);

		CONVERT_IMAGE_TO_DIB(img, dib)

			AfxNewBitmap(dib);
	}
	else if (m_Dib.GetBitCount() == 24)
	{
		CONVERT_DIB_TO_RGBIMAGE(m_Dib, img)
			IppInverse(img);

		CONVERT_IMAGE_TO_DIB(img, dib)

			AfxNewBitmap(dib);
	}
}


void CImageToolDoc::OnUpdateImageInverse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(m_Dib.GetBitCount() == 8 || m_Dib.GetBitCount() == 24);
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
	if (m_Dib.GetBitCount() == 8)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
			IppHistogramEQ(img);
		CONVERT_IMAGE_TO_DIB(img, dib)

			AfxNewBitmap(dib);
	}
	else if (m_Dib.GetBitCount() == 24)
	{
		CONVERT_DIB_TO_RGBIMAGE(m_Dib, img);
		IppByteImage imgY, imgU, imgV;
		IppColorSplitYUV(img, imgY, imgU, imgV);
		IppHistogramEQ(imgY);
		IppRGBBYTEImage imgRes;
		IppColorCombineYUV(imgY, imgU, imgV, imgRes);
		CONVERT_IMAGE_TO_DIB(imgRes, dib)

			AfxNewBitmap(dib);
	}
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
			IppFloatImage imgDst;
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


void CImageToolDoc::OnCanny()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCannyDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
			IppByteImage imgDst;
		IppEdgeCanny(imgSrc, imgDst, dlg.m_fSigma, dlg.m_fLow, dlg.m_fHigh);
		CONVERT_IMAGE_TO_DIB(imgDst, dib);

		AfxNewBitmap(dib);
	}
}


void CImageToolDoc::OnHough()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppEdgeCanny(imgSrc, imgDst, 1.4f, 30.f, 60.f);

	std::vector<IppLineParam> lines;
	IppHoughLine(imgDst, lines);

	if (lines.size() == 0)
	{
		AfxMessageBox(_T("No Lines on Image!"));
		return;
	}

	std::sort(lines.begin(), lines.end());

	int cnt = __min(10, lines.size());
	for (int i = 0; i < cnt; i++)
		IppDrawLine(imgSrc, lines[i], 255);

	CONVERT_IMAGE_TO_DIB(imgSrc, dib);

	AfxNewBitmap(dib);
	
}


void CImageToolDoc::OnCorner()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCornerDlg dlg;
	if (dlg.DoModal() == IDOK)
	{

		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
			std::vector<IppPoint> corners;
		IppHarrisCorner(imgSrc, corners, dlg.m_nth);

		BYTE** ptr = imgSrc.GetPixels2D();

		int x, y;
		for (IppPoint cp : corners)
		{
			x = cp.x;
			y = cp.y;

			ptr[y - 1][x - 1] = ptr[y - 1][x] = ptr[y - 1][x + 1] = 0;
			ptr[y][x - 1] = ptr[y][x] = ptr[y][x + 1] = 0;
			ptr[y + 1][x - 1] = ptr[y + 1][x] = ptr[y + 1][x + 1] = 0;

		}

		CONVERT_IMAGE_TO_DIB(imgSrc, dib);

		AfxNewBitmap(dib);

	}
}


void CImageToolDoc::OnDft()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)

		IppFourier fourier;
	fourier.SetImage(imgSrc);

	DWORD t1 = timeGetTime();
	fourier.DFT(1);

#ifdef SHOW_SOECTRUM_PHASE_IMAGE

	IppByteImage imgSpec;
	fourier.GetSpectrumImage(imgSpec);

	CONVERT_IMAGE_TO_DIB(imgSpec, dibSpec);
	AfxNewBitmap(dibSpec);

	IppByteImage imgPhase;
	fourier.GetPhaseImage(imgPhase);

	CONVERT_IMAGE_TO_DIB(imgPhase, dibPhase);
	AfxNewBitmap(dibPhase);

#endif
	
	fourier.DFT(-1);
	DWORD t2 = timeGetTime();

	IppByteImage img2;
	fourier.GetImage(img2);

	CONVERT_IMAGE_TO_DIB(img2, dib);
	AfxNewBitmap(dib);

}


void CImageToolDoc::OnDrtrc()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)

		IppFourier fourier;
	fourier.SetImage(imgSrc);

	DWORD t1 = timeGetTime();
	fourier.DFTRC(1);

#ifdef SHOW_SOECTRUM_PHASE_IMAGE

	IppByteImage imgSpec;
	fourier.GetSpectrumImage(imgSpec);

	CONVERT_IMAGE_TO_DIB(imgSpec, dibSpec);
	AfxNewBitmap(dibSpec);

	IppByteImage imgPhase;
	fourier.GetPhaseImage(imgPhase);

	CONVERT_IMAGE_TO_DIB(imgPhase, dibPhase);
	AfxNewBitmap(dibPhase);

#endif

	fourier.DFTRC(-1);
	DWORD t2 = timeGetTime();

	IppByteImage img2;
	fourier.GetImage(img2);

	CONVERT_IMAGE_TO_DIB(img2, dib);
	AfxNewBitmap(dib);
}


void CImageToolDoc::OnFourierfft()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	if (!IsPowerof2(m_Dib.GetWidth()) || !IsPowerof2(m_Dib.GetHeight()))
		return;

	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)

		IppFourier fourier;
	fourier.SetImage(imgSrc);

	DWORD t1 = timeGetTime();
	fourier.FFT(1);

#ifdef SHOW_SOECTRUM_PHASE_IMAGE

	IppByteImage imgSpec;
	fourier.GetSpectrumImage(imgSpec);

	CONVERT_IMAGE_TO_DIB(imgSpec, dibSpec);
	AfxNewBitmap(dibSpec);

	IppByteImage imgPhase;
	fourier.GetPhaseImage(imgPhase);

	CONVERT_IMAGE_TO_DIB(imgPhase, dibPhase);
	AfxNewBitmap(dibPhase);

#endif

	fourier.FFT(-1);
	DWORD t2 = timeGetTime();

	IppByteImage img2;
	fourier.GetImage(img2);

	CONVERT_IMAGE_TO_DIB(img2, dib);
	AfxNewBitmap(dib);
}



void CImageToolDoc::OnFrqFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFreqFilterDlg dlg;
	dlg.m_strRange.Format(_T("(0 ~ %d)"), __min(m_Dib.GetWidth() / 2, m_Dib.GetHeight() / 2));
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib,img)
		IppFourier fourier;
		fourier.SetImage(img);
		fourier.FFT(1);

		if (dlg.m_nFilterType == 0)
		{
			if (dlg.m_nFilterShape == 0)
				fourier.LowPassIdeal(dlg.m_nCutOff);
			else
				fourier.LowPassGaussian(dlg.m_nCutOff);
		}
		else
		{
			if (dlg.m_nFilterShape == 0)
				fourier.HighPassIdeal(dlg.m_nCutOff);
			else
				fourier.HighPassGaussian(dlg.m_nCutOff);
		}

		fourier.FFT(-1);

		IppByteImage img2;
		fourier.GetImage(img2);
		CONVERT_IMAGE_TO_DIB(img2, dib);

		AfxNewBitmap(dib);

	}
}


void CImageToolDoc::OnRgb2gray()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_RGBIMAGE(m_Dib, imgColor)
		IppByteImage imgGray;
	imgGray.Convert(imgColor);
	CONVERT_IMAGE_TO_DIB(imgGray,dib)

		AfxNewBitmap(dib);

}


void CImageToolDoc::OnRgb()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_RGBIMAGE(m_Dib, imgColor)
		IppByteImage imgR, imgG, imgB;
	IppColorSplitRGB(imgColor, imgR, imgG, imgB);
	CONVERT_IMAGE_TO_DIB(imgR, dibR)
		CONVERT_IMAGE_TO_DIB(imgG, dibG)
		CONVERT_IMAGE_TO_DIB(imgB, dibB)

		AfxNewBitmap(dibR);
	AfxNewBitmap(dibG);
	AfxNewBitmap(dibB);


}


void CImageToolDoc::OnUpdateRgb(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolDoc::OnHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_RGBIMAGE(m_Dib, imgColor)
		IppByteImage imgR, imgG, imgB;
	IppColorSplitHSI(imgColor, imgR, imgG, imgB);
	CONVERT_IMAGE_TO_DIB(imgR, dibR)
		CONVERT_IMAGE_TO_DIB(imgG, dibG)
		CONVERT_IMAGE_TO_DIB(imgB, dibB)

		AfxNewBitmap(dibR);
	AfxNewBitmap(dibG);
	AfxNewBitmap(dibB);
}


void CImageToolDoc::OnUpdateHsi(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolDoc::OnYuv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_RGBIMAGE(m_Dib, imgColor)
		IppByteImage imgR, imgG, imgB;
	IppColorSplitYUV(imgColor, imgR, imgG, imgB);
	CONVERT_IMAGE_TO_DIB(imgR, dibR)
		CONVERT_IMAGE_TO_DIB(imgG, dibG)
		CONVERT_IMAGE_TO_DIB(imgB, dibB)

		AfxNewBitmap(dibR);
	AfxNewBitmap(dibG);
	AfxNewBitmap(dibB);
}


void CImageToolDoc::OnUpdateYuv(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolDoc::OnRgbCombine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorCombineDlg dlg;
	dlg.m_strColorSpace = _T("RGB 합치기");
	if (dlg.DoModal() == IDOK)
	{
		CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
		CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;
		CImageToolDoc* pDoc3 = (CImageToolDoc*)dlg.m_pDoc3;

		CONVERT_DIB_TO_BYTEIMAGE(pDoc1->m_Dib, imgR);
		CONVERT_DIB_TO_BYTEIMAGE(pDoc2->m_Dib, imgG);
		CONVERT_DIB_TO_BYTEIMAGE(pDoc3->m_Dib, imgB);

		IppRGBBYTEImage imgColor;
		if (IppColorCombineRGB(imgR, imgG, imgB, imgColor) == false)
		{
			AfxMessageBox(_T("영상의 크기가 다릅니다!"));
		}

		CONVERT_IMAGE_TO_DIB(imgColor, dib)

			AfxNewBitmap(dib);

	}
}


void CImageToolDoc::OnHsiCombine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorCombineDlg dlg;
	dlg.m_strColorSpace = _T("HSI 합치기");
	if (dlg.DoModal() == IDOK)
	{
		CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
		CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;
		CImageToolDoc* pDoc3 = (CImageToolDoc*)dlg.m_pDoc3;

		CONVERT_DIB_TO_BYTEIMAGE(pDoc1->m_Dib, imgH);
		CONVERT_DIB_TO_BYTEIMAGE(pDoc2->m_Dib, imgS);
		CONVERT_DIB_TO_BYTEIMAGE(pDoc3->m_Dib, imgI);

		IppRGBBYTEImage imgColor;
		if (IppColorCombineHSI(imgH, imgS, imgI, imgColor) == false)
		{
			AfxMessageBox(_T("영상의 크기가 다릅니다!"));
		}

		CONVERT_IMAGE_TO_DIB(imgColor, dib)

			AfxNewBitmap(dib);

	}
}


void CImageToolDoc::OnYuvCombine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorCombineDlg dlg;
	dlg.m_strColorSpace = _T("YUV 합치기");
	if (dlg.DoModal() == IDOK)
	{
		CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
		CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;
		CImageToolDoc* pDoc3 = (CImageToolDoc*)dlg.m_pDoc3;

		CONVERT_DIB_TO_BYTEIMAGE(pDoc1->m_Dib, imgY);
		CONVERT_DIB_TO_BYTEIMAGE(pDoc2->m_Dib, imgU);
		CONVERT_DIB_TO_BYTEIMAGE(pDoc3->m_Dib, imgV);

		IppRGBBYTEImage imgColor;
		if (IppColorCombineYUV(imgY, imgU, imgV, imgColor) == false)
		{
			AfxMessageBox(_T("영상의 크기가 다릅니다!"));
		}

		CONVERT_IMAGE_TO_DIB(imgColor, dib)

			AfxNewBitmap(dib);

	}
}


void CImageToolDoc::OnEdgeColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_RGBIMAGE(m_Dib, img)
		IppByteImage imgEdge;
	IppColorEdge(img, imgEdge);
	CONVERT_IMAGE_TO_DIB(imgEdge, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnUpdateEdgeColor(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(m_Dib.GetBitCount() == 24);

}


void CImageToolDoc::OnBinary()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CBinaryDlg dlg;
	dlg.SetImage(m_Dib);
	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
			IppByteImage imgRes;
		IppBinarization(img,imgRes, dlg.m_nTh);
		CONVERT_IMAGE_TO_DIB(imgRes, dib)

			AfxNewBitmap(dib);
	}
}


void CImageToolDoc::OnLabel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppIntImage imgLabel;
	std::vector<IppLabelInfo> labels;
	int label_cnt = IppLabeling(img, imgLabel, labels);

	/*
	BYTE** ptr = img.GetPixels2D();
	for (IppLabelInfo& info : labels)
	{
		for (int j = info.miny; j <= info.maxy; j++)
			ptr[j][info.minx] = ptr[j][info.maxx] = 128;

		for (int i = info.minx; i <= info.maxx; i++)
			ptr[info.miny][i] = ptr[info.maxy][i] = 128;
	}
	*/

	for (IppLabelInfo& info : labels)
	{
		IppByteImage imgObj(info.maxx - info.minx + 1, info.maxy - info.miny + 1);
		BYTE** pObj = imgObj.GetPixels2D();
		for (IppPoint& pt : info.pixels)
			pObj[pt.y - info.miny][pt.x - info.minx] = 255;

		CONVERT_IMAGE_TO_DIB(imgObj, dib)
			AfxNewBitmap(dib);
	}



}


void CImageToolDoc::OnContuor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppIntImage imgLabel;
	std::vector<IppLabelInfo> labels;
	int label_cnt = IppLabeling(img, imgLabel, labels);

	IppByteImage imgContour(img.GetWidth(), img.GetHeight());
	BYTE** ptr = imgContour.GetPixels2D();
	for (IppLabelInfo& info : labels)
	{
		std::vector<IppPoint> cp;
		IppContourTracing(img, info.pixels[0].x, info.pixels[0].y, cp);

		for (IppPoint& pt : cp)
			ptr[pt.y][pt.x] = 255;
	}

	CONVERT_IMAGE_TO_DIB(imgContour, dib)

		AfxNewBitmap(dib);
}

void CImageToolDoc::OnErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgDst;
	IppMorphologyErosion(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);
}

void CImageToolDoc::OnDilation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgDst;
	IppMorphologyDilation(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);
}

void CImageToolDoc::OnOpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgDst;
	IppMorphologyOpening(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);
}

void CImageToolDoc::OnClosing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgDst;
	IppMorphologyClosing(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);
}

void CImageToolDoc::OnGrayErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgDst;
	IppMorphologyGrayErosion(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);
}

void CImageToolDoc::OnGrayDilation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgDst;
	IppMorphologyGrayDilation(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);
}

void CImageToolDoc::OnGrayOpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgDst;
	IppMorphologyGrayOpening(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);
}

void CImageToolDoc::OnGrayClosing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgDst;
	IppMorphologyGrayClosing(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);
}