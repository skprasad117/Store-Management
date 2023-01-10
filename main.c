#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define ANS 15

//STRUCTURE DECLARATION
struct item
{
    char name[ANS];
    float sp;
    int qty;
};
struct item i;

//main menu function
void additem();
void bill();
void updateitem();
void del();
void disp();
void display(struct item * ,int,int);
int check(char []);

COORD coord= {0,0}; // this is global variable
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
/*declaration of checking functions*/



void mainmenu();
void back();
void rest();
void password();

//MAIN FUNCTION
int main()
{
    password();
    return 0;
}

//MAIN MENU FUNCTION DEFINATION
void mainmenu()
{   system("cls");
    back();
    int choice,loop;
     gotoxy(70,44);
    printf("TO REST PRESS '*'");
    gotoxy(38,14);
    for(loop=0;loop<=20;loop++)
    printf("*");
    gotoxy (40,15);
    printf("      MENU");
    gotoxy(38,16);
    for(loop=0;loop<=20;loop++)
    printf("*");
    gotoxy (40,17);
    printf("1. BILL ");
    gotoxy (40,18);
    printf("2. ADD ITEMS ");
    gotoxy (40,19);
    printf("3. DISPLAY ITEMS");
    gotoxy (40,20);
    printf("4. UPDATE ITEM");
    gotoxy(40,21);
    printf("5. DELETE ITEM");
    gotoxy(40,22);
    printf("6. ABOUT");
    gotoxy(38,23);

    for(loop=0;loop<=20;loop++)
    printf("*");
    gotoxy(40,24);
    printf("ENTER UR CHOICE:-\t");
    fflush(stdin);
    choice=getche();
    switch(choice)
    {
        case '1': bill();
        break;
        case '2': additem();
        break;
        case '3': disp();
        break;
        case '4': updateitem();
        break;
        case '5': del();
        break;
        case '6': about();
        break;
        case '*': reset();
        break;
        default : mainmenu();
        break;
    }


}

//BILL FUNCTION DEFINATION
void bill(){
    system("cls");
    back();
    int q,size=0,j=1,line=14,loop;
    char x[ANS];
    FILE *f;
    float total=0,gtotal=0;
    gotoxy(70,42);
    printf("enter  \"end\" to finish input");
    f=fopen("record.txt","r+b");
    gotoxy(14,13);
    printf("S.NO\tNAME\t\tQUANTITY\t\tCOST\t\tTOTAL");
    while(1)
    {
        gotoxy(45,7);
        printf("BILL");
         gotoxy(30,9);
        printf("enter item name:");
        START:scanf("%s",x);
        if(strcmp(x,"end")==0)
            break;
         gotoxy(30,11);
        printf("enter quantity:");
        scanf("%d",&q);
        rewind(f);
        while(fread(&i,sizeof(i),1,f))
        {
            if((strcmp(i.name,x)==0))
             {
                if(i.qty<=0||q>i.qty)
                   { gotoxy(30,line+1);

                    printf("oops item is out of stock\n");
                    goto START;
                }
            gotoxy(10,line);
            {
                total=i.sp*q;
                printf("\n\t\t%d",j);
                printf("\t%s\t\t",i.name);
                printf("  %d\t",q);
                printf("\t\t%f",i.sp);
                printf("\t%f\n",total);
                line++;
            }
                gtotal=gtotal+total;
                size=sizeof(i);
                i.qty=i.qty-q;
                j++;
                fseek(f,-size,SEEK_CUR);
                fwrite(&i,sizeof(i),1,f);
                break;
            }
        }
    }

 if (gtotal!=0)
    {
    gotoxy(0,38);
    for(loop=1;loop<=100;loop++)
    printf("*");
    gotoxy(69,39);
    printf("TOTAL AMOUNT = INR. %6.2f",gtotal);
    gotoxy(0,41);
    for(loop=1;loop<=100;loop++)
    printf("*");
    }
    fclose(f);
    getch();
   mainmenu();
}

