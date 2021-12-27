#pragma once


// CCannyDlg 대화 상자

class CCannyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCannyDlg)

public:
	CCannyDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCannyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CANNY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_fSigma;
	float m_fLow;
	float m_fHigh;
	afx_msg void OnEnChangeEditGaussian();
	afx_msg void OnEnChangeEditLow();
	afx_msg void OnEnChangeEditHigh();
};
