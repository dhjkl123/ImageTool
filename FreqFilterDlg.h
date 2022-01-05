#pragma once


// CFreqFilterDlg 대화 상자

class CFreqFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFreqFilterDlg)

public:
	CFreqFilterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFreqFilterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FREQUENCY_FILTERING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nFilterType;
	int m_nFilterShape;
	unsigned int m_nCutOff;
	CString m_strRange;
};
