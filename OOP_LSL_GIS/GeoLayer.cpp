#include "stdafx.h"
#include "GeoLayer.h"


CGeoLayer::CGeoLayer(void)
{
}


CGeoLayer::~CGeoLayer(void)
{
	//É¾³ýobjectÖ¸Õë
	for (int i = 0; i < geoObjects.GetSize(); i++)
	{
		delete geoObjects.ElementAt(i);
	}
}

void CGeoLayer::Draw(CDC *pDC){
	for (int i = 0; i < geoObjects.GetSize(); i++)
	{
		geoObjects[i]->Draw(pDC);
	}
}

void CGeoLayer::addObject(CGeoObject *obj){
	geoObjects.Add(obj);
}
void CGeoLayer::delObjectAt(int idx){
	geoObjects.RemoveAt(idx);
}
void CGeoLayer::delObjectAll(){
	geoObjects.RemoveAll();
}
void CGeoLayer::setName(CString name){
	this->Name = name;
}
CString CGeoLayer::getName(){
	return this->Name;
}
CArray<CGeoObject *,CGeoObject *>& CGeoLayer::getObjects(){
	return this->geoObjects;
}