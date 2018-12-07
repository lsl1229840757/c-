#include "stdafx.h"
#include "GeoObject.h"


CGeoObject::CGeoObject(void)
{
}

CGeoObject::~CGeoObject(void)
{
}
int CGeoObject::getID(){
	return this->id;
}
void CGeoObject::setID(int id){
	this->id = id;
}
void CGeoObject::setRect(CRect rect){
	this->crRect = rect;
}

CRect CGeoObject::getRect(){
	return this->crRect;
}

CString CGeoObject::getName(){
	return this->Name;
}
/*
* x,y是左上的基准点
*/
void CGeoObject::setRect(int x1,int y1,int width,int height){
	this->crRect = new CRect();
	crRect.left = x1;
	crRect.top = y1;
	crRect.right = x1+width;
	crRect.bottom = y1+height;
}
/*
void CGeoObject::Draw(CDC *pDC){


}
*/