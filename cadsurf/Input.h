#pragma once
#include "afxdialogex.h"


// Input 对话框

class Input : public CDialogEx
{
	DECLARE_DYNAMIC(Input)

public:
	int OnInitDialog();
	Input(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Input();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
	CString str;
	CEdit text_edit;
};
