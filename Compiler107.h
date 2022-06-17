#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include "lexAna.h"
#include "pubic_ds.h"

using namespace std;

class Compiler107 {
    class lexAna la;

    union val{
        float c2; char ct; int c1; bool b;
    };
    enum typel {non,i,r,c,b};
    struct Sym{
        string id;
        typel t;
        val v;
    };
    struct Dag_node{
        string opt;
        string main;
        vector<string> A;
        
    };

    vector<string> statements;
    vector<Token> tokens;
    vector<Quat> quats;
    vector<Sym> syms;
    stack<Token> sem;
    stack<string> sem_t; // 压入t时记录它的名字
    stack<string> opr;  // 记录算符
    int num_v = 0; // 记录已压栈的同类型id
    int new_t = 0; // 记录
    int num = 0;
    int A = 0;

    // functions for parsing
    int PROGRAM(vector<Token>v1);
    int DEC(vector<Token>v1);
    int CONS(vector<Token>v1);
    int CON_LIST(vector<Token>v1);
    int TDF(vector<Token>v1);
    int VAR(vector<Token>v1);
    int VAR_LIST(vector<Token>v1);
    int ID_LIST(vector<Token>v1);
    int SUBID_LIST(vector<Token>v1);
    int SEN(vector<Token>v1);
    int SUB_SEN(vector<Token>v1);
    int SEN_LIST(vector<Token>v1);
    int IF(vector<Token>v1);
    int ELSE(vector<Token>v1);
    int WHILE(vector<Token>v1);
    int ASS(vector<Token>v1);
    int R(vector<Token>v1);
    int E(vector<Token>v1);
    int E1(vector<Token>v1);
    int T(vector<Token>v1);
    int T1(vector<Token>v1);
    int F(vector<Token>v1);
    int B(vector<Token>v1);
    int B1(vector<Token>v1);
    int BT(vector<Token>v1);
    int BT1(vector<Token>v1);
    int BF(vector<Token>v1);
    int W0(vector<Token>v1);
    int W1(vector<Token>v1);
    int W2(vector<Token>v1);
    int W3(vector<Token>v1);
    string judge(vector<Token>v1);
    void begin(vector<Token>v1);

    // functions for translating
    // 程序声明语句
    void PROG();
    void PROG_END();
    // 常量声明
    void ASSC();
    // 变量声明
    void DEC_V(char x);
    // 条件语句
    void IF();
    void EL();
    void IE();
    // 循环语句
    void WH();
    void DO();
    void WE();
    // 赋值语句
    void ASS();
    // 算术|布尔表达式
    void GEQ_E(string x);
    void GEQ_B(string x);
    void PUSH(Token t);
    void PUSH_V(Token t);

public:
    void init(string path);
    void lex_ana();
    void parse();
    void optimize();
    void output();
};
