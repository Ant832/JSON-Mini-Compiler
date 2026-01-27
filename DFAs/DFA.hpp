#ifndef DFA
#define DFA

#include <string>

using std::string;

class BaseDFA {
protected:
    string input;
    int start;
    int position;
    int longest = -1;
};


class trueDFA : public BaseDFA {
    void tStart();
    void t1();
    void t2();
    void t3();
    void t4();
public:
    trueDFA(string, int);
    string run();
};

class falseDFA : public BaseDFA {
    void fStart();
    void f1();
    void f2();
    void f3();
    void f4();
    void f5();
public:
    falseDFA(string, int);
    string run();
};

class nullDFA : public BaseDFA {
    void nStart();
    void n1();
    void n2();
    void n3();
    void n4();
public:
    nullDFA(string, int);
    string run();
};

class whitespaceDFA : public BaseDFA {
    void wsStart();
public:
    whitespaceDFA(string, int);
    string run();
};

class stringDFA : public BaseDFA {
    void strStart();
    void chars();
    void esc();
    void strEnd();
public:
    stringDFA(string, int);
    string run();
};

class longstringDFA : public BaseDFA {
    void longStart();
    void start1();
    void start2();
    void esc();
    void quote1();
    void quote2();
    void chars();
    void longEnd();
public:
    longstringDFA(string, int);
    string run();
};

class numberDFA : public BaseDFA {
    void numStart();
    void zero();
    void minus();
    void ints();
    void dec();
    void floats();
    void e();
    void plusMinus();
    void exp();
public:
    numberDFA(string, int);
    string run();
};

class lcurlyDFA : public BaseDFA {
    void lcStart();
    void lc1();
public:
    lcurlyDFA(string, int);
    string run();
};

class rcurlyDFA : public BaseDFA {
    void rcStart();
    void rc1();
public:
    rcurlyDFA(string, int);
    string run();
};

class lbracketDFA : public BaseDFA {
    void lbStart();
    void lb1();
public:
    lbracketDFA(string, int);
    string run();
};

class rbracketDFA : public BaseDFA {
    void rbStart();
    void rb1();
public:
    rbracketDFA(string, int);
    string run();
};

class colonDFA : public BaseDFA {
    void colStart();
    void col1();
public:
    colonDFA(string, int);
    string run();
};

class commaDFA : public BaseDFA {
    void comStart();
    void com1();
public:
    commaDFA(string, int);
    string run();
};

class unknownDFA : public BaseDFA {
    void unknown();
    void unknownEnd();
public:
    unknownDFA(string, int);
    string run();
};

#endif