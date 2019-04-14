#include "stdafx.h"
#include "MapProject.h"


CMapProject::CMapProject(void)
{
	mapScale = 1e6;
	showMapScale = 1e6;
}


CMapProject::~CMapProject(void)
{
}

void CMapProject::getXY(float L, float B, float* x, float* y){

}

void CMapProject::getLB(float x, float y, float* L, float* B)
{
}


void CMapProject::draw(CDC* pDC)
{
}


void CMapProject::Draw(CDC* pDC, CRect wcRect)
{
	float xExtends = float(wcRect.Width())/mapScale;
	float yExtends = float(-wcRect.Height())/mapScale;
	//以5度划分经纬网
	int degree = 5;
	int m = xExtends/degree;
	int n = yExtends/degree;
	int i,j = 0;
	int left = wcRect.left;
	int right = wcRect.right;
	int top = wcRect.top;
	int bottom = wcRect.bottom;
	float x1,y1,x2,y2 = 0;
	CPoint p1,p2;
	int xStart = left*1.0/mapScale/degree;
	CString infoStr;
	pDC->SetBkMode(TRANSPARENT);
	for(i=0;i<m+2;i++){
		for(j=0;j<yExtends-1;j++){
			x1 = (xStart+i)*degree;
			y1 = top*1.0/mapScale - j;
			if(x1<left*1.0/mapScale)
				x1 = left*1.0/mapScale;
			if(x1>right*1.0/mapScale)
				x1 = right*1.0/mapScale;
			getXY(x1 * mapScale,y1 * mapScale,&x2,&y2);
			p1.x = x2;
			p1.y = y2;
			if(j==0)
				pDC->MoveTo(p1);
			else
				pDC->LineTo(p1);
		}
		infoStr.Format(_T("%d"),int(x1));
		pDC->TextOut(p1.x,p1.y,infoStr);
	}
	int yStart = bottom*1.0/mapScale/degree;
	for(i=0;i<n+4;i++){
		for(j=0;j<xExtends;j++){
			y1 = (yStart+i)*1.0*degree;
			x1 = left*1.0/mapScale + j;
			if(y1<bottom*1.0/mapScale)
				y1 = bottom*1.0/mapScale;
			if(y1>top*1.0/mapScale)
				y1 = top*1.0/mapScale;
			getXY(x1 * mapScale,y1 * mapScale,&x2,&y2);
			p1.x = x2;
			p1.y = y2;
			if(j==0)
				pDC->MoveTo(p1);
			else
				pDC->LineTo(p1);
		}
		infoStr.Format(_T("%d"),int(y1));
		pDC->TextOut(p1.x,p1.y,infoStr);
	}
}
