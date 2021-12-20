// CNoiseDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "NoiseDlg.h"
#include "afxdialogex.h"


// CNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(CNoiseDlg, CDialogEx)

CNoiseDlg::CNoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NOISE, pParent)
	, m_nNoiseType(0)
	, m_nAmount(5)
{

}

CNoiseDlg::~CNoiseDlg()
{
}

void CNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_GAUSSIAN, m_nNoiseType);
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_nAmount);
}


BEGIN_MESSAGE_MAP(CNoiseDlg, CDialogEx)
END_MESSAGE_MAP()


// CNoiseDlg 메시지 처리기


BOOL CNoiseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_AMOUNT))->SetRange(0, 100);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
