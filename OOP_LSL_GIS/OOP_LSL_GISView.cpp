
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
//	ON_COMMAND(ZoomIn, &COOP_LSL_GISView::OnZoomin)
//	ON_COMMAND(AFX_ID_PREVIEW_ZOOMIN, &COOP_LSL_GISView::OnAfxIdPreviewZoomin)
ON_COMMAND(ZoomIn, &COOP_LSL_GISView::OnZoomin)
ON_UPDATE_COMMAND_UI(ZoomIn, &COOP_LSL_GISView::OnUpdateZoomin)
ON_COMMAND(FullView, &COOP_LSL_GISView::OnFullview)
ON_WM_MOUSEMOVE()
ON_COMMAND(generatePoint, &COOP_LSL_GISView::OnGeneratepoint)
ON_COMMAND(clipButton, &COOP_LSL_GISView::OnClipbutton)
ON_UPDATE_COMMAND_UI(clipButton, &COOP_LSL_GISView::OnUpdateClipbutton)
END_MESSAGE_MAP()

// COOP_LSL_GISView 构造/析构

COOP_LSL_GISView::COOP_LSL_GISView()
	: isClip(false)
{
	// TODO: 在此处添加构造代码
	map = NULL;
	isMapLoaded = false;
	clickNum = 0;
	isZoomIn = false;
	isClip = false;
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


void COOP_LSL_GISView::readFillTest(FILE* fp)
{
	isMapLoaded = false;
		int x,y;
	if(map != NULL)
		delete map;
	map = new CGeoMap(1);
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);
	while(!feof(fp)){
		int n; //多边形个数
		int m; //点数
		int color;
		CGeoObject *poly = new CGeoPolygon;
		layer->addObject(poly);
		fscanf(fp,"%d",&n);
		for(int i=0;i<n;i++){
			fscanf(fp,"%d",&m);
			for(int j=0;j<m;j++){
				fscanf(fp,"%d%d",&x,&y);
				if(i==0){
					((CGeoPolygon *)poly)->addPoint(CPoint(x,y)); // 这里是生成同种多边形的边界
				}
			}
			
		}
		fscanf(fp,"%d%d",&x,&y); // 读取种子点
		((CGeoPolygon *)poly)->seeds.Add(CPoint(x,y));
		fscanf(fp,"%d",&color); // 读取颜色
		poly->r = byte((color >> 16) & 255);
		poly->g = byte((color>> 8) & 255);
		poly->b = byte((color >> 0) & 255);
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

void COOP_LSL_GISView::readClipData(FILE * fp)
{
	if(map != NULL)
		delete map;
	map = new CGeoMap(1);
	// 开始读文件头
	int left,top,right,bottom;
	fscanf(fp,"%d%d",&left,&top);
	fscanf(fp,"%d%d",&right,&bottom);
	map->setRect(CRect(left,top,right,bottom));
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);
	while( !feof(fp)){
		int num;
		fscanf(fp,"%d",&num);
		CGeoObject *obj = new CGeoPloyline;
		for(int i=0;i<num;i++){
			int x,y;
			fscanf(fp,"%d%d",&x,&y);
			((CGeoPloyline *)obj)->addPoint(CPoint(x,y));
		}
		layer->addObject(obj);
	}
	winRect = map->crRect;
	isMapLoaded=true;
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
	//创建layer指针
	//CGeoLayer *layers = new CGeoLayer[layerNum];
	// 读头文件结束
	for(int j=0;j<layerNum;j++){
			CGeoLayer *layers = new CGeoLayer;
			//开始读取layer
			int layerNameSize;
			fscanf(fp,"%d",&layerNameSize);
			char str[30];
			fscanf(fp,"%s",&str);
			CString layerName;
			layerName = str;
			layers->setName(layerName);
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
								layers->addObject(obj);
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
								layers->addObject(obj);
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
			map->addLayer(layers);
		}
	winRect = map->crRect;
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
	else if(fileName.Right(12) == "chnCity.xlsx")
		readExcel(fileName);
	else if(fileName.Right(11) == "chnCity.xls")
		readExcel(fileName);
	else if(fileName.Right(15) == "chnFillTest.txt")
		readFillTest(fp);
	else if(fileName.Right(12) == "clipData.txt")
		readClipData(fp);

	fclose(fp);
	Invalidate();
}
void COOP_LSL_GISView::readTxt(FILE* fp){
	int x,x1,y,y1;
	fscanf(fp,"%d,%d,%d,%d",&x1,&y1,&x,&y);
}

void COOP_LSL_GISView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	if(!isMapLoaded){
		return;
	}
	CSize size;
	CSize size2;
	CPoint pt;	
	double ratio = 0.6; // 宽度缩放比例
	this->GetClientRect(&rectD);//取得客户区矩形区域大小
	size = rectD.Size();
	pt = rectD.CenterPoint();//取得客户区矩形区域中心点坐标

	pDC->SetMapMode(MM_ANISOTROPIC); //设置指定设备环境的映射方式
	//size.SetSize(size.cx*ratio,size.cy);
	pDC->SetViewportExt(size);  //设定视口尺寸
	pDC->SetViewportOrg(pt); //设置视口中心为坐标系原点
	mapRatio = -((double)size.cx)/size.cy;
	size2 = winRect.Size();  //设定窗口对应尺寸
	pt =  winRect.CenterPoint(); //设置窗口中心为对应原点
	size2.SetSize(size2.cy*mapRatio,size2.cy);
	pDC->SetWindowExt(size2);   //设置窗口长宽
	pDC->SetWindowOrg(pt);	//设置窗口原点
	CSize size3 = pDC->GetWindowExt();
	
}


