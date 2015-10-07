#include "outputVariable.h"

OutputVariable::OutputVariable(std::string name) : Variable(name)
{
}


void OutputVariable::createFuzzySets(std::ofstream& file)
{
    file << "        // ------ Output Variable - Define Fuzzy Sets - " << name << " ------" << std::endl;
    Variable::createFuzzySets(file);
}

void OutputVariable::createDeclaration(std::ofstream& file)
{
    for (std::list<Term*>::iterator it = termList.begin(); it != termList.end(); it++)
    {
        file << "        DFEVar " << (*it)->getDegreeOfMembershipName() << ";" << std::endl;
    }
}

void OutputVariable::createDefuzzification(std::ofstream& file)
{
    for (std::list<Term*>::iterator it = termList.begin(); it != termList.end(); it++)
    {
        file << "        DFEStruct " << (*it)->getMaxJName() << "DefuzzificationStruct = " << (*it)->getDefuzzification() << std::endl;
    }
    file << std::endl;

    // Calculate weighted Sum
    file << "        DFEVar " << name << "Sum = " << std::endl;
    for (std::list<Term*>::iterator it = termList.begin(); it != termList.end(); it++)
    {
        if (it != termList.begin())
        {
            file << " +" << std::endl;
        }
        file << "                " << (*it)->getMaxJName() << "DefuzzificationStruct.get(\"Area\").pack().cast(type) *" << std::endl;
        file << "                " << (*it)->getMaxJName() << "DefuzzificationStruct.get(\"Centroid\").pack().cast(type)";
    }
    file << ";" << std::endl;

    file << "        DFEVar " << name << "Area = " << std::endl;
    for (std::list<Term*>::iterator it = termList.begin(); it != termList.end(); it++)
    {
        if (it != termList.begin())
        {
            file << " +" << std::endl;
        }
        file << "                " << (*it)->getMaxJName() << "DefuzzificationStruct.get(\"Area\").pack().cast(type)";
    }
    file << ";" << std::endl;

    file << "        DFEVar " << name << " = " << name << "Sum / " << name << "Area;" << std::endl << std::endl;
}

void OutputVariable::createOutputStream(std::ofstream& file)
{
    file << "        io.output(\"" << name << "\", " << name << ", type);" << std::endl;
}
