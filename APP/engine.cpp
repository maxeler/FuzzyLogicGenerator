#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "engine.h"
#include "triangleTerm.h"
#include "strings.h"

enum ParseStateEnum {Input, Output, Rule, Invalid};

Engine::Engine(std::string inputFileName, unsigned int baseTicks) throw (std::string) 
{
    this->baseTicks = baseTicks;

    // set parse error message
    std::stringstream parseErrorStream;
    parseErrorStream << "Was not able to parse File." << std::endl << "Please check if syntax is valid" 
        << std::endl << "Abborting ...." << std::endl;
    parseError = parseErrorStream.str();

    // Try to open File
    inputFile = new std::ifstream(inputFileName.c_str(), std::ifstream::in);
    // Check if File was opened succesfull
    if (!*inputFile) 
    {
        std::stringstream error;
        error << "Was not able to open File." << std::endl << "Please check if File exists" 
            << std::endl << "Abborting ...." << std::endl;
        throw error.str();
    }

    // Parse Input
    try 
    {
        parseInput();
    }
    catch (std::string error)
    {
        throw error;
    }
}

Engine::~Engine() 
{
    delete inputFile;

    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        delete *it;
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        delete *it;
    }
    for (std::list<EvaluationRule*>::iterator it = ruleList.begin(); it != ruleList.end(); it++)
    {
        delete *it;
    }
}

