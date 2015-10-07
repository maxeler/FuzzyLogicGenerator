#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <list>
#include "term.h"

class Variable {
    protected:
        /// @brief Name of the variable
        std::string name; 
        /// @brief Lower bound of the range of the variable
        float rangeLow; 
        /// @brief Upper bound of the range of the variable
        float rangeHigh; 

        /// @brief List used to save all terms connected to the variable
        std::list<Term*> termList; 

    public:
        /**
         * @brief constructor
         * @param name Name of the variable to create
         */
        Variable(std::string name);
        /// @brief Deconstructor
        virtual ~Variable(); 
        /**
         * @brief Mehtode used to set the range of the variable
         * @param rangeLow Lower bound of the range of the variable
         * @param rangeHigh Upper bound of the range of the variable
         */
        void setRange(double rangeLow, double rangeHigh);
        /**
         * @brief Function to access the lower bound of the range of the variable
         * @return Lower bound of the range of the variable
         */
        float getRangeLow();
        /**
         * @brief Function to access the upper bound of the range of the variable
         * @return Upper bound of the range of the variable
         */
        float getRangeHigh();
        /**
         * @brief Function used to add a Term to the variable
         * @param term Pointer to the term
         */
        void addTerm(Term *term);
        /**
         * @brief Function used to get the name of the variable
         * @return Name of the variable
         */
        std::string getName() const;
        /**
         * @brief Function used to get the term to a given name
         * @param name Name of the term
         * @return Pointer to the term or NULL if not found
         */
        Term* getTermToName(std::string name);
        /**
         * @brief Function used to generate all fuzzy sets needed
         * @param file File to write to
         */
        virtual void createFuzzySets(std::ofstream& file);

        /// @brief Function providing some debug information regarding the correct parsing of the description
        virtual void debugPrint(); 

    private:
        /// @brief Forbidden standard constructor
        Variable(); 
};

#endif
