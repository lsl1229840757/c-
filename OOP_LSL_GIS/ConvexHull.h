#pragma once
#include "GeoObject.h"
class CConvexHull:
	public CGeoObject
{
public:
	CConvexHull(void);
	~CConvexHull(void);
	CArray<CPoint,CPoint> pts;//离散点
	CArray<CPoint,CPoint> Chpts;//凸颗坐标
	CRect crWCRect; //点集外接矩形
	void getConvexHull(CArray<CGeoObject*, CGeoObject*>& objs);
	void Draw(CDC *pDC);
};

