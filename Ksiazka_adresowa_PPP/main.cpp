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

struct AddressBook {
    int idNumber;
    std::string phoneNumber,firstName,lastName,address,emailAddress;
};

int convertIntToString(std::string str) {
    int intNumber;
    std::stringstream ss;
    ss<<str;
    ss>>intNumber;
    return intNumber;
}

void addNewContact(std::vector<AddressBook>&Contact,int &contactIDNumber){
    std::fstream file;
    file.open("mojekontakty.txt",std::ios::out | std::ios::app);
    AddressBook newContact;
    
    std::cout<<std::endl<<std::endl;
    
    contactIDNumber++;
    newContact.idNumber=contactIDNumber;
    
    std::cout<<"***** TWORZENIE NOWEGO KONTAKTU *** ";
    std::cout<<"ID: "<<contactIDNumber<<" *****"<<std::endl<<std::endl;
    
    std::cout<<"IMIE: ";
    std::cin.ignore();
    getline(std::cin,newContact.firstName);
    
    std::cout<<"NAZWISKO: ";
    std::cin.sync();
    getline(std::cin,newContact.lastName);
    
    std::cout<<"NUMER KONTAKTOWY: ";
    std::cin.sync();
    getline(std::cin,newContact.phoneNumber);
    
    std::cout<<"ADRES ZAMIESZKANIA: ";
    std::cin.sync();
    getline(std::cin,newContact.address);
    
    std::cout<<"ADRES E-MAIL: ";
    std::cin.sync();
    getline(std::cin,newContact.emailAddress);
    
    std::cout<<std::endl;
    
    file<<newContact.idNumber<<"|";
    file<<newContact.firstName<<"|";
    file<<newContact.lastName<<"|";
    file<<newContact.phoneNumber<<"|";
    file<<newContact.address<<"|";
    file<<newContact.emailAddress<<"|"<<std::endl;
    
    Contact.push_back(AddressBook(newContact));
    
    file.close();
}

void displayContact(std::vector<AddressBook>Contact, std::vector<AddressBook>::iterator itr){
    std::cout<<"********** KONTAKT (NR ID:"<<itr->idNumber<<") **********"<<std::endl<<std::endl;
    std::cout<<"IMIE I NAZWISKO: "<<itr->firstName<<" "<<itr->lastName<<std::endl;
    std::cout<<"NR TELEFONU: "<<itr->phoneNumber<<std::endl;
    std::cout<<"ADRES: "<<itr->address<<std::endl;
    std::cout<<"E-MAIL: "<<itr->emailAddress<<std::endl;
    std::cout<<std::endl;
}

void displayAllContacts(std::vector<AddressBook>Contacts){
    std::vector<AddressBook>::iterator itr;
    
    std::cout<<std::endl<<std::endl;
    std::cout<<"********** KSIAZKA ADRESOWA **********"<<std::endl<<std::endl;
    for(itr=Contacts.begin(); itr!=Contacts.end(); itr++) {
        displayContact(Contacts, itr);
    }
    std::cout<<"Nacisnij ENTER aby wrocic do MENU...";
    getchar();
}


void findContact(std::vector<AddressBook>Contacts) {
    std::vector<AddressBook>::iterator itr;
    std::string contactName;
    bool found=false;
    
    std::cout<<std::endl<<std::endl;
    std::cout<<"********** SZUKAJ KONTAKTU **********"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ZNAJDZ KONTAKT (PODAJ IMIE LUB NAZWISKO): ";
    std::cin.ignore();
    getline(std::cin,contactName);
    
    std::cout<<std::endl;
    for(itr=Contacts.begin(); itr!=Contacts.end(); itr++) {
        if(itr->firstName==contactName||itr->lastName==contactName) {
            displayContact(Contacts, itr);
            found=true;
        }
    }
    
    if(found==false) {
        std::cout<<"NIE ZNALEZIONO KONTAKTU "<<contactName<<std::endl<<std::endl;
    }
    std::cout<<"Nacisnij ENTER aby wrocic do MENU...";
    getchar();
}

void displayTheAmountOfContacts(std::vector<AddressBook>Contact) {
    if(Contact.size()!=0) {
        std::cout<<"W TWOJEJ KSIAZCE ADRESOWEJ ZAPISANYCH JEST "<<Contact.size()<<" KONTAKTOW"<<std::endl;
    } else {
        std::cout<<"KSIAZKA ADRESOWA JEST PUSTA"<<std::endl;
    }
}

