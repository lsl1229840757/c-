#pragma once
#include "mapproject.h"
class CMapProjectionMercator :
	public CMapProject
{
public:
	CMapProjectionMercator(void);
	~CMapProjectionMercator(void);
	void getXY(float L, float B, float* x, float* y);
	void getLB(float x, float y, float* L, float* B);
};

