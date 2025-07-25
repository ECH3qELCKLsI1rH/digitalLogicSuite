#include "truthTable_with_expression_simplifier.h"

#include <algorithm>  // For sort(), unique() and find() operations
#include <iostream>   // For input/output operations
#include <map>        // For storing variable values (char to bool mapping)
#include <stack>      // For infix to postfix conversion and evaluation
#include <string>     // For string operations
#include <vector>     // For dynamic arrays
using namespace std;

// Constructor initializes empty expression
TruthTableGenerator::TruthTableGenerator() : expression("") {}

// Removes duplicate variables from the variables vector
void TruthTableGenerator::removeDuplicateVariables() {
    sort(variables.begin(), variables.end());                                      // Sort variables alphabetically
    variables.erase(unique(variables.begin(), variables.end()), variables.end());  // Remove duplicates
}

// Checks if a character is a valid logical operator
bool TruthTableGenerator::isOperator(char c) { return c == '&' || c == '|' || c == '!' || c == '^'; }

// Returns precedence of operators for infix to postfix conversion
int TruthTableGenerator::precedence(char op) {
    if (op == '!') return 3;               // Highest precedence for NOT
    if (op == '&' || op == '^') return 2;  // AND has higher precedence than OR
    if (op == '|') return 1;               // OR and XOR have same precedence
    return 0;                              // For other characters
}

// Applies the actual logical operation based on the operator
bool TruthTableGenerator::applyOperation(bool a, bool b, char op) {
    switch (op) {
        case '&':
            return a && b;  // Logical AND
        case '|':
            return a || b;  // Logical OR
        case '^':
            return a != b;  // Logical XOR
        case '>':
            return !a || b;  // Implication (a → b)
        case '=':
            return a == b;  // Biconditional (a ↔ b)
        default:
            return false;  // Default case (shouldn't occur)
    }
}

// Converts infix expression to postfix notation (Reverse Polish Notation)
string TruthTableGenerator::infixToPostfix(string infix) {
    stack<char> s;   // Stack to hold operators
    string postfix;  // Resulting postfix expression

    for (char c : infix) {      // Process each character
        if (isalpha(c)) {       // If it's a variable
            postfix += c;       // Add directly to output
        } else if (c == '(') {  // If it's opening parenthesis
            s.push(c);          // Push to stack
        } else if (c == ')') {  // If it's closing parenthesis
            // Pop from stack until matching '(' is found
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();                 // Remove the '(' from stack
        } else if (isOperator(c)) {  // If it's an operator
            // Pop higher or equal precedence operators
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);  // Push current operator
        }
    }

    // Pop any remaining operators
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

// Evaluates the postfix expression using current variable values
bool TruthTableGenerator::evaluatePostfix(string postfix) {
    stack<bool> s;  // Stack to hold operands

    for (char c : postfix) {  // Process each character
        if (isalpha(c)) {     // If variable, push its value
            s.push(varValues[c]);
        } else if (c == '!') {  // Handle NOT operator (unary)
            bool a = s.top();
            s.pop();
            s.push(!a);  // Push negation
        } else {         // Handle binary operators
            bool b = s.top();
            s.pop();
            bool a = s.top();
            s.pop();
            s.push(applyOperation(a, b, c));  // Push result
        }
    }

    return s.top();  // Final result
}

// Converts a number to binary string of given length
string TruthTableGenerator::getBinaryString(int num, int length) {
    string binary;
    for (int i = length - 1; i >= 0; i--) {      // From MSB to LSB
        binary += ((num >> i) & 1) ? '1' : '0';  // Extract each bit
    }
    return binary;
}

// Checks if two binary strings differ by exactly one bit
bool TruthTableGenerator::differsByOneBit(const string& a, const string& b) {
    int diff = 0;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) diff++;    // Count differing bits
        if (diff > 1) return false;  // Early exit if more than 1
    }
    return diff == 1;  // True if exactly one difference
}

// Combines two terms that differ by one bit (replaces differing bit with '-')
string TruthTableGenerator::combineTerms(const string& a, const string& b) {
    string combined;
    for (size_t i = 0; i < a.size(); i++) {
        combined += (a[i] == b[i]) ? a[i] : '-';  // Keep matching bits, else '-'
    }
    return combined;
}

