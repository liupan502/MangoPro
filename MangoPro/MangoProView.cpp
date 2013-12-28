
// MangoProView.cpp : CMangoProView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMangoProView 构造/析构

CMangoProView::CMangoProView()
{
	// TODO: 在此处添加构造代码

}

CMangoProView::~CMangoProView()
{
}

BOOL CMangoProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMangoProView 绘制

void CMangoProView::OnDraw(CDC* /*pDC*/)
{
	CMangoProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMangoProView 打印

BOOL CMangoProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMangoProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMangoProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMangoProView 诊断

#ifdef _DEBUG
void CMangoProView::AssertValid() const
{
	CView::AssertValid();
}

void CMangoProView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMangoProDoc* CMangoProView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMangoProDoc)));
	return (CMangoProDoc*)m_pDocument;
}
#endif //_DEBUG


// 载入数据


void CMangoProView::LoadFile(void)
{
	char szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle = "请选择目录";
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

	// TODO:  在此添加您专用的创建代码
	LoadFile();
	return 0;
}
