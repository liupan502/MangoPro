#ifndef DATA_UTILITY
#define DATA_UTILITY
//#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
struct FilePathSet{
      string pgrPath	;
	  string XsensePath;
	  bool Init(const char* szDir );
private:
	  bool FindPGRFile(const char* szDir);
	  bool FindXSenseFile(const char* szDir);
};

#endif