#ifndef ZHEADER_H
#define ZHEADER_H

#include "yabstract.h"

using namespace std;

class Header_text: public Abstract_text{
    private:
        unsigned int intterminwidth11;
        wchar_t* startps11;
        wchar_t* endps11;

		
        struct Counters {
            unsigned long int symbols = 0;
            unsigned long int words = 0;
        };

        Counters counters;
		

    public:
        Header_text(wchar_t* startps, wchar_t* endps, unsigned int intterminwidth);
        ~Header_text();

        unsigned long int count_symbols() const;
        unsigned long int count_words() const;
        int print() const;
    
};

#endif
