#pragma once
#include "CShape.h"
class CSquare :
	public CShape
{
private:
	int Width;
	DECLARE_SERIAL(CSquare)//声明类CShape支持序列化
public:
	CSquare();
	~CSquare();
	void Serialize(CArchive &ar);
	void Draw(CDC *pDC);
	bool IsMatched(CPoint pnt);
	void GetShapeValue(ShapeDlg *dlg);
	void SetShapeValue(ShapeDlg *dlg);
};

