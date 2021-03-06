#pragma once
#include"CShape.h"
// ShapeDlg 对话框
class ShapeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShapeDlg)
public:
	ShapeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ShapeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();
public:
	
	afx_msg void OnBnClickedSure();
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedPenBuColor();
	HBRUSH  OnCtlColor(CDC*   pDC, CWnd*   pWnd, UINT   nCtlColor);
	afx_msg void OnBnClickedBrushBuColor();

	void SetShapeValueToDlg(CPoint point);
	//void GetShapeValueFromDlg(CShape *shape);

	CListBox PenType;
	CListBox BrushType;
	ElementType m_ShapeType;//记录Shape类型
	COLORREF m_PenColor;//记录画笔颜色
	COLORREF m_BrushColor;//记录画刷颜色
	int m_PenType;
	int m_BrushType;
	long OrgX;
	long OrgY;
	long Width;
	long Height;
	CString Text;
	long PenWidth;
	CEdit PenColor;
	CEdit BrushColor;
	CComboBox ShapeType;
	afx_msg void OnEditChange(UINT nID);
};

