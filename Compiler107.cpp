#include "Compiler107.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

void Compiler107::init(string path){
    ifstream f;
    f.open(path);
    if(!f) cout<<"fail to open"<<endl;
    string line;
    while(!f.eof()){
        getline(f, line);
        statements.emplace_back(line);
    }
//    for(auto iter:statements){
//        cout<<iter<<endl;
//    }
}

void Compiler107::lex_ana() {
    tokens = la.lex_ana(statements);
    for(int i=0;i<tokens.size();i++){
        cout<<tokens[i].Lineshow<<"\t"<<tokens[i].Lex<<"\t"<<tokens[i].Sem<<endl;
    }
}

void Compiler107::parse() {

}

void Compiler107::optimize() {

}

void Compiler107::output() {

}

void Compiler107::First() {
    Token id = sem.top();

    Quat q;
    q.q1 = "program";
    q.q2 = id.Sem;
    q.q3 = "_";
    q.q4 = "_";

    Sym s; // 填写符号表
    // 查重
    for(auto iter : syms){
        if (iter.id == id.Sem){
            cout<<"line "<<id.Lineshow<<", "<<id.Sem<<"has been declared"<<endl;
            exit(1);
        }
    }
    s.id = id.Sem;
    s.t = non;

    quats.emplace_back(q);
    syms.emplace_back(s);
}

void Compiler107::Last() {
    Token id = sem.top(); sem.pop();

    Quat q;
    q.q1 = "end";
    q.q2 = id.Sem;
    q.q3 = "_";
    q.q4 = "_";
    quats.emplace_back(q);
}

void Compiler107::ASSC() {
    Token cons = sem.top(); sem.pop();
    Token id = sem.top();sem.pop();

    Quat q;
    q.q1 = ":=";
    q.q2 = cons.Sem;
    q.q3 = "_";
    q.q4 = id.Sem;

    Sym s; // 填写符号表
    // 查重
    for(auto iter : syms){
        if (iter.id == id.Sem){
            cout<<"line "<<id.Lineshow<<", "<<id.Sem<<"has been declared"<<endl;
            exit(1);
        }
    }
    s.id = id.Sem;
    // 类型检查
    if(cons.Lex == IntType){
        s.t = i;
        s.v.c1 = stoi(cons.Sem);
    }
    else if(cons.Lex == RealType){
        s.t = r;
        s.v.c2 = stof(cons.Sem);
    }
    else{
        cout<<"line "<<cons.Lineshow<<", except a number after :="<<endl;
        exit(1);
    }

    // 加入四元式和符号表
    quats.emplace_back(q);
    syms.emplace_back(s);
}

void Compiler107::INI() {

}

void Compiler107::Name() {

}

void Compiler107::ENT() {

}

void Compiler107::TYP(int x) {
    Sym s;
    if(x==1) s.t = i;
    else if(x==2) s.t = r;
    else if(x==3) s.t = c;
    else if(x==4) s.t = b;

    syms.emplace_back(s);
}

void Compiler107::If() {

}

void Compiler107::Or() {

}

void Compiler107::END() {

}

void Compiler107::Beg() {

}

void Compiler107::DO() {

}

void Compiler107::WE() {

}

void Compiler107::ASS() {

}

void Compiler107::GEQ(string x) {

}
