// ************************************************************************************************
// Autor: Helmut Klaus, BFW Dortmund e.V. Fachinformatiker für Systemintegration
// Kundendatenbank für logistische Betriebe 1.0
// ************************************************************************************************

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

#define MAX 100

struct vk2
{
     string name;
     string vorname;
     string telefon; // Telefonnummer des Kunden
};

// * * * P R O TO T Y P E N * * *
void startmenue();
void kundeneumenue(vector<vk2> &liste);
void startanzeige();
void gebeaus(vector<vk2> &liste);
void speicher(struct vk * p);
void laden(struct vk ** p);
void naechsteseite();
void killallpoints(struct vk ** p);

// * * * S T R U K T U R * * *
struct vk
{
     char name[MAX]; // Nachname des Kunden
     char vorname[MAX]; // Vorname des Kunden
     char tel[MAX]; // Telefonnummer des Kunden
     struct vk *nf; //Nachfolgeradresse verkettete Liste
};


// * * * G L O B A L V A R S * * *
int kundencount=0;

// * * * GLOBALES FELD KUNDE ANLEGEN * * *
struct vk *start=(struct vk *)malloc(sizeof(struct vk));
vector <vk2> start2;
// * * * H A U P T P R O G R A M M * * *
int main()
{
  //Menüauswahl
     startanzeige();
     startmenue();
  //PROGRAMMENDE
}

// * * * F U N K T I O N E N * * *
void startmenue()
{
     char eingabe;
     while(1) // Schleife für Menüpunkt Kundeneingabe
     {
         eingabe=getchar();
         fflush(stdin);
         switch(eingabe)
         {
             case '1':
                 kundeneumenue(start2);
                 break;
             case '2':
                 gebeaus(start2);
                 break;
             case '3':
                 speicher(start);
                 break;
             case '4':
                 laden(&start);
                 break;
             case '9':
                 killallpoints(&start);
                 exit(EXIT_FAILURE);
                 break;
             default:
                 break;
         }
     }
}

void startanzeige() // Aufbau des Startbildschirms mit Auswahlmöglichkeiten
{
     system("cls");
     cout << "--------------------------------------------------------------------------------" << endl;
     cout << "- ---<<< KUNDENDATENBANK V1.0 >>>--- -" << endl;
     cout << "--------------------------------------------------------------------------------" << endl;
     cout << "- -" << endl;
     cout << "- -"<< endl;
     cout << "- 1> Kunden anlegen -" << endl;
     cout << "- 2> Kunden zeigen -" << endl;
     cout << "- 3> Speichern der Datenbank ('DB.DAT') -" << endl;
     cout << "- 4> Datenbank einladen -" << endl;
     cout << "- -" << endl;
     cout << "- -" << endl;
     cout << "- -" << endl;
     cout << "- 9> Programm beenden -" << endl;
     cout << "- -" << endl;
     cout << "- -" << endl;
     cout << "- -" << endl;
     cout << "- -" << endl;
     cout << "- -" << endl;
     cout << "- -" << endl;
     cout << "- -" << endl;
     cout << "--------------------------------------------------------------------------------" << endl;
     cout << "Ihre Eingabe: " << endl;
}

void kundeneumenue(vector<vk2> &liste)
{
     string eingabe1,eingabe2,eingabe3;
     system("cls");
     cout << "--------------------------------------------------------------------------------" << endl;
     cout << "- ---<<< KUNDENDATENBANK V1.0 >>>--- -" << endl;
     cout << "--------------------------------------------------------------------------------" << endl;
     //NAME
     cout << "\nBitte Namen eingeben: ";
     cin >> eingabe1;

     //VORNAME
     cout << "\nBitte Vorname eingeben: ";
     cin >> eingabe2;
     //TEL
     cout << "\nBitte Tel.Nr. eingeben: ";
     cin >> eingabe3;
     //ZURüCK ZUM MENü
     liste.push_back({eingabe1,eingabe2,eingabe3});
     startanzeige();
}

void gebeaus(vector<vk2> &liste)
{
     char buffer;
     int counter=0;
     if(liste.size()==0) // Schleife für leeren Bestand
     {
         system("cls");
         cout << "--------------------------------------------------------------------------------" << endl;
         cout << "- ---<<< KUNDENDATENBANK V1.0 >>>--- -" << endl;
         cout << "--------------------------------------------------------------------------------" << endl;
         cout << "- DIE DATENBANK BEINHALTET NOCH KEINEN KUNDEN .... -" << endl;
         cout << "--------------------------------------------------------------------------------" << endl;
     }
     else
     {
         system("cls");
         cout << "--------------------------------------------------------------------------------" << endl;
         cout << "- ---<<< KUNDENDATENBANK V1.0 >>>--- -" << endl;
         cout << "--------------------------------------------------------------------------------\n" << endl;

         for(vk2 akt : liste){
           cout << akt.vorname << " " << akt.name << " " << akt.telefon <<endl;
         }
     }
     cout << "\nENTER fuer weiter..." << endl;
     scanf("%c",&buffer);
     startanzeige();
}

