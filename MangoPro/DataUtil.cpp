#include "stdafx.h"
#include "DataUtil.h"


bool FilePathSet::Init(const char* szDir )
{
	bool result = true;
	result = result&&FindPGRFile(szDir);
	result = result&&FindXSenseFile(szDir);
	return result;
}

// 寻找PGR文件名
bool FilePathSet::FindPGRFile(const char* szDir)
{
	vector<CString> nameSet;
	CString dir(szDir);
	dir+="\\*.pgr";
	CFileFind finder;
	if(!finder.FindFile(dir))
		return false;
	while(finder.FindNextFile())
	{	
			CString tmp = finder.GetFilePath();
			if(tmp.Find("000000.pgr",0) > -1)
			{
				nameSet.push_back(tmp);
			}
	}
	if(nameSet.size() != 1)
		return false;
	this->pgrPath = nameSet[0].GetBuffer(nameSet[0].GetLength());
	return true;
}

// 寻找XSense文件名
bool FilePathSet::FindXSenseFile(const char* szDir)
{
	vector<CString> nameSet;
	CString dir(szDir);	
	dir+="\\Ladybug-Stream.txt";
	CFileFind finder;
	if(!finder.FindFile(dir))
		return false;	
	while(finder.FindNextFile())
	{	
		CString tmp = finder.GetFilePath();		
		nameSet.push_back(tmp);	
	}
   nameSet.push_back(finder.GetFilePath());
	if(nameSet.size() != 1)
		return false;
	this->XsensePath = nameSet[0].GetBuffer(nameSet[0].GetLength());
	return true;
}