#pragma once
#include "CShape.h"
class CRectangle :
	public CShape
{
private:
	int Width;
	int Height;
	DECLARE_SERIAL(CRectangle)//声明类CShape支持序列化
public:
	CRectangle();
	~CRectangle();
	void Serialize(CArchive &ar);
	void Draw(CDC *pDC);
	bool IsMatched(CPoint pnt);
	void GetShapeValue(ShapeDlg *dlg);
	void SetShapeValue(ShapeDlg* dlg);
};

