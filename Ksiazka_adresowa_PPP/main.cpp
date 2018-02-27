//
//  main.cpp
//  Ksiazka_Adresowa_PPP
//
//  Created by Jacek Kieler on 21/02/2018.
//  Copyright © 2018 Jacek Kieler. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <curses.h>

//using namespace std;

struct KsiazkaAdresowa {
    int numerIdentyfikacyjny;
    std::string numerTelefonu,imie,nazwisko,adresZamieszkania,adresEmail;
};


int zamianaStringNaInt(std::string str) {
    int liczbaInt;
    std::stringstream ss;
    ss<<str;
    ss>>liczbaInt;
    return liczbaInt;
}

std::string wprowadzNumerTelefonu() {
    std::string numerTelefonu;
    std::size_t dlugoscNumeruTelefonu=0;
    std::cin.sync();
    getline(std::cin,numerTelefonu);
    dlugoscNumeruTelefonu=numerTelefonu.length();
    return numerTelefonu;
}


void dodajNowyKontakt(std::vector<KsiazkaAdresowa>&Kontakt,int numerIdKontaktu){
    std::fstream plik;
    plik.open("mojekontakty.txt",std::ios::out | std::ios::app);
    KsiazkaAdresowa nowyKontakt;
    std::string numTel;
    std::cout<<std::endl<<std::endl;
    std::cout<<"***** TWORZENIE NOWEGO KONTAKTU *****"<<std::endl<<std::endl;
    nowyKontakt.numerIdentyfikacyjny=(numerIdKontaktu);
    std::cout<<"IMIE: ";
    std::cin.ignore();
    getline(std::cin,nowyKontakt.imie);
    std::cout<<"NAZWISKO: ";
    std::cin.sync();
    getline(std::cin,nowyKontakt.nazwisko);
    std::cout<<"NUMER KONTAKTOWY: ";
    nowyKontakt.numerTelefonu=wprowadzNumerTelefonu();
    std::cout<<"ADRES ZAMIESZKANIA: ";
    std::cin.sync();
    getline(std::cin,nowyKontakt.adresZamieszkania);
    std::cout<<"ADRES E-MAIL: ";
    std::cin.sync();
    getline(std::cin,nowyKontakt.adresEmail);
    std::cout<<std::endl;
    
    plik<<nowyKontakt.numerIdentyfikacyjny<<"|";
    plik<<nowyKontakt.imie<<"|";
    plik<<nowyKontakt.nazwisko<<"|";
    plik<<nowyKontakt.numerTelefonu<<"|";
    plik<<nowyKontakt.adresZamieszkania<<"|";
    plik<<nowyKontakt.adresEmail<<"|"<<std::endl;
    
    Kontakt.push_back(KsiazkaAdresowa(nowyKontakt));
    
    plik.close();
}

void wyswietlWszystkieKontakty(std::vector<KsiazkaAdresowa>&Kontakt){
    std::vector<KsiazkaAdresowa>::iterator itr;
    
    std::cout<<std::endl<<std::endl;
    std::cout<<"********** KSIAZKA ADRESOWA **********"<<std::endl<<std::endl;
    for(itr=Kontakt.begin(); itr!=Kontakt.end(); itr++) {
        std::cout<<"********** KONTAKT (NR ID:"<<itr->numerIdentyfikacyjny<<") **********"<<std::endl<<std::endl;
        std::cout<<"IMIE I NAZWISKO: "<<itr->imie<<" "<<itr->nazwisko<<std::endl;
        std::cout<<"NR TELEFONU: "<<itr->numerTelefonu<<std::endl;
        std::cout<<"ADRES: "<<itr->adresZamieszkania<<std::endl;
        std::cout<<"E-MAIL: "<<itr->adresEmail<<std::endl;
        std::cout<<std::endl;
    }
    std::cout<<"Nacisnij ENTER aby wrocic do MENU...";
    getchar();
}

