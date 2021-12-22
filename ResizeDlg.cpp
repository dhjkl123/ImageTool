// ResizeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "ResizeDlg.h"
#include "afxdialogex.h"


// CResizeDlg 대화 상자

IMPLEMENT_DYNAMIC(CResizeDlg, CDialogEx)

CResizeDlg::CResizeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDC_DIALOG_RESIZE, pParent)
	, m_nOldWidth(0)
	, m_nOldHeight(0)
	, m_nNewWidth(0)
	, m_nNewHeight(0)
	, m_bCheck(FALSE)
	, m_nSel(0)
{

}

CResizeDlg::~CResizeDlg()
{
}

void CResizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_OLD_W, m_nOldWidth);
	DDX_Text(pDX, IDC_STATIC_OLD_H, m_nOldHeight);
	DDX_Text(pDX, IDC_EDIT_W, m_nNewWidth);
	DDX_Text(pDX, IDC_EDIT_H, m_nNewHeight);
	DDX_Check(pDX, IDC_CHECK, m_bCheck);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nSel);
}


BEGIN_MESSAGE_MAP(CResizeDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_W, &CResizeDlg::OnEnChangeEditW)
	ON_EN_CHANGE(IDC_EDIT_H, &CResizeDlg::OnEnChangeEditH)
	ON_BN_CLICKED(IDC_CHECK, &CResizeDlg::OnBnClickedCheck)
END_MESSAGE_MAP()


// CResizeDlg 메시지 처리기


BOOL CResizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_nNewHeight = m_nOldHeight;
	m_nNewWidth = m_nOldWidth;

	UpdateData(0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CResizeDlg::OnEnChangeEditW()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (GetDlgItem(IDC_COMBO1) == NULL)
		return;

	if (m_bCheck)
	{
		UpdateData(1);
		m_nNewHeight = m_nNewWidth * m_nOldHeight / m_nOldWidth;
		UpdateData(0);
	}

}


void CResizeDlg::OnEnChangeEditH()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (GetDlgItem(IDC_COMBO1) == NULL)
		return;

	if (m_bCheck)
	{
		UpdateData(1);
		m_nNewWidth = m_nNewHeight * m_nOldWidth / m_nOldHeight;
		UpdateData(0);
	}
}


void CResizeDlg::OnBnClickedCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(1);
	if (m_bCheck)
	{
		m_nNewHeight = m_nNewWidth * m_nOldHeight / m_nOldWidth;
	}
	UpdateData(0);

}
