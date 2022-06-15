#include <iostream>
#include <string>
#include <vector>
#include "lexAna.h"

int lexAna::is_K(string word) //判断关键字
{
    for (int i = 0; i < 15; i++) {
        if (word == K_list[i])
            return ++i;
    }
    return 0;
}

int lexAna::is_P(string c)//判断界符
{
    for (int i = 0; i < 15; i++) {
        if (c == P_list[i])
            return ++i;
    }
    return 0;
}

int lexAna::is_I(string word)//标识符
{
    if (word[0] == '\0')return 0;
    if(word[0]=='_'||word[0]>='a'&&word[0]<='z'||word[0]>='A'&&word[0]<='Z')
    {
        return 1;
    }
    else
        return 0;
}

int lexAna::is_C1(string word)//常整数
{
    int flag1=0;
    if(word[0]=='\0')return 0;
    if(word[0]>='0'&&word[0]<='9')
    {
        for(int i=1;i<word.length();i++)
        {
            if(word[i]<'0' || word[i]>'9')
            {
                flag1=1;
            }
        }
    }
    else flag1=1;
    if(flag1==0)return 1;
    else return 0;
}

int lexAna::is_C2(string word)//常实数
{
    int flag2=0;
    int flag3=0;
    if(word[0]=='\0')return 0;
    if(word[0]>='1'&&word[0]<='9')
    {
        for(int i=1;i<word.length();i++)
        {
            if(word[i]=='.')
            {
                flag3=1;
            }
        }
        for(int i=1;i<word.length();i++)
        {
            if((word[i]<'0'||word[i]>'9')&&word[i]!='.')
            {
                flag2=1;
            }
        }
    }
    else flag2=1;
    if(flag2==0&&flag3==1)return 1;
    else return 0;
}

int lexAna::is_CT(string word)//字符常量
{
    if (word[0] == '\0')return 0;
    int len=word.length();
    if(word[0]==test[0]&&word[len]==test[0])
    {
        return 1;
    }
    else return 0;
}

int lexAna::is_B(string bo)//布尔
{
    if(bo=="true")
    {
        return 1;
    }
    if(bo=="false")
    {
        return 2;
    }
    return 0;
}

vector<Token> lexAna::lex_ana(vector<string> Statements)
{
    struct Token t[10000];
    string word, lineStr, c, d;
    int jf, j=0, count=0, hang=1;
    while(j<Statements.size()) //按行读取vector数组
    {
        lineStr=Statements[j];
        int len=lineStr.length();
        for (int i = 0; i <= len; i++)
        {
            c = lineStr[i];
            jf=is_P(c);
            if (i == len || jf || c == " ")//如果遇到界符或结尾或空格
            {
                int k=is_K(word);//判断是不是关键字
                if(k)
                {
                    t[count].Lineshow=hang;
                    t[count].Lex=KeyType;
                    t[count].Sem=word;
                    count++;
                    word="";
                }
                if(k==0)//如果不是关键字判断是不是布尔型
                {
                    int b=is_B(word);
                    if(b)
                    {
                        t[count].Lineshow=hang;
                        t[count].Lex=BoolType;
                        t[count].Sem=word;
                        count++;
                        word="";
                    }
                    if(b==0)//如果不是布尔，判断C1及C2
                    {
                        int c1=is_C1(word);
                        if(c1)//常整数
                        {
                            t[count].Lineshow=hang;
                            t[count].Lex=IntType;
                            t[count].Sem=word;
                            count++;
                            word="";
                        }
                        if(c1==0)
                        {
                            int c2=is_C2(word);
                            {
                                if(c2)//常实数
                                {
                                    t[count].Lineshow=hang;
                                    t[count].Lex=RealType;
                                    t[count].Sem=word;
                                    count++;
                                    word="";
                                }
                                if(c2==0)
                                {
                                    int ct=is_CT(word);
                                    if(ct)
                                    {
                                        t[count].Lineshow=hang;
                                        t[count].Lex=CharType;
                                        t[count].Sem=word;
                                        count++;
                                        word="";
                                    }
                                    if(ct==0)
                                    {
                                        int i2=is_I(word);
                                        if(i2)
                                        {
                                            t[count].Lineshow=hang;
                                            t[count].Lex=identifier;
                                            t[count].Sem=word;
                                            count++;
                                            word="";
                                        }
                                    }


                                }
                            }
                        }
                    }

                }
                if(i==len) continue;
                if (c == "=" || c == "<" || c == ">"||c==":")
                {
                    d=lineStr[++i];
                    if((c == "=" && d == "=") ||(c == "<" && d == "=") ||(c == ">" && d == "=") ||(c == ":" && d == "="))
                    {
                        t[count].Lineshow=hang;
                        t[count].Lex=SignType;
                        t[count].Sem=c+d;
                        count++;
                        word="";
                    }
                    else
                    {
                        t[count].Lineshow=hang;
                        t[count].Lex=SignType;
                        t[count].Sem=c;
                        count++;
                        word="";
                        i--;
                    }
                }
                else if (c!=" ")
                {
                    t[count].Lineshow=hang;
                    t[count].Lex=SignType;
                    t[count].Sem=c;
                    count++;
                    word="";
                }
                else
                {
                    word="";
                }

            }
            else word+=c;

        }
        hang++;//一行读完行数加一
        j++;
    }
    vector<Token> ts(t, t+count);
    return ts;
}