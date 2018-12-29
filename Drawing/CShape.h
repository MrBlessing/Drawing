#pragma once
#include "stdafx.h"
class ShapeDlg;
enum ElementType { NOTSET, SQUARE, RECTANGLE, CIRCLE, ELLIPSE, TRIANGLE, TEXT };
class CShape :public CObject
{
	
protected:

	ElementType Type = NOTSET;//��ͼԪ�ص�����
	int OrgX;//ԭ��
	int OrgY;
	COLORREF BorderColor;//pen����ɫ
	int BorderType;//pen������
	int BorderWidth;//pen�Ŀ��
	COLORREF FillColor;//brush�����ɫ
	int FillType;//brush���������

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
	void InitialDraw(CDC * pDC);//��ʼ��Pen�����Brush����
	void FinishDraw(CDC * pDC);//�滭��β
};


