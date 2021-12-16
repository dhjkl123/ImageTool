// ImageLogicalDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "ImageLogicalDlg.h"
#include "afxdialogex.h"

#include "ImageToolDoc.h"

// CImageLogicalDlg 대화 상자

IMPLEMENT_DYNAMIC(CImageLogicalDlg, CDialogEx)

CImageLogicalDlg::CImageLogicalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGICAL, pParent)
	, m_nFunc(0), m_pDoc1(NULL), m_pDoc2(NULL)
{

}

CImageLogicalDlg::~CImageLogicalDlg()
{
}

void CImageLogicalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IMAGE1, m_combo_image1);
	DDX_Control(pDX, IDC_COMBO_IMAGE2, m_combo_image2);
	DDX_Radio(pDX, IDC_RADIO_ADD, m_nFunc);
}


BEGIN_MESSAGE_MAP(CImageLogicalDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CImageLogicalDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CImageLogicalDlg 메시지 처리기


BOOL CImageLogicalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	int nIdx = 0;
	CString strTitle;
	
	CImageToolApp* pApp = (CImageToolApp*)AfxGetApp();
	POSITION pos = pApp->m_ImageDocTemplate->GetFirstDocPosition();

	while (pos != NULL)
	{
		CImageToolDoc* pDoc = (CImageToolDoc*)pApp->m_ImageDocTemplate->GetNextDoc(pos);
		if (pDoc->m_Dib.GetBitCount() != 8)
			continue;

		strTitle = pDoc->GetTitle();

		m_combo_image1.InsertString(nIdx, strTitle);
		m_combo_image2.InsertString(nIdx, strTitle);

		m_combo_image1.SetItemDataPtr(nIdx, (void*)pDoc);
		m_combo_image2.SetItemDataPtr(nIdx, (void*)pDoc);

		nIdx++;
	}
	
	m_combo_image1.SetCurSel(0);
	m_combo_image2.SetCurSel(0);

	if (nIdx > 1)m_combo_image2.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CImageLogicalDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pDoc1 = (CImageToolDoc*)m_combo_image1.GetItemDataPtr(m_combo_image1.GetCurSel());
	m_pDoc2 = (CImageToolDoc*)m_combo_image2.GetItemDataPtr(m_combo_image2.GetCurSel());

	CDialogEx::OnOK();
}
