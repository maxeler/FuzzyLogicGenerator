#ifndef OUTPUTVARIABLE_H
#define OUTPUTVARIABLE_H

#include "variable.h"

class OutputVariable : public Variable
{
    public:
        /**
         * @brief Constructor
         * @param name Name of the variable
         */
        OutputVariable(std::string name);
        /** 
         * @brief Methode creating the fuzzy set definitions needed by the output variable
         * @param file File to write the definitions to
         */
        virtual void createFuzzySets(std::ofstream& file);
        /**
         * @brief Methode used to create some definitions for every term to the MaxJ file that can be used later
         * @param file File to write to
         */
        void createDeclaration(std::ofstream& file);
        /**
         * @brief Methode to call the correct defuzzification function for every term
         * @param file File to write to
         */
        void createDefuzzification(std::ofstream& file);
        /**
         * @brief Methode to create the output streams
         * @param file File to write to
         */
        void createOutputStream(std::ofstream& file);

    private:
        /// @brief Forbidden standard constructor
        OutputVariable(); 
};

#endif
