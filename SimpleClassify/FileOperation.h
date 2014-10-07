//FIlE Opeartion based on MFC formulation

#pragma  once

#include "stdafx.h"

struct FileOP{

	static void MkDir(CStr &path);//Create a non-existed documentary
	static VStr LoadSubDirectory(CStr &path);//Return the names of the subdirectory of the big directory
	static VStr LoadDirectoryFile(CStr &path, CStr &format = "0");//Return the name of the files of the directory.
	static void ClearDir(CStr &path);//Delete the whole directory
};