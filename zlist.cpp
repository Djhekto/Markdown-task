#include <cstdio>
#include <cwchar>
#include <cwctype>

using namespace std;

#include "zlist.h"


List_text::List_text(wchar_t* startps, wchar_t* endps, unsigned int intdistfromleftedge, wchar_t charholdsymbolfrommflag, bool isnamedlist, unsigned int intterminwidth) {
    this->startps11 = startps;
    this->endps11 = endps-1;
    this->intdistfromleftedge11 = intdistfromleftedge;
    this->charholdsymbolfrommflag11 = charholdsymbolfrommflag;
    this->isnamedlist11 = isnamedlist;
    this->intterminwidth11 = intterminwidth;
}

List_text::~List_text() {

}

int List_text::print() const {
    bool is_colored = false;
    wprintf(L"\n");
    if (isnamedlist11) { /*printf("/nidk/n");*/
        wchar_t* current = startps11;
        while (current<endps11)
            {
                if (*current==L'.'){
					while(*current!=L'\n'){		current--;}
					current++;
					 break;
					 }
                current++;
            }
        
        while (current < endps11) {
            wprintf(L"\u001b[36m");
            while (current < endps11 && *current != L' ')
            {
                wprintf(L"%lc", *current);
                current++;
            }
            wprintf(L"\u001b[0m");

            while (current < endps11 && *current != L'\n')
            {
                if ( iswdigit(*(current))|| (*current==L'*') ){
					if (*(current+2) != L'\n' || *(current+2) != L' ') {
						
                        if ( iswdigit(*(current)) || *current==L'*')  {
							wprintf(L"\u001b[36m");
							is_colored = true;
						}
                        while (current < endps11 && *current != L' ')
                        {
							if (*current==L'*'){ 
								wprintf(L"%lc", charholdsymbolfrommflag11);
								current++;
								continue;
								}
                            wprintf(L"%lc", *current);
                            current++;
                        }
                        if (is_colored) wprintf(L"\u001b[0m");
                        is_colored = false;
					}
                }
                wprintf(L"%lc", *current);
                current++;
            }

        }
    
    	wprintf(L"\n");
    }

    else{
        wchar_t* current = startps11;
        while (current<endps11)
            {
                if (*current==L'*'){ break;}
                current++;
            }

        while (current < endps11) {
            wprintf(L"\u001b[36m");
            while (current < endps11 && *current != L' ')
            {
				if (*current==L'*'){ 
					wprintf(L"%lc", charholdsymbolfrommflag11);
					current++;
					continue;
					}
                wprintf(L"%lc", *current);
                current++;
            }
            wprintf(L"\u001b[0m");

            while (current < endps11 && *current != L'\n')
            {
                if ( iswdigit(*(current))|| (*current==L'*') ){
					if (*(current+2) != L'\n' || *(current+2) != L' ') {
                        if ( iswdigit(*(current)) || *current==L'*')  {
							wprintf(L"\u001b[36m");
							is_colored = true;
						}
						while (current < endps11 && *current != L' ')
                        {
							if (*current==L'*'){ 
								wprintf(L"%lc", charholdsymbolfrommflag11);
								current++;
								continue;
								}
                            wprintf(L"%lc", *current);
                            current++;
                        }
                        if (is_colored) wprintf(L"\u001b[0m");
                        is_colored = false;
					}
                }
                wprintf(L"%lc", *current);
                current++;
            }

        }
    
    
    }
    return 0;
}

unsigned long int List_text::count_symbols() const {
	unsigned long int returnme = 0;
	wchar_t* current = startps11;
    while (current<endps11)
        {
            returnme++;
            current++;
        }
    return returnme;
}

unsigned long int List_text::count_words() const {
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
