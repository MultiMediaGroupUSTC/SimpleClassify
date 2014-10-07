#include "FileOperation.h"

void FileOP::MkDir(CStr &path){

	DWORD dwAttr=GetFileAttributes(path.c_str());
	if(dwAttr==0xFFFFFFFF){
		CreateDirectory(path.c_str(),NULL);
	}
	else cout<<"The directory has already been created"<<endl;

}

VStr FileOP::LoadSubDirectory(CStr &path){

	VStr DirectoryList;
	CFileFind finder;  
	CStr fpath = path + "\\*";
	BOOL bWorking = finder.FindFile(fpath.c_str()); 

	while (bWorking) {  
		bWorking = finder.FindNextFile(); 
		if(finder.IsDirectory()){ 
			//go over all the labels
			CString Path=finder.GetFilePath(); 
			CString Storagename=Path.Right(Path.GetLength()-1-Path.ReverseFind('\\'));
			string label=Storagename.GetBuffer(0);
			if(label=="."||label=="..") continue;	//filter out the . and the .. situation
			DirectoryList.push_back(Path.GetBuffer(0));
			
		}
	}
	return DirectoryList;
}

VStr FileOP::LoadDirectoryFile(CStr &path, CStr &format){

	VStr FileList;
	CFileFind finder, ImageFile;  
	CString fPath = path.c_str();
	BOOL bWorking = finder.FindFile(path.c_str());  
	
	if (format == "0")
	{
		bWorking =  finder.FindFile(_T(fPath+"/*.*"),0);
	}
	else{
		CStr FindName = path + "/*." + format;
		CString FName = FindName.c_str();
		bWorking = finder.FindFile(_T(FName),0);
	}
	while(bWorking){
		//go over all the labels
		bWorking = finder.FindNextFile() ;//
		if(!finder.IsDots() && !finder.IsDirectory())//
		{	

			CString FileName = finder.GetFileName() ;
			CString ImageFileAddress =fPath+"\\"+ FileName;
			FileList.push_back(ImageFileAddress.GetBuffer(0));//get directory list
		}

	}
	
	return FileList;
}

void FileOP::ClearDir(CStr &path){

	//Fistt, delete all the files under this directory 
    CFileFind finder;  
    CString fpath;  
    fpath.Format("%s/*.*",path.c_str());  
    BOOL bWorking = finder.FindFile(fpath);  
    while(bWorking){  
        bWorking = finder.FindNextFile();  
        if(finder.IsDirectory() && !finder.IsDots()){//处理文件夹  
           ClearDir(finder.GetFilePath().GetBuffer(0)); //递归删除文件夹  
           RemoveDirectory(finder.GetFilePath());  
        }  
        else{//处理文件  
            DeleteFile(finder.GetFilePath());  
        }  
    } 

	//Then, we delete the blank directory itself
	RemoveDirectory(path.c_str());
}  

