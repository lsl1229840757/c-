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
	virtual void getXY(float L, float B, float* x, float* y);
	virtual void getLB(float x, float y, float* L, float* B);
	void draw(CDC *pDC);
	void Draw(CDC* pDC, CRect wcRect);
	// mapScale是一度占地图外界矩形多宽
	float mapScale;
	float showMapScale;
};

