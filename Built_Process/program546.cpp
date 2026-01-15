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
//  Function Name  : InitialiseUAREA
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
//  Function Name  : StartAuxillaryDataInitilaisation
//  Description    : it is used to call all such functions which are used to initialise
//                   auxillary data   
//  Author         : Saurabh Ravindra Bhonlse   
//  Date           : 13/01/2026
//
////////////////////////////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitilaisation()
{
    strcpy(bootobj.Information,"Booting process of Marvellous CVFS is done");
    printf("%s\n",bootobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("Marvellous CVFS : Auxillary data initilaised successfully\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  : DisplayHelp
//  Description    : it is used to display the help page
//                   auxillary data   
//  Author         : Saurabh Ravindra Bhonlse   
//  Date           : 14/01/2026
//
////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("------------------------------------------------------\n");
    printf("---------------Marvellous CVFS Help Page--------------\n");
    printf("------------------------------------------------------\n"); 

    printf("man   : It is used to display manual page\n");
    printf("clear : It is used to clear the terminal\n");
    printf("creat : It is used to create new file\n");
    printf("write : It is used to write data into file\n");
    printf("read  : It is used to read the data from file\n");
    printf("stat  : It is used to display statistical information\n");
    printf("unlink:It is used to delete the file\n");
    printf("exit  : It is used to terminate Marvellous CVFS\n");

    printf("------------------------------------------------------\n"); 
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  : ManPageDisplay
//  Description    : it is used to display man page
//                   auxillary data   
//  Author         : Saurabh Ravindra Bhonlse   
//  Date           : 14/01/2026
//
////////////////////////////////////////////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if(strcmp("ls",Name) == 0)
    {
        printf("About  : It is used to list the names of all files\n");
        printf("Usage  : ls\n");
    }
    else if (strcmp("man",Name) == 0)
    {
        printf("About  : It is used to display manual page\n");
        printf("Usage  : man command_name\n");
        printf("command_name : It is the name of the command\n"); 
    }
    else if(strcmp("exit",Name)== 0)
    {
        printf("About  : It is used to terminate the shell\n");
        printf("Usage  : exit\n");   
    }
    else
    {
        printf("No manual entry for %s\n",Name);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry Point Function Of The Project
//
////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{   
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    int iCount = 0;

    StartAuxillaryDataInitilaisation();

    printf("------------------------------------------------------\n");
    printf("---------Marvellous CVFS started successfully---------\n");
    printf("------------------------------------------------------\n");

    //Infinite listening shell
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        printf("Marvellous CVFS : > ");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str,"%s %s %s %s %s",Command[0],Command[1],Command[2],Command[3],Command[4]);

        fflush(stdin);
        if(iCount == 1)
        {
            if(strcmp("exit",Command[0]) == 0) //comparing exit with the given string by user
            {
                printf("Thank You For Using Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            else if(strcmp("ls",Command[0]) == 0)
            {
                printf("Inside ls");
            }
            else if(strcmp("help",Command[0]) == 0)
            {
                DisplayHelp();
            }
            
            
        } //End of else if 1       
        else if (iCount == 2)
        {
            if(strcmp("man",Command[0])== 0)
            {
                ManPageDisplay(Command[1]);
            }
        }//End of else if 2
        else if (iCount == 3)
        {

        }//End of else if 3
        else if (iCount == 4)
        {

        }//End of else if 4
        else
        {
            printf("Command not found\n");
            printf("Please refer help option to get information \n");
        }//En of else

    }//End of while


    return 0;
}//End of main