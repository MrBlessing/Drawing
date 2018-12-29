#pragma once
#include "CShape.h"
class CRectangle :
	public CShape
{
private:
	int Width;
	int Height;
	DECLARE_SERIAL(CRectangle)//������CShape֧�����л�
public:
	CRectangle();
	~CRectangle();
	void Serialize(CArchive &ar);
	void Draw(CDC *pDC);
	bool IsMatched(CPoint pnt);
	void GetShapeValue(ShapeDlg *dlg);
	void SetShapeValue(ShapeDlg* dlg);
};

