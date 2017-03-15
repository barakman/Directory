#ifndef DIRECTORY_H
#define DIRECTORY_H


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// DESCRIPTION: Navigate among directories.                                   //
//              Reveal the contents of the current directory.                 //
//                                                                            //
// REMARKS:     This module is applicable over the Windows file system.       //
//              If you use the 'GetFileName' operation, be sure to save       //
//              the file's name in a separate buffer before you use the       //
//              'ChangeTo' operation (and before the object is destroyed).    //
//              The first element in every directory is always ".", which is  //
//              a pointer to the current directory, and is therefore skipped. //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


typedef struct
{
    int    m_iFileCount; // The number of files in the current directory
    char*  m_aFileFlags; // An array of sub-dir flags (for each file)
    char** m_aFileNames; // An array of names (for each file)
}
Directory;


void Init(Directory* pDirectory,const char* pName);
void Free(Directory* pDirectory);


void ChangeTo(Directory* pDirectory,int iId);


int GetNumOfFiles(const Directory* pDirectory);
char FileIsSubDir(const Directory* pDirectory,int iId);
char* GetFileName(const Directory* pDirectory,int iId);


#endif
