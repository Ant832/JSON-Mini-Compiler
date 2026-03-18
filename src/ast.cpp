#include "../include/ast.hpp"

void JSONValue::accept(JSONVisitor& visitor) {
    visitor.visit(*this);
}

void JSONObject::accept(JSONVisitor& visitor) {
    visitor.visit(*this);
}

void JSONArray::accept(JSONVisitor& visitor) {
    visitor.visit(*this);
}

void JSONPrinter::visit(JSONValue& node) {
    switch (node.type) {
        case JSONValue::Type::String:
            cout << node.str;
            break;
        case JSONValue::Type::Number:
            cout << node.str;
            break;
        case JSONValue::Type::False:
            cout << "false";
            break;
        case JSONValue::Type::True:
            cout << "true";
            break;
        case JSONValue::Type::Null:
            cout << "null";
            break;
    }
}

void JSONPrinter::visit(JSONArray& node) {
    cout << "[";
    for (auto& value : node.array) {
        value->accept(*this);
        if (value != node.array.back()) {
            cout << ",";
        }
    }
    cout << "]";
}

void JSONPrinter::visit(JSONObject& node) {
    cout << "{";
    for (auto it = node.pairs.begin(); it != node.pairs.end(); ++it) {
        cout << it->first << ":";
        it->second->accept(*this);
        if (next(it) != node.pairs.end()) {
            cout << ",";
        }
    }
    cout << "}";
}

void JSONPrettyPrinter::printIndent() {
    for (int i = 0; i < depth; ++i) {
        cout << "  ";
    }
}

void JSONPrettyPrinter::visit(JSONValue& node) {
    switch (node.type) {
        case JSONValue::Type::String:
            cout << node.str;
            break;
        case JSONValue::Type::Number:
            cout << node.str;
            break;
        case JSONValue::Type::False:
            cout << "false";
            break;
        case JSONValue::Type::True:
            cout << "true";
            break;
        case JSONValue::Type::Null:
            cout << "null";
            break;
    }
}

void JSONPrettyPrinter::visit(JSONArray& node) {
    ++depth;
    cout << endl;
    printIndent();
    cout << "[";
    for (auto& value : node.array) {
        value->accept(*this);
        if (value != node.array.back()) {
            cout << ",\n";
            printIndent();
        }
    }
    cout << endl;
    printIndent();
    cout << "]";
    --depth;
}

void JSONPrettyPrinter::visit(JSONObject& node) {
    ++objects;
    if (!start) {
        cout << endl;
    }
    start = false;
    ++depth;
    printIndent();
    cout << "{";
    for (auto it = node.pairs.begin(); it != node.pairs.end(); ++it) {
        cout << it->first << ": ";
        it->second->accept(*this);
        if (next(it) != node.pairs.end()) {
            cout << ",\n";
            printIndent();
        }
    }
    --objects;
    if (objects == 0) {
        cout << endl;
    }
    cout << "}";
    --depth;
}