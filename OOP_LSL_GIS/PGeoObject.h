#pragma once
#include "MapProject.h"
#include "GeoPoint.h"
class CPGeoObject
{
public:
	CPGeoObject(void);
	~CPGeoObject(void);
	float L0£¬L1£¬B0£¬B1;
	CArray<CPoint,CPoint> pts;


	void Draw(CDC * pDC, CMapProject mapPrj);
	void addPoint(CGeoPoint geoPoint);
};

