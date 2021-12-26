﻿#pragma once


// CRotateDlg 대화 상자

class CRotateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRotateDlg)

public:
	CRotateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRotateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ROTATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_dbAngle;
	afx_msg void OnEnChangeEdit1();
};
