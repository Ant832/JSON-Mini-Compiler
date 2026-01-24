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


class unknownDFA : public BaseDFA {
    void unknown();
    void unknownEnd();
public:
    unknownDFA(string, int);
    string run();
};

#endif