void znajdzKontakt(std::vector<KsiazkaAdresowa>&Kontakt) {
    std::vector<KsiazkaAdresowa>::iterator itr;
    std::string nazwaKontaktu;
    bool znaleziono=false;
    
    std::cout<<std::endl<<std::endl;
    std::cout<<"********** SZUKAJ KONTAKTU **********"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ZNAJDZ KONTAKT (PODAJ IMIE LUB NAZWISKO): ";
    std::cin.sync();
    getline(std::cin,nazwaKontaktu);
    
    std::cout<<std::endl;
    for(itr=Kontakt.begin(); itr!=Kontakt.end(); itr++) {
        if(itr->imie==nazwaKontaktu||itr->nazwisko==nazwaKontaktu) {
            std::cout<<"********** KONTAKT (NR ID:"<<itr->numerIdentyfikacyjny<<") **********"<<std::endl<<std::endl;
            std::cout<<"IMIE I NAZWISKO: "<<itr->imie<<" "<<itr->nazwisko<<std::endl;
            std::cout<<"NR TELEFONU: "<<itr->numerTelefonu<<std::endl;
            std::cout<<"ADRES: "<<itr->adresZamieszkania<<std::endl;
            std::cout<<"E-MAIL: "<<itr->adresEmail<<std::endl;
            znaleziono=true;
            std::cout<<std::endl<<std::endl;
        }
    }
    
    if(znaleziono==false) {
        std::cout<<"NIE ZNALEZIONO KONTAKTU "<<nazwaKontaktu<<std::endl<<std::endl;
    }
    std::cout<<"Nacisnij ENTER aby wrocic do MENU...";
    getchar();
}

void liczbaKontaktow(std::vector<KsiazkaAdresowa>&Kontakt) {
    if(Kontakt.size()!=0) {
        std::cout<<"W TWOJEJ KSIAZCE ADRESOWEJ ZAPISANYCH JEST "<<Kontakt.size()<<" KONTAKTOW"<<std::endl;
    } else {
        std::cout<<"KSIAZKA ADRESOWA JEST PUSTA"<<std::endl;
    }
}

void wczytajKontaktyZPliku(std::vector<KsiazkaAdresowa>&Kontakt,int *numerIdKontaktu) {
    std::fstream plik;
    std::string linia;
    int nr_linii=1; // numery linii zaczynaja sie od 1
    
    KsiazkaAdresowa nowyKontakt;
    
    plik.open("mojekontakty.txt", std::ios::in);
    if(plik.good()==false) {
        std::cout<<"Nie mozna otworzyc pliku z danymi kontaktowymi!"<<std::endl<<std::endl;
        std::cout<<"Nacisnij ENTER aby utworzyc nowa ksiazke adresowa...";
        getchar();
        plik.open("mojekontakty.txt",std::ios::out | std::ios::app);
    }
    while (getline(plik, linia)) {
        
        switch (nr_linii) {
            case 1: {
                nowyKontakt.numerIdentyfikacyjny=zamianaStringNaInt(linia);
                *numerIdKontaktu=nowyKontakt.numerIdentyfikacyjny;
            }
                break;
            case 2:
                nowyKontakt.imie=linia;
                break;
            case 3:
                nowyKontakt.nazwisko=linia;
                break;
            case 4:
                nowyKontakt.numerTelefonu=linia;
                break;
            case 5:
                nowyKontakt.adresZamieszkania=linia;
                break;
            case 6: {
                nowyKontakt.adresEmail=linia;
                Kontakt.push_back(KsiazkaAdresowa(nowyKontakt));
            }
                break;
        }
        nr_linii++;
        if(nr_linii==7)
            nr_linii=1;
    }
    plik.close();
}



void zakonczDzialaniePogramu() {
    std::cout<<std::endl<<std::endl;
    
    std::cout<<"DZIEKUJEMY ZA SKORZYSTANIE Z NASZEGO PROGRAMU :)"<<std::endl<<std::endl;
    std::cout<<"Nacisnij ENTER aby zakonczyc dzialanie programu";
    getchar();
    exit(0);
}

void wyswietlPustaKsiazkaAdresowa() {
    std::cout<<std::endl<<std::endl;
    std::cout<<"KSIAZKA ADRESOWA JEST PUSTA"<<std::endl<<std::endl;
    std::cout<<"Nacisnij ENTER aby kontynuowac...";
    getchar();
    std::cout<<std::endl<<std::endl;
    
}

