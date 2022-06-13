#include "Compiler107.h"
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

void Compiler107::init(string path){
    ifstream f;
    f.open(path);
    if(!f) cout<<"fail to open"<<endl;
    string line;
    while(getline(f, line))
        statements.emplace_back(line);
}

void Compiler107::lex_ana() {

}

void Compiler107::parse() {

}

void Compiler107::optimize() {

}

void Compiler107::output() {

}
