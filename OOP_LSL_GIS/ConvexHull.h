#pragma once
#include "GeoObject.h"
class CConvexHull:
	public CGeoObject
{
public:
	CConvexHull(void);
	~CConvexHull(void);
	CArray<CPoint,CPoint> pts;//��ɢ��
	CArray<CPoint,CPoint> Chpts;//͹������
	CRect crWCRect; //�㼯��Ӿ���
	void getConvexHull(CArray<CGeoObject*, CGeoObject*>& objs);
	void Draw(CDC *pDC);
};

