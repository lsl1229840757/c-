#pragma once // ��֤.hֻ������һ��
#include "GeoLayer.h"
class CGeoMap
{
public:
	CGeoMap(void);
	~CGeoMap(void);
	CGeoMap(int Scale);
	const int Scale; // ��ͼ������
	CRect crRect;// ��ͼ��Χ
	CString getName();// �������
	void setName(CString name);
	int getScale();//��õ�ͼ������
	void setScale(int scale);
	CArray<CGeoLayer *,CGeoLayer *> geoLayers;
	void delLayerAt(int idx);// ɾ��ͼ��
	void delLayerAll(); // ɾ������ͼ��
	void setLayerIsVisible(CString layerName,boolean isVisible); // �趨ĳ��ͼ�����
	void Draw(CDC *pDC); //��ͼ
	void setRect(CRect rect);
	CRect getRect();
	void addLayer(CGeoLayer *layer);


private:
	CString Name; //����

};

