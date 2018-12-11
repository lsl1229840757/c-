
// OOP_LSL_GISView.h : COOP_LSL_GISView ��Ľӿ�
//

#pragma once
#include "GeoLayer.h"
#include "GeoObject.h"
#include "GeoMap.h"
#include "GeoPoint.h"
#include "GeoPloyline.h"
#include "GeoPolygon.h"
class COOP_LSL_GISView : public CView
{
protected: // �������л�����
	COOP_LSL_GISView();
	DECLARE_DYNCREATE(COOP_LSL_GISView)

// ����
public:
	COOP_LSL_GISDoc* GetDocument() const;

// ����
public:
	boolean isMapLoaded;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	CGeoMap *map;
	void readCHData(FILE *fp);
	void readCH1Data(FILE *fp);
	void readWHData(FILE *fp);
	virtual ~COOP_LSL_GISView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
};

#ifndef _DEBUG  // OOP_LSL_GISView.cpp �еĵ��԰汾
inline COOP_LSL_GISDoc* COOP_LSL_GISView::GetDocument() const
   { return reinterpret_cast<COOP_LSL_GISDoc*>(m_pDocument); }
#endif

