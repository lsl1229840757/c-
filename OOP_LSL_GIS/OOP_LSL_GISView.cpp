
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
END_MESSAGE_MAP()

// COOP_LSL_GISView ����/����

COOP_LSL_GISView::COOP_LSL_GISView()
{
	// TODO: �ڴ˴���ӹ������

}

COOP_LSL_GISView::~COOP_LSL_GISView()
{
}

BOOL COOP_LSL_GISView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// COOP_LSL_GISView ����

void COOP_LSL_GISView::OnDraw(CDC* /*pDC*/)
{
	COOP_LSL_GISDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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
