#include <cstdio>
#include <cwchar>
#include <iostream>

using namespace std;

#include "zcode.h"

Code_text::Code_text(wchar_t* startps, wchar_t* endps,wchar_t charholdsymbolfrommflag,int intdistfromleftedge, unsigned int intterminwidth){
    this->startps11 = startps;
    this->endps11 = endps-1;
    this->intdistfromleftedge11 = intdistfromleftedge;
    //std::wcout << charholdsymbolfrommflag;
    this->charholdsymbolfrommflag11 = charholdsymbolfrommflag;
    //std::wcout << charholdsymbolfrommflag11;
    this->intterminwidth11 = intterminwidth;
    #ifdef _WIN32
    intterminwidth11 = intterminwidth11/2;
    #endif

}

Code_text::~Code_text() {

}

int Code_text::print() const {
    wprintf(L"\u001b[32m\n");

    wchar_t* current = startps11;
    while (current<endps11)
        {
            if (*current==L' '){break;}
            current++;
        }

    while (current < endps11) {
    std::wcout << charholdsymbolfrommflag11;
    current++;
    while (current < endps11 && *current != L'\n') {
        wprintf(L"%lc", *current);
        current++;
    } 
    std::wcout << L'\n';
    current++;
    }

    wprintf(L"\u001b[0m");
    return 0;
}

unsigned long int Code_text::count_symbols() const {
    unsigned long int returnme = 0;
	wchar_t* current = startps11;
    while (current<endps11)
        {
            returnme++;
            current++;
        }
    return returnme;
    }

unsigned long int Code_text::count_words() const {
	unsigned long int returnme = 0;
	wchar_t* current = startps11;
    while (current<endps11)
        {
			if (*current==L'\n') { current++; continue;  }
            if (*current==L' '){returnme++;}
            current++;
        }
	returnme++;
    return returnme;
    }
