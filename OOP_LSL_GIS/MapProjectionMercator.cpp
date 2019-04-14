#include "stdafx.h"
#include "MapProjectionMercator.h"
#include <cmath>
#define M_PI 3.14159265358979323846
CMapProjectionMercator::CMapProjectionMercator(void)
{
}


CMapProjectionMercator::~CMapProjectionMercator(void)
{
}
void CMapProjectionMercator::getXY(float L, float B, float* x, float* y){
	L/=1e6;
	B/=1e6;
	*x = L * 20037508.34 / 180;
	*y = log(tan((90 + B) *  M_PI/ 360))/(M_PI / 180);  
	*y = (*y) * 20037508.34 / 180;
}
void CMapProjectionMercator::getLB(float x, float y, float* L, float* B){

}