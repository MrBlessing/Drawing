#include "stdafx.h"
#include "CShape.h"
#include "ShapeDlg.h"

CShape::CShape()
{
	
}


CShape::~CShape()
{
}

void CShape::GetShapeValue(ShapeDlg *dlg)
{
	dlg->OrgX = OrgX ;
	dlg->OrgY = OrgY ;
	dlg->m_ShapeType = Type;
	dlg->m_PenColor =BorderColor ;//pen的颜色
	dlg->m_PenType =BorderType ;//pen的类型
	dlg->PenWidth= BorderWidth ;//pen的宽度
	dlg->m_BrushColor =FillColor ;//brush的填充色
	dlg->m_BrushType=FillType  ;//brush的填充类型
}

void CShape::SetShapeValue(ShapeDlg *dlg)
{
	Type = dlg->m_ShapeType;
	OrgX = dlg->OrgX;
	OrgY = dlg->OrgY;
	BorderColor=dlg->m_PenColor;//pen的颜色
	BorderType=dlg->m_PenType;//pen的类型
	BorderWidth = dlg->PenWidth;//pen的宽度
	FillColor = dlg->m_BrushColor;//brush的填充色
	FillType =  dlg->m_BrushType;//brush的填充类型
}

void CShape::InitialDraw(CDC * pDC)
{
	pen = new CPen;//笔对象
	brush = new CBrush;//画刷对象
	pen->CreatePen(BorderType, BorderWidth, BorderColor);
	if (FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS)//这里判断是否选择了阴影风格，HS_HORIZONTAL的数字表示0，是风格的开始，HS_DIAGCROSS数字表示5，阴影风格的结束
		brush->CreateHatchBrush(FillType, FillColor);
	else
		brush->CreateSolidBrush(FillColor);//没有规定阴影风格，默认纯色画刷

	oldPen = pDC->SelectObject(pen);
	oldBrush = pDC->SelectObject(brush);
}

void CShape::FinishDraw(CDC * pDC)
{
	//恢复默认的画笔和画刷
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	//释放资源
	delete pen;
	delete brush;
}
