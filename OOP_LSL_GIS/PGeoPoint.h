#pragma once
#include "pgeoobject.h"
class CPGeoPoint :
	public CPGeoObject
{
public:
	CPGeoPoint(void);
	~CPGeoPoint(void);
	float L,B;

	void getPoint(float* L, float* B);
};

