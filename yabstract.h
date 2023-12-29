#ifndef YABSTRACT_H
#define YABSTRACT_H

using namespace std;

class Abstract_text {

    public:
        virtual ~Abstract_text();

        virtual unsigned long int count_symbols() const = 0;
        virtual unsigned long int count_words() const = 0;
        virtual int print() const = 0;

};

#endif
