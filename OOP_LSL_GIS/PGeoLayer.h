#pragma once
#include "MapProject.h"
class CPGeoLayer
{
public:
	CPGeoLayer(void);
	float L0£¬L1£¬B0£¬B1;
	//TODO objects


	~CPGeoLayer(void);
	void Draw(CDC* pDC, CMapProject mapPrj);
};

