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
}

void Compiler107::lex_ana() {
    tokens = la.lex_ana(statements);
    for(int i=0;i<tokens.size();i++){
        cout<<tokens[i].Lineshow<<"\t"<<tokens[i].Lex<<"\t"<<tokens[i].Sem<<endl;
    }
}

void Compiler107::parse() {
    begin(tokens);
    if(A==1) cout<<"Parsing finished"<<endl;
}

void Compiler107::optimize() {

}

void Compiler107::output() {
    cout<<"\nQuats:\n"<<endl;
    for(auto iter : quats){
        cout<<"("<<iter.q1<<","<<iter.q2<<","<<iter.q3<<","<<iter.q4<<")"<<endl;
    }
    cout<<"\nSyms:\n"<<endl;
    for(auto iter : syms){
        if(iter.t==i) cout<<"|"<<iter.id<<"\t"<<iter.t<<"\t"<<iter.v.c1<<"\t|"<<endl;
        else if(iter.t==r) cout<<"|"<<iter.id<<"\t"<<iter.t<<"\t"<<iter.v.c2<<"\t|"<<endl;
        else if(iter.t==c) cout<<"|"<<iter.id<<"\t"<<iter.t<<"\t"<<iter.v.ct<<"\t|"<<endl;
        else if(iter.t==b) cout<<"|"<<iter.id<<"\t"<<iter.t<<"\t"<<iter.v.b<<"\t|"<<endl;
    }
}

