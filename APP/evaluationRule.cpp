#include <iostream>
#include <list>
#include <sstream>
#include "evaluationRule.h"

std::string EvaluationRule::intToString(int value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

int EvaluationRule::number = 0;

EvaluationRule::EvaluationRule(std::string originalText) : ID(number++), originalText(originalText)
{
}

void EvaluationRule::pushOperandList(Term* operand)
{
    operandList.push_back(operand);
}

void EvaluationRule::pushOperatorList(Operator op)
{
    operatorList.push_back(op);
}

void EvaluationRule::createRuleEvaluation(std::ofstream& file)
{
    int tmpVarCount = 0;
    file << "        // Rule: " << originalText << std::endl;
    // Translate the Terms into Strings
    std::list<std::string> operandStringList;
    for (std::list<Term*>::iterator it = operandList.begin(); it != operandList.end(); it++)
    {
        operandStringList.push_back((*it)->getDegreeOfMembershipName());
    }

    // First we work on every AND before the EQUAL
    handleORAndAND(true, tmpVarCount, operandStringList, file);
    
    // Now evaluate every OR before the EQUAL
    handleORAndAND(false, tmpVarCount, operandStringList, file);

    // EQUAL and every AND after EQUAL
    // The value of the first operand has to be assigned to every other operand
    std::list<std::string>::iterator firstOperand = operandStringList.begin();
    for (std::list<std::string>::reverse_iterator it = operandStringList.rbegin(); it != operandStringList.rend() &&
        *it != *firstOperand; it++)
    {
        file << "        " << *it << " = " << *firstOperand << ";" << std::endl;
    }
}

void EvaluationRule::handleORAndAND(bool isAnd, int& tmpVarCount, std::list<std::string>& operandStringList, std::ofstream& file)
{
    Operator compareOperator;
    std::string compareString;
    if (isAnd == true)
    {
        compareOperator = AND;
        compareString = " < ";
    }
    else
    {
        compareOperator = OR;
        compareString = " > ";
    }
    bool found = true;
    while (found)
    {
        found = false;
        int i = 0;
        for (std::list<Operator>::iterator it = operatorList.begin(); it != operatorList.end(); it++)
        {
            if (*it == compareOperator)
            {
                found = true;
                std::list<std::string>::iterator itOperand = operandStringList.begin();
                advance(itOperand, i);
                std::string tmpVarName = std::string("rule") + intToString(ID) + std::string("TmpVar") + intToString(tmpVarCount++);
                // Create TmpVar and calculate minimum
                file << "        DFEVar " << tmpVarName << " = " << *itOperand++;
                file << compareString << *itOperand--;
                file << " ? " << *itOperand++;
                file << " : " << *itOperand << ";" << std::endl;
                // Clear up Stack
                itOperand = operandStringList.erase(itOperand);
                itOperand--;
                itOperand = operandStringList.erase(itOperand);
                operandStringList.insert(itOperand, tmpVarName);
                operatorList.erase(it);
                break;
            }
            else if (*it == EQUAL)
            {
                break; // End of search area
            }
            i++;
        }
    }
}

void EvaluationRule::debugPrint()
{
    std::cout << "ID: " << ID << " Orig Rule: " << originalText << std::endl << '\t';
    for (std::list<Term*>::iterator it = operandList.begin(); it != operandList.end(); it++)
    {
        std::cout << " Operand: " << (*it)->getMaxJName();
    }
    std::cout << std::endl << '\t';
    for (std::list<Operator>::iterator it = operatorList.begin(); it != operatorList.end(); it++)
    {
        switch(*it)
        {
            case AND:
                std::cout << " Operator: AND ";
                break;
            case OR:
                std::cout << " Operator: OR ";
                break;
            case EQUAL:
                std::cout << " Operator: EQUAL ";
                break;
        }
    }
    std::cout << std::endl;
}
