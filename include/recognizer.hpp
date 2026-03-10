#ifndef RECOGNIZER_HPP
#define RECOGNIZER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ast.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;

class Parser {
    const vector<string>& tokenVec;
    const vector<string>& valueVec;
    int position = 0;

    void read(const string expected) {
        if (tokenVec[position] == expected) {
            ++position;
            return;
        }

        throw std::runtime_error("Parsing got " + tokenVec[position] + ", expected " + expected);
    }

    unique_ptr<JSONObject> object() {
        unique_ptr<JSONObject> node = make_unique<JSONObject>();
        if (tokenVec[position] == "RCURLY") {
            return node;
        }

        string key = valueVec[position];

        read("STRING");
        read("COLON");
        node->pair[key] = value();
        objectCont(*node);
        
        return node;
    }

    void objectCont(JSONObject& node) {
        if (tokenVec[position] == "COMMA") {
            string key = valueVec[position];

            read("COMMA");
            read("STRING");
            read("COLON");
            node.pair[key] = value();
            objectCont(node);
        } else if (tokenVec[position] == "RCURLY") {
            return;
        }
    }

    unique_ptr<JSONNode> value() {
        if (tokenVec[position] == "LCURLY") {
            read("LCURLY");
            unique_ptr<JSONObject> node = object();
            read("RCURLY");
            return node;
        } else if (tokenVec[position] == "STRING") {
            unique_ptr<JSONValue> node = make_unique<JSONValue>(JSONValue::Type::String, valueVec[position]);
            string_();
            return node;
        } else if (tokenVec[position] == "LSQUARE") {
            read("LSQUARE");
            unique_ptr<JSONArray> node = array();
            cout << "check" << endl;
            read("RSQUARE");
            return node;
        } else if (tokenVec[position] == "TRUE") {
            unique_ptr<JSONValue> node = make_unique<JSONValue>(JSONValue::Type::True);
            read("TRUE");
            return node;
        } else if (tokenVec[position] == "FALSE") {
            unique_ptr<JSONValue> node = make_unique<JSONValue>(JSONValue::Type::False);
            read("FALSE");
            return node;
        } else if (tokenVec[position] == "NULL") {
            unique_ptr<JSONValue> node = make_unique<JSONValue>(JSONValue::Type::Null);
            read("NULL");
            return node;
        } else if (tokenVec[position] == "NUMBER") {
            unique_ptr<JSONValue> node = make_unique<JSONValue>(JSONValue::Type::Number, valueVec[position]);
            number();
            return node;
        }
        throw std::runtime_error("Reached end of value with no token");
    }

    void string_() {
        read("STRING");
    }

    void number() {
        read("NUMBER");
    }

    unique_ptr<JSONArray> array() {
        unique_ptr<JSONArray> node = make_unique<JSONArray>();
        if (tokenVec[position] == "RSQUARE") {
            return node;
        }
        value();
        arrayCont(*node);
        return node;
    }

    void arrayCont(JSONArray& node) {
        if (tokenVec[position] == "COMMA") {
            read("COMMA");
            node.array.push_back(value());
            arrayCont(node);
        } else if (tokenVec[position] == "RSQUARE") {
            return;
        }
    }

public:
    Parser(const vector<string>& tokenVec, const vector<string>& valueVec) : tokenVec(tokenVec), valueVec(valueVec) {}
    
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