void wyswietlMenu(std::vector<KsiazkaAdresowa>&Kontakt) {
    std::cout<<std::endl<<std::endl;
    
    std::cout<<"********** KSIAZKA ADRESOWA **********"<<std::endl;
    std::cout<<std::endl;
    liczbaKontaktow(Kontakt);
    std::cout<<std::endl;
    std::cout<<"1.\tDODAJ NOWY KONTAKT"<<std::endl;
    std::cout<<"2.\tWYSWIETL WSZYSTKIE KONTAKTY"<<std::endl;
    std::cout<<"3.\tZNAJDZ KONTAKT"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"0.\tKONIEC"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Wybierz odpowiedni klawisz: ";
}

void nowaWczytajKontaktyZPliku(std::vector<KsiazkaAdresowa>&Kontakt,int *numerIdKontaktu) {
    std::fstream plik;
    std::string linia;
    int nr_linii=1; // numery linii zaczynaja sie od 1
    int numerFragmentuLinii=1;
    std::size_t dlugoscLinii;
    std::string fragmentLinii;
    KsiazkaAdresowa nowyKontakt;
    
    plik.open("mojekontakty.txt", std::ios::in);
    if(plik.good()==false) {
        std::cout<<"Nie mozna otworzyc pliku z danymi kontaktowymi!"<<std::endl<<std::endl;
        std::cout<<"Nacisnij ENTER aby utworzyc nowa ksiazke adresowa...";
        getchar();
        plik.open("mojekontakty.txt",std::ios::out | std::ios::app);
    }
    while (getline(plik, linia)) {
        
        dlugoscLinii=linia.length();
        
        // trzeba stworzyc funkcje ktora bedzie wyluskiwala z linii odp fragmenty kontaktu
        for(int i=0;i<dlugoscLinii;i++){
            if(linia[i]!='|'){
                fragmentLinii=fragmentLinii+linia[i];
            } else {
                
                switch (numerFragmentuLinii) {
                    case 1: {
                        nowyKontakt.numerIdentyfikacyjny=zamianaStringNaInt(fragmentLinii);
                        *numerIdKontaktu=nowyKontakt.numerIdentyfikacyjny;
                    }
                        break;
                    case 2:
                        nowyKontakt.imie=fragmentLinii;
                        break;
                    case 3:
                        nowyKontakt.nazwisko=fragmentLinii;
                        break;
                    case 4:
                        nowyKontakt.numerTelefonu=fragmentLinii;
                        break;
                    case 5:
                        nowyKontakt.adresZamieszkania=fragmentLinii;
                        break;
                    case 6: {
                        nowyKontakt.adresEmail=fragmentLinii;
                        Kontakt.push_back(KsiazkaAdresowa(nowyKontakt));
                    }
                        break;
                }
                
                numerFragmentuLinii++;
                fragmentLinii="";
                
                if(numerFragmentuLinii==7){
                    numerFragmentuLinii=1;
                }
                
            }
            
        }
        
        nr_linii++;
        
    }
    plik.close();
}



int main() {
    std::vector<KsiazkaAdresowa>nowyKontakt;
    int numerIdentyfikacyjnyKontaktu=1;
    char wybor;
    
    nowaWczytajKontaktyZPliku(nowyKontakt,&numerIdentyfikacyjnyKontaktu);
    
    while (true) {
        wyswietlMenu(nowyKontakt);
        
        wybor=getchar();
        
        
        switch(wybor) {
            case '1': {
                dodajNowyKontakt(nowyKontakt,numerIdentyfikacyjnyKontaktu);
                numerIdentyfikacyjnyKontaktu++;
            }
                break;
            case '2': {
                if(nowyKontakt.size()!=0)
                    wyswietlWszystkieKontakty(nowyKontakt);
                else
                    wyswietlPustaKsiazkaAdresowa();
            }
                break;
            case '3': {
                if(nowyKontakt.size()!=0)
                    znajdzKontakt(nowyKontakt);
                else
                    wyswietlPustaKsiazkaAdresowa();
            }
                break;
            case '0': {
                zakonczDzialaniePogramu();
                {
                    break;
                default:
                    continue;
                }
            }
        }
    }
    return 0;
}






