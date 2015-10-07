#include <iostream>
#include "term.h"
#include "triangleTerm.h"
#include "strings.h"

bool Term::enableTypes[TermTypeCount] = { };
bool Term::fuzzificationTypes[TermTypeCount] = { };
bool Term::defuzzificationTypes[TermTypeCount] = { };

Term::Term(std::string name, TermType type, bool isIn)
{
    this->name = name;
    enableTypes[type] = true;
    if (isIn == true)
    {
        fuzzificationTypes[type] = true;
    }
    else
    {
        defuzzificationTypes[type] = true;
    }
}

void Term::setVariableName(std::string variableName)
{
    this->variableName = variableName;
}

std::string Term::getMaxJName() const
{
    return variableName + name;
}

std::string Term::getName() const
{
    return name;
}

std::string Term::getDegreeOfMembershipName() const
{
    return getMaxJName() + std::string("DegreeOfMembership");
}

void Term::createFuzzyfication(std::ofstream& file)
{
    file << "        DFEVar " << getDegreeOfMembershipName() << " = ";
}

void Term::debugPrint()
{
    std::cout << "Variable Name: " << variableName << " Name: " << name;
}

void Term::writeTypeDefsToFile(std::ofstream& file)
{
    if (enableTypes[TRIANGLE] == true)
    {
        TriangleTerm::writeTypeDefsToFile(file);
    }
    
    file << Strings::getDefuzzificationStructString() << std::endl;
}

void Term::writeHelperFunctionsToFile(std::ofstream& file)
{
    if (enableTypes[TRIANGLE] == true)
    {
        TriangleTerm::writeDataStructureCreationMethodeToFile(file);
    }
    if (fuzzificationTypes[TRIANGLE] == true)
    {
        TriangleTerm::writeFuzzificationMethodeToFile(file);
    }
    if (defuzzificationTypes[TRIANGLE] == true)
    {
        TriangleTerm::writeDefuzzificationMethodeToFile(file);
    }
}
