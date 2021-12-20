#pragma once


// CDiffDlg 대화 상자

class CDiffDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDiffDlg)

public:
	CDiffDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDiffDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DIFF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_fLambda;
	float m_fK;
	int m_nIter;
};