void speicher(struct vk * p)
{
     char buffer;
     FILE* file;
     if(kundencount==0) // Text bei Eingabe 0
     {
         system("cls");
         cout << "--------------------------------------------------------------------------------" << endl;
         cout << "- ---<<< KUNDENDATENBANK V1.0 >>>--- -" << endl;
         cout << "--------------------------------------------------------------------------------" << endl;
         cout << "- DIE DATENBANK BEINHALTET NOCH KEINEN KUNDEN .... -" << endl;
         cout << "--------------------------------------------------------------------------------" << endl;
     }
     else
     {
         system("cls");
         cout << "--------------------------------------------------------------------------------" << endl;
         cout << "- ---<<< KUNDENDATENBANK V1.0 >>>--- -" << endl;
         cout << "--------------------------------------------------------------------------------\n" << endl;
         cout << " speicher..." << endl;
         file = fopen("C:\\db.dat","wb");
         if(file==NULL)
             cout << "\n FEHLER BEIM OEFFNEN DER DATEI...\n" << endl;
         else
         {
             if(p==NULL)
                 cout << "...gespeichert!!!\n" << endl;
             else
             {
                 while(p!=NULL)
                 {
                     cout << file,"%100s%100s%100s",p->vorname, p->name, p->tel;
                     p=p->nf;
                     cout << "." << endl;
                 }
                 cout << "...gespeichert!!!\n" << endl;
             }
             fclose(file);
         }
     }

     cout << "\nENTER fuer weiter..." << endl;
     scanf("%c",&buffer);
     startanzeige();
}

void laden(struct vk ** p)
{
     char n[MAX],v[MAX],t[MAX];
     FILE* file;
     char buffer;
     int rc;
     struct vk * kopie = *p; //Sicherung Startadresse 1.Element
     system("cls");
     cout << "--------------------------------------------------------------------------------" << endl;
     cout << "- ---<<< KUNDENDATENBANK V1.0 >>>--- -" << endl;
     cout << "--------------------------------------------------------------------------------" << endl;
     cout << " lade..." << endl;
     file=fopen("c:\\db.dat","rb");
     if(file==NULL)
         cout << "\n FEHLER BEIM OEFFNEN DER DATEI...\n" << endl;
     else
     {
         rc=fscanf(file,"%100s%100s%100s",&v,&n,&t);
         while(rc!=EOF) //bis Dateiende
         {
             kopie = *p; //Sicherung
             *p =(struct vk *)malloc(sizeof(struct vk)); //Neues Element einfügen
             strcpy((*p)->name,n);
             strcpy((*p)->vorname,v);
             strcpy((*p)->tel,t);
             if(kundencount==0)
                 (*p)->nf=NULL; //Adresszuweisung bei ersten Kunden
             else
                 (*p)->nf=kopie; //Adresszuweisung
             kundencount++;
             cout << "." << endl;
             rc=fscanf(file,"%100s%100s%100s",&v,&n,&t);
         }
         cout << "...fertig!!!\n" << endl;
     }
     cout << "\nENTER fuer weiter..." << endl;
     scanf("%c",&buffer);
     startanzeige();
}

void naechsteseite()
{
     char buffer;
     cout << "\nENTER fuer naechste Seite..." << endl;
     scanf("%c",&buffer);
     system("cls");
     cout << "--------------------------------------------------------------------------------" << endl;
     cout << "- ---<<< KUNDENDATENBANK V1.0 >>>--- -" << endl;
     cout << "--------------------------------------------------------------------------------\n" << endl;
}

void killallpoints(struct vk ** p)
{
     int counter=1;
     struct vk * kopie = *p;
     if(kundencount==0)
         counter=0;
     else
     {
         while((*p)->nf!=NULL) //bis Listenende
         {
             kopie = *p; //Sicherung
             counter++;
             (*p)=(*p)->nf;
             free(kopie);
         }
         free(*p);
     }
     cout << "%i gelöschte Pointer bei Programmende...\n",counter;
}
