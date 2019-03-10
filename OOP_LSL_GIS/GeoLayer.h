#pragma once
#include "GeoObject.h"
class CGeoLayer
{
public:
	CGeoLayer(void);
	~CGeoLayer(void);
	CRect crRect;
	void addObject(CGeoObject *obj);
	void delObjectAt(int idx);
	void delObjectAll();
	void Draw(CDC *pDC);
	void setName(CString name);
	CString CGeoLayer::getName();
	CArray<CGeoObject *,CGeoObject *>& getObjects();
private:
	CString Name;
	// 地理目标数组
	CArray<CGeoObject *,CGeoObject *> geoObjects;
	boolean isVisible;

public:
	void clipLayer(CRect clipRect1);
};

