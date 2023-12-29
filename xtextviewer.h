#ifndef XTEXTVIEWER_H
#define XTEXTVIEWER_H

#include <iostream>
#include <cstring>
#include <cctype>
#include <wchar.h>
#include <fstream>
#include <sstream>

class Text_viewer {
    private:
        wchar_t* strholdallfileinput1;
        char* strfilemane1;

    public:
        wchar_t** ppdoublenewline_positions;
        size_t sizedoublenewline_positions;
        unsigned int intdistfromleftedge1;
        unsigned int intdistredline1;
        unsigned int intterminwidth1;
        bool boolmarkergiven1;
        wchar_t charholdsymbolfrommflag1;

        Text_viewer(char* strfilemane1, unsigned int intdistfromleftedge1, wchar_t charholdsymbolfrommflag1, unsigned int intdistredline1, unsigned int intterminwidth1, bool boolmarkergiven1);
        //Text_viewer(char* strfilemane1);
        ~Text_viewer();

        void print();
        //void print(unsigned int intterminwidth1);
        int find_dnewline_positions();
        void print_parts();
        void print_positions();
        void forceprint_astext();
        void forceprint_aslist();
        void forceprint_asheader();
        void forceprint_ascode();
        void switch_parts_ttype();
};

#endif
