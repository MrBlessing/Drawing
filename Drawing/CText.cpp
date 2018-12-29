#include "stdafx.h"
#include "CText.h"
#include "ShapeDlg.h"
IMPLEMENT_SERIAL(CText, CObject, 1)

CText::CText()
{
}


CText::~CText()
{
}

void CText::Serialize(CArchive &ar)
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

		ar << Text;
		ar << Height;
		ar << Angle;
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

		ar >> Text;
		ar >> Height;
		ar >> Angle;
	}
}

void CText::Draw(CDC * pDC)
{
	InitialDraw(pDC);
	//设置字体背景颜色
	pDC->SetBkColor(FillColor);
	//设置字体
	CFont *font, *oldFont;
	font = new CFont;
	font->CreateFontW(Height ,0, -Angle*10 ,0  , 200, false, false, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH&FF_SWISS, NULL);
	oldFont = pDC->SelectObject(font);

	pDC->TextOutW(OrgX,OrgY,Text);

	//获取字体长度
	TextSize = pDC->GetTextExtent(Text);
	CPoint p[2] = { { OrgX, OrgY }, { int(OrgX  -TextSize.cx*cos(Angle*3.14/180)) ,int(OrgY  +TextSize.cx*sin(Angle*3.14 / 180)) } };
	pDC->Polygon(p,2);

	pDC->SelectObject(oldFont);
	delete font;
	FinishDraw(pDC);
}

bool CText::IsMatched(CPoint pnt)
{
	
	return false;
}

void CText::GetShapeValue(ShapeDlg *dlg)
{

	CShape::GetShapeValue(dlg);
	dlg->Text = Text;
	dlg->Height = Height;
	dlg->Width = Angle;
}

void CText::SetShapeValue(ShapeDlg *dlg)
{
	CShape::SetShapeValue(dlg);
	Text = dlg->Text;
	Height = dlg->Height;
	Angle = dlg->Width;
}
