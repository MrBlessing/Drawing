#pragma once
#include "CShape.h"
class CText :
	public CShape
{
private:
	CString Text;
	long Height;
	long Angle;
	CSize TextSize;
	DECLARE_SERIAL(CText)//������CShape֧�����л�
public:
	CText();
	~CText();
	void Serialize(CArchive &ar);
	void Draw(CDC *pDC);
	bool IsMatched(CPoint pnt);
	void GetShapeValue(ShapeDlg *dlg);
	void SetShapeValue(ShapeDlg *dlg);
};

