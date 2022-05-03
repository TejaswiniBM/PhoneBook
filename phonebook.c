//Phonebook program using C
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Function Declarations
void addrecord();
void deleterecord();
void modifyrecord();
void searchrecord();
void listrecord();
int menu();

//creating user-defined data type 
struct person
{
    char name[35];
    char address[50];
    char mble_no[20];
    char mail[100];
};
typedef struct person ch; //ch is a name(alias name) to already existing type
ch p; //creating variable p of type struct person

//function to insert contact details
void addrecord()
{
    FILE *f, *ft;
    char name[100];
    f=fopen("project","ab+"); // opens a new file project in read and write in binary format
    printf("\nEnter name: ");
    scanf("%s",name);
    fflush(stdin); //to clear (or flush) the output buffer and move the buffered data to console
    if(f!=NULL)
    {
      ft=fopen("temp","wb+"); //opens a binary file in read and write mode
     {
            if(strcmp(p.name,name)==0) //if strings are equal that is name already exists in file
           {
             printf("Name already exists\nKindly enter another name:");
             scanf("%s",p.name);
           }
           else
           {
               strcpy(p.name,name); //copy name to p variable
           }
      }
    }
    printf("\nEnter the address: ");
    scanf("%s",p.address);
    char mobno[20]="";
    while(1)
    {   
	    printf("\nEnter 10 digit phone no:");
	    scanf ("%s",mobno);
	    if(strcmp(p.mble_no,mobno)==0) //ph num already exits in file 
        {
             printf("Contact already exists\nKindly check.");
             //scanf("%s",mobno);
             continue;
        }
	    if(strlen(mobno)<= 0)//ph num not entered
	    {
		printf("Please enter ph num\n");
		continue;
	    }
	    
	    if(atoi(mobno)<= 0)// if character entered in ph num
	    {
		printf("Character not allowed.\n");
		continue;
	    }
	    
	    if(strlen(mobno)< 10 || strlen(mobno)> 10) //ph num less than 10 digits
	    {
		printf("Only 10 digit is allowed\n");
		continue;
	    }
	    strcpy(p.mble_no, mobno);
	    break;
    }
    while(1)
    {
	char mail[50];
            //only e-mail ID of these formats is allowed (@gmail.com/@yahoo.com/@hotmail.com)
	printf ("\nEnter e-mail ID(@gmail.com/@yahoo.com/@hotmail.com):");
	scanf ("%s",mail);
	char a[25]="@gmail.com";
	char b[25]="@yahoo.com";
	char c[25]="@hotmail.com";
	char gmail[50]="";
	char yahoo[50]="";
	char hotmail[50]="";
	char *z, *q;
	if( (z=strstr(mail, "@gmail.com")) != NULL || (z=strstr(mail, "@yahoo.com")) != NULL || (z=strstr(mail, "@hotmail.com")) != NULL)
	{
		strcpy (p.mail, mail);
		goto label;
	}
	else
	{
		printf("Invalid mail format\n");
		printf("kindly use @gmail.com/@yahoo.com/@yahoo.com\n");

		continue;
	}
    }
   label:
    fwrite(&p,sizeof(p),1,f); // writes 1(count) ele, each of size p from block of mry pointed by p
    fflush(stdin);
    printf("\nRecord saved");
    fclose(ft);
    fclose(f); //closes the f file created
    menu();
}

//function to delete contact details
void deleterecord()
{
    FILE *f,*ft;
    int flag;
    char name[100];
    f=fopen("project","rb+");//opens a new file project in read and write in binary format
    if(f!=NULL)
    {
        ft=fopen("temp","wb+");//create temp file and allow write and read operation on file
        {
          printf("Enter Contact Name:");
          scanf("%s",name);
          fflush(stdin);
          while(fread(&p,sizeof(p),1,f)==1)//  fread() function is used to read bytes form the file
          {
            if(strcmp(p.name,name)!=0)
                fwrite(&p,sizeof(p),1,ft); //fwrite() function is used to write records (sequence of bytes) to the file
            if(strcmp(p.name,name)==0)
                flag=1; //flag is set to 1 if contact name is found to perform deletion
           }
        fclose(f);
        fclose(ft);
        if(flag!=1)
        {
         printf("Invalid contact name");
         remove("temp.txt");
        }
        else
        {
            remove("project");
            rename("temp","project");
            printf("Record Deleted Successfully\n");
        }
        }
    }
    else
    {
        printf("Contact is empty\n");  
    }
    menu();
}