// Converts a term (like "01-") to boolean expression (like "(!a & b)")
string TruthTableGenerator::termToExpression(const string& term) {
    string expr;
    for (size_t i = 0; i < term.size(); i++) {
        if (term[i] == '0')  // If bit is 0, use NOT
            expr += "!" + string(1, variables[i]) + " & ";
        else if (term[i] == '1')  // If bit is 1, use variable directly
            expr += string(1, variables[i]) + " & ";
        // Ignore '-' (don't care)
    }
    if (!expr.empty()) expr = expr.substr(0, expr.size() - 3);  // Remove trailing " & "
    return expr.empty() ? "1" : expr;                           // Return "1" if empty (all don't cares)
}

// Reads boolean expression from user and extracts variables
void TruthTableGenerator::readExpression() {
    cout << "Enter boolean expression (use & for AND, | for OR, ! for NOT, ^ for XOR): ";
    getline(cin, expression);
    variables.clear();
    for (char c : expression) {  // Find all variables
        if (isalpha(c)) {
            variables.push_back(c);
        }
    }
    removeDuplicateVariables();  // Remove duplicates
}

// Generates and displays the truth table
void TruthTableGenerator::generateTruthTable() {
    if (expression.empty()) {  // Check for empty expression
        cout << "No expression entered!" << endl;
        return;
    }

    string postfix = infixToPostfix(expression);  // Convert to postfix
    int varCount = variables.size();              // Number of variables
    int rows = 1 << varCount;                     // 2^varCount rows
    minterms.clear();                             // Clear previous minterms

    // Print table header
    for (char var : variables) cout << var << "\t";
    cout << expression << endl;

    // Generate each row
    for (int i = 0; i < rows; i++) {
        // Set variable values for this row
        for (int j = 0; j < varCount; j++) {
            varValues[variables[j]] = (i >> (varCount - 1 - j)) & 1;  // Extract bits
            cout << (varValues[variables[j]] ? "T" : "F") << "\t";    // Print T/F
        }

        // Evaluate and store result
        bool result = evaluatePostfix(postfix);
        minterms.push_back(result);
        cout << (result ? "T" : "F") << endl;
    }
}

// Simplifies the boolean expression using Quine-McCluskey algorithm
string TruthTableGenerator::simplifyExpression() {
    if (variables.empty()) return "0";  // No variables case
    if (minterms.empty()) return "0";   // No minterms case

    // Check for always true or always false cases
    bool all_true = true, all_false = true;
    for (bool m : minterms) {
        if (!m) all_true = false;
        if (m) all_false = false;
    }
    if (all_true) return "1";
    if (all_false) return "0";

    // Convert minterms to binary strings
    vector<string> binaryMinterms;
    for (size_t i = 0; i < minterms.size(); i++) {
        if (minterms[i]) {
            binaryMinterms.push_back(getBinaryString(i, variables.size()));
        }
    }

    // Prime implicant generation
    vector<string> primeImplicants = binaryMinterms;
    bool changed;
    do {
        changed = false;
        vector<string> used;
        vector<string> newImplicants;

        // Try to combine terms
        for (size_t i = 0; i < primeImplicants.size(); i++) {
            bool combined = false;
            for (size_t j = i + 1; j < primeImplicants.size(); j++) {
                if (differsByOneBit(primeImplicants[i], primeImplicants[j])) {
                    newImplicants.push_back(combineTerms(primeImplicants[i], primeImplicants[j]));
                    // Mark used terms
                    if (find(used.begin(), used.end(), primeImplicants[i]) == used.end()) {
                        used.push_back(primeImplicants[i]);
                    }
                    if (find(used.begin(), used.end(), primeImplicants[j]) == used.end()) {
                        used.push_back(primeImplicants[j]);
                    }
                    combined = true;
                    changed = true;
                }
            }
            // Add unused terms
            if (!combined && find(used.begin(), used.end(), primeImplicants[i]) == used.end()) {
                newImplicants.push_back(primeImplicants[i]);
            }
        }

        primeImplicants = newImplicants;
    } while (changed);

    // Remove duplicate implicants
    sort(primeImplicants.begin(), primeImplicants.end());
    primeImplicants.erase(unique(primeImplicants.begin(), primeImplicants.end()), primeImplicants.end());

    // Convert to boolean expression
    string result;
    for (const string& term : primeImplicants) {
        string expr = termToExpression(term);
        if (!expr.empty()) result += "(" + expr + ") | ";
    }

    // Clean up and return
    if (!result.empty()) result = result.substr(0, result.size() - 3);  // Remove trailing " | "
    return result.empty() ? "0" : result;
}