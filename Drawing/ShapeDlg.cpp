// ShapeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Drawing.h"
#include "ShapeDlg.h"
#include "afxdialogex.h"

// ShapeDlg 对话框

IMPLEMENT_DYNAMIC(ShapeDlg, CDialogEx)

ShapeDlg::ShapeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, OrgX(0)
	, OrgY(0)
	, Width(0)
	, Height(0)
	, Text(_T(""))
	, PenWidth(0)
{
	//初始化一些变量
	m_BrushType = -1;//默认无类型
	m_ShapeType = SQUARE;//默认选择Square
	m_PenType = 0;//默认选择第一种画笔
	//初始化颜色变量
	m_PenColor = RGB(0, 0, 0);
	m_BrushColor = RGB(255, 255, 255);
}

ShapeDlg::~ShapeDlg()
{
	
}

void ShapeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, PenType);
	DDX_Control(pDX, IDC_LIST2, BrushType);
	DDX_Text(pDX, IDC_ORGX, OrgX);
	DDX_Text(pDX, IDC_ORGY, OrgY);
	DDX_Text(pDX, IDC_WIDTH, Width);
	DDX_Text(pDX, IDC_HEIGHT, Height);
	DDX_Text(pDX, IDC_TEXT, Text);
	DDX_Text(pDX, IDC_PEN_EDIT_WIDTH, PenWidth);
	DDX_Control(pDX, IDC_PEN_COLOR, PenColor);
	DDX_Control(pDX, IDC_BRUSH_EDIT_COLOR, BrushColor);
	DDX_Control(pDX, IDC_COMBO1, ShapeType);
}


BEGIN_MESSAGE_MAP(ShapeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SURE, &ShapeDlg::OnBnClickedSure)
	ON_BN_CLICKED(IDC_QUIT, &ShapeDlg::OnBnClickedQuit)
	ON_BN_CLICKED(IDC_PEN_BU_COLOR, &ShapeDlg::OnBnClickedPenBuColor)
	ON_BN_CLICKED(IDC_BRUSH_BU_COLOR, &ShapeDlg::OnBnClickedBrushBuColor)
	ON_WM_CTLCOLOR()
	ON_CONTROL_RANGE(EN_CHANGE, IDC_ORGX, IDC_PEN_EDIT_WIDTH, OnEditChange)
END_MESSAGE_MAP()


// ShapeDlg 消息处理程序


//初始化
BOOL ShapeDlg::OnInitDialog() {
	BOOL res = CDialogEx::OnInitDialog();
	
	//初始化画笔列表框
	PenType.AddString(_T("PS_SOLID"));//值分别是0-7
	PenType.AddString(_T("PS_DASH")); 
	PenType.AddString(_T("PS_DOT"));
	PenType.AddString(_T("PS_DASHDOT"));
	PenType.AddString(_T("PS_DASHDOTDOT"));
	PenType.AddString(_T("PS_NULL"));
	PenType.AddString(_T("PS_INSIDEFRAME"));
	//初始化画刷列表框
	BrushType.AddString(_T("HS_HORIZONTAL"));//值分别是0-5
	BrushType.AddString(_T("HS_VERTICAL"));
	BrushType.AddString(_T("HS_FDIAGONAL")); 
	BrushType.AddString(_T("HS_BDIAGONAL"));
	BrushType.AddString(_T("HS_CROSS"));
	BrushType.AddString(_T("HS_DIAGCROSS"));
	BrushType.AddString(_T("SDLID"));


	ShapeType.SetCurSel(m_ShapeType-1);//初始化组合框

	//初始化列表框
	PenType.SetCurSel(m_PenType);
	if(m_BrushType!=-1)
		BrushType.SetCurSel(m_BrushType);
	if (PenWidth != 0) {//如果线宽不为0，那么说明肯定是在修改图形对象，这时候不能选择形状
		ShapeType.EnableWindow(false);
	}
	return res;
}

void ShapeDlg::OnBnClickedSure()
{
	
	// TODO: 在此添加控件通知处理程序代码
	switch (ShapeType.GetCurSel())
	{
	case 0: m_ShapeType = SQUARE; break;
	case 1: m_ShapeType = RECTANGLE; break;
	case 2: m_ShapeType = CIRCLE; break;
	case 3: m_ShapeType = ELLIPSE; break;
	case 4: m_ShapeType = TRIANGLE; break;
	case 5: m_ShapeType = TEXT; break;
	default:
		break;
	}
	m_PenType = PenType.GetCurSel();
	m_BrushType = BrushType.GetCurSel();
	OnOK();
}


void ShapeDlg::OnBnClickedQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void ShapeDlg::OnBnClickedPenBuColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_PenColor = dlg.GetColor();
		Invalidate();//使窗口无效
	}
}


HBRUSH ShapeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	 HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);//实现父类方法
	if (pWnd->GetDlgCtrlID() == IDC_PEN_EDIT_COLOR)
	{
		hbr = ::CreateSolidBrush(m_PenColor);
	}
	if (pWnd->GetDlgCtrlID() == IDC_BRUSH_EDIT_COLOR) {
		hbr = ::CreateSolidBrush(m_BrushColor);
	}
	return hbr;
}

void ShapeDlg::OnBnClickedBrushBuColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_BrushColor = dlg.GetColor();
		Invalidate();
	}
}

void ShapeDlg::SetShapeValueToDlg(CPoint point)
{
	OrgX = point.x;
	OrgY = point.y;
}

void ShapeDlg::OnEditChange(UINT nID)
{
	CString content;
	CEdit *edit = (CEdit*)GetDlgItem(nID);
	edit->GetWindowTextW(content);

	for (int i = 0; i < content.GetLength(); i++) {
		if (content.GetAt(i) < '0' || content.GetAt(i) > '9') {
			MessageBox(L"请输入整数!");
			content = "";
			edit->SetSel(0, -1);
			edit->ReplaceSel(L"");
			break;
		}
	}
	

}