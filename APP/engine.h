#ifndef ENGINE_H
#define ENGINE_H
/*
 * Class representing the whole fuzzy logic evaluation engine.
 * Keeps handles to everything important.
 */

#include <string>
#include <fstream>
#include <list>
#include "inputVariable.h"
#include "outputVariable.h"
#include "evaluationRule.h"

class Engine 
{
    // Attributes
    private:
        /// @brief Handle to the description of the fuzzy logic problem
        std::ifstream *inputFile;
        /// @brief Name of the engine with the string "App" appended. Used to name the kernel for example
        std::string name;
        /// @brief Name of the engine as specified in the description
        std::string projectName;
        /// @brief A string containing a reusable error message used for exeption handling
        std::string parseError; 

        /// @brief List to save all input Variables
        std::list<InputVariable*> inputVariableList;
        /// @brief List to save all outputVariables
        std::list<OutputVariable*> outputVariableList;
        /// @brief List to save all evaluation rules
        std::list<EvaluationRule*> ruleList;

        unsigned int ticks;
        unsigned int baseTicks;

    // Methodes
    public:
        /**
         * @brief Constructor creating an engine class
         *
         * @param inputFileName path to the file containing the description of the fuzzy logic problem.
         * @param baseTicks Number of different input values for each inputVariable in the generated test data.
         */
        Engine(std::string inputFileName, unsigned int baseTicks) throw(std::string);
        /// @brief deconstructor
        ~Engine(); 
        /// @brief Methode to write the kernel source code in MaxJ to a file
        void createKernel() throw(std::string); 
        /// @brief Methode to write the manager source code in MaxJ to a file
        void createManager() throw(std::string); 
        /// @brief Methode to write the engine parameter source code in MaxJ to a file
        void createEngineParameters() throw(std::string); 
        /// @brief Methode to write the CPU source code in c to a file
        void createCPUCode() throw(std::string); 
        /// @brief Methode to generate a .fld file containing auto generated test data
        void createTestData() throw(std::string); 
        /// @brief Methode to copy all generated files into an directory structure usable by MaxIDE. Also generating Makefiles
        void createProject();

        /// @brief Methode to create some debug information regarding the correct parsing of the fuzzy logic problem description
        void debugPrint();

    private:
        void parseInput() throw(std::string); /// @brief Methode to parse the provided fuzzy logic description
        /**
         * @brief Methode to add an input variable to the engine class
         *
         * @param name Name of the input variable
         * @return A pointer to the input variable for further editing
         */
        InputVariable* addInputVariable(std::string name);
        /**
         * @brief Methode to add an output variable to the engine class
         *
         * @param name Name of the output variable
         * @return A pointer to the output variable for further editing
         */
        OutputVariable* addOutputVariable(std::string name);
        /**
         * @brief Methode to add an evalution rule to the engine class
         *
         * @param rule Pointer to the evaluation rule
         */
        void addRule(EvaluationRule* rule);
        /**
         * @brief Methode to parse and add a term to an variable
         *
         * @param var Pointer to the variable
         * @param line Description of the term provided by the input file
         * @param isIn Flag indicating if the variable is an input or an output variable
         */
        void parseTerm(Variable* var, std::string line, bool isIn) throw(std::string);
        /**
         * @brief Mehtode used to parse Rulese
         *
         * @param line Description of the rule provided by the input file
         */
        void parseRule(std::string line) throw(std::string);
        /**
         * @brief Methode to get a pointer to a variable given the name of the variable
         *
         * @param name Name of the variable to look for
         * @return Pointer to the variable or NULL if no variable was found
         */
        Variable* getVariableToName(std::string name);
        /**
         * @brief Methode used to generate MaxJ definitions for all used types of fuzzy sets
         *
         * @param file Handle to the file to write to
         */
        void createFuzzySets(std::ofstream& file);
        void estimateTicks(); /// Calculates how many ticks of the DFE are neccessary to use all generated test data
};
#endif
