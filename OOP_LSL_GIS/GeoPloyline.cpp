#include "stdafx.h"
#include "GeoPloyline.h"


CGeoPloyline::CGeoPloyline(void)
{
}


CGeoPloyline::~CGeoPloyline(void)
{
}
void CGeoPloyline::Draw(CDC* pDC){
	CPen pen;
	pen.CreatePen(PS_SOLID,lineWidth,RGB(r,g,b));
	CPen *oldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < pts.GetSize(); i++)
	{
		if(i==0){
			pDC->MoveTo(pts[i]);
		}else{
			pDC->LineTo(pts[i]);
		}
	}
//	pDC->SelectObject(&oldPen);
}
int CGeoPloyline::getSize(){
	return pts.GetSize();
}
void CGeoPloyline::addPoint(CPoint pt){
	this->pts.Add(pt);
}