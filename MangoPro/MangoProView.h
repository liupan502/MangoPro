
// MangoProView.h : CMangoProView ��Ľӿ�
//

#pragma once


class CMangoProView : public CView
{
protected: // �������л�����
	CMangoProView();
	DECLARE_DYNCREATE(CMangoProView)

// ����
public:
	CMangoProDoc* GetDocument() const;

// ����
public:

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
	virtual ~CMangoProView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	void LoadFile(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // MangoProView.cpp �еĵ��԰汾
inline CMangoProDoc* CMangoProView::GetDocument() const
   { return reinterpret_cast<CMangoProDoc*>(m_pDocument); }
#endif

