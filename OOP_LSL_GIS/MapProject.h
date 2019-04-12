#pragma once
class CMapProject
{
public:
	CMapProject(void);
	~CMapProject(void);
	float L0;
	float L1;
	float B0;
	float B1; // 投影区域坐标范围
	float a;//长半轴
	float e;//扁率
	void getXY(float L, float B, float* x, float* y);
	void getLB(float x, float y, float* L, float* B);
	void draw(CDC *pDC);
};

