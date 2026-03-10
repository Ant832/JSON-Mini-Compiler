#ifndef DFA
#define DFA

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class BaseDFA {
public:
    int longest = -1;
protected:
    string input;
    int start;
    int position;
    BaseDFA(const string &input, int startPos) : input(input), start(startPos), position(startPos) {}
};

template <typename BaseDFA>
void charCheck(const string &input, int &position, char check, BaseDFA &dfa, void (BaseDFA::*func)()) {
    if (position < input.size() && input[position] == check) {
        ++position;
        (dfa.*func)();
    }
}

template <typename BaseDFA>
void charCheckAny(const string &input, int &position, const string &chars, BaseDFA &dfa, void (BaseDFA::*func)()) {
    if (position < input.size() && chars.find(input[position]) != string::npos) {
        ++position;
        (dfa.*func)();
    }
}

template <typename BaseDFA>
string runT(const int start, const string input, BaseDFA &dfa, void (BaseDFA::*func)()) {
    (dfa.*func)();
    if (dfa.longest > -1) {
        return input.substr(start, dfa.longest - start);
    } else {
        return "";
    }
}


class trueDFA : public BaseDFA {
    inline void tStart() { charCheck(input, position, 't', *this, &trueDFA::t1); }
    inline void t1() { charCheck(input, position, 'r', *this, &trueDFA::t2); }
    inline void t2() { charCheck(input, position, 'u', *this, &trueDFA::t3); }
    inline void t3() { charCheck(input, position, 'e', *this, &trueDFA::t4); }
    inline void t4() { longest = position; }
public:
    inline trueDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &trueDFA::tStart); }
};

class falseDFA : public BaseDFA {
    inline void fStart() { charCheck(input, position, 'f', *this, &falseDFA::f1); }
    inline void f1() { charCheck(input, position, 'a', *this, &falseDFA::f2); }
    inline void f2() { charCheck(input, position, 'l', *this, &falseDFA::f3); }
    inline void f3() { charCheck(input, position, 's', *this, &falseDFA::f4); }
    inline void f4() { charCheck(input, position, 'e', *this, &falseDFA::f5); }
    inline void f5() { longest = position; }
public:
    inline falseDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &falseDFA::fStart); }
};

class nullDFA : public BaseDFA {
    inline void nStart() { charCheck(input, position, 'n', *this, &nullDFA::n1); }
    inline void n1() { charCheck(input, position, 'u', *this, &nullDFA::n2); }
    inline void n2() { charCheck(input, position, 'l', *this, &nullDFA::n3); }
    inline void n3() { charCheck(input, position, 'l', *this, &nullDFA::n4); }
    inline void n4() { longest = position; }
public:
    inline nullDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &nullDFA::nStart); }
};

class whitespaceDFA : public BaseDFA {
    inline void wsStart() {
        longest = position;
        charCheckAny(input, position, " \n\r\t", *this, &whitespaceDFA::wsStart);
    }
public:
    inline whitespaceDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &whitespaceDFA::wsStart); }
};

class stringDFA : public BaseDFA {
    inline void strStart() { charCheck(input, position, '"', *this, &stringDFA::chars); }

    inline void chars() {
        while (position < input.size() && (int(input[position]) >= 32 && int(input[position]) <= 126) && int(input[position]) != 34 && int(input[position]) != 92) {
            ++position;
        }
        charCheck(input, position, '\\', *this, &stringDFA::esc);
        charCheck(input, position, '"', *this, &stringDFA::strEnd);
    }

    inline void esc() { charCheckAny(input, position, "\"\\/bfnrt", *this, &stringDFA::chars); }
    inline void strEnd() { longest = position; }
public:
    inline stringDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &stringDFA::strStart); }
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
    inline longstringDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &longstringDFA::longStart); }
};

class numberDFA : public BaseDFA {
    void numStart();
    void minus();
    void ints();
    void dec();
    void floats();
    void e();
    void plusMinus();
    void zero();
    void exp();
public:
    inline numberDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &numberDFA::numStart); }
};

class lcurlyDFA : public BaseDFA {
    inline void lcStart() { charCheck(input, position, '{', *this, &lcurlyDFA::lc1); }
    inline void lc1() { longest = position; }
public:
    inline lcurlyDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &lcurlyDFA::lcStart); }
};

class rcurlyDFA : public BaseDFA {
    inline void rcStart() { charCheck(input, position, '}', *this, &rcurlyDFA::rc1); }
    inline void rc1() { longest = position; }
public:
    inline rcurlyDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &rcurlyDFA::rcStart); }
};

class lbracketDFA : public BaseDFA {
    inline void lbStart() { charCheck(input, position, '[', *this, &lbracketDFA::lb1); }
    inline void lb1() { longest = position; }
public:
    inline lbracketDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &lbracketDFA::lbStart); }
};

class rbracketDFA : public BaseDFA {
    inline void rbStart() { charCheck(input, position, ']', *this, &rbracketDFA::rb1); }
    inline void rb1() { longest = position; }
public:
    inline rbracketDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &rbracketDFA::rbStart); }
};

class colonDFA : public BaseDFA {
    inline void colStart() { charCheck(input, position, ':', *this, &colonDFA::col1); }
    inline void col1() { longest = position; }
public:
    inline colonDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &colonDFA::colStart); }
};

class commaDFA : public BaseDFA {
    inline void comStart() { charCheck(input, position, ',', *this, &commaDFA::com1); }
    inline void com1() { longest = position; }
public:
    inline commaDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &commaDFA::comStart); }
};

class unknownDFA : public BaseDFA {
    inline void unknown() { 
        if (position < input.size() && input[position]) {
            ++position;
            unknownEnd();
        }
    }

    inline void unknownEnd() {  longest = position; }
public:
    inline unknownDFA(string input, int start) : BaseDFA(input, start) {}
    inline string run() { return runT(start, input, *this, &unknownDFA::unknown); }
};

#endif