// BrightContrast.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "BrightContrast.h"
#include "afxdialogex.h"


// CBrightContrast 대화 상자

IMPLEMENT_DYNAMIC(CBrightContrast, CDialogEx)

CBrightContrast::CBrightContrast(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BRIGHT_CONTRAST, pParent)
	, m_nBright(0), m_nContrast(0)
{

}

CBrightContrast::~CBrightContrast()
{
}

void CBrightContrast::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_BRIGHT, m_slider_Bright);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_slider_Contrast);
	DDX_Text(pDX, IDC_EDIT_BRIGHT, m_nBright);
	DDV_MinMaxInt(pDX, m_nBright, -255, 255);
	DDX_Text(pDX, IDC_EDIT_CONSTRAST, m_nContrast);
	DDV_MinMaxInt(pDX, m_nContrast, -100, 100);
}


BEGIN_MESSAGE_MAP(CBrightContrast, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_BRIGHT, &CBrightContrast::OnEnChangeEditBright)
	ON_EN_CHANGE(IDC_EDIT_CONSTRAST, &CBrightContrast::OnEnChangeEditConstrast)
END_MESSAGE_MAP()


// CBrightContrast 메시지 처리기


BOOL CBrightContrast::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_slider_Bright.SetRange(-255, 255);
	m_slider_Bright.SetTicFreq(32);
	m_slider_Bright.SetPageSize(32);

	m_slider_Contrast.SetRange(-100, 100);
	m_slider_Contrast.SetTicFreq(20);
	m_slider_Contrast.SetPageSize(20);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBrightContrast::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_slider_Bright.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nBright = m_slider_Bright.GetPos();
		UpdateData(FALSE);
	}
	else if(m_slider_Contrast.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nContrast = m_slider_Contrast.GetPos();
		UpdateData(FALSE);

	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBrightContrast::OnEnChangeEditBright()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(1);
	m_slider_Bright.SetPos(m_nBright);
}


void CBrightContrast::OnEnChangeEditConstrast()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(1);
	m_slider_Contrast.SetPos(m_nContrast);

}
