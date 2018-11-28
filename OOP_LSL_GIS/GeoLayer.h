#pragma once
#include "GeoObject.h"
class CGeoLayer
{
public:
	CGeoLayer(void);
	~CGeoLayer(void);
	CRect crRect;
	void addObject(CGeoObject *obj);
	void delObjectAt(int idx);
	void delObjectAll();
	void Draw(CDC *pDC);

private:
	CString Name;
	// ����Ŀ������
	CArray<CGeoObject *,CGeoObject *> geoObjects;
	boolean isVisible;

};

