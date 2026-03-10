## AST
Each nonterminal will have its own JSON type class (value, object, and array) which will have an accept method that takes a visitor object as its parameter. The visitor will have methods to visit each JSON type.

```
class JSONNode {
    virtual void accept(JSONVisitor&) = 0;

};

class JSONValue : public JSONNode {

};

class JSONObject : public JSONNode {

};

class JSONArray : public JSONNode {

};

class JSONVisitor {
    virtual void visit(JSONValue&) = 0;
    virtual void visit(JSONObject&) = 0;
    virtual void visit(JSONArray&) = 0;
};
```

The nodes will store the children or terminals with an object node being the root node of the AST.
```
    {object}
        |
 string : value
            |
        {object} | [array] | string | number | 'true' | 'false' | 'null'
        ...
```

Children stored in nodes will be unique_ptrs, each child lives under their parent node. 

## Modifying the Parser
When reading tokens, instead of only recognizing the tokens, the parser should create a node of the correct type and save any children if we're in an object or array type. Then each node will be structured into a tree and the root node may be save and visited later.