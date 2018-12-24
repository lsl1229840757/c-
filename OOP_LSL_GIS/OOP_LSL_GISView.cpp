
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
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
//	ON_COMMAND(ZoomIn, &COOP_LSL_GISView::OnZoomin)
//	ON_COMMAND(AFX_ID_PREVIEW_ZOOMIN, &COOP_LSL_GISView::OnAfxIdPreviewZoomin)
ON_COMMAND(ZoomIn, &COOP_LSL_GISView::OnZoomin)
ON_UPDATE_COMMAND_UI(ZoomIn, &COOP_LSL_GISView::OnUpdateZoomin)
ON_COMMAND(FullView, &COOP_LSL_GISView::OnFullview)
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// COOP_LSL_GISView ����/����

COOP_LSL_GISView::COOP_LSL_GISView()
{
	// TODO: �ڴ˴���ӹ������
	map = NULL;
	isMapLoaded = false;
	clickNum = 0;
	isZoomIn = false;
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
	// ��ʼ���ļ�ͷ
	int left,top,right,bottom;
	fscanf(fp,"%d,%d",&left,&top);
	fscanf(fp,"%d,%d",&right,&bottom);
	map->setRect(CRect(left,top,right,bottom));
	int layerNum;
	fscanf(fp,"%d",&layerNum);
	//����layerָ��
	//CGeoLayer *layers = new CGeoLayer[layerNum];
	// ��ͷ�ļ�����
	for(int j=0;j<layerNum;j++){
			CGeoLayer *layers = new CGeoLayer;
			//��ʼ��ȡlayer
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
						//������
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
						//������
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
						//����ע��
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
	else if(fileName.Right(10) == "china1.opt")
		readCH1OPTD(fp);	
	else if(fileName.Right(12) == "chnCity.xlsx")
		readExcel(fileName);
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
	double ratio = 0.6; // ������ű���
	this->GetClientRect(&rectD);//ȡ�ÿͻ������������С
	size = rectD.Size();
	pt = rectD.CenterPoint();//ȡ�ÿͻ��������������ĵ�����

	pDC->SetMapMode(MM_ANISOTROPIC); //����ָ���豸������ӳ�䷽ʽ
	size.SetSize(size.cx*0.4,size.cy*ratio);
	pDC->SetViewportExt(size);  //�趨�ӿڳߴ�
	pDC->SetViewportOrg(pt); //�����ӿ�����Ϊ����ϵԭ��

	size2 = winRect.Size();  //�趨���ڶ�Ӧ�ߴ�
	pt =  winRect.CenterPoint(); //���ô�������Ϊ��Ӧԭ��
	pDC->SetWindowExt(size2);   //���ô��ڳ���
	pDC->SetWindowOrg(pt);	//���ô���ԭ��

	CSize size3 = pDC->GetWindowExt();
}


void COOP_LSL_GISView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isMapLoaded == false)
		return;
	if(isZoomIn==false)
		return;
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
}


void COOP_LSL_GISView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(isMapLoaded==false)
		return;
	if(isZoomIn==false)
		return;
	clickNum=0;
	clickNum++;
	if(clickNum==1){
		downPoint = point;
	}
}

void COOP_LSL_GISView::OnZoomin()
{
	// TODO: �ڴ���������������SL
	if (isZoomIn == false){
		isZoomIn = true;
	}
	else if(isZoomIn == true){
		isZoomIn = false;
	}
}
void COOP_LSL_GISView::OnUpdateZoomin(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(isZoomIn==true);
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


void COOP_LSL_GISView::readExcel(CString path)
{
	CoInitialize(NULL);   //��ʼ��COM���
	_ConnectionPtr connection;
	try
    {
		CString strPath;
		CString str1;
		CString str2;
		str1 = "Provider=Microsoft.Ace.OLEDB.12.0;Data Source=";
		str2 = ";Extended Properties='Excel 8.0;HDR=Yes;IMEX=2'";
		strPath = str1+path+str2;
        connection.CreateInstance(__uuidof(Connection));   //����Connection����
        connection->Open(_bstr_t(strPath), "", "", adModeUnknown);
    }
    catch (_com_error e)
    {
		MessageBox(e.ErrorMessage());
	}
	_RecordsetPtr pRecordset;
    char szSQL[] = "Select * From [Sheet1$]";
	try
    {
        pRecordset.CreateInstance(__uuidof(Recordset));	//����Recordset����
        pRecordset->Open(_bstr_t(szSQL), _variant_t((IDispatch*)connection, TRUE),
            adOpenUnspecified, adLockUnspecified, adCmdUnknown);
    }
    catch (_com_error e)
    {
        connection->Close();
    }
	if (pRecordset == NULL)
    {
        connection->Close();
    }

	  if (!pRecordset->BOF)
    {
        try
        {
            pRecordset->MoveFirst();
			while (!pRecordset->adoEOF)
            {
                _variant_t vtName = pRecordset->Fields->GetItem("Name")->Value;
                _variant_t vtX = pRecordset->Fields->GetItem("X")->Value;
				 _variant_t vtY = pRecordset->Fields->GetItem("Y")->Value;
                pRecordset->MoveNext();
            }
        }
        catch (_com_error e)
        {
			e.Error();
        }
	}
}