//function to list all contacts in file in the order entered by user
void listrecord()
{
    FILE *f;
    char *temp;
    f=fopen("project","rb");// opens a new file project in read mode in binary format
    if(f!=NULL)
    {
      printf("----------------------------------------------------------------------------------\n");
      printf("\t\tPhonebook Record\n");
      printf("----------------------------------------------------------------------------------");
      printf("\nName\t\tAddress\t\tPhone Number\t\tMail_Id\n");
      printf("----------------------------------------------------------------------------------\n");
	  while(fread(&p,sizeof(p),1,f)==1)
      {
          printf("%s\t\t%s\t\t%s\t\t%s\n",p.name,p.address,p.mble_no,p.mail);
      }
      printf("----------------------------------------------------------------------------------\n");
    }
    else
    {
       printf("No Records\n");
    } 
    menu();
}

//function to modify contact details
void modifyrecord()
{
    FILE *f;
    int flag=0;
    struct person p,s;
    char  name[50];
    f=fopen("project","rb+");// opens a new file project in read and write in binary format
    if(f==NULL)
    {
        printf("Contact is empty\n");
    }
    else
    {
        printf("\nEnter contact name to modify:\n");
        scanf("%s",name);
            while(fread(&p,sizeof(p),1,f)==1)
            {
                if(strcmp(name,p.name)==0)// if entered name matches with names in file then modify contact
                {
                    printf("\nEnter name:");
                    scanf("%s",s.name);
                    printf("\nEnter the address: ");
                    scanf("%s",s.address);
                   char mobno[20]="";
                   while(1)
                {   
	                printf("\nEnter 10 digit phone no:");
	                scanf ("%s",mobno);
	                if(strlen(mobno)<= 0)
	               {
	                   	printf("Please enter ph num\n");
		                continue;
	               }
	               if(atoi(mobno)<= 0)
	              {
		             printf("Character not allowed.\n");
		             continue;
	              }
	    
	              if(strlen(mobno)< 10 || strlen(mobno)> 10)
	              {
		           printf("Only 10 digit is allowed\n");
		           continue;
	              }
	             strcpy(s.mble_no, mobno);
	               break;
               }
               printf ("\nEnter e-mail ID(@gmail.com/@yahoo.com/@hotmail.com):");
	           scanf ("%s",s.mail);
                   fseek(f,-sizeof(p),SEEK_CUR);
                    fwrite(&s,sizeof(p),1,f);
                    flag=1;//flag is set to 1 if contact is modified
                    break;
                }
                fflush(stdin);

            }
            if(flag==1)
            {
                printf("\nContact is modified");         
            }
            else
            {
                    printf("\nContact not found");
            }
            fclose(f);
    }
    menu();
}
//function to search contact name and retrieve contact details
void searchrecord()
{
  char name[100];
  FILE *f;
  f=fopen("project","rb+");//opens a new file project in read and write in binary format
  if(f==NULL)//if file is null
  {
    printf("\nContact is empty");
    exit(1);
  }
  else
  {
    printf("\nEnter contact name to search:");
    scanf("%s",name);
    if(strcmp(p.name,name)!=0)//if name doesn’t  match with names in file
    {
         printf("Contact not found\n");
    }
    else
    {
        printf("\nContact Details About %s",name);//print all details of that contact
        printf("\nName:%s\nAddress:%s\nMobile no:%s\nE-mail:%s\n",p.name,p.address,p.mble_no,p.mail);
    }
  }
    menu();
}
//menu() contains menu of program with each case assigned with operations in switch statement.
int menu()
{
   int choice;
   printf("\n--------------------------------------------PHONEBOOK PROGRAM---------------------------------------------------");
   printf("\n\n\t\t\t\t\t\t MENU\t\t\n\n");
   printf("1.Add Contact\t2.Delete Contact\t3.Modify Contact\t4.Search Contact\t5.List Contacts\t6.Exit");
   printf("\n----------------------------------------------------------------------------------------------------------------\n");
   printf("\nEnter the choice:");
   scanf("%d",&choice);
   for(;;)
   {
     switch(choice)
     {
       case 1 : addrecord();break;
       case 2 : deleterecord();break;
       case 3 : modifyrecord();break;
       case 4 : searchrecord();break;
       case 5 : listrecord();break;
       case 6 : exit(0);break;
       default: printf("Invalid choice\nPlease enter valid choice:");
     }
     return (0);
   }
}
//execution of program begins here
int main()
{
    menu();//function call 
    return(1);//function is returning true.
}
