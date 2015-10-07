#ifndef TERM_H
#define TERM_H

#include <string>
#include <fstream>

/// @brief enum containing all possible (implemented) term types
enum TermType {TRIANGLE, TermTypeCount}; // TermTypeCount must allways be the last Element; no manual value declarations allowed

class Term
{
    protected:
        /// @brief Name of the term
        std::string name; 
        /// @brief Name of the variable the term is belonging to
        std::string variableName; 

    private:
        /// @brief Array to keep track of all used term types
        static bool enableTypes[TermTypeCount]; 
        /// @brief Array to keep track of all term types used as input
        static bool fuzzificationTypes[TermTypeCount]; 
        /// @brief Array to keep track of all term types used as output
        static bool defuzzificationTypes[TermTypeCount]; 

    public:
        /**
         * @brief constructor
         * @param name Name of the term
         * @param type Type of the term
         * @param isIn flag indicating if the term is used with an input or an output variable
         */
        Term(std::string name, TermType type, bool isIn);
        /// @brief destructor
        virtual ~Term(){}; 
        /**
         * @brief Function returning the type of the term
         * @return Type of the term
         */
        virtual TermType getType() = 0;
        /**
         * @brief Function used to set the name of the associated variable
         * @param variableName name of the variable
         */
        void setVariableName(std::string variableName);
        /**
         * @brief Function used to get the name of the term in MaxJ
         * @return name of the term in MaxJ
         */
        std::string getMaxJName() const;
        /**
         * @brief Function used to get the name of the term
         * @return name of the term
         */
        std::string getName() const;
        /**
         * @brief Function to get the name of the variable containing the degree of membership for the term
         * @return name of the variable containing the degree of membership for the term
         */
        std::string getDegreeOfMembershipName() const;
        /**
         * @brief Function used to get the name of the defuzzification function
         * @return name of the defuzzification function
         */
        virtual std::string getDefuzzification() const = 0;
        /**
         * @brief Function used to generate a fuzzy set equaling the term
         * @param file File to write to
         */
        virtual void createFuzzySet(std::ofstream& file) = 0;
        /**
         * @brief Function used to create a the fuzzification for a given term
         * @param file File to write to
         */
        virtual void createFuzzyfication(std::ofstream& file);

        /// @brief Function providing some debug information regarding the correct parsing of the description
        virtual void debugPrint(); 

        /**
         * @brief Function used to write all needed Type definitions to the file
         * @param file File to write to
         */
        static void writeTypeDefsToFile(std::ofstream& file);
        /**
         * @brief Function used to write all needed helper function (like (de)fuzzification) to the file
         * @param file File to write to
         */
        static void writeHelperFunctionsToFile(std::ofstream& file);

    private:
        /// @brief Forbidden standard constructor
        Term(); 
};

#endif
