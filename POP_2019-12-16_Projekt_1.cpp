/*
    Projekt na studia: Baza Specjalistów. 
*/ 

//biblioteki (dozwolne jedynie iostream)
#include <iostream>
using namespace std;
//Struktury:
// 1. Lekarz
struct lekarz
{
    unsigned short id;                                                                                                                          //         Numer specjalisty.
    string imie;                                                                                                                               //          Imię specjalisty.                                      
    string nazwisko;                                                                                                                          //           Nazwisko specjalisty.    
    string nazwa_osrodka;                                                                                                                    //            Nazwa ośrodka, w którym pracuje.
    string specjalnosc;                                                                                                                     //             Specjalizacja specjalisty.
    string e_mail;                                                                                                                         //              E-mail kontaktowy do danego lekarza.
    unsigned short liczba_pacjentow_aktualnie_zarejestrowanych;                                                                           //              Liczba pacjentów aktualnie zarejestrowanych do danego specjalisty.
    lekarz *wskaznik;
};
// 2.Opinie
struct opinia
{
    unsigned short id_lekarza; 
    string dane_autora;                                                                                                            
    string tresc;                                                                                                                      
    opinia  *wskaznik;                                                                                                               
};
//Spis funkcji.
void funkcja_wyszukujaca_lekarzy(lekarz *&poczatek, opinia *&start); 			                                                //  65-107
void Wyszukiwanie_najszybszej_wizyty(lekarz *&poczatek,opinia *&start);		                                                   //   109-143
void Dodawanie_lekarzy(lekarz *&poczatek);					                                                                  //    145-197
void FRONT_PAGE();								                                                                             //     199-210
void menu(lekarz *&poczatek,unsigned short wybor, opinia *&start);	  	                                                    //	    212-225
void panel_administracyjny(lekarz *&poczatek);				                                                               //	    227-248
void Wyswietlanie_lekarzy(lekarz *&poczatek);					                                                          //	    250-269
void wyszukiwanie_po_osrodku(lekarz *&poczatek, opinia *&start);	                                                   	 //	        271-299
void dodawanie_opinii(lekarz *&podajnik,opinia *&start);			                                                    //	        301-329
void karta_lekarza(lekarz *&podajnik, opinia *&licznik);                                                               //	        331-381
void wybierz_lekarza(lekarz *&poczatek, opinia *&start);		                                                      //	        383-415
void dodawanie_opinii2(opinia *&start);					                                                             //             417-447
void Usuwanie_lekarzy(lekarz *&poczatek,opinia *&start);		                                                    //		        449-465
void Usun_lekarza(lekarz *&poczatek);					                                                           //               467-488
void edytowanie_danych_lekarzy(lekarz *&poczatek);		                                                    	  //		        490-541
int main()
{
    lekarz *poczatek;                                                                                       // Tworzenie listy lekarzy.
    opinia *start;                                                                                         //  Tworzenie listy opinii.
	poczatek = NULL;                                                                                      //   Ustawianie listy lekarzy na początku.
    start = NULL;                                                                                        //    Ustawianie listy opinii na początku.
    unsigned short wybor=0;
    do
    {
        FRONT_PAGE();                                                                                //       Wyświetlania opcji dostępnych dla użytkownika.
        cin>>wybor;                                                                                 //        Pobieranie wyboru użytkownika.
        cin.get();
       menu(poczatek,wybor,start);                                                                //          Wybór użytkownika przechodzi do realizacji.
    } while (wybor!=7);                                                                          //           Całość znajduje się w pętli. Program nie zamknie się bez stanowczej decyzji użytkownika.
    Usuwanie_lekarzy(poczatek,start);                                                           //            Gdy użytkownik podejmie decyzję o zakończeniu pracy programu. Ta funkcja zwolni miejsce w pamięci zajmowane przez listy.
    return 0;
}
//-------------------------------------------------------------------------- Funkcje:
//Funkcja wyszukująca Lekarzy---------------------------------------------------------------------------------------------------------------1----------------------------------------------------
void funkcja_wyszukujaca_lekarzy(lekarz *&poczatek, opinia *&start)
{
    string napis, napis_h;
    unsigned char pomocnik;
    lekarz *podajnik;
    unsigned short znaleziono=0;
    cout<<"szukaj: ";
  getline(cin, napis);                                                                                        //Pobranie wiersza z klawiatury.
  napis_h = "";                                                                                              // Zerowanie zmiennej odpowiedzialnej za pojedyńcze słowo.
  napis += " ";                                                                                             //  Dodanie do napisu pomocnika.
  for(unsigned short i = 0; i < napis.length(); i++)                                                       //   Pętla działająca tyle razy ile znaków wprowadzi użytkownik z klawiatury.
  {
    pomocnik = napis [ i ];                                                                                 //  Przypisanie zmiennej pomocniczej wartości pierwszego znaku.
    if(((pomocnik >= '0') && (pomocnik <= '9')) || (pomocnik == '_') || (pomocnik == '-')  ||              //   Jeżeli zmienna pomocnicza należy do podanego przedziału znaku i cyfr to dodaj ją do słowa.
       ((pomocnik >= 'A') && (pomocnik <= 'Z')) ||((pomocnik >= 'a') && (pomocnik <= 'z')) ||
        (pomocnik == 164) || (pomocnik == 165)  || (pomocnik == 143) || (pomocnik == 134)  ||
        (pomocnik == 168) || (pomocnik == 169)  || (pomocnik == 157) || (pomocnik == 136)  ||
        (pomocnik == 227) || (pomocnik == 228)  || (pomocnik == 224) || (pomocnik == 162)  ||
        (pomocnik == 151) || (pomocnik == 152)  || (pomocnik == 141) || (pomocnik == 171)  ||
        (pomocnik == 189) || (pomocnik == 190))
       napis_h += pomocnik;
    else if(napis_h != "")                                                                             //       Jeżeli słowo istnieje. To przeszukaj listę w poszukiwaniu tego samego słowa.
    {                                                                                                 //        Jeżeli takie słowo istnieje to wyświetl cały element tej listy. Według schematu.
        podajnik = poczatek;
        while(podajnik)
        {   
            if((podajnik->imie==napis_h)||(podajnik->nazwisko==napis_h)||(podajnik->nazwa_osrodka==napis_h)||(podajnik->specjalnosc==napis_h)||(podajnik->e_mail==napis_h))
            { 
                znaleziono++;
                cout << "id: " << podajnik->id
                << ", imi\251: " << podajnik->imie
                << ", nazwisko: " << podajnik->nazwisko 
                << ", nazwa osrodka: " << podajnik->nazwa_osrodka
                << ", specjalno\230\206: " << podajnik->specjalnosc 
                << ", liczba pacjent\242w: " << podajnik->liczba_pacjentow_aktualnie_zarejestrowanych  
                << endl;                               
            }
            podajnik = podajnik->wskaznik;
        }
        napis_h = "";                                                                          //              Wyzeruj słowo by móc wprowadzić kolejne.
    }
  }
}
//Funkcja wybierająca lekarz z najmniejsza iloscią pacjentów obecnie zarejestrowanych-------------------------------------------------------2---------------------------------------------------------
void Wyszukiwanie_najszybszej_wizyty(lekarz *&poczatek,opinia *&start)
{
    lekarz *podajnik;
    podajnik = poczatek;
    unsigned short id_duplikat;                                                                                                                          
    string imie_duplikat;                                                                                                           //Tworzenie duplikatów jednego elementu tablicy.                                                                                                           
    string nazwisko_duplikat;                                                                                                                             
    string nazwa_osrodka_duplikat;                                                                                                                  
    string specjalnosc_duplikat;                                                                                                             
    string e_mail_duplikat;                                                                                                                      
    unsigned short liczba_pacjentow_duplikat=podajnik->liczba_pacjentow_aktualnie_zarejestrowanych;
    while(podajnik)                                                                                                             //   Przeszukiwanie tablicy.
    {   
        if(liczba_pacjentow_duplikat>=podajnik->liczba_pacjentow_aktualnie_zarejestrowanych)                                  //     Jeżeli znajdzie się lekarz z mniejszą ilością pacjentów to zapisze jego dane do duplikatu.
        {
            id_duplikat= podajnik->id;
            imie_duplikat= podajnik->imie;
            nazwisko_duplikat= podajnik->nazwisko;
            e_mail_duplikat = podajnik->e_mail;
            nazwa_osrodka_duplikat = podajnik->nazwa_osrodka;
            specjalnosc_duplikat = podajnik->specjalnosc;
            liczba_pacjentow_duplikat = podajnik->liczba_pacjentow_aktualnie_zarejestrowanych;  
        }
        podajnik = podajnik->wskaznik;
    }
    cout<<"Lekarz z najmniejsz\245 liczb\245 pacjent\242w: "<<endl;                                                    //          Wypisz duplikat z najmniejszą ilością pacjentów.
        cout << "id: " << id_duplikat
            << ", imi\251: " << imie_duplikat
            << ", nazwisko: " << nazwisko_duplikat
            <<", e-mail: "<<e_mail_duplikat
            << ", nazwa osrodka: " << nazwa_osrodka_duplikat
            << ", specjalno\230\206: " << specjalnosc_duplikat
            << ", liczba pacjent\242w: " << liczba_pacjentow_duplikat 
            << endl;
}
//Funkcja dodająca lekarzy do bazy----------------------------------------------------------------------------------------------------------3-------------------------------------------------------------------------------------------------------------------------
void Dodawanie_lekarzy(lekarz *&poczatek)
{
    lekarz *podajnik;
    podajnik = poczatek;
    cout<<"Podaj ilu lekarzy chcesz wpisa\206 na list\251: ";
    unsigned short ilosc_dodawanych=0;
    cin>>ilosc_dodawanych;                                                                                     //Podaj ile elementów chcesz wpisać na listę.
    while(ilosc_dodawanych!=0)
    {
        unsigned short a=0;
        podajnik = new lekarz;
         cout<<"Podaj id: ";
        cin >> podajnik->id;
        unsigned short test_id=podajnik->id;
        if(cin.fail())                                                                                     //    Kontrola błędu.
        {
            cin.clear();
            a++;
        }
        cin.get();
        cout<<"Podaj imi\251: ";
        cin>>podajnik->imie;
        cout<<"Podaj nazwisko: ";
        cin>>podajnik->nazwisko;
        cout<<"Podaj e-mail: ";
        cin>>podajnik->e_mail;
        cout<<"Podaj nazwa_o\230rodka: ";
        cin.get();
        getline( cin, podajnik->nazwa_osrodka);
        cout<<"Podaj specjalno\230\206: ";
        getline(cin,podajnik->specjalnosc);
        cout<<"Podaj liczba pacjent\242w aktualnie zarejestrowanych: ";
        cin>>podajnik->liczba_pacjentow_aktualnie_zarejestrowanych;
        if(cin.fail())                                                                              //          Kontrola błędu.
        {
            cin.clear();
            a++;
        }
        cin.get();
        cout<<"---------------------------------------------------------------------------------------------------"<<endl;
        if(a!=0)                                                                               //               Informacja o błędach.
            cout<<"Niepoprawne Dane! "<<"Pop\210eniono: "<<a<<" b\210\251d\242w "<<"Prosz\251 wprowadzi\206 dane ponownie."<<endl; 
        else
        {
            podajnik->wskaznik = poczatek;
            poczatek = podajnik;
            ilosc_dodawanych--;
        }
        cin.clear();
    }
    system("CLS");
    cout<<"Dodano lekarzy pomy\230lnie: ";
}
// Funkcja odpowiedzialna za wyświetlanie dostępnych opcji użytkownika----------------------------------------------------------------------4--------------------------------------------------------------------------------------
void FRONT_PAGE()
{
    cout<<endl;
    cout<<"                                        Baza specjalist\242w                                         "<<endl;
    cout<<endl;
    cout<<"---------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Wyszukiwanie lekarzy wybierz: 1                                    Wyszykiwanie o\230rodka wybierz: 2"<<endl;
    cout<<"Lekarz z najmniejsz\245 kolejk\245: 3                                          Panel administracyjny: 4"<<endl;
    cout<<"wybierz lekarza: 5                                                              dodawanie opinii: 6"<<endl;
    cout<<"Wyj\230cie z programu 7"<<endl;
    cout<<"Wprowad\253 sw\242j wyb\242r: ";
}
//Funkcja odpowiedzialna za switch'a obsługującego funkcje dostępne dla normalnego użytkownika----------------------------------------------5-----------------------------------------------------------------------------------------------
void menu(lekarz *&poczatek,unsigned short wybor, opinia *&start)
{
    switch (wybor)
	{
        case 1: system("CLS"); funkcja_wyszukujaca_lekarzy(poczatek,start);                 break;                                                
        case 2: system("CLS"); wyszukiwanie_po_osrodku(poczatek,start);                     break;                                                     
        case 3: system("CLS"); Wyszukiwanie_najszybszej_wizyty(poczatek,start);             break;                                     
        case 4: system("CLS"); panel_administracyjny(poczatek);                             break;  
        case 5: system("CLS"); wybierz_lekarza(poczatek,start);                             break;
        case 6: system("CLS"); dodawanie_opinii2(start);                                    break; 
        case 7: system("CLS"); cout<<"Zamykanie programu!"<<endl;                           break;                                                           
        default: cout<<"Niestety wybrana opcja nie istnieje.";                              break;
	}
}
//Funkcja posiadająca dostęp do funkcji administracyjnych, niedostępnych dla normalnego użytkownika-----------------------------------------6---------------------------------------------------------------------------------------------------------------------------
void panel_administracyjny(lekarz *&poczatek)
{
    cout<<endl;
    cout<<"                                       Panel Administracyjny                                       "<<endl;
    cout<<endl;
    cout<<"---------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Dodawanie lekarzy wybierz: 1                                            Usuwanie lekarzy wybierz: 2"<<endl;
    cout<<"Edytowanie danych lekarzy wybierz: 3                                Powr\242t do ekranu g\210\242wnego: 4"<<endl;
    cout<<"Wprowad\253 sw\242j wyb\242r: ";
    unsigned short wybor;
    cin>>wybor;
     switch (wybor)
	{
        case 1: system("CLS"); Dodawanie_lekarzy(poczatek);               break;                                                
        case 2: system("CLS"); Usun_lekarza(poczatek);                     break;                                                     
        case 3: system("CLS"); edytowanie_danych_lekarzy(poczatek);       break;                                     
        case 4: system("CLS"); main();                                    break;                                                                      
        default:
        cout<<"Niestety wybrana opcja nie istnieje.";                                     
        break;
	}
}
//Funkcja Wyświetlająca lekarzy z listy-----------------------------------------------------------------------------------------------------7---------------------------------------------------------------------------------------------------------------
void Wyswietlanie_lekarzy(lekarz *&poczatek)
{
    lekarz *podajnik;
    podajnik = poczatek;
    cout<<"---------------------------------------------------------------------------------------------------"<<endl;
    while(podajnik)
    {
        cout << "id: " << podajnik->id
            << ", imi\251: " << podajnik->imie
            << ", nazwisko: " << podajnik->nazwisko
            <<", e-mail: "<<podajnik->e_mail  
            << ", nazwa osrodka: " << podajnik->nazwa_osrodka
            << ", specjalno\230\206: " << podajnik->specjalnosc 
            << ", liczba pacjent\242w: " << podajnik->liczba_pacjentow_aktualnie_zarejestrowanych  
            << endl;

        podajnik = podajnik->wskaznik;
    }
    cout<<"---------------------------------------------------------------------------------------------------"<<endl;
}
//Funkcja wyszukująca lekarzy w danym ośrodku-----------------------------------------------------------------------------------------------8------------------------------------------------------------------------------------------------------------------------------
void wyszukiwanie_po_osrodku(lekarz *&poczatek, opinia *&start)
{
    string napis;
    unsigned short znaleziono=0;
    cout<<"szukaj: ";
    getline(cin, napis);                                                            
    for(unsigned short i=0; i<napis.length(); i++)                                          // Pętla jeżeli napotka nieporządany znak wprowadzony z klawiatury. Usunie go.                                  
    {
        if((napis[i]==',')||(napis[i]=='.'))
            napis[i]='\0';        
    }
    lekarz *podajnik;
    podajnik = poczatek;
    while(podajnik)                                             
    {   
        if(podajnik->nazwa_osrodka==napis)                                              //    Jeżeli istnieje ośrodek o podanej nazwie to funkcja wyświetli wszystkich lekarzy w nim pracujących.
        {
            znaleziono++;
            cout << "id: " << podajnik->id
            << ", imi\251: " << podajnik->imie
            << ", nazwisko: " << podajnik->nazwisko 
            << ", nazwa osrodka: " << podajnik->nazwa_osrodka
            << ", specjalno\230\206: " << podajnik->specjalnosc 
            << ", liczba pacjent\242w: " << podajnik->liczba_pacjentow_aktualnie_zarejestrowanych  
            << endl;                                            
            }
            podajnik = podajnik->wskaznik;
        }                                                                   
}
// Funkcja do dodawania opinii przed obejrzeniem karty lekarza------------------------------------------------------------------------------9---------------------------------------------------------------------------------
void dodawanie_opinii(lekarz *&podajnik,opinia *&start)
{
    opinia *p;
    p = start;
    p = new opinia;
    p->id_lekarza=podajnik->id;                                                                                                       //         Przypisanie numeru lekarza do numeru opinii.
    cin.get();
    cout<<"Podaj swoje imie i nazwisko: ";
    getline( cin, p->dane_autora);
    cout<<"Napisz swoj\245 opini\251: (Pami\251taj, \276e opinia nie mo\276e mie\206 wi\251cej ni\276 60 znak\242w!) ";
    getline(cin,p->tresc);
    if(p->tresc.length()>=60)                                                                                                       //            Jeżeli treść opinii jest dłuższa, niż możliwa to zostanie skrócona.
    {
        for(unsigned short i=50; i<p->tresc.length(); i++)
        {
            if(p->tresc[i]==' ')
            {
                for(unsigned short j=i; j<p->tresc.length(); j++)
                    {
                        p->tresc[j]='\0';
                    }
            }
       }
    }
    p->wskaznik = start;
    start = p;
    cin.clear();
    system("CLS");  
}
// Funkcja  wyświetlająca pełną kartę lekarza-----------------------------------------------------------------------------------------------10-----------------------------------------------------------------------------
void karta_lekarza(lekarz *&podajnik, opinia *&licznik)
{
            if (podajnik->id==licznik->id_lekarza)
            {
                cout<<"                                                  Karta lekarza                                    "<<endl;
                cout<<endl;
                cout<<"---------------------------------------------------------------------------------------------------"<<endl;    
                cout<<left<<"id: ";
                cout<<left<< podajnik->id;
                cout.width(70);
                cout<<right<<"autor: ";
                cout<<right<<licznik->dane_autora;
                cout<<endl;
                cout<<left<<"imi\251 i nazwisko:  " <<left<<podajnik->imie<<" "<<left<<podajnik->nazwisko;
                cout.width(70);
                cout<<right<<licznik->tresc;
                cout<<endl;
                cout<<left<<"e-mail: "<<left<<podajnik->e_mail<<endl;
                cout<<left<<"nazwa osrodka: " <<left<< podajnik->nazwa_osrodka<<endl;
                cout<<left<< "specjalno\230\206: " <<left<< podajnik->specjalnosc<<endl;
                cout<<left<<"liczba pacjent\242w: " <<left<< podajnik->liczba_pacjentow_aktualnie_zarejestrowanych<<endl;
                cout<<endl;
                cout<<"---------------------------------------------------------------------------------------------------"<<endl;
                cout<<"Wybierz 1 aby przeczyta\206 kolejn\245 opini\251 lub cokolwiek innego by wr\242ci\206 do strony g\210\242wnej. ";
                unsigned short x;
                cin>>x;
                if(x==1)
                {
                    if(!licznik->wskaznik)
                    {
                        system("CLS");
                        cout<<"Lekarz nie ma wi\251cej opinii!"<<endl;
                    
                    }
                    else
                    {
                        system("CLS");
                         licznik=licznik->wskaznik;
                        karta_lekarza(podajnik,licznik);
                    }
                }
                else
                {
            
                } 
            }
            else
            {
                licznik=licznik->wskaznik;
            }
}
// Funkcja w której użytkownik podejmuje wybór, którego lekarza kartę chce zobaczyć---------------------------------------------------------11-----------------------------------------------------------------------------------------
void wybierz_lekarza(lekarz *&poczatek, opinia *&start)
{
    lekarz *podajnik;
    podajnik = poczatek;
    opinia *licznik;
    licznik = start;
    unsigned short test=0;
    cout<<"Podaj numer identyfikacyjny lekarza, kt\242rego chcesz zobaczy\206: ";
    unsigned short nr;
    cin>>nr;
    while(podajnik)
    {
        if(podajnik->id==nr)
        {
            cout<<"Pozostaw swoj\245 opini\251 odno\230nie lekarza "<<podajnik->imie<<" "<<podajnik->nazwisko<<endl;
           dodawanie_opinii(podajnik,start);
           karta_lekarza(podajnik,licznik);
        }
        podajnik = podajnik->wskaznik;
    }
    if(test==0)
    {
        system("CLS");
        cout<<"Nie znaleziono lekarza o tym numerze identyfikacyjnym: "<<nr<<endl;
        cout<<"Aby wybra\206 ponownie wybierz 1. Aby  wr\242ci\206 do strony g\210\242wnej wybierz cokolowiek innego."<<endl;
        unsigned short o=0;
        cin>>o;
        if(o==1)
            wybierz_lekarza(poczatek,start);
    
         
    }
}
// Funkcja pozwalająca dodać opinię wprost z perspektywy menu() bez konieczności oglądania karty lekarza------------------------------------12-----------------------------------------------------------------------------------------------
void dodawanie_opinii2(opinia *&start)
{
    opinia *p;
    p = start;
    p = new opinia;
    cout<<"Podaj id lekarza, kt\242remu chcesz wystawi\206 opini\251 ";
    cin>>p->id_lekarza;
    cin.get();
    cout<<"Podaj swoje imie i nazwisko: ";
    getline( cin, p->dane_autora);
    cout<<"Napisz swoj\245 opini\251: (Pami\251taj, \276e opinia nie mo\276e mie\206 wi\251cej ni\276 60 znak\242w!) ";
    getline(cin,p->tresc);
    if(p->tresc.length()>=60)
    {
        for(unsigned short i=60; i<p->tresc.length(); i++)
        {
            if(p->tresc[i]==' ')
            {
                for(unsigned short j=i; j<p->tresc.length(); j++)
                    {
                        p->tresc[j]='\0';
                    }
            }
       }
    }
    p->wskaznik = start;
    start = p;
    system("CLS");
    cin.clear();  
    cout<<"Opini\251 dodano pomy\230lnie! "<<endl;
}
//Funkcja usuwająca lekarzy z listy---------------------------------------------------------------------------------------------------------13-------------------------------------------------------------------------------------
void Usuwanie_lekarzy(lekarz *&poczatek,opinia *&start)
{
    lekarz *podajnik;
    opinia *podajnik2;
    while(poczatek)
    {
        podajnik = poczatek;
        poczatek = poczatek->wskaznik;
        delete podajnik;
    }
    while(start)
    {
        podajnik2 = start;
        start = start->wskaznik;
        delete podajnik;
    }
}
//Funkcja odpowiedzialna za usuwanie wybrango lekarza z bazy--------------------------------------------------------------------------------14------------------------------------------------------------------------------------------------
void Usun_lekarza(lekarz *&poczatek)
{
    lekarz *podajnik;
    podajnik = poczatek;
    unsigned short numer_id=0;
    cout<<"Podaj numer identyfikacjyny lekarza. Kt\242rego chcesz usuna\206: ";
    cin>>numer_id;
    while (podajnik->wskaznik != NULL)
    {
        if (podajnik->wskaznik->id == numer_id )                                                    // Jeżeli numer id się zgadza z numerem elementu przeprzedzającego 
        {
            lekarz *usuwany=podajnik->wskaznik;                                                    //  zapamiętujemy usuwany element 
            podajnik->wskaznik = usuwany->wskaznik;                                               //   przestawiam wskaźnik  by omijał usuwany element 
            free(usuwany);                           
            cout<<"Lekarz usuni\251ty pomy\230lnie!"<<endl;
        } 
        else 
        {
            podajnik = podajnik->wskaznik;                                                    //       Jeżeli nie usuwany to idziemy dalej.
        }  
    }          
}
//Funkcja edytujaca lekarzy  po numerze identyfikacyjnym------------------------------------------------------------------------------------15------------------------------------------------------------------------------------------------------------
void edytowanie_danych_lekarzy(lekarz *&poczatek)
{
    unsigned short nr;
    cout<<"Edytuj dane lekarza o numerze identyfikacyjnym: ";
    cin>>nr;
    lekarz *podajnik;
    podajnik = poczatek;
        while(podajnik)
        {   
            if(podajnik->id==nr)
            {
                string imie=podajnik->imie;                                                                                                                                                          
                string nazwisko=podajnik->nazwisko;                                                                                                                           
                string nazwa_osrodka=podajnik->nazwa_osrodka;                                                                                                                      
                string specjalnosc=podajnik->specjalnosc;                                                                                                         
                string e_mail=podajnik->e_mail;                                                                                                                           
                unsigned short liczba_pacjentow_aktualnie_zarejestrowanych=podajnik->liczba_pacjentow_aktualnie_zarejestrowanych;             
                cout << "id: " << podajnik->id;
                cout<< "imi\251( " << podajnik->imie<<" )";
                cout<<" nowe imi\251: ";
                cin>>imie;
                cout<< "nazwisko( " << podajnik->nazwisko<<" )";
                cout<<" nowe nazwisko: ";
                cin>>nazwisko; 
                cout<< "nazwa o\230rodka( " << podajnik->nazwa_osrodka<<" )";
                cout<<" nowa nazwa o\230rodka: ";
                cin.get();
                getline(cin,nazwa_osrodka);
                cout<< "specjalno\230\206( " << podajnik->specjalnosc<<" )";
                cout<<" nowa specjalnosc: ";
                getline(cin,specjalnosc);
                cout<< "e-mail(  " << podajnik->e_mail<<" )";
                cout<<" nowy e-mail: ";
                cin>>e_mail;
                cout<< "liczba pacjent\242w( " << podajnik->liczba_pacjentow_aktualnie_zarejestrowanych<<" )";
                cout<<" nowa liczba pacjent\242w: ";
                cin>>liczba_pacjentow_aktualnie_zarejestrowanych;  
                cout<< endl;
                podajnik->imie = imie;
                podajnik->nazwisko = nazwisko;
                podajnik->nazwa_osrodka = nazwa_osrodka;
                podajnik->specjalnosc = specjalnosc;
                podajnik->e_mail = e_mail;
                podajnik->liczba_pacjentow_aktualnie_zarejestrowanych = liczba_pacjentow_aktualnie_zarejestrowanych;   
            }
            podajnik = podajnik->wskaznik;
        }
    system("CLS");
    cout<<"Dane edytowane pomy\230lnie! "<<endl;
}