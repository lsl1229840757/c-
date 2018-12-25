#include "stdafx.h"
#include "GeoAnno.h"


CGeoAnno::CGeoAnno(void)
{
}


CGeoAnno::~CGeoAnno(void)
{
}
void CGeoAnno::setPoint(int x,int y){
	this->pt = CPoint(x,y);
}
void CGeoAnno::setName(CString name){
	this->name = name;
}


void CGeoAnno::Draw(CDC *pDC){
		CFont font;
		font.CreatePointFont(300000, _T("宋体"));
		//载入字体
		CFont* pOldFont;
		pOldFont = pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		//绘制字
		pDC->TextOut(pt.x, pt.y, this->name);
		//载出字体
		pDC->SelectObject(pOldFont);
}