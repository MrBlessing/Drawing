// SetProperty.cpp: 实现文件
//

#include "stdafx.h"
#include "Drawing.h"
#include "SetPropertyDlg.h"
#include "afxdialogex.h"


// SetProperty 对话框

IMPLEMENT_DYNAMIC(SetProperty, CDialogEx)

SetProperty::SetProperty(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

SetProperty::~SetProperty()
{
}

void SetProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, TypeCmb);
	DDX_Control(pDX, IDC_LIST1, PenType);
	DDX_Control(pDX, IDC_LIST2, BrushType);
}



BEGIN_MESSAGE_MAP(SetProperty, CDialogEx)
END_MESSAGE_MAP()


// SetProperty 消息处理程序
