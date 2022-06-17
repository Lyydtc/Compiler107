
#ifndef COMPILER107_LEXANA_H
#define COMPILER107_LEXANA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pubic_ds.h"

using namespace std;

class lexAna {
    vector<string> P_list={",",":",";",":=","*","/","+","-","(",")",">","<","="};//界符表
    vector<string> K_list={"program","const","var","integer","real","char","bool","begin","end","if","else","while","or","and","then","do", "true", "false"};//关键字表
    string test="'";

    int is_K(string word);
    int is_P(string c);
    int is_I(string word);
    int is_C1(string word);
    int is_C2(string word);
    int is_CT(string word);
    int is_B(string bo);
public:
    vector<Token> lex_ana(vector<string> lines);
};


#endif //COMPILER107_LEXANA_H
