
#include "stdafx.h"
#include "CRectangle.h"
#include "ShapeDlg.h"
IMPLEMENT_SERIAL(CRectangle, CObject, 1)
CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::Serialize(CArchive &ar)
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

		ar >> Width;
		ar >> Height;
	}
}

void CRectangle::Draw(CDC * pDC)
{
	InitialDraw(pDC);
										   //»­Í¼
	pDC->Rectangle(OrgX - Width / 2, OrgY - Height / 2, OrgX + Width / 2, OrgY + Height / 2);

	FinishDraw(pDC);
}

bool CRectangle::IsMatched(CPoint pnt)
{
	if (pnt.x <= OrgX + Width / 2 && pnt.x >= OrgX - Width / 2 && pnt.y >= OrgY - Height / 2 && pnt.y <= OrgY + Height / 2)
		return true;
	else
		return false;
}

void CRectangle::GetShapeValue(ShapeDlg * dlg)
{
	CShape::GetShapeValue(dlg);
	dlg->Width = Width;
	dlg->Height = Height;
}

void CRectangle::SetShapeValue(ShapeDlg * dlg)
{
	CShape::SetShapeValue(dlg);
	Width = dlg->Width;
	Height = dlg->Height;
}
