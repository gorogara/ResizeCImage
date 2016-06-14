
// ResizeCImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ResizeCImage.h"
#include "ResizeCImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CResizeCImageDlg dialog



CResizeCImageDlg::CResizeCImageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResizeCImageDlg::IDD, pParent),
	iNewWidth(100),
	iNewHeight(100)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CResizeCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SELECT, m_editPathSrc);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_EditWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_EditHeight);
}

BEGIN_MESSAGE_MAP(CResizeCImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_STN_CLICKED(IDC_STATIC_WIDTH, &CResizeCImageDlg::OnStnClickedStaticWidth)
ON_BN_CLICKED(IDC_BUTTON_SELECT, &CResizeCImageDlg::OnBnClickedButtonSelect)
ON_BN_CLICKED(IDC_BUTTON_RESIZE, &CResizeCImageDlg::OnBnClickedButtonResize)
END_MESSAGE_MAP()


// CResizeCImageDlg message handlers

BOOL CResizeCImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CString str;
	str.Format(_T("%d"), iNewWidth);
	m_EditWidth.SetWindowTextW(str);

	str.Format(_T("%d"), iNewHeight);
	m_EditHeight.SetWindowTextW(str);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CResizeCImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CResizeCImageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CResizeCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CResizeCImageDlg::OnStnClickedStaticWidth()
//{
//	// TODO: Add your control notification handler code here
//}


void CResizeCImageDlg::OnBnClickedButtonSelect()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, 0, 0, 0, _T(""));
	
	if (dlg.DoModal() == IDOK)
	{
		pathSrc = dlg.GetPathName();
		extSrc = dlg.GetFileExt();
		m_editPathSrc.SetWindowTextW(pathSrc);

		return;
	}
}


void CResizeCImageDlg::OnBnClickedButtonResize()
{
	// TODO: Add your control notification handler code here
	if (ResizeCImage(pathSrc, _T("resized_image.") + extSrc))
		AfxMessageBox(_T("Success!"));
	else
		AfxMessageBox(_T("Failed!"));
}


void CResizeCImageDlg::SetSize()
{
	CString str;
	m_EditWidth.GetWindowTextW(str);
	iNewWidth = _ttoi(str);

	m_EditHeight.GetWindowTextW(str);
	iNewHeight = _ttoi(str);
}


bool CResizeCImageDlg::ResizeCImage(CString _pathSrc, CString _pathDst)
{
	SetSize();

	CImage srcImage;
	HRESULT res = srcImage.Load(_pathSrc);

	if (SUCCEEDED(res))
	{
		// 새 이미지 생성
		CImage dstImage;
		dstImage.CreateEx(iNewWidth, iNewHeight, 32, BI_RGB, NULL, dstImage.createAlphaChannel);

		// StretchBlt 모드 설정
		SetStretchBltMode(dstImage.GetDC(), WHITEONBLACK);
		dstImage.ReleaseDC();

		// StretchBlt 실행
		srcImage.SetTransparentColor(RGB(255, 255, 255));
		srcImage.StretchBlt(dstImage.GetDC(), 0, 0, iNewWidth, iNewHeight, SRCCOPY);
		dstImage.ReleaseDC();

		dstImage.Save(_pathDst);

		return true;
	}

	return false;
}