// ColorCombineDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "ColorCombineDlg.h"
#include "afxdialogex.h"

#include "ImageToolDoc.h"

// CColorCombineDlg 대화 상자

IMPLEMENT_DYNAMIC(CColorCombineDlg, CDialogEx)

CColorCombineDlg::CColorCombineDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COLOR_COMBINE, pParent)
	, m_strColorSpace(_T(""))
	, m_pDoc1(NULL)
	, m_pDoc2(NULL)
	, m_pDoc3(NULL)
{

}

CColorCombineDlg::~CColorCombineDlg()
{
}

void CColorCombineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COLOR_SPACE, m_strColorSpace);
	DDX_Control(pDX, IDC_COMBO1, m_combo_img1);
	DDX_Control(pDX, IDC_COMBO2, m_combo_img2);
	DDX_Control(pDX, IDC_COMBO3, m_combo_img3);
}


BEGIN_MESSAGE_MAP(CColorCombineDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CColorCombineDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CColorCombineDlg 메시지 처리기


BOOL CColorCombineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	int nIdx = 0;
	CString strTitle;
	CImageToolApp* pApp = (CImageToolApp*)AfxGetApp();
	CImageToolDoc* pDoc = NULL;
	POSITION pos = pApp->m_ImageDocTemplate->GetFirstDocPosition();

	while (pos != NULL)
	{
		pDoc = (CImageToolDoc*)pApp->m_ImageDocTemplate->GetNextDoc(pos);
		if (pDoc->m_Dib.GetBitCount() != 8) continue;

		strTitle = pDoc->GetTitle();

		m_combo_img1.InsertString(nIdx, strTitle);
		m_combo_img2.InsertString(nIdx, strTitle);
		m_combo_img3.InsertString(nIdx, strTitle);

		m_combo_img1.SetItemDataPtr(nIdx, (void*)pDoc);
		m_combo_img2.SetItemDataPtr(nIdx, (void*)pDoc);
		m_combo_img3.SetItemDataPtr(nIdx, (void*)pDoc);

		nIdx++;

	}

	if (nIdx == 0)
	{
		AfxMessageBox(_T("그레이스케일 영상이 없습니다"));
	}

	m_combo_img1.SetCurSel(0);
	m_combo_img2.SetCurSel(0);
	m_combo_img3.SetCurSel(0);
	if (nIdx > 1)m_combo_img1.SetCurSel(1);
	if (nIdx > 2)m_combo_img1.SetCurSel(2);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CColorCombineDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pDoc1 = (CImageToolDoc*)m_combo_img1.GetItemDataPtr(m_combo_img1.GetCurSel());
	m_pDoc2 = (CImageToolDoc*)m_combo_img2.GetItemDataPtr(m_combo_img2.GetCurSel());
	m_pDoc3 = (CImageToolDoc*)m_combo_img3.GetItemDataPtr(m_combo_img3.GetCurSel());
	CDialogEx::OnOK();
}
