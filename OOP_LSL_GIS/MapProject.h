#pragma once
class CMapProject
{
public:
	CMapProject(void);
	~CMapProject(void);
	float L0;
	float L1;
	float B0;
	float B1; // ͶӰ�������귶Χ
	float a;//������
	float e;//����
	void getXY(float L, float B, float* x, float* y);
	void getLB(float x, float y, float* L, float* B);
	void draw(CDC *pDC);
};

