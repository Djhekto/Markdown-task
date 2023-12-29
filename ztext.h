#ifndef ZTEXT_H
#define ZTEXT_H

#include "yabstract.h"

using namespace std;

class Text_text/*lol*/: public Abstract_text{
    private:
        //wchar_t* strtext;
        unsigned int intdistfromleftedge11;
        unsigned int intdistredline11;
        unsigned int intterminwidth11;
        wchar_t* startps11;
        wchar_t* endps11;
        
    public:

        Text_text(wchar_t* startps, wchar_t* endps11, unsigned int intdistfromleftedge, unsigned int intdistredline, unsigned int intterminwidth);
        ~Text_text();

        unsigned long int count_symbols() const override;
        unsigned long int count_words() const override;
        int print() const override;
};


#endif