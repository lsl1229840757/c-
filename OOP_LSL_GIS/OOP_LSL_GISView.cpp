
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
END_MESSAGE_MAP()

// COOP_LSL_GISView 构造/析构

COOP_LSL_GISView::COOP_LSL_GISView()
{
	// TODO: 在此处添加构造代码

}

COOP_LSL_GISView::~COOP_LSL_GISView()
{
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
	pDC->SetMapMode(MM_ANISOTROPIC);
	CPen penBlack;//定义一个画笔变量
	 penBlack.CreatePen(PS_SOLID,2,RGB(0,0,0));//创建画笔
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
		cline.Draw(pDC);
		ReleaseDC(pDC);
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
