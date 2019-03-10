#pragma once // 保证.h只被包含一次
#include "GeoLayer.h"
#include "atltypes.h"
class CGeoMap
{
public:
	CGeoMap(void);
	~CGeoMap(void);
	CGeoMap(CGeoMap& map);
	CGeoMap(int Scale);
	const int Scale; // 地图比例尺
	CRect crRect;// 地图范围
	CString getName();// 获得名字
	void setName(CString name);
	int getScale();//获得地图比例尺
	void setScale(int scale);
	CArray<CGeoLayer *,CGeoLayer *> geoLayers;
	void delLayerAt(int idx);// 删除图层
	void delLayerAll(); // 删除所有图层
	void setLayerIsVisible(CString layerName,boolean isVisible); // 设定某个图层可视
	void Draw(CDC *pDC); //画图
	void setRect(CRect rect);
	CRect getRect();
	void addLayer(CGeoLayer *layer);
	CGeoLayer* getLayerByName(CString name);
private:
	CString Name; //名字

public:
	CRect clipRect;

	void clipMap(CRect clipRect);
};

