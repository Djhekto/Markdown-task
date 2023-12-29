#include <cstdio>
#include <cwchar>

using namespace std;

#include "zheader.h"

Header_text::Header_text(wchar_t* startps, wchar_t* endps, unsigned int intterminwidth){
    this->startps11 = startps;
    this->endps11 = endps-1;
    this->intterminwidth11 = intterminwidth;
    #ifdef _WIN32
    intterminwidth11 = intterminwidth11/2;
    #endif
}

Header_text::~Header_text() {

}

int Header_text::print() const {
	unsigned int fixtheramka = 0;
	wchar_t* cendps11 = endps11-1;
    wprintf(L"\033[33m\n");
    for(unsigned int i = 0; i < intterminwidth11; i++){
        wprintf(L"#");
    }
    if (*endps11!=L'-'&&*(endps11-1)!=L'-') {
		    wprintf(L"\n#");
		    fixtheramka++;
	}

    wchar_t* current = startps11;
    while (current<endps11)
        {
            if (*current==L' '){break;}
            current++;
        }
    
    while (current<cendps11)
        {
            if (*cendps11!=L'-'){
				break;
				}
            cendps11--;
        }
    
    unsigned int num_symbols = endps11 - current;
    if (*endps11==L'-'||*(endps11-1)==L'-') {
		    num_symbols = cendps11 - current-4;
	}
    num_symbols = (intterminwidth11-num_symbols)/2-1;

    for(unsigned int i = 0; i <= num_symbols; i++){
        wprintf(L" ");
        fixtheramka++;
    }

    if (*endps11!=L'-'&&*(endps11-1)!=L'-') {
		cendps11 = endps11;
	}

    while (current != cendps11) {
		if (*current==L'-') {break;}
        wprintf(L"%lc", *current);
		fixtheramka++;
        current++;
    }
	
    for(unsigned int i = 0; i <= num_symbols; i++){
		fixtheramka++;
		if (fixtheramka==intterminwidth11) {break;}
        wprintf(L" ");
        
    }

    if (*endps11!=L'-'&&*(endps11-1)!=L'-') {
    wprintf(L"#\n");
	}
	else{
	wprintf(L"\n");
	}
    for(unsigned int i = 0; i < intterminwidth11; i++){
    wprintf(L"#");
    }
    wprintf(L"\033[0m\n");
    return 0;
}

unsigned long int Header_text::count_symbols() const {
    unsigned long int returnme = 0;
	wchar_t* current = startps11;
    while (current<endps11)
        {
            returnme++;
            current++;
        }
    return returnme;
}

unsigned long int Header_text::count_words() const {
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
