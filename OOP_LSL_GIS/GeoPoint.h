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
	CGeoPoint(float L, float B);
private:
	CPoint cpt;


public:
	float L;
	float B;
	void setXY(double x, double y);
	CPoint getPos(void);
};

