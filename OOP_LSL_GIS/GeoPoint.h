#pragma once
#include "geoobject.h"
class CGeoPoint :
	public CGeoObject
{
public:
	double x;
	double y;
	CGeoPoint(void);
	~CGeoPoint(void);
	void setPoint(int x,int y);
	void setPoint(CPoint pt);
	void Draw(CDC *pDC);
private:
	CPoint cpt;


public:
	void setXY(double x, double y);
};

