
// OOP_LSL_GISView.cpp : COOP_LSL_GISView 类的实现
//
#include "stdafx.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OOP_LSL_GIS.h"
#endif

#include "OOP_LSL_GISDoc.h"
#include "OOP_LSL_GISView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COOP_LSL_GISView

IMPLEMENT_DYNCREATE(COOP_LSL_GISView, CView)

BEGIN_MESSAGE_MAP(COOP_LSL_GISView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &COOP_LSL_GISView::OnFileOpen)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// COOP_LSL_GISView 构造/析构

COOP_LSL_GISView::COOP_LSL_GISView()
{
	// TODO: 在此处添加构造代码
	map = NULL;
	isMapLoaded = false;
	clickNum = 0;
}

COOP_LSL_GISView::~COOP_LSL_GISView()
{
	if(map!= NULL)
		delete map;
}

BOOL COOP_LSL_GISView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COOP_LSL_GISView 绘制

void COOP_LSL_GISView::OnDraw(CDC* pDC)
{
	COOP_LSL_GISDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc){
		return;
	}
	if(map != NULL){
		map->Draw(pDC);
	}
}

void COOP_LSL_GISView::readCH1OPTD(FILE *fp){
	if(isMapLoaded == true){
		int totalNum;
		fscanf(fp,"%d",&totalNum);
		for(int i=0;i<totalNum;i++){
			char str[30];
			fscanf(fp,"%s",&str);
			CString layerName;
			layerName = str;
			CGeoLayer *layer = map->getLayerByName(layerName);
			int hasLine;
			fscanf(fp,"%d",&hasLine);
			if(hasLine==1){
				double lineWidth;
				fscanf(fp,"%lf",&lineWidth);
				int r,g,b;
				fscanf(fp,"%d, %d, %d",&r,&g,&b);
				for(int i=0;i<layer->getObjects().GetSize();i++){
					(layer->getObjects())[i]->r = r;
					(layer->getObjects())[i]->g = g;	
					(layer->getObjects())[i]->b = b;
					(layer->getObjects())[i]->lineWidth = lineWidth;
				}
			}
			int hasPolygon;
			fscanf(fp,"%d",&hasPolygon);
			if(hasPolygon==1){
				int r,g,b;
				fscanf(fp,"%d, %d, %d",&r,&g,&b);
				for(int i=0;i<layer->getObjects().GetSize();i++){
					(layer->getObjects())[i]->r = r;
					(layer->getObjects())[i]->g = g;	
					(layer->getObjects())[i]->b = b;
				}
			}
		}
	}
}


void COOP_LSL_GISView::readWHData(FILE *fp)
{
	isMapLoaded = false;
	int x1,y1,x2,y2;
	if(map != NULL)
		delete map;
	map = new CGeoMap(1);
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);
	while( !feof(fp))
	{
		//CGeoPolyline *polyline=new CGeoPolyline;
		CGeoObject *obj=new CGeoPloyline;
		fscanf(fp,"%d%d%d%d",&x1,&y1,&x2,&y2);
		x1 = x1+650;
		x2 = x2+650;
		((CGeoPloyline*)obj)->addPoint(CPoint(x1,y1));
		((CGeoPloyline*)obj)->addPoint(CPoint(x2,y2));
		layer->addObject(obj);
	}
}

void COOP_LSL_GISView::readCHData(FILE *fp)
{
	isMapLoaded = false;
	int x,y;
	if(map != NULL)
		delete map;
	map = new CGeoMap(1);
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);
	while( !feof(fp))
	{
		CGeoObject *obj=new CGeoPoint;
		fscanf(fp,"%d%d",&x,&y);
		((CGeoPoint *)obj)->setPoint(CPoint(x,y));
		layer->addObject(obj);
	}
}

void COOP_LSL_GISView::readCH1Data(FILE *fp)
{
	if(map != NULL)
		delete map;
	map = new CGeoMap(1);
	// 开始读文件头
	int left,top,right,bottom;
	fscanf(fp,"%d,%d",&left,&top);
	fscanf(fp,"%d,%d",&right,&bottom);
	map->setRect(CRect(left,top,right,bottom));
	int layerNum;
	fscanf(fp,"%d",&layerNum);
	// 创建layer指针
	CGeoLayer *layers = new CGeoLayer[layerNum];
	// 读头文件结束
	for(int j=0;j<layerNum;j++){
			//开始读取layer
			int layerNameSize;
			fscanf(fp,"%d",&layerNameSize);
			char str[30];
			fscanf(fp,"%s",&str);
			CString layerName;
			layerName = str;
			(layers+j)->setName(layerName);
			int featureNum;
			fscanf(fp,"%d",&featureNum);
			for(int i=0;i<featureNum;i++){
					int featureType;
					fscanf(fp,"%d",&featureType);
					CGeoObject *obj;
					switch (featureType)
					{
					case 1:
						//这是线
						obj = new CGeoPloyline;
						while(!feof(fp)){
							int x1,y1;
							fscanf(fp,"%d,%d",&x1,&y1);
							if(x1==-99999&&y1==-99999){
								(layers+j)->addObject(obj);
								break;
							}
							((CGeoPloyline*)obj)->addPoint(CPoint(x1,y1));
						}
						break;
					case 2:
						//这是面
						obj = new CGeoPolygon;
						while(!feof(fp)){
							int x,y;
							fscanf(fp,"%d,%d",&x,&y);
							if(x==-99999&&y==-99999){
								(layers+j)->addObject(obj);
								break;
							}
							((CGeoPolygon *)obj)->addPoint(CPoint(x,y));
						}
						break;
					case 4:
						//这是注记
						break;
					default:
						break;
					}
			}
		}
	for(int i =0;i<layerNum;i++){
		map->addLayer((layers+i));
	}
	isMapLoaded = true;
}

