#ifndef RULE_H
#define RULE_H

#include <list>
#include "term.h"

/// @brief enum containg all possible operators in evaluation rules
enum Operator {AND, OR, EQUAL};

class EvaluationRule
{
    private:
        /// @brief List (stack) of all operands
        std::list<Term*> operandList; 
        /// @brief List (stack) of all operators
        std::list<Operator> operatorList; 
        /// @brief ID of the rule (used for debugging and comments)
        const int ID; 
        /// @brief Original description (used for debugging)
        const std::string originalText; 

        /// @brief ID pool
        static int number; 

    public:
        /**
         * @brief Constructor
         * @param originalText Original text from the description
         */
        EvaluationRule(std::string originalText);
        /**
         * @brief pushes an operand onto the operand list
         * @param operand The operand to push
         */
        void pushOperandList(Term* operand);
        /**
         * @brief pushes an operator onto the operator list
         * @param op The operator to push
         */
        void pushOperatorList(Operator op);
        /**
         * @brief generates the MaxJ code to evaluate the rule and writes it to a file
         * @param file The file to write to
         */
        void createRuleEvaluation(std::ofstream& file);

        /// @brief function to provide some debug information regarding the description parsing
        void debugPrint(); 

    private:
        /// forbidden standard constructor
        EvaluationRule(); 
        /**
         * @brief Little helper function to create int to string conversion
         * @param Value value to convert
         * @return String containing the value
         */
        std::string intToString(int value);
        /**
         * @brief Function using the lists to process all operators and to divide the rule into little parts that can be processed easily.
         * @param isAnd Flag indicating if ANDs or ORs should be evaluated
         * @param tmpVarCount Count to create distinct variable names used to store iterim results in the rule evaluation
         * @param operandStringList List of the operands converted to strings (name of the variable used in the MaxJ source code)
         * @param file File to write to
         */
        void handleORAndAND(bool isAnd, int& tmpVarCount, std::list<std::string>& operandStringList, std::ofstream& file);
};

#endif
