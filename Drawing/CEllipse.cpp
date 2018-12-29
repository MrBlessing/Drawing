#include "stdafx.h"
#include "CEllipse.h"
#include "ShapeDlg.h"
IMPLEMENT_SERIAL(CEllipse, CObject, 1)

CEllipse::CEllipse()
{
}

CEllipse::~CEllipse()
{
}

void CEllipse::Serialize(CArchive& ar)
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
		ar << Height;
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
		ar >>Width;
		ar >> Height;
	}
}

void CEllipse::Draw(CDC * pDC)
{
	InitialDraw(pDC);
	pDC->Ellipse(OrgX - Width / 2, OrgY - Height / 2, OrgX + Width / 2, OrgY + Height / 2);
	FinishDraw(pDC);
}

bool CEllipse::IsMatched(CPoint pnt)
{
	//将Orgx,orgY对应成原点，求出x2/a2+y2/b2的值
	int res = pow(pnt.x - OrgX, 2) / pow((Width / 2), 2) + pow(OrgY - pnt.y, 2) / pow(Height / 2, 2);
	if (res<=1)
		return true;
	else
		return false;
}

void CEllipse::GetShapeValue(ShapeDlg * dlg)
{
	CShape::GetShapeValue(dlg);
	dlg->Width = Width;
	dlg->Height = Height;
}

void CEllipse::SetShapeValue(ShapeDlg * dlg)
{
	CShape::SetShapeValue(dlg);
	 Width =dlg->Width;
	 Height = dlg->Height;
}
