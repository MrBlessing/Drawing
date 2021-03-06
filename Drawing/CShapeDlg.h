#pragma once


// SetProperty 对话框

class CShapeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShapeDlg)

public:
	CShapeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShapeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()
public:

	CComboBox TypeCmb;
	CListBox PenType;
	CListBox BrushType;
};
