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
	dlg->m_PenColor =BorderColor ;//pen����ɫ
	dlg->m_PenType =BorderType ;//pen������
	dlg->PenWidth= BorderWidth ;//pen�Ŀ��
	dlg->m_BrushColor =FillColor ;//brush�����ɫ
	dlg->m_BrushType=FillType  ;//brush���������
}

void CShape::SetShapeValue(ShapeDlg *dlg)
{
	Type = dlg->m_ShapeType;
	OrgX = dlg->OrgX;
	OrgY = dlg->OrgY;
	BorderColor=dlg->m_PenColor;//pen����ɫ
	BorderType=dlg->m_PenType;//pen������
	BorderWidth = dlg->PenWidth;//pen�Ŀ��
	FillColor = dlg->m_BrushColor;//brush�����ɫ
	FillType =  dlg->m_BrushType;//brush���������
}

void CShape::InitialDraw(CDC * pDC)
{
	pen = new CPen;//�ʶ���
	brush = new CBrush;//��ˢ����
	pen->CreatePen(BorderType, BorderWidth, BorderColor);
	if (FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS)//�����ж��Ƿ�ѡ������Ӱ���HS_HORIZONTAL�����ֱ�ʾ0���Ƿ��Ŀ�ʼ��HS_DIAGCROSS���ֱ�ʾ5����Ӱ���Ľ���
		brush->CreateHatchBrush(FillType, FillColor);
	else
		brush->CreateSolidBrush(FillColor);//û�й涨��Ӱ���Ĭ�ϴ�ɫ��ˢ

	oldPen = pDC->SelectObject(pen);
	oldBrush = pDC->SelectObject(brush);
}

void CShape::FinishDraw(CDC * pDC)
{
	//�ָ�Ĭ�ϵĻ��ʺͻ�ˢ
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	//�ͷ���Դ
	delete pen;
	delete brush;
}
