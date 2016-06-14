
// ResizeCImageDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CResizeCImageDlg dialog
class CResizeCImageDlg : public CDialogEx
{
// Construction
public:
	CResizeCImageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RESIZECIMAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CString pathSrc;
	CString extSrc; // »Æ¿Â¿⁄
	int iNewWidth;
	int iNewHeight;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnStnClickedStaticWidth();
	afx_msg void OnBnClickedButtonSelect();
	CEdit m_editPathSrc;
	CEdit m_EditWidth;
	CEdit m_EditHeight;
	afx_msg void OnBnClickedButtonResize();

	bool ResizeCImage(CString _pathSrc, CString _pathDst, int _newWidth, int _newHeight);
	void SetSize();
};
