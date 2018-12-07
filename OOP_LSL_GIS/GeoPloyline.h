#pragma once
#include "geoobject.h"
#include "GeoPoint.h"
class CGeoPloyline :
	public CGeoObject
{
private:
	CArray<CPoint,CPoint> pts; //TODO ����û�д���ָ��
	CArray<CGeoPoint *,CGeoPoint*> gpts;
public:
	CGeoPloyline(void);
	~CGeoPloyline(void);
	void addPoint(CPoint pt);
	int getSize();
	void Draw(CDC* pDC);
};