void COOP_LSL_GISView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isMapLoaded == false)
		return;
	if(isZoomIn==true){
		CRect rc;
		this->GetClientRect(&rc);
		if(!rc.PtInRect(point))
			return;
		clickNum++;
		if(clickNum==2){
			upPoint = point;
			CDC* pDC = GetDC();
			OnPrepareDC(pDC);
			pDC -> DPtoLP(&downPoint);
			pDC -> DPtoLP(&upPoint);
			int xmax = downPoint.x>upPoint.x?downPoint.x:upPoint.x;
			int ymax = downPoint.y>upPoint.y?downPoint.y:upPoint.y;
			int xmin = downPoint.x<upPoint.x?downPoint.x:upPoint.x;
			int ymin = downPoint.y<upPoint.y?downPoint.y:upPoint.y;
			rc = CRect(xmin,ymax,xmax,ymin);
			winRect = rc;
			Invalidate();
		}
	}else if(isClip==true){
		CRect rc;
		this->GetClientRect(&rc);
		if(!rc.PtInRect(point))
			return;
		clickNum++;
		if(clickNum==2){
			upPoint = point;
			CDC* pDC = GetDC();
			OnPrepareDC(pDC);
			pDC -> DPtoLP(&downPoint);
			pDC -> DPtoLP(&upPoint);
			int xmax = downPoint.x>upPoint.x?downPoint.x:upPoint.x;
			int ymax = downPoint.y>upPoint.y?downPoint.y:upPoint.y;
			int xmin = downPoint.x<upPoint.x?downPoint.x:upPoint.x;
			int ymin = downPoint.y<upPoint.y?downPoint.y:upPoint.y;
			rc = CRect(xmin,ymax,xmax,ymin);
			map->clipMap(rc);
			Invalidate();
		}
	}
}


void COOP_LSL_GISView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(isMapLoaded==false)
		return;
	if(isZoomIn==false&&isClip==false)
		return;
	clickNum=0;
	clickNum++;
	if(clickNum==1){
		downPoint = point;
	}
}

void COOP_LSL_GISView::OnZoomin()
{
	// TODO: 在此添加命令处理程序代码SL
	if (isZoomIn == false){
		isZoomIn = true;
	}
	else if(isZoomIn == true){
		isZoomIn = false;
	}
}
void COOP_LSL_GISView::OnUpdateZoomin(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isZoomIn==true);
}

