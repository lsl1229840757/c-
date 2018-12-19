#include "stdafx.h"
#include "GeoPolygon.h"


CGeoPolygon::CGeoPolygon(void)
{
}


CGeoPolygon::~CGeoPolygon(void)
{
}
void CGeoPolygon::Draw(CDC* pDC){
	CBrush brush;
	brush.CreateSolidBrush(RGB(r,g,b));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	int size = pts.GetSize();
	POINT *point = new POINT[size];
	for(int i=0;i<size;i++)
	{
		point[i] = pts[i];
	}
	//pDC->SelectObject(oldBrush);
	pDC->Polygon(point,size);
}
int CGeoPolygon::getSize(){
	return pts.GetSize();
}
void CGeoPolygon::addPoint(CPoint pt){
	this->pts.Add(pt);
}