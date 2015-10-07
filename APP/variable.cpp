#include <iostream>
#include "variable.h"

Variable::Variable(std::string name)
{
    this->name = name;
}

Variable::~Variable()
{
    for (std::list<Term*>::iterator it = termList.begin(); it != termList.end(); it++)
    {
        delete *it;
    }
}

void Variable::setRange(double rangeLow, double rangeHigh)
{
    this->rangeLow = rangeLow;
    this->rangeHigh = rangeHigh;
}

float Variable::getRangeLow()
{
    return rangeLow;
}

float Variable::getRangeHigh()
{
    return rangeHigh;
}

void Variable::addTerm(Term* term)
{
    term->setVariableName(name);
    termList.push_back(term);
}

std::string Variable::getName() const
{
    return name;
}

Term* Variable::getTermToName(std::string name)
{
    for (std::list<Term*>::iterator it = termList.begin(); it != termList.end(); it++)
    {
        if ((*it)->getName().compare(name) == 0)
        {
            return *it;
        }
    }
    return NULL;
}

void Variable::createFuzzySets(std::ofstream& file)
{
    for (std::list<Term*>::iterator it = termList.begin(); it != termList.end(); it++)
    {
        (*it)->createFuzzySet(file);
    }
    file << std::endl;
}

void Variable::debugPrint()
{
    std::cout << "Name: " << name << " Range: " << rangeLow << " - " << rangeHigh << std::endl;
    for (std::list<Term*>::iterator it = termList.begin(); it != termList.end(); it++)
    {
        (*it)->debugPrint();
    }
}
