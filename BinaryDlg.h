#pragma once
#include "afxcmn.h"

#include "IppDib.h"

// CBinaryDlg 대화 상자

class CBinaryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBinaryDlg)

public:
	CBinaryDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBinaryDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slide_th;
	int m_nTh;

	IppDib m_DibSrc;
	IppDib m_DibRes;
	void SetImage(IppDib& dib);
	void MakePreviewImage();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditTh();
};