// COOP_LSL_GISView 打印

BOOL COOP_LSL_GISView::OnPreparePrinting(CPrintInfo* pInfo)
{

	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COOP_LSL_GISView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COOP_LSL_GISView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// COOP_LSL_GISView 诊断

#ifdef _DEBUG
void COOP_LSL_GISView::AssertValid() const
{
	CView::AssertValid();
}

void COOP_LSL_GISView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COOP_LSL_GISDoc* COOP_LSL_GISView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COOP_LSL_GISDoc)));
	return (COOP_LSL_GISDoc*)m_pDocument;
}
#endif //_DEBUG


// COOP_LSL_GISView 消息处理程序


void COOP_LSL_GISView::OnFileOpen()
{
	CFileDialog fDlg(true);
	if( fDlg.DoModal()!= IDOK) return;
	CString fileName = fDlg.GetPathName();

	USES_CONVERSION;
	FILE *fp=fopen(T2A(fileName),"r");
	if(fp==NULL)
	{
		return;
	}
	if( fileName.Right(9) == "wuhan.txt") //读取武汉线状
		readWHData(fp);
	else if( fileName.Right(10) == "china1.txt" )
		readCHData(fp);
	else if( fileName.Right(10) == "china1.dat" ) //测试数据
		readCH1Data(fp);
	else if(fileName.Right(10) == "china1.opt")
		readCH1OPTD(fp);	
	fclose(fp);
	Invalidate();
}


void COOP_LSL_GISView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	if( !isMapLoaded ) 
		return;
	CSize size;
	CSize size2;
	CPoint pt;	
	double ratio = 0.8; // 宽度缩放比例
	this->GetClientRect(&rectD);//取得客户区矩形区域大小
	size = rectD.Size();
	pt = rectD.CenterPoint();//取得客户区矩形区域中心点坐标

	pDC->SetMapMode(MM_ANISOTROPIC); //设置指定设备环境的映射方式
	size.SetSize(size.cx*ratio,size.cy*ratio);
	pDC->SetViewportExt(size);  //设定视口尺寸
	viewSize = size;
	pDC->SetViewportOrg(pt); //设置视口中心为坐标系原点
	viewPoint = pt;
	
	size2 = (map->getRect()).Size();  //设定窗口对应尺寸
	winSize = size2;
	pt =  (map->getRect()).CenterPoint(); //设置窗口中心为对应原点
	winPoint = pt;
	pDC->SetWindowExt(size2);   //设置窗口长宽
	pDC->SetWindowOrg(pt);	//设置窗口原点

	CSize size3 = pDC->GetWindowExt();
}


void COOP_LSL_GISView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isMapLoaded == false)
		return;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rc;
	this->GetClientRect(&rc);
	if(!rc.PtInRect(point))
		return;
	clickNum++;
	if(clickNum==2){
		upPoint = point;
		CRect rect = CRect(downPoint,upPoint);
		CDC* pDC = GetDC();
		CPoint downCPoint = CPoint((downPoint.x-viewPoint.x)*(winSize.cx/viewSize.cx)+winPoint.x,(downPoint.y-viewPoint.y)*(winSize.cy/viewSize.cy)+winPoint.y);
		CPoint upCPoint = CPoint((upPoint.x-viewPoint.x)*(winSize.cx/viewSize.cx)+winPoint.x,(upPoint.y-viewPoint.y)*(winSize.cy/viewSize.cy)+winPoint.y);
		rc = CRect(downCPoint,upCPoint);
		winSize = rc.Size();
		winPoint = rc.CenterPoint();
		map->crRect = rc;
		Invalidate();
	}
}


void COOP_LSL_GISView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(isMapLoaded==false)
		return;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	clickNum = 0;
	clickNum++;
	if(clickNum==1){
		downPoint = point;
	}
}
