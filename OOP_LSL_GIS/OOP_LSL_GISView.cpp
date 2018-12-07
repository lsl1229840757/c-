
// OOP_LSL_GISView.cpp : COOP_LSL_GISView ���ʵ��
//
#include "stdafx.h"

// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &COOP_LSL_GISView::OnFileOpen)
END_MESSAGE_MAP()

// COOP_LSL_GISView ����/����

COOP_LSL_GISView::COOP_LSL_GISView()
{
	// TODO: �ڴ˴���ӹ������
	map = NULL;
}

COOP_LSL_GISView::~COOP_LSL_GISView()
{
	if(map!= NULL)
		delete map;
}

BOOL COOP_LSL_GISView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// COOP_LSL_GISView ����

void COOP_LSL_GISView::OnDraw(CDC* pDC)
{
	COOP_LSL_GISDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc){
		return;
	}
	if(map != NULL)
		map->Draw(pDC);
	/*
	pDC->SetMapMode(MM_ANISOTROPIC);
	CPen penBlack;//����һ�����ʱ���
	penBlack.CreatePen(PS_SOLID,2,RGB(0,0,0));//��������
	CPen *pOldPen=pDC->SelectObject(&penBlack);
	CPoint p1 = CPoint();
	p1.x = 10;
	p1.y = 10;
	CPoint p2 = CPoint();
	p2.y = 2000;
	p2.y = 2000;
	CGeoPloyline cline = CGeoPloyline();
	cline.addPoint(p1);
	cline.addPoint(p2);
	//cline.Draw(pDC);
	
	CGeoPoint cp = CGeoPoint();
	cp.setPoint(p1);
	cp.Draw(pDC);

	ReleaseDC(pDC);
	*/

}

void COOP_LSL_GISView::readWHData(FILE *fp)
{
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
		//polyline->addPoint(CPoint(x1,y1));
		//polyline->addPoint(CPoint(x2,y2));
		//layer->addObject(polyline);
		((CGeoPloyline*)obj)->addPoint(CPoint(x1,y1));
		((CGeoPloyline*)obj)->addPoint(CPoint(x2,y2));
		layer->addObject(obj);
	}
}

void COOP_LSL_GISView::readCHData(FILE *fp)
{
	int x,y;
	if(map != NULL)
		delete map;
	map = new CGeoMap(1);
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);
	while( !feof(fp))
	{
		//CGeoPoint pt;
		CGeoObject *obj=new CGeoPoint;
		fscanf(fp,"%d%d",&x,&y);
		//pt.setPoint(CPoint(x,y));
		((CGeoPoint *)obj)->setPoint(CPoint(x,y));
		//layer->addObject(pt);
		layer->addObject(obj);
	}
}

void COOP_LSL_GISView::readCH1Data(FILE *fp)
{
	if(map != NULL)
		delete map;
	map = new CGeoMap(1);
	/*
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);
	while( !feof(fp))
	{
		//CGeoPoint pt;
		CGeoObject *obj=new CGeoPoint;
		fscanf(fp,"%d%d",&x,&y);
		//pt.setPoint(CPoint(x,y));
		((CGeoPoint *)obj)->setPoint(CPoint(x,y));
		//layer->addObject(pt);
		layer->addObject(obj);
	}
	*/
	// ��ʼ���ļ�ͷ
	int left,top,right,bottom;
	fscanf(fp,"%d,%d",&left,&top);
	fscanf(fp,"%d,%d",&right,&bottom);
	map->setRect(CRect(left,top,right,bottom));
	int layerNum;
	fscanf(fp,"%d",&layerNum);
	// ����layerָ��
	CGeoLayer* layers = new CGeoLayer[layerNum];
	int layerIndex = 0;
	// ��ͷ�ļ�����
	while(!feof(fp)){
			//��ʼ��ȡlayer
			int layerNameSize;
			fscanf(fp,"%d",&layerNameSize);
			char layerName[20];
			fscanf(fp,"%s",&layerName);
			int featureNum;
			fscanf(fp,"%d",&featureNum);
			for(int i=0;i<featureNum;i++){
					int featureType;
					fscanf(fp,"%d",&featureType);
					if(featureType==1){
						int a = 10;
					}
					switch (featureType)
					{
					case 1:
						//������
						while(!feof(fp)){
							int x1,y1,x2,y2;
							CGeoObject *obj=new CGeoPloyline;
							fscanf(fp,"%d,%d",&x1,&y1);
							if(x1==-99999){
								break;
							}
							x1 = x1/1000;
							y1 = y1/1000;
							fscanf(fp,"%d,%d",&x2,&y2);
							x2 = x2/1000;
							y2 = y2/1000;
							((CGeoPloyline*)obj)->addPoint(CPoint(x1,y1));
							((CGeoPloyline*)obj)->addPoint(CPoint(x2,y2));
							(layers+layerIndex)->addObject(obj);
						}
						break;
					case 2:
						//���ǵ�
						while(!feof(fp)){
							int x,y;
							CGeoObject *obj=new CGeoPoint;
							fscanf(fp,"%d,%d",&x,&y);
							if(x==-99999){
								break;
							}
							x = x/1000;
							y = y/1000;
							((CGeoPoint *)obj)->setPoint(CPoint(x,y));
							(layers+layerIndex)->addObject(obj);
						}
						break;
					case 4:
						//����ע��
						char name[20];
						fscanf(fp,"%s",&name);
						int x;
						fscanf(fp,"%d",&x);
						break;
					default:
						break;
					}
			}
			layerIndex++;
	}
	for(int i =0;i<layerNum;i++){
		map->addLayer((layers+i));
	}
}

// COOP_LSL_GISView ��ӡ

BOOL COOP_LSL_GISView::OnPreparePrinting(CPrintInfo* pInfo)
{

	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void COOP_LSL_GISView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void COOP_LSL_GISView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// COOP_LSL_GISView ���

#ifdef _DEBUG
void COOP_LSL_GISView::AssertValid() const
{
	CView::AssertValid();
}

void COOP_LSL_GISView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COOP_LSL_GISDoc* COOP_LSL_GISView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COOP_LSL_GISDoc)));
	return (COOP_LSL_GISDoc*)m_pDocument;
}
#endif //_DEBUG


// COOP_LSL_GISView ��Ϣ�������


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
	if( fileName.Right(9) == "wuhan.txt") //��ȡ�人��״
		readWHData(fp);
	else if( fileName.Right(10) == "china1.txt" )
		readCHData(fp);
	else if( fileName.Right(10) == "china1.dat" ) //��������
		readCH1Data(fp);
	fclose(fp);
	Invalidate();
}
