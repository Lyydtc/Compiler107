#include <vector>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

class Compiler107 {
    struct Token{
        string type;
        int num;
    };
    struct Quat{
        string q1,q2,q3,q4;
    };
    union val{
        float c2; char ct; int c1; bool b;
    };
    struct Sym{
        string id;
        union val v;
    };

    vector<string> statements;
    vector<string> P_list;
    vector<string> K_list;
    vector<string> I_list;
    vector<int> C1_list;
    vector<float> C2_list;
    vector<char> CT_list;
    vector<bool> B_list;
    vector<Token> tokens;
    vector<Quat> quats;
    vector<Sym> syms;
    stack<val> sem;

public:
    void init(string path);
    void lex_ana();
    void parse();
    void optimize();
    void output();
};