//ADD ITEM FUNCTION DEFINATION
void additem(){
int count=0;
    system("cls");
    back();
char choice='y';
FILE *f;
gotoxy(38,5);
printf("ADD ITEM");
gotoxy(15,7);
 printf("Enter new record(Y/N)?");
fflush(stdin);
choice=getche();

while(choice=='y')
{
f=fopen("record.txt","ab");

 START:gotoxy(25,8);
printf("enter  price of item");
gotoxy(55,9);
 scanf("%f",&i.sp);
gotoxy(25,10);
printf("enter  quantity of item");
gotoxy(55,11);
scanf("%d",&i.qty);
gotoxy(25,12);
printf("enter name of item");
gotoxy(55,13);
scanf("%s",i.name);

fseek(f,0,SEEK_END);
fwrite(&i,sizeof(i),1,f);
fclose(f);
gotoxy(15,25);
printf("Enter new record(Y/N)?");
fflush(stdin);
choice=getche();
count++;
gotoxy(25,30);
printf("ITEMS ADDED SUCCESFULLY  %d",count);

}
mainmenu();
}

//DISP FUNCTION DEFINATION
//DISP PRINT DATA OF ITEMS
void disp(){
    system("cls");
    back();
    int j=1,e;
    FILE *f;
    f=fopen("record.txt","rb");
    rewind(f);
    e=10;
    fflush(f);
    while(fread(&i,sizeof(i),1,f)){
             gotoxy (40,7);
            printf("DISPLAY ALL ITEMS");
             gotoxy (20,9);
            printf("SNO.\t\tName\t\tQUANTITY\t\tPRICE");
           display(&i,e,j);
           e++;
          j++;
          if ((j%20)==0)
        {

            printf("Press any key to see more...........");
            getch();
            system("cls");
            back();
             e=10;
            continue;
        }

    }
  getch();
    if (e==10)
    {
        gotoxy(35,30);
        printf("-- no articles found --");
    }
    getch();
    fclose(f);
   mainmenu();
}

//DISPLAY FUNCTION DEFINATION
void display(struct item *a,int e,int j)
{   gotoxy(16,e);

    printf("    %d",j);
    printf("\t\t\t%s",i.name);
    printf("\t\t%d",i.qty);
    printf("\t\t\t%f",i.sp);
}

// UPDATE ITEM FUNCTION DEFINATION
void updateitem(){
    system("cls");
    back();
    int flag=0,choice,size,choice1;
    char x[ANS];
   gotoxy(37,7);
    printf("UPDATE ITEM");
    gotoxy(33,9);
    printf("ENTER ITEM NAME");
    gotoxy(52,9);
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
    FILE *f;
    f=fopen("record.txt","r+b");
    rewind(f);
    while(fread(&i,sizeof(i),1,f))
    {
        if(strcmp(&i.name,x)==0)
        {       gotoxy(30,11);
                printf("name       = %s",i.name);
                gotoxy(30,12);
                printf("rate       = %f",i.sp);
                gotoxy(30,13);
                printf("quantity   = %d",i.qty);
                gotoxy(45,15);
                printf("\nDo you want to edit this record?(y/n):\n");
                fflush(f);
                fflush(stdin);
                gotoxy(45,16);
                choice1=getche();
                 if(choice1=='y')
                 {
                    gotoxy(40,18);
                    printf("1- edit name\n ");
                    gotoxy(40,19);
                    printf("2- edit rate\n ");
                    gotoxy(40,20);
                    printf("3- edit quantity\n ");
                    gotoxy(40,23);
                    printf(" enter your choice(1, 2, 3) ");
                    gotoxy(75,23);
                    fflush(stdin);
                    choice1=getche();
                    switch(choice1)
                    {
                        case '1':

                        gotoxy(40,26);
                        printf("UPDATE ITEMS");
                        gotoxy(35,28);
                        printf(" enter new name: ");
                        gotoxy(60,28);
                        scanf("%s",i.name);
                        printf("\n");
                        size=sizeof(i);
                        fseek(f,-size,SEEK_CUR);
                        fwrite(&i,sizeof(i),1,f);
                        break;

                        case '2':


                        gotoxy(40,26);
                        printf("UPDATE ITEMS");
                         gotoxy(35,28);
                        printf(" enter new rate: ");
                        gotoxy(60,28);
                        scanf("%f",&i.sp);
                        size=sizeof(i);
                        fseek(f,-size,SEEK_CUR);
                        fwrite(&i,sizeof(i),1,f);
                        break;

                        case '3':
                        gotoxy(40,26);
                        printf("UPDATE ITEMS");
                         gotoxy(35,28);
                        printf(" enter new quantity: ");
                        gotoxy(60,28);
                        scanf("%d",&i.qty);
                        size=sizeof(i);
                        fseek(f,-size,SEEK_CUR);
                        fwrite(&i,sizeof(i),1,f);
                        break;

                    }
                 }
                    gotoxy(40,43);
                    printf("--- item edited---");
                    break;
                 }
        }
getch();
fclose(f);
mainmenu();
}
   if (flag==1)
    {
        gotoxy(32,30);
        printf("Item does not exist.");
        gotoxy(36,32);
        printf("TRY ABGAIN Y/N");
        fflush(stdin);
        choice1=getche();
        if(choice1=='y')
            updateitem();
        else
            mainmenu();
    }
}

