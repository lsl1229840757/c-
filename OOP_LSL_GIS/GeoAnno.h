#pragma once
#include "geoobject.h"
class CGeoAnno :
	public CGeoObject
{
private:
	CPoint pt;
	CString name;

public:
	CGeoAnno(void);
	~CGeoAnno(void);
	void Draw(CDC *pDC);
	void setPoint(int x,int y);
	void setName(CString name);
};

