#include "stdafx.h"
#include "GeoPolygon.h"


CGeoPolygon::CGeoPolygon(void)
{
	r = 0;
	g = 0;
	b = 0;
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
	for(int i=0;i<size;i++){
		if(i==0)
			pDC->MoveTo(pts[i]);
		else{
			pDC->LineTo(pts[i]);
		}
	}
	//pDC->SelectObject(oldBrush);
	pDC->Polygon(point,size);
	//FloodFillPolygon(pDC);
}
int CGeoPolygon::getSize(){
	return pts.GetSize();
}
void CGeoPolygon::addPoint(CPoint pt){
	this->pts.Add(pt);
}
void CGeoPolygon::FloodFillPolygon(CDC *pDC){
	int x,y;
	CPoint pt;
	while(seeds.GetSize()>0){
		pt = seeds.GetAt(seeds.GetSize()-1);
		x = pt.x;
		y = pt.y;
		pDC->SetPixel(x,y,RGB(r,g,b));
		seeds.RemoveAt(seeds.GetSize()-1);
		if(pDC->GetPixel(x+1,y) == RGB(255,255,255))
			seeds.Add(CPoint(x+1,y));
		if(pDC->GetPixel(x,y+1) == RGB(255,255,255))
			seeds.Add(CPoint(x,y+1));
		if(pDC->GetPixel(x-1,y) == RGB(255,255,255))
			seeds.Add(CPoint(x-1,y));
		if(pDC->GetPixel(x,y-1) == RGB(255,255,255))
			seeds.Add(CPoint(x,y-1));
	}
}