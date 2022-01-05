// FreqFilterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "FreqFilterDlg.h"
#include "afxdialogex.h"


// CFreqFilterDlg 대화 상자

IMPLEMENT_DYNAMIC(CFreqFilterDlg, CDialogEx)

CFreqFilterDlg::CFreqFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FREQUENCY_FILTERING, pParent)
	, m_nFilterType(0)
	, m_nFilterShape(0)
	, m_nCutOff(32)
	, m_strRange(_T(""))
{

}

CFreqFilterDlg::~CFreqFilterDlg()
{
}

void CFreqFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nFilterType);
	DDX_CBIndex(pDX, IDC_COMBO_SHAPE, m_nFilterShape);
	DDX_Text(pDX, IDC_EDIT1, m_nCutOff);
	DDX_Text(pDX, IDC_STATIC_RANGE, m_strRange);
}


BEGIN_MESSAGE_MAP(CFreqFilterDlg, CDialogEx)
END_MESSAGE_MAP()


// CFreqFilterDlg 메시지 처리기
