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
    if((a=="p")||(a=="P"))                                                                             //  Je??eli p lub P to podzia?? du??ego pliku na ma??e.
        podzial(argv);
    else if((a=="s")||(a=="S"))                                                                      //    Je??eli s lub S to scalanie ma??ego pliku w du??y.
        scalanie(argv);
    return 0;
}
int zliczanie_bajtow(fstream &pierwszy) //Funkcja sumuj??ca ilo???? wszystkich bajt??w w pliku------------------------------------------------------------------------------------------------
{
    unsigned int waga;                                                                                  // Zmienna ca??kowita, kt??ra w wyniku funkcji przeka??e ilo???? wszystkich bajt??w.
    pierwszy.seekg( 0, ios::end );                                                                     //  Przesuwa pozycje na koniec.     
    waga = pierwszy.tellg();                                                                          //   Odczytaj pozycje w pliku.
    pierwszy.seekg( 0, ios::beg );                                                                   //    Wraca na poczatek pliku!
    return waga;                                                                                    //     Zwraca wcze??niej wspomnian?? ilo???? wszystkich bajt??w.
}
string intToStr(int  liczba) // Funkcja zamieniaj??ca inta na stringa----------------------------------------------------------------------------------------------------------------------
{
    string q;                                                                                           // Zmienna pomocnicza.                        
    if(liczba < 0)                                                                                     //  Je??eli int jest mniejszy od 0 to dodaj minus z przodu w stringu i usu?? z inta.
    {
        q = "-";
        liczba = -liczba;
    }
    if(liczba > 9)                                                                                  //     Je??eli int jest wi??kszy od 9 to wywo??aj funkcj?? jeszcze raz.
        q += intToStr(liczba / 10);
        q += liczba % 10 + 48;                                                                
     return q;
}
string dodawanie_zer(string  q) // Pod Funkcja funkcji intToStr, kt??ra dodaje zera aby utworzy?? 3 cyfrowy numer pod pliku-----------------------------------------------------------------
{
    if(q.length()==1)                                                                                   // Je??eli liczba jest jednocyfrowa to dodaj przed ni?? dwa zera.
       q = "00" + q;
    else if(q.length()==2)                                                                            //   Je??eli liczba jest dwucyfrowa to dodaj przed ni?? jedno zero.
        q = "0" + q;
    return q;
}
string nazwa_pliku(char* argv[],int numer_pliku)  // Pe??na nazwa pliku z nazw?? pod pliku. Gotowego do podzia??u----------------------------------------------------------------------------
{
    string a=nazwa_p(argv[4]);                                                                          // Nazwa pliku kt??ry ma by?? podzielony. 
    string x="";                                                                                       //  Zmienna pomocniczna.
    for(unsigned short i=0; i<a.length(); i++)                                                        //   Dop??ki nie p??tla nie przejdzie po ka??dym znaku w nazwie.
    {
        x = x+a[i];                                                                                 //     Dodaj znak z nazwy do zmiennej pomocniczej.
        if(a[i+1]=='.')                                                                            //      Je??eli napotkasz kropk?? w nazwie pliku to przed ni?? dodaj numer pliku. 
            {
                string q = intToStr(numer_pliku);
                x=x+dodawanie_zer(q);
            }
    }
    return x;                                                                                 //           Zwr???? pe??n?? nazw?? gotow?? do przekazania. 
}
string naglowek(unsigned int suma_kontrolna,char* argv[],int i,int waga,int ilosc_bajtow) // Funkcja zwracaj??ca nag????wek do pliku podzielonego--------------------------------------------
{
    int ilosc= waga/ilosc_bajtow;                                                                       // Zmienna przedstawiaj??ca ilo???? plik??w podzielonych.
    string rezultat="";                                                                                //  Zmienna pomocnicza do zbudowania nag????wka na stringu.
    rezultat = rezultat + intToStr(waga);                                                             //   Wielkosc pliku du??ego przed podzia??em.
    rezultat = rezultat + " " + intToStr(ilosc);                                                     //    Ilo???? plik??w po podziale.
    rezultat = rezultat + " " + nazwa_pliku(argv,i+1);                                              //     Nazwa nast??pnego pliku.
    rezultat = rezultat + " " +intToStr(suma_kontrolna);
    return rezultat;
}
string nazwa_p(string nazwa)  // Funkcja usuwaj??ca numer z nazwy pliku--------------------------------------------------------------------------------------------------------------------
{
    string x="";                                                                                        // Zmienna pomocniczna.
    for(unsigned short i=0; i<nazwa.length(); i++)                                                     //  Dop??ki p??tla nie przejdzie po ka??dym znaku w nazwie.
    { 
        switch( nazwa[i] )                                                                           //    Switch kasuje wszystkie liczby od 0 do 9 w stringu z nazw??.
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
    return x;                                                                              //              Zwr???? pe??n?? nazw?? gotow?? do przekazania. 
}
unsigned int crc(const string bajty,unsigned int dlugosc)// Funkcja obliczaj??ca crc dla podanego  ci??gu danych-----------------------------------------------------------------------------
{
    int dzielnik = 0xA001;                                                            
    int crc = 0xFFFF;                        
    for(unsigned int i = 0; i < dlugosc; ++i)                                                           // Dop??ki wszystkie bajty nie przejd?? przez  p??tle.
    {
        crc ^= (int)bajty[i];                                                                         //   Zamiana bajt??w na bity po przez rzutowanie na ASCII
        for(int j = 0; j < 8; ++j)
        {
            if((crc & 1) != 0)                                                                     //      Je??eli najstarszy bit nie jest 0.
            {       
                crc >>= 1;                                                                       //        Przesu?? o jeden bit w prawo.
                crc ^= dzielnik;                                                                //         Wykonaj operacj?? xor na dzielniku.
            }
            else                                                                              //           W przeciwnym wypadku przesu?? w prawo.
                crc >>= 1;
        }
    }
    return crc;                                                                           //               Zwr???? sum?? kontroln?? crc16.
}
void dodawanie_charow(string &x,unsigned char* t,int liczba_bajtow)// Funkcja dodaj??ca po przez referencj?? znaki do napisu-----------------------------------------------------------------
{
    for(int i=0; i<liczba_bajtow; i++)                                                                  // Dop??ki p??tla nie przejdzie po ka??dym znaku.
    {
        x+=t[i];                                                                                      //   Dodaj znak do stringa.
    }
}
unsigned int crc_plik(int ilosc,int ilosc_bajtow,fstream &plik)// Funkcja oblicza sum?? kontroln?? crc na podstawie pliku--------------------------------------------------------------------
{
    plik.seekg( 0, ios::beg );                                                                          // Wraca na poczatek pliku.
    string x="";                                                                                       //  Zmienna pomocnicza.
    int i=0;                                                                                          //   Zmienna pomocnicza.
    unsigned char * t = new unsigned char[ilosc_bajtow];                                             //    Dynamiczna tablica, w kt??rej b??d?? przechowywane znaki.
    while(i<ilosc)                                                                                  //     Dop??ki nie przejdziesz wszystkich blok??w danych.
    {
        plik.read(reinterpret_cast<char*>(t), ilosc_bajtow);                                      //       Wczytaj blok bajt??w o ilo??ci zadanej przy wywo??aniu funkcji.
        dodawanie_charow(x,t,ilosc_bajtow);                                                      //        Funkcja doda blok bajt??w do zmiennej pomocniczej x, tworz??c tym samym sume bajt??w z ca??ego pliku.
        i++;
    }
    delete []t;                                                                                //          Zwolnienie miejsca w pami??ci.
    plik.seekg( 0, ios::beg );                                                                //           Powr??t na poczatek pliku.
    return crc(x,x.length());                                                                //            Zwracaj??c warto???? funkcja wywo??uje funkcj?? crc, kt??ra dla zsumowanych wcze??niej bajt??w przy pomocy zmiennej pomocniczej obliczy i zwr??ci sum?? kontroln??.
}
void podzial(char* argv[]) // Funkcja przeprowadzaj??ca podzia?? du??ego pliku na mniejsze----------------------------------------------------------------------------------------------------
{
    fstream pierwszy;       
    pierwszy.open( argv[4], ios::binary | ios::in );                                                    // Otwieranie strumienia du??ego pliku do podzia??u.
    if ( !pierwszy )                                                                                   //  Sprawdzanie czy plik znaleziony i otwarty poprawnie.
        cout<<"Nie ma mo??liwo??ci odczytu pliku.";
    else                                                                                             //    Je??li tak to podziel plik.
    {
        int ilosc_bajtow = stoi(argv[3]);                                                          //      Ilo???? bajt??w w ka??dym pliku, kt??ry zostanie utworzony.
        int waga = zliczanie_bajtow(pierwszy);                                                    //       Wielkosc du??ego pliku.
        int ilosc= waga/ilosc_bajtow;                                                            //        Ilosc plik??w kt??re zostan?? utworzone.
        unsigned char * txt = new unsigned char[ilosc_bajtow];                                  //         Przygotowanie tablicy dynamicznej pod przechwytywanie bajt??w z du??ego pliku i przesy??anie do mniejszych.
        int i=0;                                                                               //          Zmienna ca??kowita odpowiedzialna za numer pliku.
        unsigned int suma_kontrolna = crc_plik(ilosc,ilosc_bajtow,pierwszy);                  //           Wyliczenie przy pomocy funkcji sumy kontrolnej tego pliku.
        while(i<ilosc)                                                                       //            Dop??ki ilosc plik??w zwi??kszona o jeden plik z reszt?? danych jest wi??ksza od i.
        {
            pierwszy.read(reinterpret_cast<char*>(txt), ilosc_bajtow);                     //              Pobiera bajty z pliku.
            fstream zapisywany( nazwa_pliku(argv,i), ios::binary | ios::out );            //               Utworzy plik do podzia??u.
            string header = naglowek(suma_kontrolna,argv,i,waga,ilosc_bajtow);           //                Nag????wek pliku.
            zapisywany<<header<<endl;                                                   //                 Wpisuje nag????wek do pliku.
            zapisywany.write(reinterpret_cast<char*>(txt), ilosc_bajtow);              //                  Wpisuje bajty do pliku.
            zapisywany.close();                                                       //                   Zamyka plik podzielony.
            i++;
        }
        if(waga%ilosc_bajtow!=0)                                                    //                     Je??eli istniej?? bajty kt??re nie zosta??y jeszcze wczytane bo jest ich mniej ni?? ilo???? wymagana przez u??ytkownika, wczytaj je wszystkie do nowego pliku.
        {
            pierwszy.read(reinterpret_cast<char*>(txt), waga%ilosc_bajtow);       //                       Pobiera bajty z pliku.
            fstream zapisywany( nazwa_pliku(argv,i), ios::binary | ios::out );   //                        Tworzy plik do podzia??u.
            zapisywany<<naglowek(suma_kontrolna,argv,i,waga,ilosc_bajtow);      //                         Wpisuje nag????wek do pliku.
            zapisywany.write(reinterpret_cast<char*>(txt), waga%ilosc_bajtow); //                          Wpisuje bajty do pliku.
            zapisywany.close();                                               //                           Zamyka plik.  
        }
        delete [] txt;                                                      //                             Usuwa zb??dn?? ju?? tablic?? dynamiczn??.
    }
    pierwszy.close();                                                      //                              Zamyka du??y, pierwotny plik.
}
void scalanie(char*argv[])// Funkcja przeprowadzaj??ca scalanie ma??ych plik??w w jeden du??y--------------------------------------------------------------------------------------------------
{
    fstream pierwszy;                                                                                   // Otwiera strumie?? do pliku.
    pierwszy.open(argv[4],ios::binary|ios::in);                                                        //  Otwiera plik.
    if(!pierwszy)                                                                                     //   Je??eli plik jest uszkodzony lub go nie ma to wy??wietla komunikat.
        cout<<"Nie ma mo\276liwo\230ci odczytu pliku.";
    else                                                                                            //     Je??eli wszystko jest okej to przyst??puje do scalania.
    {
        string nazwa,pomocnik;                                                                    //       Zmienne pomocnicze.
        int waga,do_scalenia, c;                                                                 //        Zmienne pomocnicze.
        pierwszy>>waga;                                                                         //         Wczytanie wielko??ci du??ego pliku przed podzia??em z nag????wka.
        pierwszy>>do_scalenia;                                                                 //          Wczytanie liczby plik??w na, kt??rego zosta?? podzielony du??y plik.
        pierwszy>>nazwa;                                                                      //           Wczytanie nazwy nast??pnego pliku do scalenia.
        pierwszy>>c;                                                                         //            Wczytanie sumy kontrolnej du??ego.
        pierwszy.seekg( 0, ios::beg );                                                      //             Powr??t na poczatek pliku.
        getline(pierwszy,pomocnik);
        int naglowek = pomocnik.length()+1;                                               //               Zmienna pomocnicza okre??laj??ca d??ugo???? nag????wka.
        int ilosc_bajtow=zliczanie_bajtow(pierwszy) -naglowek;                           //                Zmienna okre??laj??ca ile bajt??w trzeba scali?? przy pomocy funkcji i zmiennej pomocniczej do nag????wka.
        pierwszy.close();                                                               //                 Zamkni??cie pierwszego pliku.
        int i=0;                                                                       //                  Zmienna pomocnicza.
        unsigned char * txt = new unsigned char[ilosc_bajtow];                        //                   Utworzenie tablicy dynamicznej do przekazywania bajt??w.
        string x="";                                                                 //                    Zmienna pomocnicza.
        fstream zapisywany( nazwa_p(nazwa), ios::binary | ios::out );               //                     Utworzenie pliku do, kt??rego zostan?? scalone pliku.
        while(i<=do_scalenia)                                                      //                      Dop??ki wszystkie pliki do scalenia nie zostan?? scalone.
        {       
            fstream pierwszy;                                                    //                        Ponowne otwarcie ma??ego pliku do scalenia.
            pierwszy.open(nazwa_pliku(argv,i), ios::binary|ios::in);
            ilosc_bajtow=zliczanie_bajtow(pierwszy) -naglowek;
            pierwszy.seekg(naglowek,ios::beg);                                //                           Ustawienie odczytu na pozycji za nag????wkiem.
            pierwszy.read(reinterpret_cast<char*>(txt), ilosc_bajtow);       //                            Pobieranie bajt??w z ma??ego pliku.
            zapisywany.write(reinterpret_cast<char*>(txt),ilosc_bajtow);    //                             Zapisanie bajt??w do du??ego pliku
            dodawanie_charow(x,txt,ilosc_bajtow);                          //                              Przekazanie tych bajt??w do stringa w celu p????niejszego sprawdzenia sumy kontrolnej ca??ego pliku.
            pierwszy.close();                                             //                               Zamkni??cie ma??ego pliku.
            i++; 
        }
        delete []txt;                                                   //                                 Zwolnienie pami??ci.
        if(c==crc(x,x.length()))                                       //                                  Kontrola zgodno??ci sumy kontrolnej. 
            cout<<"Plik zosta\210 scalony poprawnie!"<<endl;            
        zapisywany.close();                                          //                                    Zamkni??cie pliku.
    }
}