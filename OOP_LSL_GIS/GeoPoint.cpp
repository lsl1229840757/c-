#include "stdafx.h"
#include "GeoPoint.h"


CGeoPoint::CGeoPoint(void)
{
}

CGeoPoint::CGeoPoint(int x, int y)
{
	cpt.x = x;
	cpt.y = y;
}

CGeoPoint::~CGeoPoint(void)
{

}
void CGeoPoint::setPoint(int x,int y){
	this->cpt.x = x;
	this->cpt.y = y;
}
void CGeoPoint::setPoint(CPoint pt){
	this->cpt = pt;
}

void CGeoPoint::Draw(CDC *pDC)
{
	pDC->SetPixel(cpt.x,cpt.y,RGB(r,g,b));
}

void CGeoPoint::setXY(double x, double y)
{
	this->x = x;
	this->y = y;
}


CPoint CGeoPoint::getPos(void)
{
	return CPoint(cpt.x,cpt.y);
}
