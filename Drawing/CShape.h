#pragma once
#include "stdafx.h"
class ShapeDlg;
enum ElementType { NOTSET, SQUARE, RECTANGLE, CIRCLE, ELLIPSE, TRIANGLE, TEXT };
class CShape :public CObject
{
	
protected:

	ElementType Type = NOTSET;//绘图元素的类型
	int OrgX;//原点
	int OrgY;
	COLORREF BorderColor;//pen的颜色
	int BorderType;//pen的类型
	int BorderWidth;//pen的宽度
	COLORREF FillColor;//brush的填充色
	int FillType;//brush的填充类型

	CPen *pen, *oldPen;
	CBrush *brush, *oldBrush;

public:
	CShape();
	~CShape();
	virtual void Serialize(CArchive& ar)=0;
	virtual void Draw(CDC *pDC)=0;
	virtual bool IsMatched(CPoint pnt)=0;
	virtual void GetShapeValue(ShapeDlg *dlg);
	virtual void SetShapeValue(ShapeDlg *dlg);
	void InitialDraw(CDC * pDC);//初始化Pen对象和Brush对象
	void FinishDraw(CDC * pDC);//绘画收尾
};