// functions for parsing
void Compiler107::begin(vector <Token> v1) {
    if (PROGRAM(v1))
        A = 1;
    else
        A = 0;
}
int Compiler107::PROGRAM(vector<Token>v1) {
    if (judge(v1) == "program") {
        cout << v1[num].Sem << endl;
        num++;
        if (judge(v1) == "id") {
            cout << v1[num].Sem << endl;
            PUSH(v1[num]);
            num++;
            if (judge(v1) == ":") {
                PROG();
                cout << v1[num].Sem << endl;
                num++;
                if (DEC(v1)){
                    if (SEN(v1)) {
                        PROG_END();
                        return 1;
                    }
                    else return 0;
                }
                else return 0;
            }
            else {
                cout << "ERROR in line " << v1[num].Lineshow<<endl;
                return 0;
            }
        }
        else {
            cout << "ERROR in line " << v1[num].Lineshow << endl;
            return 0;
        }
    }
    else {
        cout << "ERROR in line " << v1[num].Lineshow << endl;
        return 0;
    }
}
int Compiler107::DEC(vector<Token>v1) {
    if (CONS(v1)) {
        if (VAR(v1)) return 1;
        else return 0;
    }
    else return 0;
}
int Compiler107::CONS(vector<Token>v1) {
    if (judge(v1) == "const") {
        cout << v1[num].Sem << endl;
        num++;
        if (CON_LIST(v1)) return 1;
        else return 0;
    }
    else return 1;
}
int Compiler107::CON_LIST(vector<Token>v1) {
    if (judge(v1) == "id") {
        cout << v1[num].Sem << endl;
        PUSH(v1[num]);
        num++;
        if (judge(v1) == "=") {
            cout << v1[num].Sem << endl;
            num++;
            if (judge(v1) == "cons") {
                cout << v1[num].Sem << endl;
                PUSH(v1[num]);
                num++;
                if (judge(v1) == ";") {
                    cout << v1[num].Sem << endl;
                    ASSC();
                    num++;
                    if (CON_LIST(v1)) return 1;
                    else return 0;
                }
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    else return 1;
}
int Compiler107::TDF(vector<Token>v1) {
    if (judge(v1) == "integer") {
        DEC_V('i');
        cout << v1[num].Sem << endl;
        num++;
        return 1;
    }
    else if (judge(v1) == "real") {
        cout << v1[num].Sem<<endl;
        DEC_V('r');
        num++;
        return 1;
    }
    else if (judge(v1) == "char") {
        cout << v1[num].Sem << endl;
        DEC_V('c');
        num++;
        return 1;
    }
    else if (judge(v1) == "bool") {
        cout << v1[num].Sem<<endl;
        DEC_V('b');
        num++;
        return 1;
    }
    else return 0;
}
int Compiler107::VAR(vector<Token>v1) {
    if (judge(v1) == "var") {
        cout << v1[num].Sem << endl;
        num++;
        if (VAR_LIST(v1)) return 1;
        else return 0;
    }
    else return 1;
}
int Compiler107::VAR_LIST(vector<Token>v1) {
    if (ID_LIST(v1)) {
        if (judge(v1) == ":") {
            cout << v1[num].Sem << endl;
            num++;
            if (TDF(v1)) {
                if (judge(v1) == ";") {
                    cout << v1[num].Sem << endl;
                    num++;
                    if (VAR_LIST(v1)) return 1;
                    else return 0;
                }
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    else return 1;
}
int Compiler107::ID_LIST(vector<Token>v1) {
    if (judge(v1) == "id") {
        cout << v1[num].Sem << endl;
        PUSH_V(v1[num]);
        num++;
        if (SUBID_LIST(v1)) return 1;
        else return 0;
    }
    else return 0;
}
int Compiler107::SUBID_LIST(vector<Token>v1) {
    if (judge(v1) == ",") {
        cout << v1[num].Sem << endl;
        num++;
        if (judge(v1) == "id") {
            cout << v1[num].Sem << endl;
            PUSH_V(v1[num]);
            num++;
            if (SUBID_LIST(v1)) return 1;
            else return 0;
        }
        else return 0;
    }
    else return 1;
}
int Compiler107::SEN(vector<Token>v1) {
    if (judge(v1) == "begin") {
        cout << v1[num].Sem << endl;
        num++;
        if (SUB_SEN(v1)) {
            if (judge(v1) == "end") {
                cout << v1[num].Sem << endl;
                return 1;
            }
            else {
                cout << "ERROR in line " << v1[num].Lineshow << endl;
                return 0;
            }
        }
        else return 0;
    }
    else {
        cout << "ERROR in line " << v1[num].Lineshow << endl;
        return 0;
    }
}
int Compiler107::SUB_SEN(vector<Token>v1) {
    if (SEN_LIST(v1)) {
        if (SUB_SEN(v1)) return 1;
        else return 0;
    }
    else return 1;
}
int Compiler107::SEN_LIST(vector<Token>v1) {
    if (ASS(v1)) return 1;
    else if (IF(v1)) return 1;
    else if (WHILE(v1)) return 1;
    else return 0;
}
int Compiler107::IF(vector<Token>v1) {
    if (judge(v1) == "if") {
        cout << v1[num].Sem << endl;
        num++;
        if (R(v1)) {
            IF();
            if (judge(v1) == "then") {
                cout << v1[num].Sem << endl;
                num++;
                if (SUB_SEN(v1)) {
                    if (ELSE(v1)) {
                        if (judge(v1) == ";") {
                            cout << v1[num].Sem << endl;
                            num++;
                            return 1;
                        }
                        else return 0;
                    }
                    else return 0;
                }
                else return 0;
            }
            else {
                return 0;
            }
        }
        else return 0;
    }
    else return 0;
}
int Compiler107::ELSE(vector<Token>v1) {
    if (judge(v1) == "else") {
        cout<<v1[num].Sem<<endl;
        EL();
        num++;
        if (SUB_SEN(v1)) {
            IE();
            return 1;
        }
        else return 0;
    }
    else return 1;
}
int Compiler107::WHILE(vector<Token>v1) {
    if (judge(v1) == "while") {
        cout << v1[num].Sem << endl;
        WH();
        num++;
        if (R(v1)) {
            if (judge(v1) == "do") {
                DO();
                cout << v1[num].Sem << endl;
                num++;
                if (SUB_SEN(v1)) {
                    WE();
                    if (judge(v1) == ";") {
                        cout << v1[num].Sem << endl;
                        num++;
                        return 1;
                    }
                    else return 0;
                }
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}
int Compiler107::ASS(vector<Token>v1) {
    if (judge(v1) == "id") {
        cout << v1[num].Sem << endl;
        PUSH(v1[num]);
        num++;
        if (judge(v1) == "=") {
            cout << v1[num].Sem << endl;
            num++;
            if (R(v1)) {
                ASS();
                if (judge(v1) == ";") {
                    cout << v1[num].Sem << endl;
                    num++;
                    return 1;
                }
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}
int Compiler107::R(vector<Token>v1) {
    if (E(v1)) return 1;
    else if (B(v1)) return 1;
    else return 0;
}
int Compiler107::E(vector<Token>v1) {
    if (T(v1)) {
        if (E1(v1)) return 1;
        else return 0;
    }
    else return 0;
}
int Compiler107::E1(vector<Token>v1) {
    if (W0(v1)) {
        if (T(v1)) {
            GEQ_E(opr.top());
            opr.pop();
            if (E1(v1)) return 1;
            else return 0;
        }
        else return 0;
    }
    else return 1;
}
int Compiler107::T(vector<Token>v1) {
    if (F(v1)) {
        if (T1(v1)) return 1;
        else return 0;
    }
    else return 0;
}
int Compiler107::T1(vector<Token>v1) {
    if (W1(v1)) {
        if (F(v1)) {
            GEQ_E(opr.top());
            opr.pop();
            if (T1(v1)) return 1;
            else return 0;
        }
        else return 0;
    }
    else return 1;
}
int Compiler107::F(vector<Token>v1) {
    if ((judge(v1) == "id")&&(v1[num+1].Sem!="==")&& (v1[num + 1].Sem != ">")&& (v1[num + 1].Sem != "<") && (v1[num + 1].Sem != ">=") && (v1[num + 1].Sem != "<=")) {
        cout << v1[num].Sem << endl;
        PUSH(v1[num]);
        num++;
        return 1;
    }
    else if (judge(v1) == "cons") {
        cout << v1[num].Sem << endl;
        PUSH(v1[num]);
        num++;
        return 1;
    }
    else if (judge(v1) == "(") {
        num++;
        cout << v1[num].Sem << endl;
        if (E(v1)) {
            if (judge(v1) == ")") {
                num++;
                cout << v1[num].Sem << endl;
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}
int Compiler107::B(vector<Token>v1) {
    if (BT(v1)) {
        if (B1(v1)) return 1;
        else return 0;
    }
    else return 0;
}
int Compiler107::B1(vector<Token>v1) {
    if (W2(v1)) {
        if (BT(v1)) {
            GEQ_B(opr.top());
            opr.pop();
            if (B1(v1)) return 1;
            else return 0;
        }
        else return 0;
    }
    else return 1;
}
int Compiler107::BT(vector<Token>v1) {
    if (BF(v1)) {
        if (BT1(v1)) return 1;
        else return 0;
    }
    else return 0;
}
int Compiler107::BT1(vector<Token>v1) {
    if (W3(v1)) {
        if (BF(v1)) {
            GEQ_B(opr.top());
            opr.pop();
            if (BT1(v1)) return 1;
            else return 0;
        }
        else return 0;
    }
    else return 1;
}
int Compiler107::BF(vector<Token>v1) {
    if (judge(v1) == "true") {
        PUSH(v1[num]);
        num++;
        return 1;
    }
    else if (judge(v1) == "false") {
        PUSH(v1[num]);
        num++;
        return 1;
    }
    else if (judge(v1) == "id") {
        cout << v1[num].Sem << endl;
        PUSH(v1[num]);
        num++;
        return 1;
    }
    else if (judge(v1) == "cons") {
        PUSH(v1[num]);
        num++;
        cout << v1[num].Sem << endl;
        return 1;
    }
    else if (judge(v1) == "(")
    {
        num++;
        if (B(v1))
        {
            if (judge(v1) == ")") {
                num++;
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}
int Compiler107::W0(vector<Token>v1) {
    if (judge(v1) == "+") {
        cout << v1[num].Sem << endl;
        opr.push("+");
        num++;
        return 1;
    }
    else if (judge(v1) == "-") {
        cout << v1[num].Sem << endl;
        opr.push("-");
        num++;
        return 1;
    }
    else
        return 0;
}
int Compiler107::W1(vector<Token>v1) {
    if (judge(v1) == "*") {
        cout << v1[num].Sem << endl;
        opr.push("*");
        num++;
        return 1;
    }
    else if (judge(v1) == "/") {
        cout << v1[num].Sem << endl;
        opr.push("/");
        num++;
        return 1;
    }
    else
        return 0;
}
int Compiler107::W2(vector<Token>v1) {
    if (judge(v1) == "or") {
        opr.push("or");
        num++;
        return 1;
    }
    else if (judge(v1) == "and") {
        opr.push("and");
        num++;
        return 1;
    }
    else
        return 0;
}
int Compiler107::W3(vector<Token>v1) {
    if (judge(v1) == "<") {
        cout << v1[num].Sem << endl;
        opr.push("<");
        num++;
        return 1;
    }
    else if (judge(v1) == ">") {
        cout << v1[num].Sem << endl;
        opr.push(">");
        num++;
        return 1;
    }
    else if (judge(v1) == "<=") {
        cout << v1[num].Sem << endl;
        opr.push("<=");
        num++;
        return 1;
    }
    else if (judge(v1) == ">=") {
        cout << v1[num].Sem << endl;
        opr.push(">=");
        num++;
        return 1;
    }
    else if (judge(v1) == "==") {
        cout << v1[num].Sem << endl;
        opr.push("==");
        num++;
        return 1;
    }
    else if (judge(v1) == "<>") {
        cout << v1[num].Sem << endl;
        opr.push("<>");
        num++;
        return 1;
    }
    else
        return 0;
}
string Compiler107::judge(vector <Token> v1) {
    if ((v1[num].Lex == KeyType) || (v1[num].Lex == SignType) || (v1[num].Lex == BoolType))
        return(v1[num].Sem);
    else if ((v1[num].Lex == RealType) || (v1[num].Lex == IntType))
        return ("cons");
    else if ((v1[num].Lex == identifier) || (v1[num].Lex == CharType))
        return ("id");
}

// functions for translating
void Compiler107::PROG() {
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
            cout<<"ERROR, line "<<id.Lineshow<<", "<<id.Sem<<"has been declared"<<endl;
            exit(1);
        }
    }
    s.id = id.Sem;
    s.t = non;

    quats.emplace_back(q);
    syms.emplace_back(s);
}

void Compiler107::PROG_END() {
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
            cout<<"ERROR, line "<<id.Lineshow<<", "<<id.Sem<<"has been declared"<<endl;
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
        cout<<"line "<<cons.Lineshow<<", except a number in declaration of consts"<<endl;
        exit(1);
    }

    // 加入四元式和符号表
    quats.emplace_back(q);
    syms.emplace_back(s);
}

void Compiler107::DEC_V(char x) {
    Token t;
    Sym s;
    for(int j=num_v;j>0;j--){
        t = sem.top(); sem.pop();
        s.id = t.Sem;
        if(x=='i') s.t = i;
        else if(x=='r') s.t = r;
        else if(x=='c') s.t = c;
        else s.t = b;
        s.v.c1 = 0;
        syms.emplace_back(s);
    }
    num_v = 0;
}

void Compiler107::IF() {
    Token t = sem.top(); sem.pop();
    Quat q;
    q.q1 = "if";
    q.q2 = t.Sem;
    q.q3 = "_";
    q.q4 = "_";

    sem_t.pop();
    quats.emplace_back(q);
}

void Compiler107::EL() {
    Quat q;
    q.q1 = "el";
    q.q2 = "_";
    q.q3 = "_";
    q.q4 = "_";

    quats.emplace_back(q);
}

void Compiler107::IE() {
    Quat q;
    q.q1 = "ie";
    q.q2 = "_";
    q.q3 = "_";
    q.q4 = "_";

    quats.emplace_back(q);
}

void Compiler107::WH() {
    Quat q;
    q.q1 = "wh";
    q.q2 = "_";
    q.q3 = "_";
    q.q4 = "_";

    quats.emplace_back(q);
}

void Compiler107::DO() {
    Token t = sem.top(); sem.pop();
    Quat q;
    q.q1 = "do";
    q.q2 = t.Sem;
    q.q3 = "_";
    q.q4 = "_";

    quats.emplace_back(q);
}

void Compiler107::WE() {
    Quat q;
    q.q1 = "we";
    q.q2 = "_";
    q.q3 = "_";
    q.q4 = "_";

    quats.emplace_back(q);
}

void Compiler107::ASS() {
    Token res = sem.top(); sem.pop();
    Token id = sem.top(); sem.pop();

    Quat q;

    if(!sem_t.empty()){
        q.q2 = sem_t.top(); sem_t.pop();
    }
    else q.q2 = res.Sem;

    q.q1 = ":=";
    q.q3 = "_";
    q.q4 = id.Sem;
    // 查重
    int j;
    for(j=0;j<syms.size();j++) {
        if (syms[j].id == id.Sem) {
            // 类型检查
            if (res.Lex == IntType && syms[j].t == i) syms[j].v.c1 = stoi(res.Sem);
            else if (res.Lex == RealType && syms[j].t == r) syms[j].v.c2 = stof(res.Sem);
            else if (res.Lex == CharType && syms[j].t == c) syms[j].v.ct = res.Sem[0];
            else if (res.Lex == BoolType && syms[j].t == b) {
                if(res.Sem=="true") syms[j].v.b = true;
                else syms[j].v.b = false;
            }
            else {
                cout << "ERROR, line " << id.Lineshow << ", different types between =" << endl;
                exit(1);
            }
            quats.emplace_back(q);
            return;
        }
    }

    // 是新id
    Sym s;
    s.id = id.Sem;
    if(res.Lex==IntType) {
        s.t = i;
        s.v.c1 = stoi(res.Sem);
    }
    else if(res.Lex==RealType) {
        s.t = r;
        s.v.c2 = stof(res.Sem);
    }
    else if(res.Lex==CharType) {
        s.t = c;
        s.v.ct = res.Sem[0];
    }
    else if(res.Lex==BoolType) {
        s.t = b;
        if(res.Sem=="true") syms[j].v.b = true;
        else syms[j].v.b = false;
    }
    else cout << "ERROR, line " << id.Lineshow << ", invalid type" << endl;

    // 加入四元式和符号表
    quats.emplace_back(q);
    syms.emplace_back(s);
}

void Compiler107::GEQ_E(string x) {
    Quat q;
    Token t1, t2, temp;
    t1 = sem.top(); sem.pop();
    t2 = sem.top(); sem.pop();

    new_t += 1;
    string index = to_string(new_t);
    string newt = "t"+index;

    // t1 t2均为id, 必须都在符号表中找到
    if(t1.Lex==identifier && t2.Lex==identifier){
        Sym s1,s2;
        int flag = 0;
        for(int j=0;j<syms.size();j++){
            if(syms[j].id==t1.Sem) {
                s1 = syms[j];
                flag = 1;
            }
            if(syms[j].id==t2.Sem) {
                s2 = syms[j];
                flag = 2;
            }
        }
        if(flag!=2){     // 没找到
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        if(s1.t!=s2.t){  // 找到了, 但类型不一致
            cout<<"ERROR, line"<<t1.Lineshow<<", different types between "<<x<<endl;
            exit(1);
        }
        if(s1.t==c || s1.t==b){ // 找到了 但是是char或者bool
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        else {           // 正常
            if(s1.t == i) {
                temp.Lex=IntType;
                if(x=="+") temp.Sem = to_string(s2.v.c1+s1.v.c1);
                else if(x=="-") temp.Sem = to_string(s2.v.c1-s1.v.c1);
                else if(x=="*") temp.Sem = to_string(s2.v.c1*s1.v.c1);
                else if(x=="/") temp.Sem = to_string(s2.v.c1/s1.v.c1);
            }
            else if(s1.t == r) {
                temp.Lex=RealType;
                if(x=="+") temp.Sem = to_string(s2.v.c2+s1.v.c2);
                else if(x=="-") temp.Sem = to_string(s2.v.c2-s1.v.c2);
                else if(x=="*") temp.Sem = to_string(s2.v.c2*s1.v.c2);
                else if(x=="/") temp.Sem = to_string(s2.v.c2/s1.v.c2);
            }
        }
        q.q1 = x;
        q.q2 = t2.Sem;
        q.q3 = t1.Sem;
        q.q4 = newt;
    }
    // t1为id t2为cons
    else if(t1.Lex==identifier && (t2.Lex==IntType||t2.Lex==RealType)){
        Sym s;
        int flag = 0;
        for(int j=0;j<syms.size();j++){
            if(syms[j].id==t1.Sem) {
                s = syms[j];
                flag = 1;
            }
        }
        if(flag!=1){     // 没找到
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        if(s.t==c || s.t==b){ // 找到了 但是是char或者bool
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        else {           // 正常
            if(s.t == i) {
                temp.Lex = IntType;
                if(x=="+") temp.Sem = to_string(stof(t2.Sem)+s.v.c1);
                else if(x=="-") temp.Sem = to_string(stof(t2.Sem)-s.v.c1);
                else if(x=="*") temp.Sem = to_string(stof(t2.Sem)*s.v.c1);
                else if(x=="/") temp.Sem = to_string(stof(t2.Sem)/s.v.c1);
            }
            else if(s.t == r) {
                temp.Lex = RealType;
                if(x=="+") temp.Sem = to_string(stof(t2.Sem)+s.v.c2);
                else if(x=="-") temp.Sem = to_string(stof(t2.Sem)-s.v.c2);
                else if(x=="*") temp.Sem = to_string(stof(t2.Sem)*s.v.c2);
                else if(x=="/") temp.Sem = to_string(stof(t2.Sem)/s.v.c2);
            }
        }
        q.q1 = x;
        q.q2 = t2.Sem;
        q.q3 = t1.Sem;
        q.q4 = newt;
    }
    // t2为id t1为cons
    else if(t2.Lex==identifier && (t1.Lex==IntType||t1.Lex==RealType)){
        Sym s;
        int flag = 0;
        for(int j=0;j<syms.size();j++){
            if(syms[j].id==t2.Sem) {
                s = syms[j];
                flag = 1;
            }
        }
        if(flag!=1){     // 没找到
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        if(s.t==c || s.t==b){ // 找到了 但是是char或者bool
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        else {           // 正常
            if(s.t == i) {
                temp.Lex = IntType;
                if (x=="+") temp.Sem = to_string(s.v.c1+stof(t1.Sem));
                else if(x=="-") temp.Sem = to_string(s.v.c1-stof(t1.Sem));
                else if(x=="*") temp.Sem = to_string(s.v.c1*stof(t1.Sem));
                else if(x=="/") temp.Sem = to_string(s.v.c1/stof(t1.Sem));
                q.q2 = to_string(s.v.c1);
            }
            else if(s.t == r) {
                temp.Lex = RealType;
                if(x=="+") temp.Sem = to_string(stof(t2.Sem)+s.v.c2);
                else if(x=="-") temp.Sem = to_string(stof(t2.Sem)-s.v.c2);
                else if(x=="*") temp.Sem = to_string(stof(t2.Sem)*s.v.c2);
                else if(x=="/") temp.Sem = to_string(stof(t2.Sem)/s.v.c2);
                q.q2 = to_string(s.v.c2);
            }
        }
        q.q1 = x;
        q.q2 = t2.Sem;
        q.q3 = t1.Sem;
        q.q4 = newt;
    }
    // t1 t2均为cons
    else if((t1.Lex==IntType||t1.Lex==RealType) && (t2.Lex==IntType||t2.Lex==RealType)){
        if(t1.Lex==IntType&&t2.Lex==IntType){
            temp.Lex = IntType;
            if(x=="+") temp.Sem = to_string(stoi(t2.Sem)+stoi(t1.Sem));
            else if(x=="-") temp.Sem = to_string(stoi(t2.Sem)-stoi(t1.Sem));
            else if(x=="*") temp.Sem = to_string(stoi(t2.Sem)*stoi(t1.Sem));
            else if(x=="/") temp.Sem = to_string(stoi(t2.Sem)/stoi(t1.Sem));
        }
        else {
            temp.Lex = RealType;
            if(x=="+") temp.Sem = to_string(stof(t2.Sem)+stof(t1.Sem));
            else if(x=="-") temp.Sem = to_string(stof(t2.Sem)-stof(t1.Sem));
            else if(x=="*") temp.Sem = to_string(stof(t2.Sem)*stof(t1.Sem));
            else if(x=="/") temp.Sem = to_string(stof(t2.Sem)/stof(t1.Sem));
        }
        q.q1 = x;
        q.q2 = t2.Sem;
        q.q3 = t1.Sem;
        q.q4 = newt;
    }

    if(!sem_t.empty()){
        if(t2.Lex==identifier){
            q.q3 = sem_t.top(); sem_t.pop();
        }
        else{
            q.q2 = sem_t.top(); sem_t.pop();
        }
    }

    sem_t.push(newt);
    sem.push(temp);
    quats.emplace_back(q);
}

void Compiler107::GEQ_B(string x) {
    Quat q;
    Token t1, t2, temp;
    t1 = sem.top(); sem.pop();
    t2 = sem.top(); sem.pop();

    new_t += 1;
    string index = to_string(new_t);
    string newt = "t"+index;

    // t1 t2均为id, 必须都在符号表中找到
    if(t1.Lex==identifier && t2.Lex==identifier){
        Sym s1,s2;
        int flag = 0;
        for(int j=0;j<syms.size();j++){
            if(syms[j].id==t1.Sem) {
                s1 = syms[j];
                flag = 1;
            }
            if(syms[j].id==t2.Sem) {
                s2 = syms[j];
                flag = 2;
            }
        }
        if(flag!=2){     // 没找到
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        if(s1.t!=s2.t){  // 找到了, 但类型不一致
            cout<<"ERROR, line"<<t1.Lineshow<<", different types between "<<x<<endl;
            exit(1);
        }
        if(s1.t==c){ // 找到了 但是是char
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        else {           // 正常
            if(s1.t == r||s1.t==i) {
                temp.Lex = BoolType;
                if(x==">") {
                    if(s2.v.c2 > s1.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x==">=") {
                    if(s2.v.c2 >= s1.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="<") {
                    if(s2.v.c2 < s1.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="<=") {
                    if(s2.v.c2 <= s1.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="==") {
                    if(s2.v.c2 == s1.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="<>") {
                    if(s2.v.c2 != s1.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else {
                    cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
                    exit(1);
                }
            }
            else if(s1.t == b) {
                temp.Lex=BoolType;
                if(x=="and") {
                    if(s1.v.b&&s2.v.b) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="or") {
                    if(s1.v.b||s2.v.b) temp.Sem = "true";
                    else temp.Sem = "false";
                }
            }

        }
        q.q1 = x;
        q.q2 = to_string(s2.v.c1);
        q.q3 = to_string(s1.v.c1);
        q.q4 = newt;
    }
    // t1为id t2为cons
    else if(t1.Lex==identifier && (t2.Lex==IntType||t2.Lex==RealType)){
        Sym s;
        int flag = 0;
        for(int j=0;j<syms.size();j++){
            if(syms[j].id==t1.Sem) {
                s = syms[j];
                flag = 1;
            }
        }
        if(flag!=1){     // 没找到
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        if(s.t==c){ // 找到了 但是是char
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        else {           // 正常
            if(s.t == i||s.t==r) {
                temp.Lex=BoolType;
                if(x==">") {
                    if(stof(t2.Sem) > s.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x==">=") {
                    if(stof(t2.Sem) >= s.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="<") {
                    if(stof(t2.Sem) < s.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="<=") {
                    if(stof(t2.Sem) <= s.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="==") {
                    if(stof(t2.Sem) == s.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="<>") {
                    if(stof(t2.Sem) != s.v.c2) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else {
                    cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
                    exit(1);
                }
            }
            else if(s.t == b) {
                temp.Lex=BoolType;
                if(x=="and") {
                    if(t2.Sem=="true"&&s.v.b) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="or") {
                    if(t2.Sem=="false"&&!s.v.b) temp.Sem = "false";
                    else temp.Sem = "true";
                }
            }
        }
        q.q1 = x;
        q.q2 = t2.Sem;
        if(s.v.b) q.q3 = "true";
        else q.q3 = "false";
        q.q4 = newt;
    }
    // t1为cons t2为id
    else if(t2.Lex==identifier && (t1.Lex==IntType||t1.Lex==RealType)){
        Sym s;
        int flag = 0;
        for(int j=0;j<syms.size();j++){
            if(syms[j].id==t2.Sem) {
                s = syms[j];
                flag = 1;
            }
        }
        if(flag!=1){     // 没找到
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        if(s.t==c){ // 找到了 但是是char
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        else {           // 正常
            if(s.t == i||s.t==r) {
                temp.Lex=BoolType;
                if(x==">") {
                    if(s.v.c2 > stof(t1.Sem)) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x==">=") {
                    if(s.v.c2 >= stof(t1.Sem)) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="<") {
                    if(s.v.c2 < stof(t1.Sem)) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="<=") {
                    if(s.v.c2 <= stof(t1.Sem)) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="==") {
                    if(s.v.c2 == stof(t1.Sem)) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="<>") {
                    if(s.v.c2 != stof(t1.Sem)) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else {
                    cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
                    exit(1);
                }
            }
            else if(s.t == b) {
                temp.Lex=BoolType;
                if(x=="and") {
                    if(t1.Sem=="true"&&s.v.b) temp.Sem = "true";
                    else temp.Sem = "false";
                }
                else if(x=="or") {
                    if(t1.Sem=="false"&&!s.v.b) temp.Sem = "false";
                    else temp.Sem = "true";
                }
            }
        }
        q.q1 = x;
        q.q2 = t2.Sem;
        q.q3 = t1.Sem;
        q.q4 = newt;
    }
    // t1 t2均为cons
    else if((t1.Lex==IntType||t1.Lex==RealType) && (t2.Lex==IntType||t2.Lex==RealType)){
        if(t1.Lex==IntType&&t2.Lex==IntType){
            temp.Lex = BoolType;
            if(x==">") {
                if(stof(t2.Sem) > stof(t1.Sem)) temp.Sem = "true";
                else temp.Sem = "false";
            }
            else if(x==">=") {
                if(stof(t2.Sem) >= stof(t1.Sem)) temp.Sem = "true";
                else temp.Sem = "false";
            }
            else if(x=="<") {
                if(stof(t2.Sem) < stof(t1.Sem)) temp.Sem = "true";
                else temp.Sem = "false";
            }
            else if(x=="<=") {
                if(stof(t2.Sem) <= stof(t1.Sem)) temp.Sem = "true";
                else temp.Sem = "false";
            }
            else if(x=="==") {
                if(stof(t2.Sem) == stof(t1.Sem)) temp.Sem = "true";
                else temp.Sem = "false";
            }
            else if(x=="<>") {
                if(stof(t2.Sem) != stof(t1.Sem)) temp.Sem = "true";
                else temp.Sem = "false";
            }
            else {
                cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
                exit(1);
            }
        }
        q.q1 = x;
        q.q2 = t2.Sem;
        q.q3 = t1.Sem;
        q.q4 = newt;
    }
    // t1为id, t2为bool
    else if(t1.Lex==identifier&&t2.Lex==BoolType){
        Sym s;
        int flag = 0;
        for(int j=0;j<syms.size();j++){
            if(syms[j].id==t1.Sem) {
                s = syms[j];
                flag = 1;
            }
        }
        if(flag!=1){     // 没找到
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        if(s.t==c||s.t==i||s.t==r){ // 找到了 但是t1不是bool
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        else {           // 正常
            temp.Lex=BoolType;
            if(x=="and") {
                if(t2.Sem=="true"&&s.v.b) temp.Sem = "true";
                else temp.Sem = "false";
            }
            else if(x=="or") {
                if(t2.Sem=="false"&&!s.v.b) temp.Sem = "false";
                else temp.Sem = "true";
            }
            else{
                cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
                exit(1);
            }
        }
        q.q1 = x;
        q.q2 = t2.Sem;
        if(s.v.b) q.q3 = "true";
        else q.q3 = "false";
        q.q4 = newt;
    }
    // t1为bool, t2为id
    else if(t1.Lex==BoolType&&t2.Lex==identifier){
        Sym s;
        int flag = 0;
        for(int j=0;j<syms.size();j++){
            if(syms[j].id==t2.Sem) {
                s = syms[j];
                flag = 1;
            }
        }
        if(flag!=1){     // 没找到
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        if(s.t==c||s.t==i||s.t==r){ // 找到了 但是t2不是bool
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        else {           // 正常
            temp.Lex=BoolType;
            if(x=="and") {
                if(t1.Sem=="true"&&s.v.b) temp.Sem = "true";
                else temp.Sem = "false";
            }
            else if(x=="or") {
                if(t1.Sem=="false"&&!s.v.b) temp.Sem = "false";
                else temp.Sem = "true";
            }
            else{
                cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
                exit(1);
            }
        }
        q.q1 = x;
        if(s.v.b) q.q2 = "true";
        else q.q2 = "false";
        q.q3 = t1.Sem;
        q.q4 = newt;
    }
    // t1 t2均为bool
    else if(t1.Lex==BoolType&&t2.Lex==BoolType){
        if(x=="and") {
            if(t1.Sem=="true"&&t2.Sem=="true") temp.Sem = "true";
            else temp.Sem = "false";
        }
        else if(x=="or") {
            if(t1.Sem=="false"&&t2.Sem=="false") temp.Sem = "false";
            else temp.Sem = "true";
        }
        else{
            cout<<"ERROR, line"<<t1.Lineshow<<", invalid variables"<<endl;
            exit(1);
        }
        q.q1 = x;
        q.q2 = t2.Sem;
        q.q3 = t1.Sem;
        q.q4 = newt;
    }

    if(!sem_t.empty()){
        if(t2.Lex==identifier){
            q.q3 = sem_t.top(); sem_t.pop();
        }
        else{
            q.q2 = sem_t.top(); sem_t.pop();
        }
    }

    sem_t.push(newt);
    temp.Sem = newt;
    sem.push(temp);
    quats.emplace_back(q);
}

void Compiler107::PUSH(Token t) {
    sem.push(t);
}

void Compiler107::PUSH_V(Token t) {
    num_v += 1;
    sem.push(t);
}
