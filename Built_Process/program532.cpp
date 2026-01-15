// CVFS Project 
////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Header File Inclusion
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros
//
////////////////////////////////////////////////////////////////////////////////////////////////

//Maximum file size that we allow in project---
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0


////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : BootBlock
//  Description    : Holds the information to boot the OS
//
////////////////////////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : SuperBlock
//  Description    : Holds the information about the file system
//
////////////////////////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : Inode
//  Description    : Holds the information about the file
//
////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack (1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;           // 200pages book
    int ActualFileSize;     // used pages 70 from 200 book pages
    int ReferenceCount;
    int Permission;         // for file permission 
    char *Buffer;           // file data
    struct Inode *next;     //  Self Refrential pointer
};

typedef struct Inode INODE;
typedef struct Inode* PINODE;
typedef struct Inode** PPINODE;

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : FileTable
//  Description    : Holds the information about opened file
//
////////////////////////////////////////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;     // from which offset to read
    int WriteOffset;    // from which offset to write
    int Mode;           // access file using given mode
    PINODE ptrinode;
};
typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : UAREA
//  Description    : Holds the information about process
//
////////////////////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Global variables or objects used in the project
//
////////////////////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : InitialiseUAREA
//  Description    : it is used to initialise UAREA member
//  Author         : Saurabh Ravindra Bhonlse   
//  Date           : 13/01/2026
//
////////////////////////////////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0;
    for(i = 0; i < MAXOPENFILES; i ++)
    {
        uareaobj.UFDT[i] = NULL;       // initialise pointer to NULL
    }
    
    printf("Marvellous CVFS : UAREA  gets initialised successfully\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  : InitialiseSuperBlock
//  Description    : to initialise Super block members
//  Author         : Saurabh Ravindra Bhonlse   
//  Date           : 13/01/2026
//
////////////////////////////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super block gets initialised successfully\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  : CreateDILB
//  Description    : It is used to create linkedlist of inodes
//  Author         : Saurabh Ravindra Bhonlse   
//  Date           : 13/01/2026
//
////////////////////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName,"\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if(temp == NULL)        // LL is empty
        {
           head = newn;
           temp = head;  
        }
        else                    // LL contains atleast one node
        {
            temp->next = newn;
            temp = temp->next;
        }

    }

    printf("Marvellous CVFS : DILB created successfully\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry Point Function Of The Project
//
////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{   
    
    return 0;
}