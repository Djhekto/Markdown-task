#include <cstdlib>
#include <locale.h>
#include <stdio.h>
#include <wchar.h>

using namespace std;

#include "xtextviewer.h"
#include "yabstract.h"
#include "zcode.h"
#include "zheader.h"
#include "zlist.h"
#include "ztext.h"


Text_viewer::Text_viewer(char* strfilemane1, unsigned int intdistfromleftedge1, wchar_t charholdsymbolfrommflag1, unsigned int intdistredline1, unsigned int intterminwidth1, bool boolmarkergiven1) {
    this->intdistfromleftedge1 = intdistfromleftedge1;
    this->charholdsymbolfrommflag1 = charholdsymbolfrommflag1;
    this->intdistredline1 = intdistredline1;
    this->intterminwidth1 = intterminwidth1;//*2;
    this->boolmarkergiven1 = boolmarkergiven1;

    setlocale(LC_ALL, "ru_RU.UTF-8");

    FILE* file = fopen(strfilemane1, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", strfilemane1);
        exit(EXIT_FAILURE);
    }

    char* buffer;
    long length;
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
buffer = new char[length + 1];
if (buffer) {
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
}
    fclose(file);

size_t size1 = mbstowcs(NULL, buffer, 0) + 1;
strholdallfileinput1 = new wchar_t[size1];
mbstowcs(strholdallfileinput1, buffer, size1);
strholdallfileinput1[size1 - 1] = L'\0';
    
    
    delete[] buffer;

    ppdoublenewline_positions = new wchar_t*[size1 + 1];
    sizedoublenewline_positions = 0;

}

Text_viewer::~Text_viewer() {
            delete[] strholdallfileinput1;
            delete[] ppdoublenewline_positions;
            //if (strfilemane1) { delete[] strfilemane1; }
            //delete sizedoublenewline_positions;
        }

void Text_viewer::print(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    size_t i = 0;
    unsigned int localcounter = 0;
    unsigned int countword = 0;

    while (strholdallfileinput1[i]!=L'\0') {
        while (strholdallfileinput1[i]!=L'\n') {
            if (localcounter == intterminwidth1){
                localcounter = 0;

                if (strholdallfileinput1[i] == L' ') {
                    printf("\n");
                    countword++;
                    i++;
                    }
                else {
                    if (strholdallfileinput1[i+1] == L' ' || strholdallfileinput1[i+1] == L'\n')
                        {
                            //printf("%c\n",strholdallfileinput1[i]);
                            wprintf(L"%lc\n",strholdallfileinput1[i]);
                            i++;
                            countword++;
                            if (strholdallfileinput1[i]==L' ')
                                {
                                    i++;
                                }
                        }
                    else {
                        /*if          */
                        //printf("-\n%c",strholdallfileinput1[i-1]);
                        wprintf(L"-\n%lc",strholdallfileinput1[i-1]);
                        localcounter = 1;
                        }
                    }

                }
            else{
                if (strholdallfileinput1[i]==L' '){
                    countword++;
                    if (localcounter >= intterminwidth1-3) {
                        printf("\n");
                        i++;
                        localcounter = 0;
                        }
                    }
                //printf("%c",strholdallfileinput1[i]);
                wprintf(L"%lc",strholdallfileinput1[i]);
                localcounter++;
                i++;
                }
            }
        printf("\n");
        i++;
        localcounter = 0;
        }
    
        printf("Total words: %u\nTotal symbols: %u\n", (unsigned int)countword,
                                                   (unsigned int)i);
    }

int Text_viewer::find_dnewline_positions() {
    bool wasthaprevioussymbolnewline = false;
    unsigned int sizedoublenewline_positions = 0;

    //std::wcout << L"-000-";
    ppdoublenewline_positions[sizedoublenewline_positions++] = &strholdallfileinput1[0];
    //std::wcout << L"-000-";
    for (unsigned int i = 1; i < wcslen(strholdallfileinput1); ++i) {
        if (strholdallfileinput1[i] == L'\n') {
            //std::wcout << L"000";
            if (wasthaprevioussymbolnewline) {
                //std::wcout << L"111";
                ppdoublenewline_positions[sizedoublenewline_positions++] = &strholdallfileinput1[i];
                wasthaprevioussymbolnewline = false;
            } else {
                wasthaprevioussymbolnewline = true;
            }
        } else {
            wasthaprevioussymbolnewline = false;
        }
    }
    printf("%u",sizedoublenewline_positions);
    return sizedoublenewline_positions;
}

void Text_viewer::print_positions() {
    for (unsigned int i = 0; i < sizedoublenewline_positions; ++i) {
        std::wcout << *ppdoublenewline_positions[i] << std::endl;
        std::wcout << ppdoublenewline_positions[i] << std::endl;
    }
}

void Text_viewer::print_parts() {
    for (unsigned int i = 0; i < sizedoublenewline_positions - 1; ++i) {
        wchar_t* start = ppdoublenewline_positions[i];
        wchar_t* end = ppdoublenewline_positions[i + 1];
        for (wchar_t* p = start; p < end; ++p) {
            std::wcout << *p;
        }
        std::wcout << std::endl;
        std::wcout << L"=======================================================" << std::endl;
    }
}

void Text_viewer::forceprint_astext() {
    Text_text* textInstance = new Text_text(ppdoublenewline_positions[2], ppdoublenewline_positions[3], intdistfromleftedge1, intdistredline1, intterminwidth1);
    textInstance->print();
    delete textInstance;
}

