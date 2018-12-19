#pragma once
class CGeoObject
{
public:
	CGeoObject(void);
	virtual ~CGeoObject(void);
	CRect crRect;// 外界矩形
	void setName(CString Name);
	CString getName();
	void setID(int id);
	int getID();
	//void Draw(CDC *pDC);
	void setRect(CRect rect);
	void setRect(int x1,int y1,int width,int height);
	CRect getRect();
	virtual void Draw(CDC *pDC)=0;
	double lineWidth;
	int r;
	int g;
	int b;
private:
	CString Name;
	int id;
protected:
	int Type; // 1,2,3,4分别表示点，线，面，文字

};

