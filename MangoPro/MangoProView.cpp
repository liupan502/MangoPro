
// MangoProView.cpp : CMangoProView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MangoPro.h"
#endif

#include "MangoProDoc.h"
#include "MangoProView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMangoProView

IMPLEMENT_DYNCREATE(CMangoProView, CView)

BEGIN_MESSAGE_MAP(CMangoProView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMangoProView ����/����

CMangoProView::CMangoProView()
{
	// TODO: �ڴ˴���ӹ������

}

CMangoProView::~CMangoProView()
{
}

BOOL CMangoProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMangoProView ����

void CMangoProView::OnDraw(CDC* /*pDC*/)
{
	CMangoProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMangoProView ��ӡ

BOOL CMangoProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMangoProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMangoProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMangoProView ���

#ifdef _DEBUG
void CMangoProView::AssertValid() const
{
	CView::AssertValid();
}

void CMangoProView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMangoProDoc* CMangoProView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMangoProDoc)));
	return (CMangoProDoc*)m_pDocument;
}
#endif //_DEBUG


// ��������


void CMangoProView::LoadFile(void)
{
	char szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle = "��ѡ��Ŀ¼";
	bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	pidl = SHBrowseForFolder(&bi);
	if(pidl == NULL)  return;
	if(!SHGetPathFromIDList(pidl, szDir))   return;
	CMangoProDoc* pDoc = (CMangoProDoc*)GetDocument();
	if(!pDoc)
		return ;
	pDoc->LoadFile(szDir);
}


int CMangoProView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	LoadFile();
	return 0;
}
