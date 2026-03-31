#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <utility>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::map;
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
    vector<pair<string, unique_ptr<JSONNode>>> array;
    void accept(JSONVisitor& visitor) override;
};

class JSONPrinter : public JSONVisitor {
public:
    void visit(JSONValue& node) override;
    void visit(JSONArray& node) override;
    void visit(JSONObject& node) override;
};


class HasTypeValidator : public JSONVisitor {
public:
    void visit(JSONValue& node) override;
    void visit(JSONArray& node) override;
    void visit(JSONObject& node) override;
};

class StructureValidator : public JSONVisitor {
    map<string, vector<pair<string, string>>> structures;
    map<string, string> arrays;

    string typeToString(JSONValue::Type);
    string getType(JSONNode*);
    string getTypeName(JSONObject*);
public:
    void visit(JSONValue& node) override;
    void visit(JSONArray& node) override;
    void visit(JSONObject& node) override;
};

class JSONPrettyPrinter : public JSONVisitor {
    bool start = true;
    int depth = -1;
    int objects = 0;
public:
    void printIndent();
    void visit(JSONValue& node) override;
    void visit(JSONArray& node) override;
    void visit(JSONObject& node) override;
};

#endif