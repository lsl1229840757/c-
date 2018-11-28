#include "stdafx.h"
#include "GeoMap.h"


CGeoMap::CGeoMap(int Scale):Scale(Scale)
{
}


CGeoMap::~CGeoMap(void)
{
}

CString CGeoMap::getName(){
	return this->Name;
}
void CGeoMap::setName(CString name){
	this->Name = name;
}
int CGeoMap::getScale(){
	return this->Scale;
}

void CGeoMap::setRect(CRect rect){
	this->crRect = rect;
}
CRect CGeoMap::getRect(){
	return this->crRect;
}

void CGeoMap::Draw(CDC *pDC){
	for (int i = 0; i < geoLayers.GetSize(); i++)
	{
		geoLayers[i]->Draw(pDC);
	}
}

void CGeoMap::addLayer(CGeoLayer *layer){
	geoLayers.Add(layer);
}

void CGeoMap::delLayerAt(int idx){
	geoLayers.RemoveAt(idx);
}
void CGeoMap::delLayerAll(){
	geoLayers.RemoveAll();
}