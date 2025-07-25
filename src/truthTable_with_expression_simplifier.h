#ifndef TRUTH_TABLE_GENERATOR_H
#define TRUTH_TABLE_GENERATOR_H

#include <map>
#include <string>
#include <vector>

class TruthTableGenerator {
   private:
    std::string expression;          // Stores the boolean expression entered by users
    std::vector<char> variables;     // Stores all unique variables in the expression
    std::map<char, bool> varValues;  // Maps variables to their current truth values
    std::vector<bool> minterms;      // Stores the results (minterms) from truth table

    void removeDuplicateVariables();
    bool isOperator(char c);
    int precedence(char op);
    bool applyOperation(bool a, bool b, char op);
    std::string infixToPostfix(std::string infix);
    bool evaluatePostfix(std::string postfix);
    std::string getBinaryString(int num, int length);
    bool differsByOneBit(const std::string& a, const std::string& b);
    std::string combineTerms(const std::string& a, const std::string& b);
    std::string termToExpression(const std::string& term);

   public:
    TruthTableGenerator();
    void readExpression();
    void generateTruthTable();
    std::string simplifyExpression();
};

#endif