void Text_viewer::forceprint_aslist() {
    List_text* listInstance = new List_text(ppdoublenewline_positions[4], ppdoublenewline_positions[5], intdistfromleftedge1, charholdsymbolfrommflag1,true, intterminwidth1);
    listInstance->print();
    delete listInstance;

    listInstance = new List_text(ppdoublenewline_positions[8], ppdoublenewline_positions[9], intdistfromleftedge1, charholdsymbolfrommflag1,false, intterminwidth1);
    listInstance->print();
    delete listInstance;
}

void Text_viewer::forceprint_asheader() {
    Header_text* headerInstance = new Header_text(ppdoublenewline_positions[1], ppdoublenewline_positions[2], intterminwidth1);
    headerInstance->print();
    delete headerInstance;
}

void Text_viewer::forceprint_ascode() {
    //std::wcout << charholdsymbolfrommflag1;
    Code_text* codeInstance = new Code_text(ppdoublenewline_positions[29], ppdoublenewline_positions[30], charholdsymbolfrommflag1, intdistfromleftedge1, intterminwidth1);
    codeInstance->print();
    delete codeInstance;
}

void Text_viewer::switch_parts_ttype(){
    unsigned int aaaa = 0;
    unsigned long int pallsymb = 0;
    unsigned long int pallword = 0;
    wchar_t holdthatsymbol = L'@';
    if (boolmarkergiven1) { 
		holdthatsymbol = charholdsymbolfrommflag1;
		}
    //std::wcout<<aaaa<<sizedoublenewline_positions;
    while(aaaa<sizedoublenewline_positions-1)
    {
        wprintf(L"\n");

        wchar_t* pointer = ppdoublenewline_positions[aaaa];
        while(pointer<ppdoublenewline_positions[aaaa+1]){
            if (*pointer!=L'\n'){break;}
            pointer++;
        }

        wchar_t* p1 = pointer;

        if (*p1 == L'\\') {
            p1++;
            if (*p1==L'#')
            {
                Header_text* headerInstance = new Header_text(ppdoublenewline_positions[aaaa], ppdoublenewline_positions[aaaa+1], intterminwidth1);
                headerInstance->print();
                pallsymb += headerInstance->count_symbols();
				pallword += headerInstance->count_words();
                delete headerInstance;
                aaaa++;
                continue;
            }
        }
        p1 = pointer;

        if (*p1==L'#')
        {
            Header_text* headerInstance = new Header_text(ppdoublenewline_positions[aaaa], ppdoublenewline_positions[aaaa+1], intterminwidth1);
            headerInstance->print();
            pallsymb += headerInstance->count_symbols();
            pallword += headerInstance->count_words();
            delete headerInstance;
            aaaa++;
            continue;
        }

        if (*p1==L' '){p1++; 
        if (*p1==L' '){p1++; 
        if (*p1==L' '){p1++; 
        if (*p1==L' '){p1++;
		
        Code_text* codeInstance = new Code_text(ppdoublenewline_positions[aaaa], ppdoublenewline_positions[aaaa+1], holdthatsymbol, intdistfromleftedge1, intterminwidth1);
        codeInstance->print();
        pallsymb += codeInstance->count_symbols();
		pallword += codeInstance->count_words();
        delete codeInstance;
        aaaa++;
        continue;
        }
        }
        }
        }
        p1 = pointer;

        if (*p1==L'*'){
            List_text* listInstance = new List_text(ppdoublenewline_positions[aaaa], ppdoublenewline_positions[aaaa+1], intdistfromleftedge1, charholdsymbolfrommflag1,false, intterminwidth1);
            listInstance->print();
            pallsymb += listInstance->count_symbols();
			pallword += listInstance->count_words();
            delete listInstance;
            aaaa++;
            continue;
        }

        bool isthereadotnear = false;
        for (unsigned int i = 0; i<4; i++){
            p1++;
            if (*p1==L'.') {isthereadotnear = true; break;}
        }
        if (isthereadotnear){
            List_text* listInstance = new List_text(ppdoublenewline_positions[aaaa], ppdoublenewline_positions[aaaa+1], intdistfromleftedge1, charholdsymbolfrommflag1,true, intterminwidth1);
            listInstance->print();
            pallsymb += listInstance->count_symbols();
			pallword += listInstance->count_words();
            delete listInstance;
            aaaa++;
            continue;
        }
        p1 = pointer;

		p1 = ppdoublenewline_positions[aaaa+1]-2;
		if (*p1==L'-' && *(p1-1)==L'-'){
			Header_text* headerInstance = new Header_text(ppdoublenewline_positions[aaaa], ppdoublenewline_positions[aaaa+1], intterminwidth1);
            headerInstance->print();
            pallsymb += headerInstance->count_symbols();
            pallword += headerInstance->count_words();
            delete headerInstance;
            aaaa++;
            continue;
		}

        Text_text* textInstance = new Text_text(ppdoublenewline_positions[aaaa], ppdoublenewline_positions[aaaa+1], intdistfromleftedge1, intdistredline1, intterminwidth1);
        textInstance->print();
        pallsymb += textInstance->count_symbols();
		pallword += textInstance->count_words();
        delete textInstance;
        aaaa++;
        continue;
    }

std::wcout << std::endl;
std::wcout << L"File symbol count:" << pallsymb << std::endl;
std::wcout << L"File word count:" << pallword << std::endl;
    
}
