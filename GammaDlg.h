#pragma once


// CGammaDlg 대화 상자

class CGammaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGammaDlg)

public:
	CGammaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGammaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GAMMA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slider_gamma;
	float m_fGamma;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
