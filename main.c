#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NR_MAX_UTILIZATORI 10000
#define maxCharsPerLine 100

struct user
{
    char nume[30];
    char prenume[30];
    char nrTel[12];
    char email[50];
    int varsta;
} users[NR_MAX_UTILIZATORI];
char id[20],password[25];
int contorUsers = 0;
void printUserInConsole (struct user u)
{
    printf("%s | %s | %d | %s | %s \n", u.prenume, u.nume, u.varsta, u.email, u.nrTel);
}
// Converteste o linie intr-un utilizator
struct user splitLineToUser(char str[maxCharsPerLine])
{
    struct user newUser;
    int valuesPerLine = 5;
    char readedValues[valuesPerLine][100];

    const char separator[3] = ",\n";
    char *token;
    token = strtok(str, separator);

    int i = 0;
    while( token != NULL )
    {
       strcpy(readedValues[i], token);
        i++;
        token = strtok(NULL, separator);
    }

    strcpy(newUser.prenume,readedValues[0]);
    strcpy(newUser.nume,readedValues[1]);
    newUser.varsta=atoi(readedValues[2]);
    strcpy(newUser.nrTel,readedValues[3]);
    strcpy(newUser.email,readedValues[4]);
    return newUser;

}
char id1[20];

char pass[25];
int login(char fileName[200])
{
    FILE *filePointer = fopen(fileName, "r");
    if(filePointer == NULL)
    {
        printf("Nu pot deschide fisierul!\n");
        return 0 ;
    }
    fgets(id,20,filePointer);
    fgets(password,25,filePointer);
    fclose(filePointer);
    strncpy(id1,id,(strlen(id)-1));
    strncpy(pass,password,strlen(password)-1);
    return 1;

}
int readFromFile(char fileName[200])
{
    FILE *filePointer = fopen(fileName, "r");
    if(filePointer == NULL)
    {
        printf("Nu pot deschide fisierul!\n");
        return 0 ;
    }

    contorUsers = 0;

    char linie[maxCharsPerLine];

    while (fgets (linie, maxCharsPerLine, filePointer))
    {
        if (linie[0] != '\n')
        {
            struct user newUser = splitLineToUser(linie);
            users[contorUsers] = newUser;
            contorUsers++;

        }
    }

    fclose(filePointer) ;
    return 1;
}
//daca e sters cu succes return 1 ,daca nu e gasit return 0;
int stergere_nume(char s[200])
{
    int k=-1;
    //char prenume[30];
    //scanf("%s",prenume);
    for(int i=0; i<contorUsers; i++)
        if(strcmp(users[i].nume,s)==0)
        {
            k=i;
            break;
        }
    if(k==-1)
    {
        return 0;
    }
    for(int i=k; i<=contorUsers - 2; i++)
    {
        strcpy(users[i].nume,users[i+1].nume);
        strcpy(users[i].prenume,users[i+1].prenume);
        users[i].varsta=users[i+1].varsta;
        strcpy(users[i].email,users[i+1].email);
        strcpy(users[i].nrTel,users[i+1].nrTel);
    }
    contorUsers--;
    return 1;
}
int stergere_nr_tel(char s[50])
{
    int k=-1;
    for(int i=0; i<contorUsers; i++)
        if(strcmp(users[i].nrTel,s)==0)
        {
            k=i;
            break;
        }
    if(k==-1)
    {
        return 0;
    }
    for(int i=k; i<contorUsers-2; i++)
    {
        strcpy(users[i].nume,users[i+1].nume);
        strcpy(users[i].prenume,users[i+1].prenume);
        users[i].varsta=users[i+1].varsta;
        strcpy(users[i].email,users[i+1].email);
        strcpy(users[i].nrTel,users[i+1].nrTel);
    }
    contorUsers--;
    return 1;
}
int stergere_email(char s[200])
{
    int k=-1;
    for(int i=0; i<contorUsers; i++)
        if(strcmp(users[i].email,s)==0)
        {
            k=i;
            break;
        }
    if(k==-1)
        return 0;
    for(int i=k; i<contorUsers-2; i++)
    {
        strcpy(users[i].nume,users[i+1].nume);
        strcpy(users[i].prenume,users[i+1].prenume);
        users[i].varsta=users[i+1].varsta;
        strcpy(users[i].email,users[i+1].email);
        strcpy(users[i].nrTel,users[i+1].nrTel);
    }
    contorUsers--;
    return 1;
}