void COOP_LSL_GISView::OnClipbutton()
{
	isClip?isClip=false:isClip=true;
}


void COOP_LSL_GISView::OnUpdateClipbutton(CCmdUI *pCmdUI)
{
		pCmdUI->SetCheck(isClip==true);
}


void COOP_LSL_GISView::OnFullview()
{
	winRect = map->crRect;
	Invalidate();
}


void COOP_LSL_GISView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!(clickNum==1))
		return;
	CDC *pDC = GetDC();
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->Rectangle(downPoint.x,downPoint.y,point.x,point.y);
	upPoint = point;
	pDC->Rectangle(downPoint.x,downPoint.y,upPoint.x,upPoint.y);
}

void COOP_LSL_GISView::readExcel(CString path){
	if(isMapLoaded==false)
		return;
	CApplication  m_oExcelApp;
	CWorksheet    m_oWorkSheet;
	CWorkbook     m_oWorkBook;
	CWorkbooks    m_oWorkBooks;
	CWorksheets   m_oWorkSheets;
	CRange        m_oCurrRange;
    LPDISPATCH lpDisp = NULL;
    COleVariant covTrue((short)TRUE);
    COleVariant covFalse((short)FALSE);
    COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
    CRange  oCurCell;
 
    // 创建连接
    if (!m_oExcelApp.CreateDispatch(_T("Excel.Application")))
    {
        ::MessageBox(NULL, _T("创建Excel服务失败!"), _T("错误提示!"), MB_OK | MB_ICONERROR);
        return;
    }
 
    m_oWorkBooks.AttachDispatch(m_oExcelApp.get_Workbooks());
    // 打开文件
	lpDisp = m_oWorkBooks.Open(path,
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing),
        _variant_t(vtMissing));
 
    m_oWorkBook.AttachDispatch(lpDisp);
    m_oWorkSheets.AttachDispatch(m_oWorkBook.get_Worksheets());
    //lpDisp = m_oWorkBook.get_ActiveSheet();
    //m_oWorkSheet.AttachDispatch(lpDisp);
 
    // 获取第几个sheet表就写几
    m_oWorkSheet.AttachDispatch(m_oWorkSheets.get_Item(_variant_t((long)1)), TRUE);
 
    // 获取行数和列数
    CRange usedRange;
    CRange mRange;
    usedRange.AttachDispatch(m_oWorkSheet.get_UsedRange());
    mRange.AttachDispatch(usedRange.get_Rows(), TRUE);
	long nCount = mRange.get_Count();
    mRange.ReleaseDispatch();
    mRange.AttachDispatch(usedRange.get_Columns(), TRUE);
	long nLines = mRange.get_Count();
    usedRange.ReleaseDispatch();
    mRange.ReleaseDispatch();
 
    // 读取
    COleVariant vResult;
    CString strData = _T("");
	CGeoLayer* layer = new CGeoLayer;
	for(long i = 1;i<=nCount;i++){
		// 跳过行
		if(i==1)
			continue;
		CGeoObject* anno = new CGeoAnno;
		int x,y;
		for (int j = 1; j <= nLines; j++)
		{
			m_oCurrRange.AttachDispatch(m_oWorkSheet.get_Cells());
			m_oCurrRange.AttachDispatch(m_oCurrRange.get_Item(COleVariant((long)i), COleVariant((long)j)).pdispVal);
 
			vResult = m_oCurrRange.get_Value2();
			if (vResult.vt == VT_BSTR)
			{
				strData = vResult.bstrVal;
				((CGeoAnno*)anno)->setName(strData);
			}
			else if (vResult.vt == VT_R8)
			{
				if(j==2)
					x = (int)vResult.dblVal;
				if(j==3)
					y =(int)vResult.dblVal;
			}
			else
			{
				AfxMessageBox(_T("数据类型错误!"));
			}
			m_oCurrRange.ReleaseDispatch();
		}
		((CGeoAnno*)anno)->setPoint(x,y);
		layer->addObject(anno);
		map->addLayer(layer);
	}
    m_oWorkBooks.Close();
    m_oExcelApp.Quit();
 
    m_oCurrRange.ReleaseDispatch();
    m_oWorkSheet.ReleaseDispatch();
    m_oWorkSheets.ReleaseDispatch();
    m_oWorkBook.ReleaseDispatch();
    m_oWorkBooks.ReleaseDispatch();
    m_oExcelApp.ReleaseDispatch();

}

