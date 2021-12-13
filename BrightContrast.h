#pragma once


// CBrightContrast 대화 상자

class CBrightContrast : public CDialogEx
{
	DECLARE_DYNAMIC(CBrightContrast)

public:
	CBrightContrast(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBrightContrast();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BRIGHT_CONTRAST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nBright;
	int m_nContrast;
	CSliderCtrl m_slider_Bright;
	CSliderCtrl m_slider_Contrast;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditBright();
	afx_msg void OnEnChangeEditConstrast();

};
