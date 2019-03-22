#pragma once
#include "geoobject.h"
#include "GeoPoint.h"
class CGeoPloyline :
	public CGeoObject
{
private:
	CArray<CPoint,CPoint> pts; //TODO 这里没有传入指针
	CArray<CGeoPoint *,CGeoPoint*> gpts;
public:
	CGeoPloyline(void);
	~CGeoPloyline(void);
	void addPoint(CPoint pt);
	int getSize();
	void Draw(CDC* pDC);
	void DrawDDA(CDC *pDC);
	int GetCode(CRect wcRect1, CPoint pt1);
	void ClipObj(CRect wcRect1);
	CArray<CPoint,CPoint> clipPts;
	void drawBezier(CDC * pDC, CArray<CPoint,CPoint>& pts);
};
