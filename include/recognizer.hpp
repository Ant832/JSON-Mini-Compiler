#ifndef RECOGNIZER_PP
#define RECOGNIZER_PP

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Parser {
    const vector<string>& tokenVec;
    int position = 0;

    void read(const string expected) {
        if (tokenVec[position] == expected) {
            ++position;
            return;
        }

        throw std::runtime_error("Parsing got " + tokenVec[position] + ", expected " + expected);
    }

    bool object() {
        if (tokenVec[position] == "RCURLY") {
            if (position == tokenVec.size() - 1) {
                return true;
            }
            return false;
        }
        read("STRING");
        read("COLON");
        value();
        objectCont();
        
        if (position == tokenVec.size() - 1) {
            return true;
        }
        return false;
    }

    void objectCont() {
        if (tokenVec[position] == "COMMA") {
            read("COMMA");
            read("STRING");
            read("COLON");
            value();
            objectCont();
        } else if (tokenVec[position] == "RCURLY") {
            return;
        }
    }

    void value() {
        if (tokenVec[position] == "LCURLY") {
            read("LCURLY");
            object();
            read("RCURLY");
        } else if (tokenVec[position] == "STRING") {
            string_();
        } else if (tokenVec[position] == "LSQUARE") {
            read("LSQUARE");
            array();
            read("RSQUARE");
        } else if (tokenVec[position] == "TRUE") {
            read("TRUE");
        } else if (tokenVec[position] == "FALSE") {
            read("FALSE");
        } else if (tokenVec[position] == "NULL") {
            read("NULL");
        } else if (tokenVec[position] == "NUMBER") {
            number();
        }
    }

    void string_() {
        read("STRING");
    }

    void number() {
        read("NUMBER");
    }

    void array() {
        if (tokenVec[position] == "]") {
            return;
        }
        value();
        arrayCont();
    }

    void arrayCont() {
        if (tokenVec[position] == "COMMA") {
            read("COMMA");
            value();
            arrayCont();
        } else if (tokenVec[position] == "RSQUARE") {
            return;
        }
    }

public:
    Parser(const vector<string>& tokenVec) : tokenVec(tokenVec) {}
    
    bool JSON() {
        read("LCURLY");
        if (object()) {
            read("RCURLY");
            return true;
        }
        return false;
    }

};


#endif