#pragma once


// CHistogramDlg 대화 상자

class CHistogramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDlg)

public:
	CHistogramDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHistogramDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HISTOGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	int m_nHistogram[256];



	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void SetImage(IppDib* pDib);
};
