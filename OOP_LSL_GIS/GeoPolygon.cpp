#include "stdafx.h"
#include "GeoPolygon.h"


CGeoPolygon::CGeoPolygon(void)
{
}


CGeoPolygon::~CGeoPolygon(void)
{
}
void CGeoPolygon::Draw(CDC* pDC){
	for (int i = 0; i < pts.GetSize(); i++)
	{
		if(i==0){
			pDC->MoveTo(pts[i]);
		}else{
			pDC->LineTo(pts[i]);
		}
	}
}
int CGeoPolygon::getSize(){
	return pts.GetSize();
}
void CGeoPolygon::addPoint(CPoint pt){
	this->pts.Add(pt);
}