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
	CPoint a = { OrgX,int(OrgY - sqrt(3) / 3 * Width) };//����
	CPoint b = { int(OrgX + Width / 2),int(OrgY + sqrt(3) / 6 * Width) };//�Ҳ��
	CPoint c = { int(OrgX - Width / 2),int(OrgY + sqrt(3) / 6 * Width) };//����
	CPoint p[3] = { a,b,c };
	pDC->Polygon(p,3);
	//�ָ�Ĭ�ϵĻ��ʺͻ�ˢ
	FinishDraw(pDC);
}

bool CTriangle::IsMatched(CPoint pnt)
{
	//���������������Ǹ��ߵĺ���
	int ly = int(-sqrt(3)*pnt.x + OrgY + sqrt(3)*OrgX - sqrt(3) / 3 * Width);
	//�����������Ҳ���Ǹ��ߵĺ���
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
