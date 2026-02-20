#include <iostream>
#include <string>
#include "DFA.hpp"

using std::cout;
using std::endl;
using std::string;

// ----------------- longstringDFA method definitions -----------------
void longstringDFA::longStart() {
    charCheck(input, position, '\"', *this, &longstringDFA::start1);
}

void longstringDFA::start1() {
    charCheck(input, position, '\"', *this, &longstringDFA::start2);
}

void longstringDFA::start2() {
    charCheck(input, position, '\"', *this, &longstringDFA::chars);
}

void longstringDFA::chars() {
    if (position < input.size() && (((int(input[position]) >= 32 && int(input[position]) <= 126) && int(input[position]) != 34 && int(input[position]) != 92))) {
        ++position;
        chars();
    }
    charCheck(input, position, '\\', *this, &longstringDFA::esc);
    charCheck(input, position, '"', *this, &longstringDFA::quote1);
}

void longstringDFA::quote1() {
    if (position < input.size() && (((int(input[position]) >= 32 && int(input[position]) <= 126) && int(input[position]) != 34 && int(input[position]) != 92))) {
        ++position;
        chars();
    }
    charCheck(input, position, '\\', *this, &longstringDFA::esc);
    charCheck(input, position, '"', *this, &longstringDFA::quote2);
}

void longstringDFA::quote2() {
    if (position < input.size() && (((int(input[position]) >= 32 && int(input[position]) <= 126) && int(input[position]) != 34 && int(input[position]) != 92))) {
        ++position;
        chars();
    }
    charCheck(input, position, '\\', *this, &longstringDFA::esc);
    charCheck(input, position, '"', *this, &longstringDFA::longEnd);
}

void longstringDFA::esc() {
    charCheckAny(input, position, "\"\\/bnfrt", *this, &longstringDFA::chars);
}

void longstringDFA::longEnd() {
    longest = position;
}

// ----------------- numberDFA method definitions -----------------

void numberDFA::numStart() {
    if (position< input.size() && (int(input[position] - '0') >= 1 && int(input[position] - '0') <= 9)) {
        ++position;
        ints();
    }
    charCheck(input, position, '0', *this, &numberDFA::zero);
    charCheck(input, position, '-', *this, &numberDFA::minus);
}

void numberDFA::zero() {
    longest = position;
    charCheck(input, position, '.', *this, &numberDFA::dec);
    charCheck(input, position, 'e', *this, &numberDFA::e);
    charCheck(input, position, 'E', *this, &numberDFA::e);
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
    }
    charCheck(input, position, '.', *this, &numberDFA::dec);
    charCheck(input, position, 'e', *this, &numberDFA::e);
    charCheck(input, position, 'E', *this, &numberDFA::e);
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
