#include "stdafx.h"
#include "GeoPoint.h"


CGeoPoint::CGeoPoint(void)
{
}


CGeoPoint::~CGeoPoint(void)
{
}
void CGeoPoint::setPoint(int x,int y){
	this->x = x;
	this->y = y;
}
void CGeoPoint::setPoint(CPoint pt){
	this->x = pt.x;
	this->y = pt.y;
}