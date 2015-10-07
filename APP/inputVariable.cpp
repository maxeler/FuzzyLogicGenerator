#include "inputVariable.h"

InputVariable::InputVariable(std::string name) : Variable(name)
{
}

void InputVariable::createFuzzySets(std::ofstream& file)
{
    file << "        // ------ Input Variable - Define Fuzzy Sets - " << name << " ------" << std::endl;
    Variable::createFuzzySets(file);
}

void InputVariable::createInputStream(std::ofstream& file)
{
    file << "        DFEVar " << name << " = io.input(\"" << name << "\", type);" << std::endl;
}

void InputVariable::createFuzzyfication(std::ofstream& file)
{
    for (std::list<Term*>::iterator it = termList.begin(); it != termList.end(); it++)
    {
        (*it)->createFuzzyfication(file);
    }
}
