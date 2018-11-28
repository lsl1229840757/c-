#pragma once
#include "geoobject.h"
class CGeoPoint :
	public CGeoObject
{
public:
	CGeoPoint(void);
	~CGeoPoint(void);
	void setPoint(int x,int y);
	void setPoint(CPoint pt);
	void Draw(CDC *pDC);
private:
	CPoint cpt;


};

