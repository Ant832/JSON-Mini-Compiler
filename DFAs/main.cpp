#include <iostream>
#include <string>
#include <vector>
#include "DFA.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using runDFA = string (*)(const string&, int);

string runWhitespace(const string& input, int start) {
    whitespaceDFA dfa(input, start);
    return dfa.run();
}

string runTrue(const string& input, int start) {
    trueDFA dfa(input, start);
    return dfa.run();
}

string runFalse(const string& input, int start) {
    falseDFA dfa(input, start);
    return dfa.run();
}

string runNull(const string& input, int start) {
    nullDFA dfa(input, start);
    return dfa.run();
}

string runUnknown(const string& input, int start) {
    unknownDFA dfa(input, start);
    return dfa.run();
}

struct DFAs {
    const char* token;
    runDFA run;
};

vector<DFAs> allDFAs = {
    {"WHITESPACE", runWhitespace},
    {"TRUE", runTrue},
    {"FALSE", runFalse},
    {"NULL", runNull},
    {"UNKOWN", runUnknown},
};

void lex(string input) {
    vector<string> tokens;
    int i = 0;

    while (i < input.size())  {
        string longestLexeme = "";
        string token;

        for (auto entry: allDFAs) {
            string lexeme = entry.run(input, i);

            if (lexeme.size() > longestLexeme.size()) {
                longestLexeme = lexeme;
                token = entry.token;
            }
        }

        if (longestLexeme.empty()) {
            longestLexeme = input.substr(i, 1);
            token = "UNKNOWN";
        }

        cout << token << ": " << longestLexeme << endl;
        i += longestLexeme.size();
    }
}

int main() {
    lex(" true false null true");
    
    return 0;
}