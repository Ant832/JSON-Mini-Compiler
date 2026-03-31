#include <map>
#include <algorithm>

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
        value.second->accept(*this);
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
        value.second->accept(*this);
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

// JSON Validator Visitors
void HasTypeValidator::visit(JSONValue& node) {
    switch (node.type) {
        case JSONValue::Type::String:
            break;
        case JSONValue::Type::Number:
            break;
        case JSONValue::Type::False:
            break;
        case JSONValue::Type::True:
            break;
        case JSONValue::Type::Null:
            break;
    }
}

void HasTypeValidator::visit(JSONArray& node) {
    for (auto& value : node.array) {
        value.second->accept(*this);
    }
}

void HasTypeValidator::visit(JSONObject& node) {
    bool hasType = false;
    string typeName = "";

    for (auto it = node.pairs.begin(); it != node.pairs.end(); ++it) {
        if (it->first == "\"type\"") {
            hasType = true;

            JSONValue* value = dynamic_cast<JSONValue*>(it->second.get());
            if (!value || value->type != JSONValue::Type::String) {
                throw std::runtime_error("object type must be a string");
            }
            typeName = value->str;
        }
        it->second->accept(*this);
    }
    if (!hasType) {
        throw std::runtime_error("Bad object, no type");
    }
}

string StructureValidator::getType(JSONNode* node) {
    string property;
    JSONValue* val = dynamic_cast<JSONValue*>(node);
    JSONArray* arr = dynamic_cast<JSONArray*>(node);
    JSONObject* obj = dynamic_cast<JSONObject*>(node);
    if (val) {
        if (val->type == JSONValue::Type::String) {
            return "string";
        } else if (val->type == JSONValue::Type::Number) {
            return "number";
        } else if (val->type == JSONValue::Type::False) {
            return "bool";
        } else if (val->type == JSONValue::Type::True) {
            return "bool";
        } else if (val->type == JSONValue::Type::Null) {
            return "null";
        }
    } else if (arr) {
        return "array";
    } else if (obj) {
        return "object";
    }
    return "";
}

string StructureValidator::typeToString(JSONValue::Type type) {
    if (type == JSONValue::Type::String) {
        return "string";
    } else if (type == JSONValue::Type::Number) {
        return "number";
    } else if (type == JSONValue::Type::True) {
        return "true";
    } else if (type == JSONValue::Type::False) {
        return "false";
    } else if (type == JSONValue::Type::Null) {
        return "null";
    }
    return "";
}

string StructureValidator::getTypeName(JSONObject* obj) {
    string typeName;
    for (auto it2 = obj->pairs.begin(); it2 != obj->pairs.end(); ++it2) {
        if (it2->first == "\"type\"") {
            JSONValue* value = dynamic_cast<JSONValue*>(it2->second.get());
            typeName = value->str;
        }
    }
    return typeName;
}

void StructureValidator::visit(JSONValue& node) {
    switch (node.type) {
        case JSONValue::Type::String:
            break;
        case JSONValue::Type::Number:
            break;
        case JSONValue::Type::False:
            break;
        case JSONValue::Type::True:
            break;
        case JSONValue::Type::Null:
            break;
    }
}
void StructureValidator::visit(JSONArray& node) {
    for (auto it = node.array.begin(); it != node.array.end(); ++it) {
        JSONArray* arr = dynamic_cast<JSONArray*>(it->second.get());
        JSONObject* obj = dynamic_cast<JSONObject*>(it->second.get());
        if (obj && arrays.find(it->first) == arrays.end()) {
            it->second->accept(*this);
            string typeName = getTypeName(obj);
            arrays[it->first] = typeName;
            continue;
        } else if (obj) {
            it->second->accept(*this);
            string typeName = getTypeName(obj);
            if (arrays[it->first] != typeName) {
                throw std::runtime_error("array types must be " + arrays[it->first] + ", got: " + typeName);
            }
            continue;
        } else if (arr && arrays.find(it->first) == arrays.end()) {
            JSONValue* value = dynamic_cast<JSONValue*>(arr->array[0].second.get());
            arrays[it->first] = typeToString(value->type);
            continue;
        } else if (arr) {
            string expected = arrays[it->first];
            JSONValue* value = dynamic_cast<JSONValue*>(arr->array[0].second.get());
            if (typeToString(value->type) != expected) {
                throw std::runtime_error("array types must be " + expected + ", got: " + typeToString(value->type));
            }
        } else if (arrays.find(it->first) == arrays.end()) {
            JSONValue* value = dynamic_cast<JSONValue*>(it->second.get());
            arrays[it->first] = typeToString(value->type);
        } else {
            string expected = arrays[it->first];
            JSONValue* value = dynamic_cast<JSONValue*>(it->second.get());
            if (typeToString(value->type) != expected) {
                throw std::runtime_error("array types must be " + expected + ", got: " + typeToString(value->type));
            }
        }
        it->second->accept(*this);
    }
}

void StructureValidator::visit(JSONObject& node) {
    string typeName = "";

    for (auto it = node.pairs.begin(); it != node.pairs.end(); ++it) {
        if (it->first == "\"type\"") {
            JSONValue* value = dynamic_cast<JSONValue*>(it->second.get());
            if (!value || value->type != JSONValue::Type::String) {
                throw std::runtime_error("object type must be a string");
            }
            typeName = value->str;

            if (structures.find(typeName) == structures.end()) {
                vector<pair<string, string>> structure;

                for (auto it2 = node.pairs.begin(); it2 != node.pairs.end(); ++it2) {
                    string property = getType(it2->second.get());
                    structure.push_back(make_pair(it2->first, property));
                }
                structures[typeName] = structure;
            } else {
                vector<pair<string, string>> expected = structures[typeName];

                if (expected.size() != node.pairs.size()) {
                    throw std::runtime_error(typeName + " has incorrect number of properties");
                }

                for (auto it3 = node.pairs.begin(); it3 != node.pairs.end(); ++it3) {
                    auto found = std::find_if(expected.begin(), expected.end(), [&](const pair<string, string>& property) { return property.first == it3->first; });
                    if (found == expected.end()) {
                        throw std::runtime_error("unexpected type: " + it3->first);
                    }
                    string type = getType(it3->second.get());
                    if (found->second != type) {
                        throw std::runtime_error("expected: " + found->second + ", got: " + type);
                    }
                }
            }
        }
        it->second->accept(*this);
    }
}

void Flattener::visit(JSONValue& node) {
    switch (node.type) {
        case JSONValue::Type::String:
            break;
        case JSONValue::Type::Number:
            break;
        case JSONValue::Type::False:
            break;
        case JSONValue::Type::True:
            break;
        case JSONValue::Type::Null:
            break;
    }
}

void Flattener::visit(JSONArray& node) {
    for (auto& value : node.array) {
        value.second->accept(*this);
    }

    vector<pair<string, unique_ptr<JSONNode>>> flat;

    for (auto& element : node.array) {
        JSONArray* childArray = dynamic_cast<JSONArray*>(element.second.get());
        if (!childArray) {
            flat.push_back(make_pair(element.first, move(element.second)));
            continue;
        }

        for (auto& child : childArray->array) {
            flat.push_back(make_pair(child.first, move(child.second)));
        }
    }
    node.array = move(flat);
}

void Flattener::visit(JSONObject& node) {
    for (auto it = node.pairs.begin(); it != node.pairs.end(); ++it) {
        it->second->accept(*this);
    }
}