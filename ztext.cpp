#include <cstdio>
#include <cwchar>

using namespace std;

#include "ztext.h"

Text_text::Text_text(wchar_t* startps, wchar_t* endps11, unsigned int intdistfromleftedge, unsigned int intdistredline, unsigned int intterminwidth1) {
    this->startps11 = startps;
    this->endps11 = endps11-1;
    this->intdistfromleftedge11 = intdistfromleftedge;
    this->intdistredline11 = intdistredline;
    this->intterminwidth11 = intterminwidth1;
    #ifdef _WIN32
    //intterminwidth11 = intterminwidth11/2;
    #endif
}

Text_text::~Text_text() {

}

int Text_text::print() const {
    unsigned int localcounter = 1;
    
    for (unsigned int i = 1; i <= intdistredline11; ++i) { wprintf(L" "); }
    //for (unsigned int i = 1; i <= intdistfromleftedge11; ++i) { wprintf(L" "); }
	//localcounter = intdistredline11+intdistfromleftedge11;
	localcounter = intdistredline11+1;
    
    wchar_t* current = startps11;
    while (current < endps11) {
        if (localcounter >= intterminwidth11-4){
            if (*current==L' '||*current==L'\n') {
                wprintf(L"\n");
                for (unsigned int i = 1; i <= intdistfromleftedge11; ++i) { wprintf(L" "); }
                localcounter = intdistfromleftedge11+1;
                if (*current==L' '){
					current++;
					//
				}
                continue;
                }
        }

        if (localcounter >= intterminwidth11-1){
            if (*(current+1)!=L' ' && *(current+2)!=L' ' && *(current+1)!=L'\n' && *(current+2)!=L'\n' ){
                //localcounter = 0;
                wprintf(L"-\n");
                for (unsigned int i = 1; i <= intdistfromleftedge11; ++i) { wprintf(L" "); }
                localcounter = intdistfromleftedge11+1;
                continue;
            }
        }

        if (*current==L' '&&*(current-1)!=L' '){
            wprintf(L"%lc", *current);
            localcounter++;
            current++;
            continue;
        }

        if (*current!=L'\n'){
            wprintf(L"%lc", *current);
            localcounter++;
            current++;
            continue;
		}
        else{
			if (*(current-1) != L' ') {wprintf(L" ");}
            current++;
            localcounter++;
            continue;
			}
		current++;
		}
	return 0;
	}

unsigned long int Text_text::count_symbols() const {
    unsigned long int returnme = 0;
	wchar_t* current = startps11;
    while (current<endps11)
        {
            returnme++;
            current++;
        }
    return returnme;
}

unsigned long int Text_text::count_words() const {
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