void Engine::parseInput() throw (std::string) 
{
    // TODO: Add more error checking (if strings and numbers really exist)
    std::string line;
    std::getline(*inputFile, line);
    ParseStateEnum parseState = Invalid;
    InputVariable* actInputVar = NULL;
    OutputVariable* actOutputVar = NULL;

    while (!inputFile->eof())
    {
        if (line.find("#") == std::string::npos) // No comment
        {
            std::size_t delimiterPos = line.find(":");
            std::string token = line.substr(0, delimiterPos);
            if (token.compare("Engine") == 0)
            {
                std::size_t endPos = line.find(" ", delimiterPos + 2);
                name = line.substr(delimiterPos + 2, endPos - delimiterPos - 2);
                projectName = name;
                name = name + "App";
            }
            else if (token.compare("InputVariable") == 0)
            {
                parseState = Input;
                std::size_t endPos = line.find(" ", delimiterPos + 2);
                actInputVar = addInputVariable(line.substr(delimiterPos + 2, endPos - delimiterPos - 2));
            }
            else if (token.compare("OutputVariable") == 0)
            {
                parseState = Output;
                std::size_t endPos = line.find(" ", delimiterPos + 2);
                actOutputVar = addOutputVariable(line.substr(delimiterPos + 2, endPos - delimiterPos - 2));
            }
            else if (token.compare("RuleBlock") == 0)
            {
                parseState = Rule;
            }
            else if (token.compare("  enabled") == 0)
            {
                switch(parseState) 
                {
                    case Invalid:
                        throw parseError;
                        break;
                    default:
                        std::cout << "Warning: The enabled option is not supported" << std::endl;
                        break;
                }
            }
            else if (token.compare("  range") == 0)
            {
                std::size_t endFirstNumber = line.find(" ", delimiterPos + 2);
                std::size_t endSecondNumber = line.find(" ", endFirstNumber + 1);
                if (line.length() == endFirstNumber) throw parseError;
                switch(parseState) // range: scalar scalar
                {
                    case Input:
                        actInputVar->setRange(strtod(line.substr(delimiterPos + 2, endFirstNumber - delimiterPos - 2).c_str(), NULL),
                        strtod(line.substr(endFirstNumber + 1, endSecondNumber - endFirstNumber - 1).c_str(), NULL));
                        break;
                    case Output:
                        actOutputVar->setRange(strtod(line.substr(delimiterPos + 2, endFirstNumber - delimiterPos - 2).c_str(), NULL),
                        strtod(line.substr(endFirstNumber + 1, endSecondNumber - endFirstNumber - 1).c_str(), NULL));
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  term") == 0)
            {
                switch(parseState) 
                {
                    case Input:
                        try
                        {
                            parseTerm(actInputVar, line.substr(delimiterPos + 2), true);
                        }
                        catch (std::string error)
                        {
                            throw error;
                        }
                        break;
                    case Output:
                        try
                        {
                            parseTerm(actOutputVar, line.substr(delimiterPos + 2), false);
                        }
                        catch (std::string error)
                        {
                            throw error;
                        }
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  accumulation") == 0)
            {
                switch(parseState) 
                {
                    case Output:
                        std::cout << "Warning: The accumulation option is not supported" << std::endl;
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  defuzzifier") == 0)
            {
                switch(parseState) 
                {
                    case Output:
                        std::cout << "Warning: The defuzzifier option is not supported" << std::endl;
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  default") == 0)
            {
                switch(parseState) 
                {
                    case Output:
                        std::cout << "Warning: The default option is not supported" << std::endl;
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  lock-previous") == 0)
            {
                switch(parseState) 
                {
                    case Output:
                        std::cout << "Warning: The lock-previous option is not supported" << std::endl;
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  lock-range") == 0)
            {
                switch(parseState) 
                {
                    case Output:
                        std::cout << "Warning: The lock-range option is not supported" << std::endl;
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  conjunction") == 0)
            {
                switch(parseState) 
                {
                    case Rule:
                        std::cout << "Warning: The conjunction option is not supported" << std::endl;
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  disjunction") == 0)
            {
                switch(parseState) 
                {
                    case Rule:
                        std::cout << "Warning: The disjunction option is not supported" << std::endl;
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  activation") == 0)
            {
                switch(parseState) 
                {
                    case Rule:
                        std::cout << "Warning: The activation option is not supported" << std::endl;
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else if (token.compare("  rule") == 0)
            {
                switch(parseState) 
                {
                    case Rule:
                        try
                        {
                            parseRule(line.substr(delimiterPos + 2));
                        }
                        catch (std::string error)
                        {
                            throw error;
                        }
                        break;
                    default:
                        throw parseError;
                        break;
                }
            }
            else // Not a valid symbol
            {
                throw parseError;
            }
        }
        std::getline(*inputFile, line);
    }
}

InputVariable* Engine::addInputVariable(std::string name)
{
    InputVariable* variable = new InputVariable(name);
    inputVariableList.push_back(variable);
    return variable;
}

OutputVariable* Engine::addOutputVariable(std::string name)
{
    OutputVariable* variable = new OutputVariable(name);
    outputVariableList.push_back(variable);
    return variable;
}

void Engine::addRule(EvaluationRule* rule)
{
    ruleList.push_back(rule);
}

void Engine::parseTerm(Variable *var, std::string line, bool isIn) throw(std::string) // identifier TERM [parameters]
{
    std::size_t identifierEnd = line.find(" ");
    std::size_t termTypeEnd = line.find(' ', identifierEnd + 1);
    if(identifierEnd == line.length() || termTypeEnd == line.length() || identifierEnd == std::string::npos ||
            termTypeEnd == std::string::npos) throw parseError;
    if (line.substr(identifierEnd + 1, termTypeEnd - identifierEnd - 1).compare("Triangle") == 0)
    {
        // 3 floats
        std::size_t startEnd = line.find(" ", termTypeEnd + 1);
        std::size_t peakEnd = line.find(" ", startEnd + 1);
        std::size_t endEnd = line.find(" ", peakEnd + 1);
        if (startEnd == line.length() || peakEnd == line.length() || startEnd == std::string::npos ||
                peakEnd == std::string::npos) throw parseError;
        TriangleTerm* term = new TriangleTerm(line.substr(0, identifierEnd), isIn);
        term->setValues(strtod(line.substr(termTypeEnd + 1, startEnd - termTypeEnd - 1).c_str(), NULL),
            strtod(line.substr(startEnd + 1, peakEnd - startEnd - 1).c_str(), NULL), 
            strtod(line.substr(peakEnd + 1, endEnd - peakEnd - 1).c_str(), NULL));
        var->addTerm(term);
    }
    else
    {
        std::cerr << "Term Type " << line.substr(identifierEnd + 1, termTypeEnd - identifierEnd - 1) << " not supported" << std::endl;
        throw parseError;
    }
}

void Engine::parseRule(std::string line) throw(std::string)
{
    EvaluationRule* rule = new EvaluationRule(line);

    while (line.length() > 0 && line.find_first_not_of(' ') != std::string::npos)
    {
        std::size_t keyWordEnd = line.find(" ");
        if (line.substr(0, keyWordEnd).compare("and") == 0)
        {
            rule->pushOperatorList(AND);
        }
        else if (line.substr(0, keyWordEnd).compare("or") == 0)
        {
            rule->pushOperatorList(OR);
        }
        else if (line.substr(0, keyWordEnd).compare("then") == 0)
        {
            rule->pushOperatorList(EQUAL);
        }
        else if (line.substr(0, keyWordEnd).compare("if") != 0) // No valid keyword
        {
            throw parseError;
        }
        // the rest looks now like : VARIABLENAME is TERM ......
        std::size_t variableNameEnd = line.find(" ", keyWordEnd + 1);
        std::size_t fillWordEnd = line.find(" ", variableNameEnd + 1);
        std::size_t termNameEnd = line.find(" ", fillWordEnd + 1);
        std::string variableName = line.substr(keyWordEnd + 1, variableNameEnd - keyWordEnd - 1);
        std::string termName = line.substr(fillWordEnd + 1, termNameEnd - fillWordEnd - 1);

        // Now find variable and term
        Variable* var = getVariableToName(variableName);
        if (var == NULL) throw parseError;
        Term* term = var->getTermToName(termName);
        if (term == NULL) throw parseError;
        rule->pushOperandList(term);

        if (line == line.substr(termNameEnd + 1))
        {
            line = "";
        }
        else
        {
            line = line.substr(termNameEnd + 1);
        }
    }

    addRule(rule);
}

Variable* Engine::getVariableToName(std::string name)
{
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        if ((*it)->getName().compare(name) == 0)
        {
            return *it;
        }
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        if ((*it)->getName().compare(name) == 0)
        {
            return *it;
        }
    }
    return NULL;
}

void Engine::createKernel() throw(std::string)
{
    std::string kernelName = name + "Kernel";
    // Open maxj file to write to
    std::ofstream kernelFile;
    std::string kernelFileName = kernelName + ".maxj";
    kernelFile.open (kernelFileName.c_str(), std::ofstream::trunc);
    if (!kernelFile) throw("Error opening kernel file");
    std::string packageName = name;
    std::transform(packageName.begin(), packageName.end(), packageName.begin(), ::tolower);
    kernelFile << "package " << packageName << ";"  << std::endl << std::endl;
    kernelFile << Strings::getImportString() << std::endl; // all needed imports
    kernelFile << "public class " << kernelName << " extends Kernel {" << std::endl << std::endl 
               << "    static final DFEType type = dfeFloat(8, 24);" << std::endl << std::endl;
    Term::writeTypeDefsToFile(kernelFile);

    // Create Constructor now
    kernelFile << "    protected " << kernelName << "(KernelParameters parameters, " << name << 
            "EngineParameters engineParameters) {" << std::endl <<
            "        super(parameters);" << std::endl << std::endl;
    // Create Fuzzy Sets (Terms)
    kernelFile << "        // ------ Section: Definition of Fuzzy Sets (Terms) ------" << std::endl;
    createFuzzySets(kernelFile);

    // Create input streams
    kernelFile << "        // ------ Section: Creating Input Streams ------" << std::endl;
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        (*it)->createInputStream(kernelFile);
    }
    kernelFile << std::endl;

    // Now Step 1: Fuzzication
    kernelFile << "        // ------ Step 1: Fuzzyfication ------" << std::endl;
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        (*it)->createFuzzyfication(kernelFile);
    }
    kernelFile << std::endl;
    // Also we add a declaration for every output variable
    kernelFile << "        // Declartion of output variables" << std::endl;
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        (*it)->createDeclaration(kernelFile);
    }
    kernelFile << std::endl;

    // Step 2: Rule Evaluation
    kernelFile << "        // ------ Step 2: Rule Evaluation ------" << std::endl;
    for (std::list<EvaluationRule*>::iterator it = ruleList.begin(); it != ruleList.end(); it++)
    {
        (*it)->createRuleEvaluation(kernelFile);
    }
    kernelFile << std::endl;
    
    // Step 3: Defuzzification
    kernelFile << "        // ------ Step 3: Defuzzification ------" << std::endl;
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        (*it)->createDefuzzification(kernelFile);
    }
    kernelFile << std::endl;

    // Output
    kernelFile << "        // ------ Section: Creating Output Streams ------" << std::endl;
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        (*it)->createOutputStream(kernelFile);
    }
    kernelFile << std::endl << "    }" << std::endl << std::endl;

    // Helper Functions
    Term::writeHelperFunctionsToFile(kernelFile);
    kernelFile << "}";

    kernelFile.close();
}

void Engine::createManager() throw(std::string)
{
    // Open maxj file to write to
    std::ofstream file;
    std::string fileName = name + "Manager.maxj";
    file.open (fileName.c_str(), std::ofstream::trunc);
    if (!file) throw("Error opening manager file");
    std::string packageName = name;
    std::transform(packageName.begin(), packageName.end(), packageName.begin(), ::tolower);
    file << "package " << packageName << ";" << std::endl << std::endl;
    file << Strings::getManagerImportString();
    file << "public final class " << name << "Manager extends CustomManager {" << std::endl << std::endl;
    file << "    private final " << name << "EngineParameters m_params;" << std::endl;
    file << "    private KernelConfiguration m_kernelConfig;" << std::endl << std::endl;
    file << "    public " << name << "Manager(" << name << "EngineParameters params) {" << std::endl;
    file << Strings::getManagerString1();
    file << "        engine_interface.setTicks(\"" << name << "Kernel\", N);" << std::endl << std::endl;
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << "        engine_interface.setStream(\"" << (*it)->getName() << "\", type, N * size);" << std::endl;
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << "        engine_interface.setStream(\"" << (*it)->getName() << "\", type, N * size);" << std::endl;
    }
    file << std::endl << Strings::getManagerString2();
    file << "                " << name << "Kernel.class.getSimpleName(), m_kernelConfig);" << std::endl;
    file << "        KernelBlock kernel = addKernel(new " << name << "Kernel(kernelParams, m_params));" << std::endl << std::endl;
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << "        DFELink fromCPU" << name << " = addStreamFromCPU(\"" << (*it)->getName() << "\");" << std::endl;
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << "        DFELink toCPU" << name << " = addStreamToCPU(\"" << (*it)->getName() << "\");" << std::endl;
    }
    file << std::endl;
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << "        kernel.getInput(\"" << (*it)->getName() << "\") <== fromCPU" << name << ";" << std::endl;
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << "        toCPU" << name << " <== kernel.getOutput(\"" << (*it)->getName() << "\");" << std::endl;
    }
    file << "    }" << std::endl << std::endl;
    file << "    public static void main(String[] args) {" << std::endl;
    file << "        " << name << "EngineParameters params = new " << name << "EngineParameters(args);" << std::endl;
    file << "        " << name << "Manager manager = new " << name << "Manager(params);" << std::endl << std::endl;
    file << Strings::getManagerString3();

    file.close();
}

void Engine::createEngineParameters() throw(std::string)
{
    // Open maxj file to write to
    std::ofstream file;
    std::string fileName = name + "EngineParameters.maxj";
    file.open (fileName.c_str(), std::ofstream::trunc);
    if (!file) throw("Error opening engine parameters file");
    std::string packageName = name;
    std::transform(packageName.begin(), packageName.end(), packageName.begin(), ::tolower);
    file << "package " << packageName << ";" << std::endl << std::endl;
    file << Strings::getEngineParametersImportString();
    file << "public class " << name << "EngineParameters extends EngineParameters {" << std::endl << std::endl;
    file << Strings::getEngineParametersString1();
    file << "    public " << name << "EngineParameters(String[] argv) {" << std::endl;
    file << Strings::getEngineParametersString2();
    file << "        declareParam(maxFileName, DataType.STRING, \"" << name << "\");" << std::endl;
    file << Strings::getEngineParametersString3();
    
    file.close();
}

void Engine::createCPUCode() throw(std::string)
{
    estimateTicks();

    // Open file to write to
    std::ofstream file;
    std::string fileName = name + "CpuCode.c";
    file.open (fileName.c_str(), std::ofstream::trunc);
    if (!file) throw("Error opening fld file");

    file << Strings::getCPUIncludes();
    // Function to read fld file
    file << "void readFile(int size";
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << ", float* input" << (*it)->getName();
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << ", float* output" << (*it)->getName();
    }
    file << ") {" << std::endl;
    file << "    FILE * file;" << std::endl;
    file << "    char buffer[1000];" << std::endl;
    file << "    int i;" << std::endl << std::endl;
    file << "    file = fopen(\"" << name << ".fld\", \"r\");" << std::endl;
    file << "    fscanf(file, \"";
    for (unsigned int i = 0; i < inputVariableList.size() + outputVariableList.size(); i++)
    {
        file << "\%s ";
    }
    file << "\"";
    for (unsigned int i = 0; i < inputVariableList.size() + outputVariableList.size(); i++)
    {
        file << ", buffer";
    }
    file << ");" << std::endl;
    file << "    for (i = 0; i < size; i++) {" << std::endl;
    file << "        fscanf(file, \"";
    for (unsigned int i = 0; i < inputVariableList.size() + outputVariableList.size(); i++)
    {
        if (i != 0) file << " ";
        file << "\%f";
    }
    file << "\"";
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << ", &(input" << (*it)->getName() << ")[i]";
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << ", &(output" << (*it)->getName() << ")[i]";
    }
    file << ");" << std::endl;
    file << "    }" << std::endl;
    file << "}" << std::endl << std::endl;

    // Function to write to fld file
    file << "void writeFile(int size";
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << ", float* input" << (*it)->getName();
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << ", float* output" << (*it)->getName();
    }
    file << ") {" << std::endl;
    file << "    FILE * file;" << std::endl;
    file << "    int i;" << std::endl << std::endl;
    file << "    file = fopen(\"" << name << ".fld\", \"w\");" << std::endl;
    file << "    fprintf(file, \"";
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        if (it != inputVariableList.begin()) file << " ";
        file << (*it)->getName();
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << " " << (*it)->getName();
    }
    file << "\\n\");" << std::endl;
    file << "    for (i = 0; i < size; i++) {" << std::endl;
    file << "        fprintf(file, \"";
    for (unsigned int i = 0; i < inputVariableList.size() + outputVariableList.size(); i++)
    {
        if (i != 0) file << " ";
        file << "\%f";
    }
    file << "\\n\"";
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << ", input" << (*it)->getName() << "[i]";
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << ", output" << (*it)->getName() << "[i]";
    }
    file << ");" << std::endl << "    }" << std::endl << "}" << std::endl << std::endl;

    // main function
    file << "int main(void)" << std::endl << "{" << std::endl;
    file << "    const int size = " << ticks << ";" << std::endl;
    file << "    const int sizeBytes = size * sizeof(float);" << std::endl;
    
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << "    float *input" << (*it)->getName() << " = malloc(sizeBytes);" << std::endl;
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << "    float *output" << (*it)->getName() << " = malloc(sizeBytes);" << std::endl;
    }

    file << std::endl << "    readFile(size";
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << ", input" << (*it)->getName();
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << ", output" << (*it)->getName();
    }
    file << ");" << std::endl << std::endl;
    file << "    printf(\"Running on DFE.\\n\");" << std::endl;
    file << "    " << name << "(size";
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << ", input" << (*it)->getName();
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << ", output" << (*it)->getName();
    }
    file << ");" << std::endl << std::endl;

    file << std::endl << "    writeFile(size";
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << ", input" << (*it)->getName();
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << ", output" << (*it)->getName();
    }
    file << ");" << std::endl << std::endl;

    file << "    return 0;" << std::endl << "}";

    file.close();
}

void Engine::createTestData() throw(std::string)
{
    estimateTicks();

    // Open file to write to
    std::ofstream file;
    std::string fileName = name + ".fld";
    file.open (fileName.c_str(), std::ofstream::trunc);
    if (!file) throw("Error opening fld file");
    
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        file << (*it)->getName() << " ";
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        file << (*it)->getName() << " ";
    }
    file << std::endl;
    int *ticksArray = new int[inputVariableList.size()];
    for (unsigned int i = 0; i < inputVariableList.size(); i++)
    {
        ticksArray[i] = 0;
    }
    for (unsigned int i = 0; i < ticks; i++)
    {
        for (unsigned int number = 0; number < inputVariableList.size(); number++)
        {
            if (i % (int)pow(baseTicks, number) == 0)
            {
                ticksArray[number]++;
                for (unsigned int j = 0; j < number; j++)
                {
                    ticksArray[j] = 1;
                }
            }
        }
        int number = 0;
        for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
        {
            file << std::showpoint << (((*it)->getRangeHigh() - (*it)->getRangeLow()) / baseTicks) * ticksArray[number] << " ";
            number++;
        }
        for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
        {
            file << std::showpoint << 0 << " ";
        }
        file << std::endl;
    }
    delete [] ticksArray;

    file.close();
}

void Engine::createProject()
{
    std::string nameLower = name;
    std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);

    // First try to delete an perhaps existing directory
    std::string executeString = std::string("rm -r ") + projectName + std::string(" >/dev/null 2>&1");
    system(executeString.c_str());

    // Copy the template
    executeString = std::string("cp -r APP/ ") + projectName;
    system(executeString.c_str());

    // First change all file and directory names
    executeString = std::string("mv ") + projectName + std::string("/RunRules/DFE/\\{\\{cookiecutter.stem_name\\}\\}.xml ") +
        projectName + std::string("/RunRules/DFE/") + name + std::string(".xml");
    system(executeString.c_str());
    executeString = std::string("mv ") + projectName + std::string("/RunRules/DFE/\\{\\{cookiecutter.stem_name\\}\\}_Build.xml ") +
        projectName + std::string("/RunRules/DFE/") + name + std::string("_Build.xml");
    system(executeString.c_str());

    executeString = std::string("mv ") + projectName + std::string("/RunRules/Simulation/\\{\\{cookiecutter.stem_name\\}\\}.xml ") +
        projectName + std::string("/RunRules/Simulation/") + name + std::string(".xml");
    system(executeString.c_str());
    executeString = std::string("mv ") + projectName + 
        std::string("/RunRules/Simulation/\\{\\{cookiecutter.stem_name\\}\\}_Build.xml ") +
        projectName + std::string("/RunRules/Simulation/") + name + std::string("_Build.xml");
    system(executeString.c_str());

    executeString = std::string("mv ") + projectName + 
        std::string("/EngineCode/bin/\\{\\{cookiecutter.stem_name\\|lower\\}\\}/\\{\\{cookiecutter.stem_name\\}\\}EngineParameters.class ") + 
        projectName + std::string("/EngineCode/bin/\\{\\{cookiecutter.stem_name\\|lower\\}\\}/") + name + 
        std::string("EngineParameters.class");
    system(executeString.c_str());
    executeString = std::string("mv ") + projectName + 
        std::string("/EngineCode/bin/\\{\\{cookiecutter.stem_name\\|lower\\}\\}/\\{\\{cookiecutter.stem_name\\}\\}Kernel.class ") + 
        projectName + std::string("/EngineCode/bin/\\{\\{cookiecutter.stem_name\\|lower\\}\\}/") + name + std::string("Kernel.class");
    system(executeString.c_str());
    executeString = std::string("mv ") + projectName + 
        std::string("/EngineCode/bin/\\{\\{cookiecutter.stem_name\\|lower\\}\\}/\\{\\{cookiecutter.stem_name\\}\\}Manager.class ") + 
        projectName + std::string("/EngineCode/bin/\\{\\{cookiecutter.stem_name\\|lower\\}\\}/") + name + std::string("Manager.class");
    system(executeString.c_str());
    executeString = std::string("mv ") + projectName + std::string("/EngineCode/bin/\\{\\{cookiecutter.stem_name\\|lower\\}\\} ") +
        projectName + std::string("/EngineCode/bin/") + nameLower;
    system(executeString.c_str());
    executeString = std::string("rm -r ") + projectName + std::string("/EngineCode/src/\\{\\{cookiecutter.stem_name\\|lower\\}\\}");
    system(executeString.c_str());
    executeString = std::string("mkdir ") + projectName + std::string("/EngineCode/src/") + nameLower;
    system(executeString.c_str());
    executeString = std::string("rm ") + projectName + std::string("/CPUCode/{{cookiecutter.cpu_project_name}}CpuCode.c");
    system(executeString.c_str());

    // Copy src code to the correct directory
    executeString = std::string("cp ") + name + std::string("Kernel.maxj ") + projectName + std::string("/EngineCode/src/");
    system(executeString.c_str());
    executeString = std::string("cp ") + name + std::string("Manager.maxj ") + projectName + std::string("/EngineCode/src/");
    system(executeString.c_str());
    executeString = std::string("cp ") + name + std::string("EngineParameters.maxj ") + projectName + std::string("/EngineCode/src/");
    system(executeString.c_str());
    executeString = std::string("cp ") + name + std::string("CpuCode.c ") + projectName + std::string("/CPUCode/");
    system(executeString.c_str());
    executeString = std::string("cp ") + name + std::string(".fld ") + projectName + std::string("/CPUCode/");
    system(executeString.c_str());

    // Change names and so on
    executeString = std::string("find . -type f -exec sed -i 's/SimpleDimmerApp/") + name + std::string("/g' {} \\;");
    system(executeString.c_str());
    executeString = std::string("find . -type f -exec sed -i 's/simpledimmerapp/") + nameLower 
        + std::string("/g' {} \\;");
    system(executeString.c_str());
    executeString = std::string("find . -type f -exec sed -i 's/SimpleDimmer/") + projectName + 
        std::string("/g' {} \\;");
    system(executeString.c_str());
}

void Engine::estimateTicks()
{
    ticks = pow(baseTicks, inputVariableList.size());
}

void Engine::createFuzzySets(std::ofstream& file)
{
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        (*it)->createFuzzySets(file);
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        (*it)->createFuzzySets(file);
    }
}

void Engine::debugPrint()
{
    for (std::list<InputVariable*>::iterator it = inputVariableList.begin(); it != inputVariableList.end(); it++)
    {
        (*it)->debugPrint();
    }
    for (std::list<OutputVariable*>::iterator it = outputVariableList.begin(); it != outputVariableList.end(); it++)
    {
        (*it)->debugPrint();
    }
    for (std::list<EvaluationRule*>::iterator it = ruleList.begin(); it != ruleList.end(); it++)
    {
        (*it)->debugPrint();
    }
}
