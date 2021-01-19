
// CodeAnalyzerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CodeAnalyzer.h"
#include "CodeAnalyzerDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCodeAnalyzerDlg dialog



CCodeAnalyzerDlg::CCodeAnalyzerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CODEANALYZER_DIALOG, pParent)
	, m_CheckBoxH(TRUE)
	, m_CheckBoxTxt(TRUE)
	, m_CheckBoxCpp(TRUE)
	, m_FolderBrowser(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodeAnalyzerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_H, m_CheckBoxH);
	DDX_Check(pDX, IDC_CPP, m_CheckBoxCpp);
	DDX_Check(pDX, IDC_TXT, m_CheckBoxTxt);
	DDX_Text(pDX, IDC_FOLDERBROWSER, m_FolderBrowser);
	DDX_Control(pDX, IDC_LISTOFSTATISTICS, m_ListOfStatistics);
}

BEGIN_MESSAGE_MAP(CCodeAnalyzerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDANALYZE, &CCodeAnalyzerDlg::OnClickedIdanalyze)
	ON_BN_CLICKED(IDCLEAR, &CCodeAnalyzerDlg::OnClickedIdclear)
	ON_BN_CLICKED(IDEXIT, &CCodeAnalyzerDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CCodeAnalyzerDlg message handlers

BOOL CCodeAnalyzerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Insert headers for displayed list
	m_ListOfStatistics.InsertColumn(0, L"Lines", LVCFMT_LEFT, 80);
	m_ListOfStatistics.InsertColumn(1, L"Letters", LVCFMT_CENTER, 100);
	m_ListOfStatistics.InsertColumn(2, L"Words", LVCFMT_CENTER, 100);
	m_ListOfStatistics.InsertColumn(3, L"File`s path", LVCFMT_LEFT, 500);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCodeAnalyzerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCodeAnalyzerDlg::OnPaint()
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
HCURSOR CCodeAnalyzerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCodeAnalyzerDlg::OnClickedIdanalyze()
{
	UpdateData(TRUE);
	if (m_FolderBrowser.IsEmpty() == false) {

		// Setting by checkboxes which file extensions will
		// be used to set files map
		workingFolder.setTxtExtension(m_CheckBoxTxt);
		workingFolder.setCppExtension(m_CheckBoxCpp);
		workingFolder.setHExtension(m_CheckBoxH);

		// Define folder path by reading it from EditBrowseControl
		workingFolder.setFolderPathWstring(std::wstring(m_FolderBrowser));

		// Analyzing selected folder
		workingFolder.updateMapOfAnalyzedFiles();
		workingFolder.fillStatisticsForMapOfAnalyzedFiles();
		workingFolder.sumUpStatisticsForFolder(workingFolder.getFolderPathWstring());
		workingFolder.addFolderInfoToMap();
		
		// Necessary variables to add statistics to ListControl 
		int indexOfRow{};
		CString strToDisplayNumber{};

		// After each analysis displayed list will be refreshed,
		// but firstly it has to be clear
		m_ListOfStatistics.DeleteAllItems();
		
		// Adding properly converted files statistics to ListControl 
		for (auto [path,file] : workingFolder.getMapOfAnalyzedFiles()) {
			strToDisplayNumber.Format(_T("%d"), file.getNumberOfLines());
			indexOfRow = m_ListOfStatistics.InsertItem(0, strToDisplayNumber);
			strToDisplayNumber.Format(_T("%d"), file.getNumberOfLetters());
			m_ListOfStatistics.SetItemText(indexOfRow, 1, strToDisplayNumber);
			strToDisplayNumber.Format(_T("%d"), file.getNumberOfWords());
			m_ListOfStatistics.SetItemText(indexOfRow, 2, strToDisplayNumber);
			m_ListOfStatistics.SetItemText(indexOfRow, 3, file.getFilePathWstring().c_str());
		}
			
	
		UpdateData(FALSE);
	}
	
}


void CCodeAnalyzerDlg::OnClickedIdclear()
{
	// Clearing list with statistics
	m_ListOfStatistics.DeleteAllItems();
	workingFolder.clearMapOfAnalyzedFiles();
}


void CCodeAnalyzerDlg::OnBnClickedExit()
{
	// Exit app
	EndDialog(IDEXIT);
}
