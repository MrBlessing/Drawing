
// DrawingView.cpp: CDrawingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Drawing.h"
#endif

#include "DrawingDoc.h"
#include "DrawingView.h"
#include "custom.h"
#include "CShape.h"
#include "CSquare.h"
#include "ShapeDlg.h"
#include "CCircle.h"
#include "CText.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CEllipse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawingView

IMPLEMENT_DYNCREATE(CDrawingView, CScrollView)

BEGIN_MESSAGE_MAP(CDrawingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CDrawingView 构造/析构

CDrawingView::CDrawingView()
{
	// TODO: 在此处添加构造代码

}

CDrawingView::~CDrawingView()
{
}

BOOL CDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CDrawingView 绘图

void CDrawingView::OnDraw(CDC* pDC)
{
	CDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	
	CObArray &temp =  pDoc->elements;
	for (int i = 0; i <temp.GetSize(); i++) {
		CShape *shape = (CShape*)temp.GetAt(i);
		shape->Draw(pDC);
		//这里将文档类中Elements中存的图形类遍历，分别多态调用子类中的Draw方法来画出每一个子类
		//之所以在这里调用的原因是这里有CDC指针
	}
}

void CDrawingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
}


// CDrawingView 打印

BOOL CDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawingView 诊断

#ifdef _DEBUG
void CDrawingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrawingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDrawingDoc* CDrawingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawingDoc)));
	return (CDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawingView 消息处理程序

//鼠标左键点击事件
void CDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//nFlags表示鼠标的控制状态
	if ((nFlags&MK_CONTROL) == MK_CONTROL)//9&0X0008=8
	{
		//一些初始化的操作 
		CDrawingDoc *pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)	return;

		//转化坐标
		CClientDC dc(this);//CClientDC:（客户区设备上下文）用于客户区的输出，与特定窗口关联，可以让开发者访问目标窗口中客户区
		CPoint pntLogical = point;
		OnPrepareDC(&dc);
		dc.DPtoLP(&pntLogical);//DP->LP进行转换(设备坐标和逻辑坐标的转换)

		ShapeDlg dlg;//打开弹窗
		dlg.SetShapeValueToDlg(pntLogical);//传入点的坐标
		if (dlg.DoModal() == IDOK) {//如果点击的是ok，则执行下一步操作

			CShape *shape = NULL ;
			switch (dlg.m_ShapeType)
			{
			case SQUARE: shape = new CSquare(); break;
			case RECTANGLE: shape = new CRectangle(); break;
			case CIRCLE: shape = new CCircle(); break;
			case ELLIPSE: shape = new CEllipse(); break;
			case TRIANGLE: shape = new CTriangle(); break;
			case TEXT: shape = new CText(); break;
			default:
				break;
			}
			if (shape != NULL) {
				shape->SetShapeValue(&dlg);//将属性传入shape对象
				pDoc->elements.Add(shape);
				pDoc->SetModifiedFlag();
				pDoc->UpdateAllViews(NULL);
			}
			
		}
		CScrollView::OnLButtonDown(nFlags, point);
	}
	
}


void CDrawingView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//转化坐标
	CClientDC dc(this);//CClientDC:（客户区设备上下文）用于客户区的输出，与特定窗口关联，可以让开发者访问目标窗口中客户区
	CPoint pntLogical = point;
	OnPrepareDC(&dc);
	dc.DPtoLP(&pntLogical);//DP->LP进行转换(设备坐标和逻辑坐标的转换)

	CDrawingDoc *pDoc = GetDocument();
	CObArray &temp = pDoc->elements;
	for (int i = 0; i < temp.GetSize(); i++) {
		CShape *shape = (CShape*)temp.GetAt(i);
		if (shape->IsMatched(pntLogical)) {
			//如果匹配上了，先在集合中删掉这个对象
			//然后创建新的对象
			ShapeDlg dlg;//打开弹窗
			shape->GetShapeValue(&dlg);//获取Shape对象中的值
			if (dlg.DoModal() == IDOK) {//如果点击的是ok，则执行下一步操作
				temp.RemoveAt(i);
				shape->SetShapeValue(&dlg);//将属性传入shape对象
				pDoc->elements.Add(shape);
				pDoc->SetModifiedFlag();
				pDoc->UpdateAllViews(NULL);
			}
		}
	}
	CScrollView::OnRButtonDblClk(nFlags, point);
}


void CDrawingView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);//CClientDC:（客户区设备上下文）用于客户区的输出，与特定窗口关联，可以让开发者访问目标窗口中客户区
	CPoint pntLogical = point;
	OnPrepareDC(&dc);
	dc.DPtoLP(&pntLogical);//DP->LP进行转换(设备坐标和逻辑坐标的转换)

	CDrawingDoc *pDoc = GetDocument();
	CObArray &temp = pDoc->elements;
	for (int i = 0; i < temp.GetSize(); i++) {
		CShape *shape = (CShape*)temp.GetAt(i);
		if (shape->IsMatched(pntLogical)) {
			//如果匹配上了，先在集合中删掉这个对象
			//然后销毁对象
			temp.RemoveAt(i);
			delete shape;
			pDoc->SetModifiedFlag();
			pDoc->UpdateAllViews(NULL);
		}
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}
