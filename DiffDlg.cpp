// DiffDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "DiffDlg.h"
#include "afxdialogex.h"


// CDiffDlg 대화 상자

IMPLEMENT_DYNAMIC(CDiffDlg, CDialogEx)

CDiffDlg::CDiffDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DIFF, pParent)
	, m_fLambda(0.25f)
	, m_fK(4.f)
	, m_nIter(10)
{

}

CDiffDlg::~CDiffDlg()
{
}

void CDiffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LAMBDA, m_fLambda);
	DDX_Text(pDX, IDC_EDIT_K, m_fK);
	DDX_Text(pDX, IDC_EDIT_ITER, m_nIter);
}


BEGIN_MESSAGE_MAP(CDiffDlg, CDialogEx)
END_MESSAGE_MAP()


// CDiffDlg 메시지 처리기
