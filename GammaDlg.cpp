// GammaDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "GammaDlg.h"
#include "afxdialogex.h"


// CGammaDlg 대화 상자

IMPLEMENT_DYNAMIC(CGammaDlg, CDialogEx)

CGammaDlg::CGammaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GAMMA, pParent)
	, m_fGamma(2.20f)
{

}

CGammaDlg::~CGammaDlg()
{
}

void CGammaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_GAMMA, m_slider_gamma);
	DDX_Text(pDX, IDC_EDIT_GAMMA, m_fGamma);
}


BEGIN_MESSAGE_MAP(CGammaDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CGammaDlg 메시지 처리기


BOOL CGammaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_slider_gamma.SetRange(10, 250);
	m_slider_gamma.SetTicFreq(20);
	m_slider_gamma.SetPageSize(20);
	m_slider_gamma.SetPos(static_cast<int>(m_fGamma * 50));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CGammaDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_slider_gamma.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_slider_gamma.GetPos();
		m_fGamma = (pos / 50.f);
		UpdateData(0);
	}


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
