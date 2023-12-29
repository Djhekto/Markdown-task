#ifndef ZLIST_H
#define ZLIST_H

#include "yabstract.h"

using namespace std;

class List_text: public Abstract_text{
    private:
        unsigned int intdistfromleftedge11;
        unsigned int intterminwidth11;
        wchar_t charholdsymbolfrommflag11;
        bool isnamedlist11;
        wchar_t* startps11;
        wchar_t* endps11;

    public:

        List_text(wchar_t* startps, wchar_t* endps, unsigned int intdistfromleftedge, wchar_t charholdsymbolfrommflag, bool isnamedlist, unsigned int intterminwidth);
        ~List_text();

        unsigned long int count_symbols() const;
        unsigned long int count_words() const;
        int print() const;
    
};

#endif