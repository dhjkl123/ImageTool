// CannyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "CannyDlg.h"
#include "afxdialogex.h"


// CCannyDlg 대화 상자

IMPLEMENT_DYNAMIC(CCannyDlg, CDialogEx)

CCannyDlg::CCannyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CANNY, pParent)
	, m_fSigma(0)
	, m_fLow(0)
	, m_fHigh(0)
{

}

CCannyDlg::~CCannyDlg()
{
}

void CCannyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GAUSSIAN, m_fSigma);
	DDX_Text(pDX, IDC_EDIT_LOW, m_fLow);
	DDX_Text(pDX, IDC_EDIT_HIGH, m_fHigh);
}


BEGIN_MESSAGE_MAP(CCannyDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_GAUSSIAN, &CCannyDlg::OnEnChangeEditGaussian)
	ON_EN_CHANGE(IDC_EDIT_LOW, &CCannyDlg::OnEnChangeEditLow)
	ON_EN_CHANGE(IDC_EDIT_HIGH, &CCannyDlg::OnEnChangeEditHigh)
END_MESSAGE_MAP()


// CCannyDlg 메시지 처리기


void CCannyDlg::OnEnChangeEditGaussian()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(1);
}


void CCannyDlg::OnEnChangeEditLow()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(1);
}


void CCannyDlg::OnEnChangeEditHigh()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(1);
}
