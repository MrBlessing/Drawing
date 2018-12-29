#include "stdafx.h"
#include "CTriangle.h"
#include "ShapeDlg.h"
#include "Math.h"
IMPLEMENT_SERIAL(CTriangle, CObject, 1)


CTriangle::CTriangle()
{
}

CTriangle::~CTriangle()
{
}

void CTriangle::Serialize(CArchive &ar)
{
	if (ar.IsStoring()) {
		ar << (WORD)Type;
		ar << OrgX;
		ar << OrgY;
		ar << BorderColor;
		ar << BorderType;
		ar << BorderWidth;
		ar << FillColor;
		ar << FillType;

		ar << Width;
	}
	else {
		WORD temp;
		ar >> temp;
		Type = (ElementType)temp;
		ar >> OrgX;
		ar >> OrgY;
		ar >> BorderColor;
		ar >> BorderType;
		ar >> BorderWidth;
		ar >> FillColor;
		ar >> FillType;

		ar >> Width;
	}
}

void CTriangle::Draw(CDC * pDC)
{
	InitialDraw(pDC);
	CPoint a = { OrgX,int(OrgY - sqrt(3) / 3 * Width) };//顶点
	CPoint b = { int(OrgX + Width / 2),int(OrgY + sqrt(3) / 6 * Width) };//右侧点
	CPoint c = { int(OrgX - Width / 2),int(OrgY + sqrt(3) / 6 * Width) };//左测点
	CPoint p[3] = { a,b,c };
	pDC->Polygon(p,3);
	//恢复默认的画笔和画刷
	FinishDraw(pDC);
}

bool CTriangle::IsMatched(CPoint pnt)
{
	//算正三角形左侧的那个边的函数
	int ly = int(-sqrt(3)*pnt.x + OrgY + sqrt(3)*OrgX - sqrt(3) / 3 * Width);
	//算正三角形右侧的那个边的函数
	int ry = int(sqrt(3)*pnt.x + OrgY - sqrt(3)*OrgX - sqrt(3) / 3 * Width);
	if (pnt.y>=ly&&pnt.y>=ry&&pnt.y<=OrgY + sqrt(3) / 6 * Width)
		return true;
	else
		return false;
}

void CTriangle::GetShapeValue(ShapeDlg *dlg)
{
	CShape::GetShapeValue(dlg);
	dlg->Width = Width;
}

void CTriangle::SetShapeValue(ShapeDlg *dlg)
{
	CShape::SetShapeValue(dlg);
	Width = dlg->Width;
}