//DEL FUNCTION DEFINATION
void del()
{
    int flag;
    char x[ANS],choice;
    FILE *file,*file1;
    system("cls");
    back();
//textbackground(11);
//textcolor(0);
    gotoxy(40,10);
    printf("DELETE ARTICLES");
    gotoxy(40,12);
    printf("enter item name: ");
    START:gotoxy(60,12);
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file1=fopen("record1.txt","ab");
        file=fopen("record.txt","rb");
        rewind(file);
        while (fread(&i,sizeof (i),1,file))
        {
            if(strcmp(i.name,x)!=0)
                fwrite(&i,sizeof(i),1,file1);
        }
        gotoxy(40,18);
        printf("---item deleted---");
         fclose(file1);
         fclose(file);
        remove("record.txt");
        rename("record1.txt","record.txt");

    }
    if (flag==1)
    {
        gotoxy(40,15);
        printf("---item does not exist---");
        gotoxy(40,18);
        printf("WANT TO TRY AGAIN y/n");
        fflush(stdin);
        gotoxy(65,18);
        choice=getche();
        if(choice=='y')
        goto START;
        else
            goto LAST;
    }
    fclose(file1);
    fclose(file);
    LAST: mainmenu();
}

//CHECK FUNCTION DEFINATION
//TO CHECK THE PRESENCE OF ITEM
int check  (char x[ANS])
{
FILE *f;
int flag=1;
f=fopen("record.txt","rb");
rewind(f);
  while (fread(&i,sizeof (i),1,f))
    {
        if(strcmp(i.name,x)==0)
        {
            flag=0;
            break;
        }
    }
    fclose(f);
    return flag;
    }





//ABOUT FUNCTION DEFINATION
void about()
{
system("cls");
back();
gotoxy(17,10);
printf("**********************ITP  PROJECT*********************");
gotoxy(17,11);
printf("*****************SHOP MANAGEMENT PROGRAM***************");
gotoxy(17,12);
printf("****SANJAY KUMAR PRASAD        07320903614*************");
gotoxy(17,13);
printf("****HAIDER ABBAS               00820903614*************");
gotoxy(17,14);
printf("****DEEPESH SAH                07120903614*************");
gotoxy(17,15);
printf("****RANJEET PRAJAPATI          04720903614*************");
gotoxy(17,16);
printf("*******************************************************");
getch();
mainmenu();

}

//BACK FUNCTION DEFINATION
void back()
{
    int loop,loop1;
    gotoxy(0,0);
    for(loop=1;loop<=100;loop++)
    printf("*");
    gotoxy(38,1);
    printf("STORE MANAGEMENT SOFTWARE");
    gotoxy(44,2);
    printf("ITP PROJECT");
    gotoxy(0,3);
    for(loop=1;loop<=100;loop++)
    printf("*");
    gotoxy(0,45);
    for(loop=1;loop<=100;loop++)
    printf("*");
    gotoxy(34,46);
    printf("G.B. PANT COLLEGE OF ENGG.");
    gotoxy(0,47);
    for(loop=1;loop<=100;loop++)
    printf("*");
}

//RESET FUNCTION DEFINATION
void reset()
{
    remove("record.txt");
    mainmenu();
}
//PASSWORD FUNCTION DEFINATION
void password()
{   system("cls");
    back();
    int l;
    char mpass []={"tango"},pass[10];
    gotoxy(40,20);
    printf("ENTER PASSWORD");
    gotoxy(60,20);
    gets(pass);
    l=strcmp(pass,mpass);
    if(l==0)
    {
        mainmenu();
    }
    else
        password();

}