void quitTheProgram() {
    std::cout<<std::endl<<std::endl;
    std::cout<<"DZIEKUJEMY ZA SKORZYSTANIE Z NASZEGO PROGRAMU :)"<<std::endl<<std::endl;
    std::cout<<"Nacisnij ENTER aby zakonczyc dzialanie programu";
    getchar();
    exit(0);
}

void displayEmptyAddressBook() {
    std::cout<<std::endl<<std::endl;
    std::cout<<"KSIAZKA ADRESOWA JEST PUSTA"<<std::endl<<std::endl;
    std::cout<<"Nacisnij ENTER aby kontynuowac...";
    getchar();
    std::cout<<std::endl<<std::endl;
}

void displayMENU(std::vector<AddressBook>&Contact) {
    std::cout<<std::endl<<std::endl;
    
    std::cout<<"********** KSIAZKA ADRESOWA **********"<<std::endl;
    std::cout<<std::endl;
    displayTheAmountOfContacts(Contact);
    std::cout<<std::endl;
    std::cout<<"1.\tDODAJ NOWY KONTAKT"<<std::endl;
    std::cout<<"2.\tWYSWIETL WSZYSTKIE KONTAKTY"<<std::endl;
    std::cout<<"3.\tZNAJDZ KONTAKT"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"0.\tKONIEC"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Wybierz odpowiedni klawisz: ";
}

std::vector<AddressBook>loadContactsFromAFile(int &contactIDNumber) {
    std::vector<AddressBook>Contact;
    AddressBook newContact;
    std::fstream file;
    std::string fileLine;
    int numberOfFileLine=1;
    std::size_t fileLineLength;
    int numberOfContactField=1;
    
    std::string contactField;
    
    file.open("mojekontakty.txt", std::ios::in);
    if(file.good()==false) {
        std::cout<<"Nie mozna otworzyc pliku z danymi kontaktowymi!"<<std::endl<<std::endl;
        std::cout<<"Nacisnij ENTER aby utworzyc nowa ksiazke adresowa...";
        getchar();
        file.open("mojekontakty.txt",std::ios::out | std::ios::app);
    }
    while (getline(file, fileLine)) {
        
        fileLineLength=fileLine.length();
        
        // trzeba stworzyc funkcje ktora bedzie wyluskiwala z linii odp fragmenty kontaktu
        for(int i=0;i<fileLineLength;i++){
            if(fileLine[i]!='|'){
                contactField=contactField+fileLine[i];
            } else {
                
                switch (numberOfContactField) {
                    case 1: {
                        newContact.idNumber=convertIntToString(contactField);
                        contactIDNumber=newContact.idNumber;
                    }
                        break;
                    case 2:
                        newContact.firstName=contactField;
                        break;
                    case 3:
                        newContact.lastName=contactField;
                        break;
                    case 4:
                        newContact.phoneNumber=contactField;
                        break;
                    case 5:
                        newContact.address=contactField;
                        break;
                    case 6: {
                        newContact.emailAddress=contactField;
                        Contact.push_back(AddressBook(newContact));
                    }
                        break;
                }
                
                numberOfContactField++;
                contactField="";
                
                if(numberOfContactField==7){
                    numberOfContactField=1;
                }
            }
        }
        numberOfFileLine++;
    }
    file.close();
    
    return Contact;
}

int main() {
    int numerIdentyfikacyjnyKontaktu=1;
    char selectionKey;
    std::vector<AddressBook>newContact(loadContactsFromAFile(numerIdentyfikacyjnyKontaktu));
    
    while (true) {
        displayMENU(newContact);
        
        selectionKey=getchar();
        
        switch(selectionKey) {
            case '1': {
                addNewContact(newContact,numerIdentyfikacyjnyKontaktu);
            }
                break;
            case '2': {
                if(newContact.size()!=0)
                    displayAllContacts(newContact);
                else
                    displayEmptyAddressBook();
            }
                break;
            case '3': {
                if(newContact.size()!=0)
                    findContact(newContact);
                else
                    displayEmptyAddressBook();
            }
                break;
            case '0': {
                quitTheProgram();
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
