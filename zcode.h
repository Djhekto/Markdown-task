#ifndef ZCODE_H
#define ZCODE_H

using namespace std;

#include "yabstract.h"


class Code_text: public Abstract_text{
    private:
        wchar_t charholdsymbolfrommflag11;
        unsigned int intdistfromleftedge11;
        unsigned int intterminwidth11;
        wchar_t* startps11;
        wchar_t* endps11;

    public:
        Code_text(wchar_t* startps, wchar_t* endps,wchar_t charholdsymbolfrommflag,int intdistfromleftedge, unsigned int intterminwidth);
        ~Code_text();

        unsigned long int count_symbols() const;
        unsigned long int count_words() const;
        int print() const;
    
};

#endif

/*#ifndef ZHEADER_H
#define ZHEADER_H

#include "yabstract.h"

using namespace std;

class Header_text: public Abstract_text{
    private:
        unsigned int intterminwidth11;
        wchar_t* startps11;
        wchar_t* endps11;

    public:
        Header_text(wchar_t* startps, wchar_t* endps, unsigned int intterminwidth);
        ~Header_text();

        unsigned long int count_symbols() const;
        unsigned long int count_words() const;
        int print() const;
    
};

#endif*/