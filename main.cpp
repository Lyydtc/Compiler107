#include <iostream>
#include "Compiler107.h"

using namespace std;

int main(){
    string path = "E:\\Github_local\\Compiler107\\test2.txt"; // 自己改路径,我这边由于不可抗力必须绝对
    Compiler107 c;
    c.init(path);
    cout<<"initialized"<<endl;
    c.lex_ana();
    cout<<"lexical_analysis finished"<<endl;
    c.parse();
    c.optimize();
    c.output();
}