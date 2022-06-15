//
// Created by 23860 on 2022/6/15.
//

#ifndef COMPILER107_PUBIC_DS_H
#define COMPILER107_PUBIC_DS_H

#include <string>

using namespace std;

enum LexType{KeyType,SignType,BoolType,RealType,IntType,identifier,CharType};//关键字，界符，布尔表，常实数，常整数，标识符，字符常量

struct Token{
    int Lineshow;
    LexType Lex;
    string Sem;
};

#endif //COMPILER107_PUBIC_DS_H
