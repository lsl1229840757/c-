#pragma once
#include"GeoLayer.h"
#include "MapProject.h"
class MyCMap
{
public:
	MyCMap(void);
	~MyCMap(void);
	float L0;
	float L1;
	float B0;
	float B1;
	CArray<CGeoLayer *, CGeoLayer *> geoLayers;
	void Draw(CDC* pDC, CMapProject mapPrj);
	void addLayers(CGeoLayer geoLayer);
};

