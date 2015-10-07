#include <iostream>
#include "triangleTerm.h"
#include "strings.h"

TriangleTerm::TriangleTerm(std::string name, bool isIn) : Term(name, TRIANGLE, isIn)
{
}

TermType TriangleTerm::getType()
{
    return TRIANGLE;
}

void TriangleTerm::setValues(double start, double peak, double end)
{
    this->start = start;
    this->peak = peak;
    this->end = end;
}

void TriangleTerm::createFuzzySet(std::ofstream& file)
{
    file << "        DFEVector<DFEVar> " << getMaxJName() << " = createNewTriangleVector(" << std::showpoint << start << ", " << peak << ", " <<
        end << ");" << std::endl;
}

void TriangleTerm::createFuzzyfication(std::ofstream& file)
{
    Term::createFuzzyfication(file);
    file << "getFuzzificationTriangle(" << getMaxJName() << ", " << variableName << ");" << std::endl;
}

std::string TriangleTerm::getDefuzzification() const
{
    return "getDefuzzificationTriangle(" + getMaxJName() + ", " + getDegreeOfMembershipName() + ");";
}

void TriangleTerm::debugPrint()
{
    Term::debugPrint();
    std::cout << " TRIANGLE " << "Start: " << start << " Peak: " << peak << " End: " << end << std::endl;
}

void TriangleTerm::writeTypeDefsToFile(std::ofstream& file)
{
    file << Strings::getTriangleTypeString() << std::endl;
}

void TriangleTerm::writeDataStructureCreationMethodeToFile(std::ofstream& file)
{
    file << Strings::getTriangleDataStructureCreationMethodeString();
}

void TriangleTerm::writeFuzzificationMethodeToFile(std::ofstream& file)
{
    file << Strings::getTriangleFuzzificationMethodeString();
}

void TriangleTerm::writeDefuzzificationMethodeToFile(std::ofstream& file)
{
    file << Strings::getTriangleDefuzzificationMethodeString();
}
