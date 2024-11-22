// Input.cpp: 实现文件
//

#include "stdafx.h"
#include "CadSurf.h"
#include "afxdialogex.h"
#include "Input.h"


// Input 对话框

IMPLEMENT_DYNAMIC(Input, CDialogEx)

int Input::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	text_edit.SetWindowTextA(str);
	return 0;
}

Input::Input(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Input::~Input()
{
}

void Input::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, text_edit);
}


BEGIN_MESSAGE_MAP(Input, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &Input::OnEnChangeEdit2)
END_MESSAGE_MAP()


// Input 消息处理程序
void Input::OnEnChangeEdit2()
{
	text_edit.GetWindowTextA(str);

	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
