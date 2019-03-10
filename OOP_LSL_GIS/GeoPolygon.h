#pragma once
#include "geoobject.h"
#include "GeoPoint.h"
class CGeoPolygon :
	public CGeoObject
{
public:
	void addPoint(CPoint pt);
	int getSize();
	void Draw(CDC* pDC);
	CGeoPolygon(void);
	~CGeoPolygon(void);
	void FloodFillPolygon(CDC *pDC);
	CArray<CPoint,CPoint> pts; //TODO 这里没有传入指针
	CArray<CPoint,CPoint> seeds;
};

