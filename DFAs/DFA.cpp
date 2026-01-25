#include <iostream>
#include <string>
#include "DFA.hpp"

using std::cout;
using std::endl;
using std::string;


// ----------------- trueDFA method definitions -----------------
void trueDFA::tStart() {
    if (position < input.size() && input[position] == 't') {
        ++position;
        t1();
    } 
}

void trueDFA::t1() {
    if (position < input.size() && input[position] == 'r') {
        ++position;
        t2();
    } 
}

void trueDFA::t2() {
    if (position < input.size() && input[position] == 'u') {
        ++position;
        t3();
    } 
}

void trueDFA::t3() {
    if (position < input.size() && input[position] == 'e') {
        ++position;
        t4();
    } 
}

void trueDFA::t4() {
    longest = position;
}


trueDFA::trueDFA(string input, int start) {
    this->input = input;
    this->start = start;
    position = start;
}

string trueDFA::run() {
    tStart();
    if (longest > -1) {
        return input.substr(start, longest - start);
    } else {
        return "";
    }
}

// ----------------- falseDFA method definitions -----------------
void falseDFA::fStart() {
    if (position < input.size() && input[position] == 'f') {
        ++position;
        f1();
    } 
}

void falseDFA::f1() {
    if (position < input.size() && input[position] == 'a') {
        ++position;
        f2();
    } 
}

void falseDFA::f2() {
    if (position < input.size() && input[position] == 'l') {
        ++position;
        f3();
    } 
}

void falseDFA::f3() {
    if (position < input.size() && input[position] == 's') {
        ++position;
        f4();
    } 
}

void falseDFA::f4() {
    if (position < input.size() && input[position] == 'e') {
        ++position;
        f5();
    } 
}

void falseDFA::f5() {
    longest = position;
}


falseDFA::falseDFA(string input, int start) {
    this->input = input;
    this->start = start;
    position = start;
}

string falseDFA::run() {
    fStart();
    if (longest > -1) {
        return input.substr(start, longest - start);
    } else {
        return "";
    }
}

// ----------------- nullDFA method definitions -----------------
void nullDFA::nStart() {
    if (position < input.size() && input[position] == 'n') {
        ++position;
        n1();
    } 
}

void nullDFA::n1() {
    if (position < input.size() && input[position] == 'u') {
        ++position;
        n2();
    } 
}

void nullDFA::n2() {
    if (position < input.size() && input[position] == 'l') {
        ++position;
        n3();
    } 
}

void nullDFA::n3() {
    if (position < input.size() && input[position] == 'l') {
        ++position;
        n4();
    } 
}

void nullDFA::n4() {
    longest = position;
}


nullDFA::nullDFA(string input, int start) {
    this->input = input;
    this->start = start;
    position = start;
}

string nullDFA::run() {
    nStart();
    if (longest > -1) {
        return input.substr(start, longest - start);
    } else {
        return "";
    }
}

//  ----------------- whitespaceDFA method definitions -----------------
void whitespaceDFA::wsStart() {
    longest = position;
    if (position < input.size() && (input[position] == ' ' || input[position] == '\n' || input[position] == '\r' || input[position] == '\t')) {
        ++position;
        wsStart();
    }
}

whitespaceDFA::whitespaceDFA(string input, int start) {
    this->input = input;
    this->start = start;
    position = start;
}

string whitespaceDFA::run() {
    wsStart();
    if (longest > -1) {
        return input.substr(start, longest - start);
    } else {
        return "";
    }
}

// ----------------- stringDFA method definitions -----------------
void stringDFA::strStart() {
    if (position < input.size() && input[position] == '"') {
        ++position;
        chars();
    }
}

void stringDFA::chars() {
    if (position < input.size() && (int(input[position]) >= 32 && int(input[position]) <= 126) && int(input[position]) != 34 && int(input[position]) != 92) {
        ++position;
        chars();
    } else if (position < input.size() && input[position] == '\\') {
        ++position;
        esc();
    } else if (position < input.size() && input[position] == '"') {
        ++position;
        strEnd();
    }
}

void stringDFA::esc() {
    if (position < input.size() && (input[position] == '"' || input[position] == '\\' || input[position] == '/' || input[position] == 'b' || input[position] == 'f' || input[position] == 'n' || input[position] == 'r' || input[position] == 't')) {
        ++position;
        chars();
    }
}

void stringDFA::strEnd() {
    longest = position;
}


stringDFA::stringDFA(string input, int start) {
    this->input = input;
    this->start = start;
    position = start;
}

string stringDFA::run() {
    strStart();
    if (longest > -1) {
        return input.substr(start, longest - start);
    } else {
        return "";
    }
}

// ----------------- longstringDFA method definitions -----------------
void longstringDFA::longStart() {
    if (position + 2 < input.size() && input.substr(position, 3) == "\"\"\"") {
        position += 3;
        chars();
    }
}

