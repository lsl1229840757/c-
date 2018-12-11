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
private:
	CArray<CPoint,CPoint> pts; //TODO ����û�д���ָ��
	CArray<CGeoPoint *,CGeoPoint*> gpts;

};