// 随机生成点
void COOP_LSL_GISView::OnGeneratepoint()
{
	map = new CGeoMap(1);
	CGeoObject *polygon = new CGeoPolygon();
	CArray<CPoint,CPoint> pts;
	pts.Add(CPoint(100, 100));
	pts.Add(CPoint(50, 150));
	pts.Add(CPoint(100, 125));
	pts.Add(CPoint(150, 150));
	pts.Add(CPoint(100, 100));
	for (int i = 0; i < pts.GetSize(); i++)
	{
		((CGeoPolygon *)polygon)->addPoint(pts.GetAt(i));
	}
	CGeoLayer *layer = new CGeoLayer();
	int size = ((CGeoPolygon *)polygon)->pts.GetSize();
	CGeoObject *point = new CGeoPoint;
	for(int i=0;i<size-2;i++){
		CPoint p1 = ((CGeoPolygon *)polygon)->pts[i];
		CPoint p2 = ((CGeoPolygon *)polygon)->pts[i+1];
		CPoint p3 = ((CGeoPolygon *)polygon)->pts[i+2];
		if(judgeDirection(p1,p2,p3)){
			CPoint inPoint;
			int x = (p1.x+p2.x+p3.x)/3;
			int y = (p1.y+p2.y+p3.y)/3;
			inPoint.x = x;
			inPoint.y = y;
			if(PtInPolygon(inPoint,((CGeoPolygon *)polygon)->pts)){
				((CGeoPoint *)point)->setPoint(inPoint);
				break;
			}
		}
	}
	point->r = 255;
	point->g = 0;
	point->b = 0;
	layer->addObject(polygon);
	layer->addObject(point);
	map->addLayer(layer);
	Invalidate();
}


double COOP_LSL_GISView::getCrossProducts(CPoint p1, CPoint p2, double oldvx,double oldvy )
{
	double nvx = p2.x - p1.x;
	double nvy = p2.y - p1.y;
	return oldvx*nvy + nvx*oldvy;
}
// 返回true就是逆时针，返回false就是顺时针，注意电脑坐标轴有点不一样
bool COOP_LSL_GISView::judgeDirection(CPoint p1, CPoint p2,CPoint p3)
{
	double x1 = p2.x-p1.x;
	double y1 = p2.y-p1.y;
	double x2 = p3.x-p2.x;
	double y2 = p3.y-p2.y;
	double crossProduct = x1 * y2 - x2 * y1;
	if(crossProduct<0){
		return true;
	}
	return false;
}
//作用：判断点是否在多边形内
//p指目标点， ptPolygon指多边形的点集合， nCount指多边形的边数
bool COOP_LSL_GISView::PtInPolygon (CPoint p, CArray<CPoint ,CPoint>& ptPolygon)  
{  
	int nCount = ptPolygon.GetSize();
	// 交点个数  
	int nCross = 0;  
	for (int i = 0; i < nCount; i++)   
	{  
		CPoint p1 = ptPolygon[i];  
		CPoint p2 = ptPolygon[(i + 1) % nCount];// 点P1与P2形成连线  
 
		if ( p1.y == p2.y )  
			continue;  
		if ( p.y < min(p1.y, p2.y) )  
			continue;  
		if ( p.y >= max(p1.y, p2.y) )  
			continue;  
		// 求交点的x坐标（由直线两点式方程转化而来）   
 
		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;  
 
		// 只统计p1p2与p向右射线的交点  
		if ( x > p.x )  
		{  
			nCross++;  
		}  
 
	}  
 
	// 交点为偶数，点在多边形之外  
	// 交点为奇数，点在多边形之内
	if ((nCross % 2) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
} 
