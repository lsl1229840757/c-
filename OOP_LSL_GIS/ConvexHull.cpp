#include "stdafx.h"
#include "ConvexHull.h"
#include "GeoObject.h"
#include "GeoPoint.h"
#include <math.h>
CConvexHull::CConvexHull(void)
{
}


CConvexHull::~CConvexHull(void)
{
}


void CConvexHull::getConvexHull(CArray<CGeoObject*, CGeoObject*>& objs)
{
	Chpts.RemoveAll();
	CPoint pt,tmpPt;
	int idx = 0;
	int size = objs.GetSize();
	if(size<1)return;
	tmpPt = ((CGeoPoint *)objs.GetAt(idx))->getPos();
	for(int i=1;i<size;i++){
		pt = ((CGeoPoint *)objs.GetAt(i))->getPos();
		if(tmpPt.y>pt.y){
			tmpPt = pt;
			idx = i;
		}
	}
	tmpPt = ((CGeoPoint *)objs.GetAt(idx))->getPos();
	this->Chpts.Add(tmpPt);
	pt = tmpPt;
	tmpPt.x = tmpPt.x-10;
	CPoint originPt = pt;
	float cosDelt1;
	CPoint tt;
	do{
		float cosDelt = INT_MIN;
		size = objs.GetSize();
		for(int j=0;j<size;j++){
			tt = ((CGeoPoint *)objs.GetAt(j))->getPos();
			cosDelt1 = ((pt.x-tmpPt.x)*1.0*(tt.x-pt.x)+(pt.y-tmpPt.y)*1.0*(tt.y-pt.y))/(sqrt((pt.x-tmpPt.x)*1.0*(pt.x-tmpPt.x)+(pt.y-tmpPt.y)*1.0*(pt.y-tmpPt.y))*sqrt((tt.x-pt.x)*1.0*(tt.x-pt.x)+(tt.y-pt.y)*1.0*(tt.y-pt.y)));
			if(cosDelt1>=cosDelt){
					cosDelt = cosDelt1;
					idx = j;
			}
		}
		tmpPt = pt;
		pt = ((CGeoPoint *)objs.GetAt(idx))->getPos();
		Chpts.Add(pt);
	}while (originPt!=pt);
}




void CConvexHull::Draw(CDC * pDC)
{

	CPen penb;
	penb.CreatePen(PS_SOLID, 100, RGB(0,0,255));
	CPen *oldPen = pDC->SelectObject(&penb);
	for (int i = 0; i < Chpts.GetSize(); i++)
	{
		if(i==0){
			pDC->MoveTo(Chpts[i]);
		}else{
			pDC->LineTo(Chpts[i]);
		}
	}
	 pDC->SelectObject(&oldPen);
}
