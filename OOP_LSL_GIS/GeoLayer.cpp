#include "stdafx.h"
#include "GeoLayer.h"


CGeoLayer::CGeoLayer(void)
{
}


CGeoLayer::~CGeoLayer(void)
{
}

void CGeoLayer::Draw(CDC *pDC){
	for (int i = 0; i < geoObjects.GetSize(); i++)
	{
		geoObjects[i]->Draw(pDC);
	}
}