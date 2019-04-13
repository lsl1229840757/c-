#include "stdafx.h"
#include "GeoPloyline.h"         



CGeoPloyline::CGeoPloyline(void)
{
}

CGeoPloyline::~CGeoPloyline(void)
{
}

void CGeoPloyline::Draw(CDC* pDC,CMapProject *mapPrj){
	for (int i = 0; i < gpts.GetSize(); i++)
	{
		CGeoPoint*p = gpts[i];
		if(i==0){
			pDC->MoveTo(CPoint((int)p->L,(int)p->B));
		}else{
			pDC->LineTo(CPoint((int)p->L,(int)p->B));
		}
	}
}
void CGeoPloyline::Draw(CDC* pDC){
	CPen pen;
	pen.CreatePen(PS_SOLID,lineWidth>0?lineWidth:1,RGB(r,g,b));
	CPen penb;
	penb.CreatePen(PS_SOLID, 100, RGB(0,255,0));
	CPen *oldPen = pDC->SelectObject(&pen);
	//DrawDDA(pDC);
	// 系统贝塞尔选择绿色
	//oldPen = pDC->SelectObject(&penb); 取消贝塞尔
	//pDC->PolyBezier(&pts[0], pts.GetSize()/3*3-2);
	drawBezier(pDC, pts);
	// 选择回来
	pDC->SelectObject(oldPen);
	//for (int i = 0; i < pts.GetSize(); i++)
	//{
	//	if(i==0){
	//		pDC->MoveTo(pts[i]);
	//	}else{
	//		pDC->LineTo(pts[i]);
	//	}
	//}
	
	if(clipPts.GetSize()!=0){
		oldPen = pDC->SelectObject(&penb);

		pDC->PolyBezier(&clipPts[0], clipPts.GetSize()/3*3-2);
		//drawBezier(pDC, clipPts);
		// 选择回来
		pDC->SelectObject(oldPen);
		/*for (int i = 0; i < clipPts.GetSize(); i++)
		{
			if(i==0){
				pDC->MoveTo(clipPts[i]);
			}else{
				pDC->LineTo(clipPts[i]);
			}
		}*/
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


void CGeoPloyline::drawBezier(CDC * pDC, CArray<CPoint,CPoint>& pts)
{
	int NUM_STEPS = 30;
	CArray<CPoint,CPoint> tempArray;
	int size = pts.GetSize();
	if(size%3!=1)
		size = size/3*3-2;
	for(int i=0;i<size-1;i+=3){
		CPoint p1 = pts[i];
		CPoint p2 = pts[i+1];
		CPoint p3 = pts[i+2];
		CPoint p4 = pts[i+3];
		long x1 = p1.x;
		long y1 = p1.y;
		long x2 = p2.x;
		long y2 = p2.y;
		long x3 = p3.x;
		long y3 = p3.y;
		long x4 = p4.x;
		long y4 = p4.y;
		CPoint tmp0(x1,y1);
		tempArray.Add(tmp0); 
		double dx1 = x2 - x1;  
		double dy1 = y2 - y1;  
		double dx2 = x3 - x2;  
		double dy2 = y3 - y2;  
		double dx3 = x4 - x3;  
		double dy3 = y4 - y3;  
 
		double subdiv_step  = 1.0 / (NUM_STEPS + 1);  
		double subdiv_step2 = subdiv_step*subdiv_step;  
		double subdiv_step3 = subdiv_step*subdiv_step*subdiv_step;  
 
		double pre1 = 3.0 * subdiv_step;  
		double pre2 = 3.0 * subdiv_step2;  
		double pre4 = 6.0 * subdiv_step2;  
		double pre5 = 6.0 * subdiv_step3;  
 
		double tmp1x = x1 - x2 * 2.0 + x3;  
		double tmp1y = y1 - y2 * 2.0 + y3;  
 
		double tmp2x = (x2 - x3)*3.0 - x1 + x4;  
		double tmp2y = (y2 - y3)*3.0 - y1 + y4;  
 
		double fx = x1;  
		double fy = y1;  
 
		double dfx = (x2 - x1)*pre1 + tmp1x*pre2 + tmp2x*subdiv_step3;  
		double dfy = (y2 - y1)*pre1 + tmp1y*pre2 + tmp2y*subdiv_step3;  
 
		double ddfx = tmp1x*pre4 + tmp2x*pre5;  
		double ddfy = tmp1y*pre4 + tmp2y*pre5;  
 
		double dddfx = tmp2x*pre5;  
		double dddfy = tmp2y*pre5;  
 
		int step = NUM_STEPS;  
 
		while(step--)  
		{  
			fx   += dfx;  
			fy   += dfy;  
			dfx  += ddfx;  
			dfy  += ddfy;  
			ddfx += dddfx;  
			ddfy += dddfy;  
			CPoint tmp1(fx,fy);
			tempArray.Add(tmp0); 
		}  
		CPoint tmp2(x4,y4);
		tempArray.Add(tmp0);
	}
	for (int i = 0; i < tempArray.GetSize(); i++)
	{
		if(i==0){
			pDC->MoveTo(tempArray[i]);
		}else{
			pDC->LineTo(tempArray[i]);
		}
	}
}


void CGeoPloyline::addGeoPoint(CGeoPoint * p)
{
	this->gpts.Add(p);
}
