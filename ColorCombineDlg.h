﻿#pragma once


// CColorCombineDlg 대화 상자

class CColorCombineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColorCombineDlg)

public:
	CColorCombineDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CColorCombineDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COLOR_COMBINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strColorSpace;
	CComboBox m_combo_img1;
	CComboBox m_combo_img2;
	CComboBox m_combo_img3;

	void* m_pDoc1;
	void* m_pDoc2;
	void* m_pDoc3;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};