void longstringDFA::chars() {
    if (position < input.size() && (((int(input[position]) >= 32 && int(input[position]) <= 126) && int(input[position]) != 34 && int(input[position]) != 92))) {
        ++position;
        chars();
    } else if (position < input.size() && input[position] == '\\') {
        ++position;
        esc();
    } else if (position < input.size() && input[position] == '"') {
        ++position;
        quote1();
    }
}

void longstringDFA::quote1() {
    if (position < input.size() && (((int(input[position]) >= 32 && int(input[position]) <= 126) && int(input[position]) != 34 && int(input[position]) != 92))) {
        ++position;
        chars();
    } else if (position < input.size() && input[position] == '\\') {
        ++position;
        esc();
    } else if (position < input.size() && input[position] == '"') {
        ++position;
        quote2();
    }
}

void longstringDFA::quote2() {
    if (position < input.size() && (((int(input[position]) >= 32 && int(input[position]) <= 126) && int(input[position]) != 34 && int(input[position]) != 92))) {
        ++position;
        chars();
    } else if (position < input.size() && input[position] == '\\') {
        ++position;
        esc();
    } else if (position < input.size() && input[position] == '"') {
        ++position;
        longEnd();
    }
}

void longstringDFA::esc() {
    if (position < input.size() && (input[position] == '\\' || input[position] == '/' || input[position] == 'b' || input[position] == 'f' || input[position] == 'n' || input[position] == 'r' || input[position] == 't' || input[position] == '"')) {
        ++position;
        chars();
    }
}

void longstringDFA::longEnd() {
    longest = position;
}


longstringDFA::longstringDFA(string input, int start) {
    this->input = input;
    this->start = start;
    position = start;
}

string longstringDFA::run() {
    longStart();
    if (longest > -1) {
        // cout << longest - start << endl;
        return input.substr(start, longest - start);
    } else {
        return "";
    }
}

// ----------------- numberDFA method definitions -----------------

void numberDFA::numStart() {
    if (position < input.size() && input[position] == '0') {
        ++position;
        zero();
    } else if (position < input.size() && input[position] == '-') {
        ++position;
        minus();
    } else if (position< input.size() && (int(input[position] - '0') >= 1 && int(input[position] - '0') <= 9)) {
        ++position;
        ints();
    }
}

void numberDFA::zero() {
    longest = position;
    if (position < input.size() && input[position] == '.') {
        ++position;
        dec();
    } else if (position < input.size() && (input[position] == 'e' || input[position] == 'E')) {
        ++position;
        e();
    }
}

void numberDFA::minus() {
    if (position< input.size() && (int(input[position] - '0') >= 1 && int(input[position] - '0') <= 9)) {
        ++position;
        ints();
    }
}

void numberDFA::ints() {
    longest = position;
    if (position< input.size() && (int(input[position] - '0') >= 1 && int(input[position] - '0') <= 9)) {
        ++position;
        ints();
    } else if (position < input.size() && input[position] == '.') {
        ++position;
        dec();
    } else if (position < input.size() && (input[position] == 'e' || input[position] == 'E')) {
        ++position;
        e();
    }
}

void numberDFA::dec() {
    if (position< input.size() && (int(input[position] - '0') >= 0 && int(input[position] - '0') <= 9)) {
        ++position;
        floats();
    }
}

void numberDFA::floats() {
    longest = position;
    if (position< input.size() && (int(input[position] - '0') >= 0 && int(input[position] - '0') <= 9)) {
        ++position;
        floats();
    } else if (position < input.size() && (input[position] == 'e' || input[position] == 'E')) {
        ++position;
        e();
    }
}

void numberDFA::e() {
    if (position < input.size() && (input[position] == '+' || input[position] == '-')) {
        ++position;
        plusMinus();
    } else if (position< input.size() && (int(input[position] - '0') >= 0 && int(input[position] - '0') <= 9)) {
        ++position;
        floats();
    }
}

void numberDFA::plusMinus() {
    if (position< input.size() && (int(input[position] - '0') >= 0 && int(input[position] - '0') <= 9)) {
        ++position;
        floats();
    }
}

void numberDFA::exp() {
    longest = position;
    if (position< input.size() && (int(input[position] - '0') >= 0 && int(input[position] - '0') <= 9)) {
        ++position;
        floats();
    }
}

numberDFA::numberDFA(string input, int start) {
    this->input = input;
    this->start = start;
    position = start;
}

string numberDFA::run() {
    numStart();
    if (longest > -1) {
        return input.substr(start, longest - start);
    } else {
        return "";
    }
}


//  ----------------- unknownDFA method definitions -----------------
void unknownDFA::unknown() {
    if (position < input.size() && input[position]) {
        ++position;
        unknownEnd();
    }
}

void unknownDFA::unknownEnd() {
    longest = position;
}

unknownDFA::unknownDFA(string input, int start) {
    this->input = input;
    this->start = start;
    position = start;
}

string unknownDFA::run() {
    unknown();
    if (longest > -1) {
        return input.substr(start, longest - start);
    } else {
        return "";
    }
}
