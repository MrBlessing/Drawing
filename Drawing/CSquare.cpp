#include "stdafx.h"
#include "CSquare.h"
#include "ShapeDlg.h"
IMPLEMENT_SERIAL(CSquare, CObject, 1)

CSquare::CSquare()
{
}

CSquare::~CSquare()
{
}

void CSquare::Serialize(CArchive & ar)
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

void CSquare::Draw(CDC * pDC)
{
	InitialDraw(pDC);
	pDC->Rectangle(OrgX -Width / 2, OrgY -Width / 2, OrgX + Width / 2, OrgY + Width / 2);
	FinishDraw(pDC);
}

bool CSquare::IsMatched(CPoint pnt)
{
	if (pnt.x <= OrgX + Width / 2 && pnt.x >= OrgX - Width / 2 && pnt.y >= OrgY - Width / 2 && pnt.y <= OrgY + Width / 2)
		return true;
	else
		return false;
}

void CSquare::GetShapeValue(ShapeDlg * dlg)
{
	CShape::GetShapeValue(dlg);
	dlg->Width = Width;
}

void CSquare::SetShapeValue(ShapeDlg* dlg)
{
	CShape::SetShapeValue(dlg);
	Width = dlg->Width;
}
