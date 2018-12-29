#pragma once
#include "CShape.h"
class CEllipse :
	public CShape
{
private:
	int Width;
	int Height;
	DECLARE_SERIAL(CEllipse)//������CShape֧�����л�
public:
	CEllipse();
	~CEllipse();
	void Serialize(CArchive &ar);
	void Draw(CDC *pDC);
	bool IsMatched(CPoint pnt);
	void GetShapeValue(ShapeDlg *dlg);
	void SetShapeValue(ShapeDlg *dlg);
};

