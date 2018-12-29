#pragma once
#include "CShape.h"
class CCircle :
	public CShape
{
private:
	int Radius;
	DECLARE_SERIAL(CCircle)//声明类CShape支持序列化
public:
	CCircle();
	~CCircle();
	void Serialize(CArchive &ar);
	void Draw(CDC *pDC);
	bool IsMatched(CPoint pnt);
	void GetShapeValue(ShapeDlg *dlg);
	void SetShapeValue(ShapeDlg *dlg);
};

