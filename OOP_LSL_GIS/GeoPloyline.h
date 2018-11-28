#pragma once
#include "geoobject.h"
class CGeoPloyline :
	public CGeoObject
{
private:
	CArray<CPoint,CPoint> pts; //TODO 这里没有传入指针


public:
	CGeoPloyline(void);
	~CGeoPloyline(void);
	void addPoint(CPoint pt);
	int getSize();
	void Draw(CDC* pDC);
};

