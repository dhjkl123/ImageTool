#pragma once


// CImageLogicalDlg 대화 상자

class CImageLogicalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageLogicalDlg)

public:
	CImageLogicalDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CImageLogicalDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGICAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo_image1;
	CComboBox m_combo_image2;
	int m_nFunc;
	void* m_pDoc1;
	void* m_pDoc2;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
