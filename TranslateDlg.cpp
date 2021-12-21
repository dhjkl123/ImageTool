// TranslateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "TranslateDlg.h"
#include "afxdialogex.h"


// CTranslateDlg 대화 상자

IMPLEMENT_DYNAMIC(CTranslateDlg, CDialogEx)

CTranslateDlg::CTranslateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TRANSLATE, pParent)
	, m_nX(0)
	, m_nY(0)
{

}

CTranslateDlg::~CTranslateDlg()
{
}

void CTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_Y, m_nY);
}


BEGIN_MESSAGE_MAP(CTranslateDlg, CDialogEx)
END_MESSAGE_MAP()


// CTranslateDlg 메시지 처리기
