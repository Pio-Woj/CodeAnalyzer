
// CodeAnalyzerDlg.h : header file
//

#pragma once

#include "AnalyzedFolder.h"
// CCodeAnalyzerDlg dialog
class CCodeAnalyzerDlg : public CDialogEx
{
// Construction
public:
	CCodeAnalyzerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODEANALYZER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


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
	afx_msg void OnClickedIdanalyze();
	BOOL m_CheckBoxH;
	BOOL m_CheckBoxTxt;
	BOOL m_CheckBoxCpp;
	CString m_FolderBrowser;
	CListCtrl m_ListOfStatistics;
	afx_msg void OnClickedIdclear();
	AnalyzedFolder workingFolder{};
	afx_msg void OnBnClickedExit();
};
