#include "stdafx.h"
#include "CCircle.h"
#include "ShapeDlg.h"
IMPLEMENT_SERIAL(CCircle, CObject, 1)

CCircle::CCircle()
{
}

CCircle::~CCircle()
{
}

void CCircle::Serialize(CArchive &ar)
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

		ar << Radius;
		
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

		ar >> Radius;
	}
}

void CCircle::Draw(CDC * pDC)
{
	InitialDraw(pDC);
	pDC->Ellipse(OrgX - Radius, OrgY - Radius, OrgX + Radius, OrgY + Radius);
	FinishDraw(pDC);
}

bool CCircle::IsMatched(CPoint pnt)

{
	//计算点到圆心的距离
	int l = (int)sqrt(pow(pnt.x - OrgX, 2)+ pow(pnt.y - OrgY, 2));
	if (l<=Radius) 
		return true;
	else
		return false;
}

void CCircle::GetShapeValue(ShapeDlg * dlg)
{
	CShape::GetShapeValue(dlg);
	dlg->Width = Radius;
}

void CCircle::SetShapeValue(ShapeDlg* dlg)
{
	CShape::SetShapeValue(dlg);
	Radius = dlg->Width;
}
