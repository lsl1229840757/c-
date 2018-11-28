#include "stdafx.h"
#include "GeoPloyline.h"


CGeoPloyline::CGeoPloyline(void)
{
}


CGeoPloyline::~CGeoPloyline(void)
{
}
void CGeoPloyline::Draw(CDC* pDC){
	for (int i = 0; i < pts.GetSize(); i++)
	{
		if(i==0){
			pDC->MoveTo(pts[i]);
		}else{
			pDC->LineTo(pts[i]);
		}
	}
}
int CGeoPloyline::getSize(){
	return pts.GetSize();
}
void CGeoPloyline::addPoint(CPoint pt){
	this->pts.Add(pt);
}