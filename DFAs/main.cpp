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

string runString(const string& input, int start) {
    stringDFA dfa(input, start);
    return dfa.run();
}

string runLongstring(const string& input, int start) {
    longstringDFA dfa(input, start);
    return dfa.run();
}

string runNumber(const string& input, int start) {
    numberDFA dfa(input, start);
    return dfa.run();
}

string runUnknown(const string& input, int start) {
    unknownDFA dfa(input, start);
    return dfa.run();
}

string runLCurly(const string& input, int start) {
    lcurlyDFA dfa(input, start);
    return dfa.run();
}

string runRCurly(const string& input, int start) {
    rcurlyDFA dfa(input, start);
    return dfa.run();
}

string runLBracket(const string& input, int start) {
    lbracketDFA dfa(input, start);
    return dfa.run();
}

string runRBracket(const string& input, int start) {
    rbracketDFA dfa(input, start);
    return dfa.run();
}

string runColon(const string& input, int start) {
    colonDFA dfa(input, start);
    return dfa.run();
}

string runComma(const string& input, int start) {
    commaDFA dfa(input, start);
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
    {"STRING", runString},
    {"STRING", runLongstring},
    {"NUMBER", runNumber},
    {"LCURLY", runLCurly},
    {"RCURLY", runRCurly},
    {"LSQUARE", runLBracket},
    {"RSQUARE", runRBracket},
    {"COLON", runColon},
    {"COMMA", runComma},
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
    lex(R"( { } [ ] : , true false "h\"i" null true """long \n\rstring\"""" 123 0 123.01 0.1 0e12 0.01E123 123E+123 589e-0 unknown)");
    
    return 0;
}