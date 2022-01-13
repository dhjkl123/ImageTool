// BinaryDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "BinaryDlg.h"
#include "afxdialogex.h"

#include "IppImage.h"
#include "IppConvert.h"
#include "IppGeometry.h"
#include "IppSegment.h"
// CBinaryDlg 대화 상자

IMPLEMENT_DYNAMIC(CBinaryDlg, CDialogEx)

CBinaryDlg::CBinaryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BIN, pParent)
	, m_nTh(0)
{

}

CBinaryDlg::~CBinaryDlg()
{
}

void CBinaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_TH, m_slide_th);
	DDX_Text(pDX, IDC_EDIT_TH, m_nTh);
}


BEGIN_MESSAGE_MAP(CBinaryDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_TH, &CBinaryDlg::OnEnChangeEditTh)
END_MESSAGE_MAP()

void CBinaryDlg::SetImage(IppDib& dib)
{
	m_DibSrc = dib;

	IppByteImage imgSrc;
	IppDibToImage(m_DibSrc, imgSrc);
	m_nTh = IppBinarizationIterative(imgSrc);

}

void CBinaryDlg::MakePreviewImage()
{
	IppByteImage imgSrc, imgDst;
	IppDibToImage(m_DibSrc, imgSrc);
	IppBinarization(imgSrc, imgDst, m_nTh);
	IppImageToDib(imgDst, m_DibRes);
}

// CBinaryDlg 메시지 처리기


BOOL CBinaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_slide_th.SetRange(0, 255);
	m_slide_th.SetTicFreq(32);
	m_slide_th.SetPageSize(32);
	m_slide_th.SetPos(m_nTh);

	CRect rc;
	CWnd* pImageWnd = GetDlgItem(IDC_PREVIEW);
	pImageWnd->GetClientRect(rc);

	IppByteImage imgSrc, imgDst;
	IppDibToImage(m_DibSrc, imgSrc);
	IppResizeNearest(imgSrc, imgDst, rc.Width(), rc.Height());
	IppImageToDib(imgDst, m_DibSrc);

	MakePreviewImage();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBinaryDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CPaintDC dcPreview(GetDlgItem(IDC_PREVIEW));
	m_DibRes.Draw(dcPreview.m_hDC, 0, 0);

}


void CBinaryDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_slide_th.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_slide_th.GetPos();
		m_nTh = nPos;
		UpdateData(0);
		MakePreviewImage();
		Invalidate(0);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBinaryDlg::OnEnChangeEditTh()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(1);
	m_slide_th.SetPos(m_nTh);

	MakePreviewImage();
	Invalidate(0);
}
