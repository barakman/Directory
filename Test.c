#include "Directory.h"
#include <stdio.h>


void Print(Directory* pDirectory,int iDepth)
{
    int numOfFiles = GetNumOfFiles(pDirectory);
    for (int i=1; i<numOfFiles; i++)
    {
        for (int j=0; j<iDepth; j++)
            printf("\t");
        printf("%s\n",GetFileName(pDirectory,i));
        if (FileIsSubDir(pDirectory,i))
        {
            ChangeTo(pDirectory,i);
            Print(pDirectory,iDepth+1);
            ChangeTo(pDirectory,0);
        }
    }
}


void Test()
{
    Directory directory;
    Init(&directory,".");
    Print(&directory,0);
    Free(&directory);
}


int main()
{
    Test();
    return 0;
}
