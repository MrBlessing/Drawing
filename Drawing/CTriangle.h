#pragma once
#include "CShape.h"
class CTriangle :
	public CShape
{
private:
	int Width;
	DECLARE_SERIAL(CTriangle)//声明类CShape支持序列化
public:
	CTriangle();
	~CTriangle();
	void Serialize(CArchive &ar);
	void Draw(CDC *pDC);
	bool IsMatched(CPoint pnt);
	void GetShapeValue(ShapeDlg *dlg);
	void SetShapeValue(ShapeDlg *dlg);
};

