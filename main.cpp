#include <getopt.h>
#include <iostream>
#include <cstring> 
#include <cctype>
#include <wchar.h>
#include <fstream>
#include <sstream>

using namespace std;

#include "xtextviewer.h"
#include "yabstract.h"//-
#include "zcode.h"//-
#include "zheader.h"//-
#include "zlist.h"//-
#include "ztext.h"//-

#ifdef _WIN32
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

unsigned int get_terminal_width() {
    #ifdef _WIN32
        return 240;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    #endif
}

int main(int argc, char **argv) {
    const char* short_options = "f:t:m:r:hv";

    const struct option long_options[] = {
        {"file", required_argument, NULL, 'f'},
        {"indent", required_argument, NULL, 't'},
        {"marker", required_argument, NULL, 'm'},
        {"redline", required_argument, NULL, 'r'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {NULL,0,NULL,0}
    };
    
    #ifdef _WIN32
    system("chcp 65001");
    #else
    setlocale(LC_ALL, "ru_RU.UTF-8");
    #endif 

    bool boolfilenamegiven = false;
    bool boolmarkergiven = false;
    char* strfilemane; //-f
    unsigned int intdistfromleftedge = 0;//-t
    wchar_t charholdsymbolfrommflag = L'*';//-m
    unsigned int intdistredline = 1;//-r

    unsigned int intterminwidth = get_terminal_width();
    if (intterminwidth<15) {std::wcout << L"terminal width too small " << intterminwidth << std::endl;
                                return -1;}
    std::wcout << L"terminal width: " << intterminwidth << L" symbols" << std::endl;
    if (intterminwidth<30 || intterminwidth > 20000) {
		std::wcout << L"invalid terminal width" << std::endl;
		}

    int c;
    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (c) {
            case 'f':
                if (optarg != NULL){
                    //std::wcout << L"File name: " << optarg << std::endl;
                    boolfilenamegiven = true;
                    strfilemane = new char[strlen(optarg) + 1];
                    strcpy(strfilemane,optarg);
                }
                else {
                    std::wcout << L"-f given with no file name" << std::endl;
					std::wcout << std::endl;
					std::wcout << L"Try /prog -h" << std::endl;
					std::wcout << std::endl;
                    delete[] strfilemane;
                    return -2;
                }
                break;
            case 't':
                if (optarg != NULL){
                    //std::wcout << L"Indent: " << optarg << std::endl;//--------------------
                    //boolindentgiven = true;
                    intdistfromleftedge = atoi(optarg);
                }
                else { 
					std::wcout << L"-t given with no number" << std::endl;
					std::wcout << std::endl;
					std::wcout << L"Try /prog -h" << std::endl;
					std::wcout << std::endl;
					delete[] strfilemane;
					return -3;
					}
                break;
            case 'm':
                if (optarg != NULL){
                    //std::wcout << L"Marker: " << optarg << std::endl;//--------------------
                    boolmarkergiven = true;
                    charholdsymbolfrommflag = optarg[0];
                }
                else {
					std::wcout << L"-m given with no symbol" << std::endl;
					std::wcout << std::endl;
					std::wcout << L"Try /prog -h" << std::endl;
					std::wcout << std::endl;
					delete[] strfilemane;
                    return -4;
                    }
                break;
            case 'r':
                if (optarg != NULL){
                    //std::wcout << L"Redline: " << optarg << std::endl;//--------------------
                    //boolredlinegiven = true;
                    intdistredline = atoi(optarg);
                }
                else {
					std::wcout << L"-r given with no number" << std::endl;
					std::wcout << std::endl;
					std::wcout << L"Try /prog -h" << std::endl;
					std::wcout << std::endl;
					delete[] strfilemane;
                    return -5;
                    }
    
                break;
            case 'h':
                    std::wcout << L"Help:" << std::endl; 
                    std::wcout << L"Try ./prog -f \"File name in local folder\" " << std::endl; 
                    std::wcout << L" -f        to choose file" << std::endl; 
                    std::wcout << L" -r number to print newline with num spaces from left edge" << std::endl; 
                    std::wcout << L" -t number to print text with num spaces from left edge" << std::endl; 
                    std::wcout << L" -m symbol to display symbol on left side on code segments" << std::endl; 
                    std::wcout << L" -h        to display help message" << std::endl; 
                    std::wcout << L" -v        to display version" << std::endl; 
                    delete[] strfilemane;
                    return 0;
                break;
            case 'v':
                std::wcout << L"Version is 1.1.9" << std::endl;
                delete[] strfilemane;
                return 0;
                //break;
            //case '?':
            default:
                std::wcout << L"Unknown option given in flags" << std::endl;
                std::wcout << std::endl;
                std::wcout << L"Try /prog -h" << std::endl;
                std::wcout << std::endl;
                delete[] strfilemane;
                return 0;
                //break;
        };
    };

    if (!boolfilenamegiven){std::wcout << L"no file name given" << std::endl;
                            return -1;}

    Text_viewer viewer(strfilemane,intdistfromleftedge,charholdsymbolfrommflag,intdistredline,intterminwidth,boolmarkergiven);
    delete[] strfilemane;
    //viewer.print();
    //viewer.print(intterminwidth);
    //printf("\ns\n");

    viewer.sizedoublenewline_positions = viewer.find_dnewline_positions();
    //viewer.print_parts();
    //    printf("\ns\n");

    //viewer.forceprint_astext();
    //viewer.forceprint_aslist();
//    viewer.forceprint_asheader();
//    viewer.forceprint_ascode();

//    printf("\n\n\n\n\n\n\n");
    viewer.switch_parts_ttype();

    return 0;
}

