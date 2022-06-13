#include <iostream>
#include "Compiler107.h"

using namespace std;

int main(){
    string path = "E:\\Github_local\\Compiler107\\in.txt";
    Compiler107 c;
    c.init(path);
    c.lex_ana();
    c.parse();
    c.optimize();
    c.output();
}