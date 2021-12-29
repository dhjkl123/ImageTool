#pragma once


// CCornerDlg 대화 상자

class CCornerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCornerDlg)

public:
	CCornerDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCornerDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CORNER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nth;
	afx_msg void OnEnChangeEditTh();
};
