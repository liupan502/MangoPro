
// MangoProDoc.cpp : CMangoProDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MangoPro.h"
#endif

#include "MangoProDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMangoProDoc

IMPLEMENT_DYNCREATE(CMangoProDoc, CDocument)

BEGIN_MESSAGE_MAP(CMangoProDoc, CDocument)
END_MESSAGE_MAP()


// CMangoProDoc 构造/析构

CMangoProDoc::CMangoProDoc()
{
	// TODO: 在此添加一次性构造代码
}

CMangoProDoc::~CMangoProDoc()
{
}

BOOL CMangoProDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMangoProDoc 序列化

void CMangoProDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMangoProDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMangoProDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMangoProDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMangoProDoc 诊断

#ifdef _DEBUG
void CMangoProDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMangoProDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// 载入数据


int CMangoProDoc::LoadFile(const char* szDir)
{	
	FilePathSet filePathSet;
	if(filePathSet.Init(szDir))
	{
		//assert(senseInfoSet);
		/*if(senseInfoSet == NULL)
			return 0;*/
		SenseInfoSet* pTmp = new SenseInfoSet();
		if(!senseInfoSet.Init(filePathSet.XsensePath.c_str()))
			return 0;		
	}
	return 1;
}
