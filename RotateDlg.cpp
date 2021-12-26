// RotateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "RotateDlg.h"
#include "afxdialogex.h"


// CRotateDlg 대화 상자

IMPLEMENT_DYNAMIC(CRotateDlg, CDialogEx)

CRotateDlg::CRotateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ROTATE, pParent)
	, m_dbAngle(0)
{

}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dbAngle);
	DDV_MinMaxDouble(pDX, m_dbAngle, 0.0, 360.0);
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CRotateDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CRotateDlg 메시지 처리기


void CRotateDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(1);

}
