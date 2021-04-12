/*
    Projekt na studia: Spliter
    
*/ 
// Biblioteki: (dozwolone jedynie iostream i fstream)
#include <iostream>
#include <fstream>
using namespace std;
//definicje funkcji:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int zliczanie_bajtow(fstream &pierwszy);                                                                // 31-38
string intToStr(int  numer_pliku);                                                                     //  39-51
string dodawanie_zer(string  q);                                                                      //   52-59
string nazwa_pliku(char* argv[],int numer_pliku);                                                    //    60-74
string naglowek(unsigned int suma_kontrolna,char* argv[],int i,int waga,int ilosc_bajtow);          //     75-84
string nazwa_p(string nazwa);                                                                      //      85-106
unsigned int crc(const string bajty,unsigned int dlugosc);                                        //       107-126
void dodawanie_charow(string &x,unsigned char* t,int liczba_bajtow);                             //        127-133
unsigned int crc_plik(int ilosc,int ilosc_bajtow,fstream &plik);                                //         134-149
void podzial(char* argv[]);                                                                    //          150-185
void scalanie(char*argv[]);                                                                   //           186-226
//Funkcje:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    string a = argv[2];                                                                                 // Pobranie rodzaju operacji z terminala do stringa.
    if((a=="p")||(a=="P"))                                                                             //  Jeżeli p lub P to podział dużego pliku na małe.
        podzial(argv);
    else if((a=="s")||(a=="S"))                                                                      //    Jeżeli s lub S to scalanie małego pliku w duży.
        scalanie(argv);
    return 0;
}
int zliczanie_bajtow(fstream &pierwszy) //Funkcja sumująca ilość wszystkich bajtów w pliku------------------------------------------------------------------------------------------------
{
    unsigned int waga;                                                                                  // Zmienna całkowita, która w wyniku funkcji przekaże ilość wszystkich bajtów.
    pierwszy.seekg( 0, ios::end );                                                                     //  Przesuwa pozycje na koniec.     
    waga = pierwszy.tellg();                                                                          //   Odczytaj pozycje w pliku.
    pierwszy.seekg( 0, ios::beg );                                                                   //    Wraca na poczatek pliku!
    return waga;                                                                                    //     Zwraca wcześniej wspomnianą ilość wszystkich bajtów.
}
string intToStr(int  liczba) // Funkcja zamieniająca inta na stringa----------------------------------------------------------------------------------------------------------------------
{
    string q;                                                                                           // Zmienna pomocnicza.                        
    if(liczba < 0)                                                                                     //  Jeżeli int jest mniejszy od 0 to dodaj minus z przodu w stringu i usuń z inta.
    {
        q = "-";
        liczba = -liczba;
    }
    if(liczba > 9)                                                                                  //     Jeżeli int jest większy od 9 to wywołaj funkcję jeszcze raz.
        q += intToStr(liczba / 10);
        q += liczba % 10 + 48;                                                                
     return q;
}
string dodawanie_zer(string  q) // Pod Funkcja funkcji intToStr, która dodaje zera aby utworzyć 3 cyfrowy numer pod pliku-----------------------------------------------------------------
{
    if(q.length()==1)                                                                                   // Jeżeli liczba jest jednocyfrowa to dodaj przed nią dwa zera.
       q = "00" + q;
    else if(q.length()==2)                                                                            //   Jeżeli liczba jest dwucyfrowa to dodaj przed nią jedno zero.
        q = "0" + q;
    return q;
}
string nazwa_pliku(char* argv[],int numer_pliku)  // Pełna nazwa pliku z nazwą pod pliku. Gotowego do podziału----------------------------------------------------------------------------
{
    string a=nazwa_p(argv[4]);                                                                          // Nazwa pliku który ma być podzielony. 
    string x="";                                                                                       //  Zmienna pomocniczna.
    for(unsigned short i=0; i<a.length(); i++)                                                        //   Dopóki nie pętla nie przejdzie po każdym znaku w nazwie.
    {
        x = x+a[i];                                                                                 //     Dodaj znak z nazwy do zmiennej pomocniczej.
        if(a[i+1]=='.')                                                                            //      Jeżeli napotkasz kropkę w nazwie pliku to przed nią dodaj numer pliku. 
            {
                string q = intToStr(numer_pliku);
                x=x+dodawanie_zer(q);
            }
    }
    return x;                                                                                 //           Zwróć pełną nazwę gotową do przekazania. 
}
string naglowek(unsigned int suma_kontrolna,char* argv[],int i,int waga,int ilosc_bajtow) // Funkcja zwracająca nagłówek do pliku podzielonego--------------------------------------------
{
    int ilosc= waga/ilosc_bajtow;                                                                       // Zmienna przedstawiająca ilość plików podzielonych.
    string rezultat="";                                                                                //  Zmienna pomocnicza do zbudowania nagłówka na stringu.
    rezultat = rezultat + intToStr(waga);                                                             //   Wielkosc pliku dużego przed podziałem.
    rezultat = rezultat + " " + intToStr(ilosc);                                                     //    Ilość plików po podziale.
    rezultat = rezultat + " " + nazwa_pliku(argv,i+1);                                              //     Nazwa następnego pliku.
    rezultat = rezultat + " " +intToStr(suma_kontrolna);
    return rezultat;
}
string nazwa_p(string nazwa)  // Funkcja usuwająca numer z nazwy pliku--------------------------------------------------------------------------------------------------------------------
{
    string x="";                                                                                        // Zmienna pomocniczna.
    for(unsigned short i=0; i<nazwa.length(); i++)                                                     //  Dopóki pętla nie przejdzie po każdym znaku w nazwie.
    { 
        switch( nazwa[i] )                                                                           //    Switch kasuje wszystkie liczby od 0 do 9 w stringu z nazwą.
        {
            case '0':break;
            case '1':break;
            case '2':break;
            case '3':break;
            case '4':break;
            case '5':break;  
            case '6':break;
            case '7':break;
            case '8':break;  
            case '9':break;                 
            default:{x=x+nazwa[i];break;} 
        }
    }
    return x;                                                                              //              Zwróć pełną nazwę gotową do przekazania. 
}
unsigned int crc(const string bajty,unsigned int dlugosc)// Funkcja obliczająca crc dla podanego  ciągu danych-----------------------------------------------------------------------------
{
    int dzielnik = 0xA001;                                                            
    int crc = 0xFFFF;                        
    for(unsigned int i = 0; i < dlugosc; ++i)                                                           // Dopóki wszystkie bajty nie przejdą przez  pętle.
    {
        crc ^= (int)bajty[i];                                                                         //   Zamiana bajtów na bity po przez rzutowanie na ASCII
        for(int j = 0; j < 8; ++j)
        {
            if((crc & 1) != 0)                                                                     //      Jeżeli najstarszy bit nie jest 0.
            {       
                crc >>= 1;                                                                       //        Przesuń o jeden bit w prawo.
                crc ^= dzielnik;                                                                //         Wykonaj operację xor na dzielniku.
            }
            else                                                                              //           W przeciwnym wypadku przesuń w prawo.
                crc >>= 1;
        }
    }
    return crc;                                                                           //               Zwróć sumę kontrolną crc16.
}
void dodawanie_charow(string &x,unsigned char* t,int liczba_bajtow)// Funkcja dodająca po przez referencję znaki do napisu-----------------------------------------------------------------
{
    for(int i=0; i<liczba_bajtow; i++)                                                                  // Dopóki pętla nie przejdzie po każdym znaku.
    {
        x+=t[i];                                                                                      //   Dodaj znak do stringa.
    }
}
unsigned int crc_plik(int ilosc,int ilosc_bajtow,fstream &plik)// Funkcja oblicza sumę kontrolną crc na podstawie pliku--------------------------------------------------------------------
{
    plik.seekg( 0, ios::beg );                                                                          // Wraca na poczatek pliku.
    string x="";                                                                                       //  Zmienna pomocnicza.
    int i=0;                                                                                          //   Zmienna pomocnicza.
    unsigned char * t = new unsigned char[ilosc_bajtow];                                             //    Dynamiczna tablica, w której będą przechowywane znaki.
    while(i<ilosc)                                                                                  //     Dopóki nie przejdziesz wszystkich bloków danych.
    {
        plik.read(reinterpret_cast<char*>(t), ilosc_bajtow);                                      //       Wczytaj blok bajtów o ilości zadanej przy wywołaniu funkcji.
        dodawanie_charow(x,t,ilosc_bajtow);                                                      //        Funkcja doda blok bajtów do zmiennej pomocniczej x, tworząc tym samym sume bajtów z całego pliku.
        i++;
    }
    delete []t;                                                                                //          Zwolnienie miejsca w pamięci.
    plik.seekg( 0, ios::beg );                                                                //           Powrót na poczatek pliku.
    return crc(x,x.length());                                                                //            Zwracając wartość funkcja wywołuje funkcję crc, która dla zsumowanych wcześniej bajtów przy pomocy zmiennej pomocniczej obliczy i zwróci sumę kontrolną.
}
void podzial(char* argv[]) // Funkcja przeprowadzająca podział dużego pliku na mniejsze----------------------------------------------------------------------------------------------------
{
    fstream pierwszy;       
    pierwszy.open( argv[4], ios::binary | ios::in );                                                    // Otwieranie strumienia dużego pliku do podziału.
    if ( !pierwszy )                                                                                   //  Sprawdzanie czy plik znaleziony i otwarty poprawnie.
        cout<<"Nie ma możliwości odczytu pliku.";
    else                                                                                             //    Jeśli tak to podziel plik.
    {
        int ilosc_bajtow = stoi(argv[3]);                                                          //      Ilość bajtów w każdym pliku, który zostanie utworzony.
        int waga = zliczanie_bajtow(pierwszy);                                                    //       Wielkosc dużego pliku.
        int ilosc= waga/ilosc_bajtow;                                                            //        Ilosc plików które zostaną utworzone.
        unsigned char * txt = new unsigned char[ilosc_bajtow];                                  //         Przygotowanie tablicy dynamicznej pod przechwytywanie bajtów z dużego pliku i przesyłanie do mniejszych.
        int i=0;                                                                               //          Zmienna całkowita odpowiedzialna za numer pliku.
        unsigned int suma_kontrolna = crc_plik(ilosc,ilosc_bajtow,pierwszy);                  //           Wyliczenie przy pomocy funkcji sumy kontrolnej tego pliku.
        while(i<ilosc)                                                                       //            Dopóki ilosc plików zwiększona o jeden plik z resztą danych jest większa od i.
        {
            pierwszy.read(reinterpret_cast<char*>(txt), ilosc_bajtow);                     //              Pobiera bajty z pliku.
            fstream zapisywany( nazwa_pliku(argv,i), ios::binary | ios::out );            //               Utworzy plik do podziału.
            string header = naglowek(suma_kontrolna,argv,i,waga,ilosc_bajtow);           //                Nagłówek pliku.
            zapisywany<<header<<endl;                                                   //                 Wpisuje nagłówek do pliku.
            zapisywany.write(reinterpret_cast<char*>(txt), ilosc_bajtow);              //                  Wpisuje bajty do pliku.
            zapisywany.close();                                                       //                   Zamyka plik podzielony.
            i++;
        }
        if(waga%ilosc_bajtow!=0)                                                    //                     Jeżeli istnieją bajty które nie zostały jeszcze wczytane bo jest ich mniej niż ilość wymagana przez użytkownika, wczytaj je wszystkie do nowego pliku.
        {
            pierwszy.read(reinterpret_cast<char*>(txt), waga%ilosc_bajtow);       //                       Pobiera bajty z pliku.
            fstream zapisywany( nazwa_pliku(argv,i), ios::binary | ios::out );   //                        Tworzy plik do podziału.
            zapisywany<<naglowek(suma_kontrolna,argv,i,waga,ilosc_bajtow);      //                         Wpisuje nagłówek do pliku.
            zapisywany.write(reinterpret_cast<char*>(txt), waga%ilosc_bajtow); //                          Wpisuje bajty do pliku.
            zapisywany.close();                                               //                           Zamyka plik.  
        }
        delete [] txt;                                                      //                             Usuwa zbędną już tablicę dynamiczną.
    }
    pierwszy.close();                                                      //                              Zamyka duży, pierwotny plik.
}
void scalanie(char*argv[])// Funkcja przeprowadzająca scalanie małych plików w jeden duży--------------------------------------------------------------------------------------------------
{
    fstream pierwszy;                                                                                   // Otwiera strumień do pliku.
    pierwszy.open(argv[4],ios::binary|ios::in);                                                        //  Otwiera plik.
    if(!pierwszy)                                                                                     //   Jeżeli plik jest uszkodzony lub go nie ma to wyświetla komunikat.
        cout<<"Nie ma mo\276liwo\230ci odczytu pliku.";
    else                                                                                            //     Jeżeli wszystko jest okej to przystępuje do scalania.
    {
        string nazwa,pomocnik;                                                                    //       Zmienne pomocnicze.
        int waga,do_scalenia, c;                                                                 //        Zmienne pomocnicze.
        pierwszy>>waga;                                                                         //         Wczytanie wielkości dużego pliku przed podziałem z nagłówka.
        pierwszy>>do_scalenia;                                                                 //          Wczytanie liczby plików na, którego został podzielony duży plik.
        pierwszy>>nazwa;                                                                      //           Wczytanie nazwy następnego pliku do scalenia.
        pierwszy>>c;                                                                         //            Wczytanie sumy kontrolnej dużego.
        pierwszy.seekg( 0, ios::beg );                                                      //             Powrót na poczatek pliku.
        getline(pierwszy,pomocnik);
        int naglowek = pomocnik.length()+1;                                               //               Zmienna pomocnicza określająca długość nagłówka.
        int ilosc_bajtow=zliczanie_bajtow(pierwszy) -naglowek;                           //                Zmienna określająca ile bajtów trzeba scalić przy pomocy funkcji i zmiennej pomocniczej do nagłówka.
        pierwszy.close();                                                               //                 Zamknięcie pierwszego pliku.
        int i=0;                                                                       //                  Zmienna pomocnicza.
        unsigned char * txt = new unsigned char[ilosc_bajtow];                        //                   Utworzenie tablicy dynamicznej do przekazywania bajtów.
        string x="";                                                                 //                    Zmienna pomocnicza.
        fstream zapisywany( nazwa_p(nazwa), ios::binary | ios::out );               //                     Utworzenie pliku do, którego zostaną scalone pliku.
        while(i<=do_scalenia)                                                      //                      Dopóki wszystkie pliki do scalenia nie zostaną scalone.
        {       
            fstream pierwszy;                                                    //                        Ponowne otwarcie małego pliku do scalenia.
            pierwszy.open(nazwa_pliku(argv,i), ios::binary|ios::in);
            ilosc_bajtow=zliczanie_bajtow(pierwszy) -naglowek;
            pierwszy.seekg(naglowek,ios::beg);                                //                           Ustawienie odczytu na pozycji za nagłówkiem.
            pierwszy.read(reinterpret_cast<char*>(txt), ilosc_bajtow);       //                            Pobieranie bajtów z małego pliku.
            zapisywany.write(reinterpret_cast<char*>(txt),ilosc_bajtow);    //                             Zapisanie bajtów do dużego pliku
            dodawanie_charow(x,txt,ilosc_bajtow);                          //                              Przekazanie tych bajtów do stringa w celu późniejszego sprawdzenia sumy kontrolnej całego pliku.
            pierwszy.close();                                             //                               Zamknięcie małego pliku.
            i++; 
        }
        delete []txt;                                                   //                                 Zwolnienie pamięci.
        if(c==crc(x,x.length()))                                       //                                  Kontrola zgodności sumy kontrolnej. 
            cout<<"Plik zosta\210 scalony poprawnie!"<<endl;            
        zapisywany.close();                                          //                                    Zamknięcie pliku.
    }
}