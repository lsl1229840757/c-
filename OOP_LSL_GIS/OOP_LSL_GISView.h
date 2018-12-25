
// OOP_LSL_GISView.h : COOP_LSL_GISView 类的接口
//

#pragma once
#include "GeoLayer.h"
#include "GeoObject.h"
#include "GeoMap.h"
#include "GeoPoint.h"
#include "GeoPloyline.h"
#include "GeoPolygon.h"
#include "CWorkbook.h"                //管理单个工作表
#include "CWorkbooks.h"         //统管所有的工作簿
#include "CApplication.h"          //Excel应用程序类,管理我们打开的这整个Excel应用
#include "CRange.h"               //区域类，对EXcel的大部分操作都要和这个打招呼
#include "CWorksheet.h"            //工作薄中的单个工作表
#include "CWorksheets.h"            //统管当前工作簿中的所有工作表
#include "GeoAnno.h"
#pragma warning(disable:4996)
class COOP_LSL_GISView : public CView
{
protected: // 仅从序列化创建
	COOP_LSL_GISView();
	DECLARE_DYNCREATE(COOP_LSL_GISView)

// 特性
public:
	COOP_LSL_GISDoc* GetDocument() const;

// 操作
public:
	boolean isMapLoaded;
	double mapRatio;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	bool isZoomIn;
	CRect winRect;
	CRect rectD;
	CPoint downPoint;
	CPoint upPoint;
	int clickNum;
	CGeoMap *map;
	void readCHData(FILE *fp);
	void readCH1Data(FILE *fp);
	void readWHData(FILE *fp);
	virtual ~COOP_LSL_GISView();
	void readCH1OPTD(FILE *fp);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnZoomin();
//	afx_msg void OnAfxIdPreviewZoomin();
	afx_msg void OnZoomin();
	afx_msg void OnUpdateZoomin(CCmdUI *pCmdUI);
	afx_msg void OnFullview();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void readExcel(CString path);
};

#ifndef _DEBUG  // OOP_LSL_GISView.cpp 中的调试版本
inline COOP_LSL_GISDoc* COOP_LSL_GISView::GetDocument() const
   { return reinterpret_cast<COOP_LSL_GISDoc*>(m_pDocument); }
#endif

