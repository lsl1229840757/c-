#pragma once
#include "geoobject.h"
class CGeoAnno :
	public CGeoObject
{
private:
	CPoint pt;

public:
	CGeoAnno(void);
	~CGeoAnno(void);
	void Draw(CDC *pDC);
};

