#pragma once


// CNoiseDlg 대화 상자

class CNoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoiseDlg)

public:
	CNoiseDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNoiseDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOISE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nNoiseType;
	int m_nAmount;
	virtual BOOL OnInitDialog();
};
