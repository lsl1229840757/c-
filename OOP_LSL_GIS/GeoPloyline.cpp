#include "stdafx.h"
#include "GeoPloyline.h"


CGeoPloyline::CGeoPloyline(void)
{
}


CGeoPloyline::~CGeoPloyline(void)
{
}
void CGeoPloyline::Draw(CDC* pDC){
	CPen pen;
	pen.CreatePen(PS_SOLID,lineWidth>0?lineWidth:1,RGB(r,g,b));
	CPen *oldPen = pDC->SelectObject(&pen);
//	DrawDDA(pDC);
	for (int i = 0; i < pts.GetSize(); i++)
	{
		if(i==0){
			pDC->MoveTo(pts[i]);
		}else{
			pDC->LineTo(pts[i]);
		}
	}
	if(clipPts.GetSize()!=0){
		for (int i = 0; i < clipPts.GetSize(); i++)
		{
			if(i==0){
				pDC->MoveTo(clipPts[i]);
			}else{
				pDC->LineTo(clipPts[i]);
			}
		}
	}
}
int CGeoPloyline::getSize(){
	return pts.GetSize();
}
void CGeoPloyline::addPoint(CPoint pt){
	this->pts.Add(pt);
}
void CGeoPloyline::DrawDDA(CDC *pDC){
	float x = pts[0].x;
	float y = pts[0].y;
	float dx = pts[1].x - x;
	float dy = pts[1].y - y;
	int n = abs((int)dx) > abs((int)dy) ? abs((int)dx) : abs((int)dy);
	dx = dx / n;
	dy = dy / n;
	for(int i=0;i<n;i++){
		pDC->SetPixel(x,y,RGB(255,0,0));
		x = x + dx;
		y = y + dy;
	}
}

int CGeoPloyline::GetCode(CRect wcRect1, CPoint pt1)
{
	int code = 0;
	if(pt1.x<wcRect1.left) //左边线的左侧
		code+=1;
	else if(pt1.x>wcRect1.right)//右边线右侧
		code+=2;
	else if(pt1.y<wcRect1.bottom)//下边线下侧
		code+=4;
	else if(pt1.y>wcRect1.top)//上边线上侧
		code+=8;
	return code;
}


void CGeoPloyline::ClipObj(CRect wcRect1)
{
	clipPts.RemoveAll();
	CPoint pt1,pt2;
	int code1,code2;
	int size = pts.GetSize();
	for(int i=0;i<size-1;i++){
		pt1 = pts[i];
		pt2 = pts[i+1];
		code1 = 1;
		code2 = 2;
		//while(code1!=0 && code2!=0){
			code1 = GetCode(wcRect1, pt1);
			code2 = GetCode(wcRect1, pt2);
			if(code1==0 && code2==0){
				// 明显在里面
				clipPts.Add(pt1);
				clipPts.Add(pt2);
			}else if((code1 & code2)!=0){
				//明显在外面
				break;
			}else{
				
			}
		//}
	}
	if(clipPts.GetSize()!=0){
		r = 255;
		g = 0;
		b = 0;
	}
}
