#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::unique_ptr;
using std::make_unique;

class JSONValue;
class JSONObject;
class JSONArray;

class JSONVisitor {
public:
    virtual void visit(JSONValue&) = 0;
    virtual void visit(JSONObject&) = 0;
    virtual void visit(JSONArray&) = 0;
};

class JSONNode {
public:
    virtual void accept(JSONVisitor&) = 0;
};

class JSONValue : public JSONNode {
public:
    enum class Type { String, Number, True, False, Null } type;
    string str;

    JSONValue(Type t, string str) : type(t), str(str) {}
    JSONValue(Type t) : type(t) {}
    void accept(JSONVisitor& visitor) override;
};

class JSONObject : public JSONNode {
public:
    vector<pair<string, unique_ptr<JSONNode>>> pairs;
    void accept(JSONVisitor& visitor) override;
};

class JSONArray : public JSONNode {
public:
    vector<unique_ptr<JSONNode>> array;
    void accept(JSONVisitor& visitor) override;
};

class JSONPrinter : public JSONVisitor {
public:
    void visit(JSONValue& node) override;
    void visit(JSONArray& node) override;
    void visit(JSONObject& node) override;
};

#endif