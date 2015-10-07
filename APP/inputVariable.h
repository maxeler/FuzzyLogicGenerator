#ifndef INPUTVARIABLE_H
#define INPUTVARIABLE_H

#include "variable.h"

class InputVariable : public Variable
{
    public:
        /**
         * @brief Constructor
         * @param name Name of the variable
         */
        InputVariable(std::string name);
        /** 
         * @brief Methode creating the fuzzy set definitions needed by the input variable
         * @param file File to write the definitions to
         */
        virtual void createFuzzySets(std::ofstream& file);
        /**
         * @brief Methode creating the input streams in the Kernel code
         * @param file File to write to
         */
        void createInputStream(std::ofstream& file);
        /**
         * @brief Methode creating the call to the correct fuzzification function for every term of the input variable.
         * @param file File to write to
         */
        void createFuzzyfication(std::ofstream& file);

    private:
        /// @brief Forbidden standard constructor
        InputVariable(); 
};

#endif
