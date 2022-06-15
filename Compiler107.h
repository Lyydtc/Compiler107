#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include "lexAna.h"
#include "pubic_ds.h"

using namespace std;

class Compiler107 {
    class lexAna la;

    struct Quat{ string q1,q2,q3,q4; };
    union val{
        float c2; char ct; int c1; bool b;
    };
    enum typel {non,i,r,c,b};
    struct Sym{
        string id;
        typel t;
        val v;
    };

    vector<string> statements;
    vector<Token> tokens;
    vector<Quat> quats;
    vector<Sym> syms;
    stack<Token> sem;

    // functions for translating
    // 程序声明语句
    void First();
    void Last();
    // 常量声明
    void ASSC();
    // 类型声明
    // 变量声明
    void INI();
    void Name();
    void ENT();
    void TYP(int x);
    // 条件语句
    void If();
    void Or();
    void END();
    // 循环语句
    void Beg();
    void DO();
    void WE();
    // 赋值语句
    void ASS();
    // 算术|布尔表达式
    void GEQ(string x);

public:
    void init(string path);
    void lex_ana();
    void parse();
    void optimize();
    void output();
};