int autentificare(char id_iden[20],char password_iden[25])
{
    printf("\nBun venit!\n\nVa rugam autentificati-va!\n\n");
    printf("ID:");
    scanf("%s",id_iden);
    printf("Parola:");
    scanf("%s",password_iden);
    if(strcmp(id_iden,id1)!=0 || strcmp(password_iden,pass)!=0)
    {
        printf("\nID-ul sau parola sunt incorecte\n\n");
        return 0;
    }
    else
        return 1;
}
void start()
{
    char id_iden[20],password_iden[25];
    char path[200]="D:\\CodeBlocks\\pp\\Agenda.txt";
    char path1[200]="D:\\CodeBlocks\\pp\\Login.txt";
    int l=login(path1);
    if(l==0)
    {
        printf("Autentificare imposibila\n");
        return;
    }
    if(autentificare(id_iden,password_iden)==0)
    {
        printf("\nVa rugam incercati din nou\n\n");
       if(autentificare(id_iden,password_iden)==0)
       {printf("Autentificare imposibila");
       return;
       }
    else{
        int citire = readFromFile(path);
        if (citire == 0)
        {
            printf("NU POTI FOLOSI APLICATIA");
            return 0;
        }
        printf("Datele au fost incarcate cu succes\n");
        printf("Bun venit!\n");
        printf("Agenda telefonica\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Alege una dintre optiunile de mai jos:\n\n");
        AfiseazaMeniu();
    }
    }

    else{
        int citire = readFromFile(path);
        if (citire == 0)
        {
            printf("NU POTI FOLOSI APLICATIA");
            return 0;
        }
        printf("Datele au fost incarcate cu succes\n");
        printf("Bun venit!\n");
        printf("Agenda telefonica\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Alege una dintre optiunile de mai jos:\n\n");
        AfiseazaMeniu();
    }
}
void ScrieOptiuni()
{
    printf("\n");
    printf("0. Pentru a iesi din aplicatie apasati tasta 0\n");
    printf("1. Adaugati un contact.\n");
    printf("2. Stergeti un contact.\n");
    printf("3. Editati un contact.\n");
    printf("4. Vizualizati lista de contacte.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

}
void adaugare(char Nume[30],char Prenume[30],int Varsta, char Email[50], char Nr_tel[12])
{
    for(int i=0; i<contorUsers; i++)
    {
        if(strcmp(users[i].nume,Nume)==0 && strcmp(users[i].prenume,Prenume)==0)
        {
            printf("Exista deja o persoana memorata ce detine aceste informatii \n\nVa rugam incercati inca odata. \n\n");
            printf("Adaugare contact\n\n");
            adaugare_contact();
        }
        if(strcmp(users[i].email,Email)==0)
        {
            printf("Exista deja un contact cu acest e-mail.\n\n");
            AfiseazaMeniu();
        }
        if(strcmp(users[i].nrTel,Nr_tel)==0)
        {
            printf("Exista deja un contact cu acest numar de telefon.\n\n");
            AfiseazaMeniu();
        }
    }
    struct user newUser;
    strcpy(newUser.nume,Nume);
    strcpy(newUser.prenume,Prenume);
    newUser.varsta=Varsta;
    strcpy(newUser.email,Email);
    strcpy(newUser.nrTel,Nr_tel);
    users[contorUsers]=newUser;
    contorUsers++;
    printf("Contactul a fost salvat cu succes!\n");
}
void modificare_prenume(char s[50])
{
    char s1[50];
    int k=0,m;
    for(int i=0; i<contorUsers; i++)
        if(strcmp(users[i].prenume,s)==0)
        {
            scanf("%s",&s1);
            k=1;
            m=i;
            break;
        }
     if(k==1){
    strcpy(users[m].prenume,s1);
    //printf("%s",users[i].prenume);
    printf("Contactul a fost actualizat cu succes!\n");
     }
    if(k==0)
    {printf("Contact inexistent\n");
    return;
    }

}
void modificare_email(char s[50])
{
    char s1[50];
    int k=0,m;
    for(int i=0; i<contorUsers; i++)
        if(strcmp(users[i].email,s)==0)
        {
            scanf("%s",s1);
            k=1;
            m=i;
            break;
        }
    strcpy(users[m].email,s1);
    printf("Contactul a fost editat cu succes!\n");
}

void modificare_nume(char s[50])
{
    char s1[50];
    int k=0,m;
    for(int i=0; i<contorUsers; i++)
        if(strcmp(users[i].nume,s)==0)
        {
            m=i;
            scanf("%s",&s1);
            k=1;
            break;
        }
    strcpy(users[m].nume,s1);
    //printf("%s",users[i].nume);
    printf("Contactul a fost actualizat cu succes!\n");


}
void adaugare_contact()
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    int d;
    printf("Pentru a reveni la meniul principal apasa tasta 0.\n\nPentru a continua apasati tasta 1.\n\n");
    scanf("%d",&d);
    if(d==0)
        AfiseazaMeniu();
    else if(d==1)
    {
        char Nume[30],Prenume[30],Mail[50],nr_tel[12];
        short int Varsta;
        printf("Nume: \n");
        fflush(stdin);
        gets(Nume);
        for(int i=0; i<strlen(Nume); i++)
        {
            if((Nume[i]>'z' || Nume[i]<'A') && Nume[i]!='-')
            {
                printf("Acest caracter nu este permis.\n\nVa rugam incercati din nou\n\nNume:\n\n");
                fflush(stdin);
                gets(Nume);
            }
        }
        printf("Prenume: \n");
        fflush(stdin);
        gets(Prenume);
        for(int i=0; i<strlen(Prenume); i++)
        {
            if((Prenume[i]>'z' || Prenume[i]<'A') && Prenume[i]!='-')
            {
                printf("Acest caracter nu este permis.\n\nVa rugam incercati din nou\n\Prenume:\n\n");
                fflush(stdin);
                gets(Prenume);
            }
        }
        printf("Varsta: \n");
        scanf("%d",&Varsta);
        printf("Numarul de telefon: \n");
        scanf("%s",nr_tel);
        for(int i=0; i<strlen(nr_tel); i++)
        {
            if(nr_tel[i]>'9' || nr_tel[i]<'0')
            {
                printf("Acest caracter nu este permis.\n\nVa rugam incercati din nou\n\Numarul de telefon:\n\n");
                scanf("%s",nr_tel);
            }
        }
        printf("E-mail: \n");
        scanf("%s",Mail);
        adaugare(Nume,Prenume,Varsta,Mail,nr_tel);


        //printf("\nContactul a fost salvat cu succes!\n\n");
        //printf("%s %s %s %s",Nume,Prenume,Mail,nr_tel);

    }
    else
    {
        printf("Alegere invalida.\n\n");
        adaugare_contact();
    }

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}
void modificare_contact()
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    int Alegere;
    int d;
    printf("Pentru a reveni la meniul principal apasa tasta 0.\n\nPentru a continua apasati tasta 1.\n\n");
    scanf("%d",&d);
    if(d==0)
        AfiseazaMeniu();
    else if(d==1)
        do
        {
            printf("0. Pentru a parasi acest meniu introduceti cifra 0.\n\n");
            printf("Alegeti informatia pe care doriti sa o modificati: \n\n");
            printf("1. Nume si Prenume.\n");
            printf("2. E-mail.\n");
            printf("3. Numar de telefon\n");
            scanf("%d", &Alegere);

            char nume_cautat[40],prenume[30],email_cautat[30],nr_telefon[20],email_actualizat[30],nr_telefon_actualizat[20];
            if(Alegere==1)
            {
                int k;
                printf("\nNume: \n\n");
                scanf("%s", nume_cautat);
                for(int i=0; i<contorUsers; i++)
                {
                    if(strcmp(users[i].nume,nume_cautat))
                        k=1;
                    if(strcmp(users[i].nume,nume_cautat)==0)
                    {
                        k=0;
                        break;
                    }
                    if(i==(contorUsers-1) && k==1)
                    {
                        printf("Acest contact nu exista in agenda telefonului\n\nVa rugam sa mai incercati odata\n");
                        printf("\nEditare contact\n\n");
                        modificare_contact();
                    }
                }
                printf("Prenume: \n");
                scanf("%s",prenume);
                for(int i=0; i<contorUsers; i++)
                {
                    if(strcmp(users[i].prenume,prenume))
                        k=1;
                    if(strcmp(users[i].prenume,prenume)==0)
                    {
                        k=0;
                        break;
                    }
                    if(i==(contorUsers-1) && k==1)
                    {
                        printf("Acest contact nu exista in agenda telefonului\n\nVa rugam sa mai incercati odata\n");
                        printf("\nEditare contact");
                        modificare_contact();
                    }
                }
                printf("Alege informatia pe care doriti sa o modificati.\n\n");
                printf("Pentru a modifica numele apasati tasta 1\n\n");
                printf("Pentru a modifica prenumele apasati tasta 2\n\n");
                scanf("%d",&k);
                if(k==1)
                {
                    printf("\nNume actualizat: \n\n");
                    modificare_nume(nume_cautat);
                    AfiseazaMeniu();
                    AfiseazaMeniu();
                }
                if(k==2)
                {
                    printf("\nPrenume actualizat:\n\n");
                    modificare_prenume(prenume);
                    AfiseazaMeniu();
                }
                if(k!=1 || k!=2)
                {
                    //printf("Alegere invalida \n\n");
                    modificare_contact();

                }
                return;
            }

            else if(Alegere==2)
            {
                int k;
                printf("\nE-mail: \n\n");
                scanf("%s", email_cautat);
                for(int i=0; i<contorUsers; i++)
                    if(strcmp(users[i].email,email_cautat))
                    {
                        k=1;
                        if(strcmp(users[i].email,email_cautat)==0)
                        {
                            k=0;
                            break;
                        }
                        if(i==(contorUsers-1) && k==1)
                        {
                            printf("Nu exista nicio persoana cu acest e-mail in agenda telefonului\n\nVa rugam mai incercati odata\n\n");
                            printf("Editare contact\n\n");
                            modificare_contact();
                        }
                    }
                printf("\nE-mail acuatlizat: \n\n");
                modificare_email(email_cautat);
                return;
            }
            else if(Alegere==3)
            {
                int k;
                printf("\nNumarul de telefon: \n\n");
                scanf("%s",nr_telefon);
                for(int i=0; i<contorUsers; i++)
                {
                    if(strcmp(users[i].nrTel,nr_telefon)!=0)
                        k=1;
                    if(strcmp(users[i].nrTel,nr_telefon)==0)
                    {
                        k=0;
                        break;
                    }
                    if(i==(contorUsers-1) && k==1)
                    {
                        printf("Acest numar nu exista in agenda dumneavoastra telefonica\n\nVa rugam sa mai incercati odata\n\n");
                        printf("Editare contact\n\n");
                        modificare_contact();
                    }
                }
                printf("\nNumarul de telefon actualizat:\n\n");
                modificare_nr_tel(nr_telefon);
                return;
            }
            else if(d!=1 && d!=0)
            {
                printf("Alegere invalida.\n\n");
                stergere_contact();
            }

        }
        while(Alegere == 1 || Alegere == 2 || Alegere==3);
    else
    {
        printf("Alegere invalida.\n");
        modificare_contact();
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}
void modificare_nr_tel(char s[20])
{
    char s1[20];
    int k=0,m;
    for(int i=0; i<contorUsers; i++)
        if(strcmp(users[i].nrTel,s)==0)
        {
            m=i;
            scanf("%s",s1);
            k=1;
            break;
        }
    strcpy(users[m].nrTel,s1);
    printf("\n");
    printf("Contactul a fost editat cu succes!\n");
    if(k==0)
        printf("Contact inexistent\n");
}
void stergere_contact()
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    int Alegere;
    int d;
    printf("Pentru a reveni la meniul principal apasa tasta 0.\n\nPentru a continua apasati tasta 1.\n\n");
    scanf("%d",&d);
    if(d==0)
        AfiseazaMeniu();
    else if(d==1)
        do
        {
            printf("0. Pentru a parasi acest meniu apasati tasta 0.\n\n");
            printf("Alegeti criteriul:\n\n");
            printf("1. Nume si Prenume\n");
            printf("2. E-mail\n");
            printf("3. Numarul de telefon\n\n");
            scanf("%d", &Alegere);
            char nume_cautat[40],email_cautat[30],nr_telefon[20],prenume[30];
            if(Alegere==1)
            {
                int k;
                printf("\nNume cautat: \n\n");
                scanf("%s", nume_cautat);
                for(int i=0; i<contorUsers; i++)
                {
                    if(strcmp(users[i].nume,nume_cautat)!=0)
                        k=1;
                    if(strcmp(users[i].nume,nume_cautat)==0)
                    {
                        k=0;
                        break;
                    }
                    if(i==(contorUsers-1) && k==1)
                    {
                        printf("Acest contact nu exista in agenda telefonului\n\nVa rugam sa mai incercati odata\n");
                        printf("\nStergere contact\n\n");
                        stergere_contact();
                    }
                }
                printf("\nPrenume cautat: \n\n");
                scanf("%s",prenume);
                for(int i=0; i<contorUsers; i++)
                {
                    if(strcmp(users[i].prenume,prenume)!=0)
                        k=1;
                    if(strcmp(users[i].prenume,prenume)==0)
                    {
                        k=0;
                        break;
                    }
                    if(i==(contorUsers-1) && k==1)
                    {
                        printf("Acest contact nu exista in agenda telefonului\n\nVa rugam sa mai incercati odata\n");
                        printf("\nStergere contact\n\n");
                        stergere_contact();
                    }
                }
                if(stergere_nume(nume_cautat)==1)
                {
                    printf("Contactul a fost sters cu succes!\n\n");
                    return;
                }
                else
                {
                    printf("Contact inexistent\n");
                    return;
                }
            }
            else if(Alegere==2)
            {
                int k;
                printf("\nE-mail cautat:\n\n");
                scanf("%s", email_cautat);
                for(int i=0; i<contorUsers; i++)
                    if(strcmp(users[i].email,email_cautat))
                    {
                        k=1;
                        if(strcmp(users[i].email,email_cautat)==0)
                        {
                            k=0;
                            break;
                        }
                        if(i==(contorUsers-1) && k==1 )
                        {
                            printf("Nu exista nicio persoana cu acest e-mail in agenda telefonului\n\nVa rugam mai incercati odata\n\n");
                            printf("Stergere contact\n\n");
                            stergere_contact();
                        }
                    }
                if(stergere_email(email_cautat)==1)
                {
                    printf("Contactul a fost sters cu succes!\n\n");
                    return;
                }
                else
                {
                    printf("Contact inexistent\n");
                    return;
                }
            }
            else if(Alegere==3)
            {
                int k;
                printf("\nNumaru de telefon cautat:\n\n");
                scanf("%s",nr_telefon);
                for(int i=0; i<contorUsers; i++)
                    if(strcmp(users[i].nrTel,nr_telefon)!=0)
                    {
                        k=1;
                        if(strcmp(users[i].nrTel,nr_telefon)==0)
                        {
                            k=0;
                            break;
                        }
                        if(i==(contorUsers-1) && k==1)
                        {
                            printf("Acest numar nu exista in agenda dumneavoastra telefonica\n\nVa rugam sa mai incercati odata\n\n");
                            printf("Editare contact\n\n");
                            modificare_contact();
                        }
                    }
                if(stergere_nr_tel(nr_telefon)==1)
                {
                    printf("Contactul a fost sters cu succes!\n\n");
                    return;
                }
                else
                {
                    printf("Contact inexistent\n");
                    return;
                }
            }
        }
        while(Alegere == 1 || Alegere == 2 || Alegere==3);
    else
    {
        printf("Alegere invalida.\n\n");
        stergere_contact();
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}
void SaveDataToFile()
{
    FILE *fptr;
    fptr = fopen("D:\\CodeBlocks\\pp\\Agenda.txt","w");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    for(int i=0; i<contorUsers; i++)
    {
        fprintf(fptr,"%s",users[i].prenume);
        fprintf(fptr,",");
        fprintf(fptr,"%s",users[i].nume);
        fprintf(fptr,",");
        fprintf(fptr,"%d",users[i].varsta);
        fprintf(fptr,",");
        fprintf(fptr,"%s",users[i].nrTel);
        fprintf(fptr,",");
        fprintf(fptr,"%s",users[i].email);
        fprintf(fptr,"\n");
    }
    fclose(fptr);



}
void AfiseazaMeniu()
{

    int alegere;
    do
    {
        ScrieOptiuni();
        printf("Alegerea dumneavoastra este: ");
        scanf("%d",&alegere);

        if(alegere==1)
        {
            printf("\n\nAdaugare Contact\n\n");
            adaugare_contact();
            printf("\nAlegeti o alta actiune.\n");
            AfiseazaMeniu();
            break;
        }
        else if(alegere==2)
        {
            printf("\n\nStergere contact\n\n");
            stergere_contact();
            printf("\nAlegeti o alta actiune.\n");
            AfiseazaMeniu();
            break;
        }
        else if(alegere==3)
        {
            printf("\n\nEditare contact \n\n");
            modificare_contact();
            printf("\nAlegeti o alta actiune.\n");
            AfiseazaMeniu();
            break;
        }
        else if(alegere==4)
        {
            printf("\n\nVizualizare lista de contacte: \n\n");
            printf("Lista de contacte: \n");
            printf("<============================================================================================>\n\n");
            //printUserInConsole(splitLineToUser(char str[maxCharsPerLine]));
            for(int i=0; i<contorUsers; i++)
                printUserInConsole(users[i]);
            printf("\nAlegeti o alta actiune.\n");
            AfiseazaMeniu();
            break;
        }
        else if(alegere==0)
        {
            SaveDataToFile();
            printf("\nVa multumim ca ati folosit serviciile noastre.\n\n\n");
            exit(0);
        }
        else
        {
            printf("Alegere invalida.\n\nAlegeti o alta actiune.\n\n\n");
            AfiseazaMeniu();
            continue;
        }
    }
    while(alegere<4);
}
int main()
{
    start();

    return 0;
}
