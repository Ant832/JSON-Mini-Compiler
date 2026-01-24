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

//  ----------------- unknownDFA method definitions -----------------
void unknownDFA::unknown() {
    longest = position;
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
