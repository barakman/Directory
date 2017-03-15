#include "Directory.h"
#include <direct.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>


static void Open(Directory* pDirectory);
static void Close(Directory* pDirectory);


void Init(Directory* pDirectory,const char* pName)
{
    _chdir(pName);
    Open(pDirectory);
}


void Free(Directory* pDirectory)
{
    Close(pDirectory);
}


void ChangeTo(Directory* pDirectory,int iId)
{
    if (FileIsSubDir(pDirectory,iId))
    {
        _chdir(GetFileName(pDirectory,iId));
        Close(pDirectory);
        Open(pDirectory);
    }
}


int GetNumOfFiles(const Directory* pDirectory)
{
    return pDirectory->m_iFileCount;
}


char FileIsSubDir(const Directory* pDirectory,int iId)
{
    if (0 <= iId && iId <= pDirectory->m_iFileCount-1)
        return pDirectory->m_aFileFlags[iId];
    return 0;
}


char* GetFileName(const Directory* pDirectory,int iId)
{
    if (0 <= iId && iId <= pDirectory->m_iFileCount-1)
        return pDirectory->m_aFileNames[iId];
    return NULL;
}


static void Open(Directory* pDirectory)
{
    int iHandle;
    struct _finddata_t sFile;

    iHandle = _findfirst("*.*",&sFile);
    pDirectory->m_iFileCount = 0;
    while (_findnext(iHandle,&sFile) == 0)
        pDirectory->m_iFileCount++;
    _findclose(iHandle);

    pDirectory->m_aFileFlags = malloc(pDirectory->m_iFileCount*sizeof(*pDirectory->m_aFileFlags));
    pDirectory->m_aFileNames = malloc(pDirectory->m_iFileCount*sizeof(*pDirectory->m_aFileNames));

    iHandle = _findfirst("*.*",&sFile);
    for (int i=0; i<pDirectory->m_iFileCount; i++)
    {
        _findnext(iHandle,&sFile);
        pDirectory->m_aFileFlags[i] = (sFile.attrib&_A_SUBDIR)!=0;
        pDirectory->m_aFileNames[i] = malloc(strlen(sFile.name)+1);
        strcpy(pDirectory->m_aFileNames[i],sFile.name);
    }
    _findclose(iHandle);
}


static void Close(Directory* pDirectory)
{
    free(pDirectory->m_aFileFlags);
    for (int i=0; i<pDirectory->m_iFileCount; i++)
        free(pDirectory->m_aFileNames[i]);
    free(pDirectory->m_aFileNames);
}
