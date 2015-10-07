#ifndef TRIANGLETERM_H
#define TRIANGLETERM_H

#include "term.h"

class TriangleTerm : public Term
{
    private:
        /// @brief Start of the triangle
        float start; 
        /// @brief Peak of the triangle
        float peak; 
        /// @brief End of the triangle
        float end; 

    public:
        /**
         * @brief constructor
         * @param name Name of the term
         * @param isIn Flag indicating if the term is associated with an input or an output variable
         */
        TriangleTerm(std::string name, bool isIn);
        /**
         * @brief Function returning the type of the term
         * @return Type of the term
         */
        virtual TermType getType();
        /**
         * @brief Function used to set all values needed to describe the triangle term
         * @param start Start of the triangle
         * @param peak Peak of the triangle
         * @param end End of the triangle
         */
        void setValues(double start, double peak, double end);
        /// @brief Function providing some debug information regarding the correct parsing of the description
        virtual void debugPrint(); 
        /**
         * @brief Function used to generate the fuzzy set equaling the term
         * @param file File to write to
         */
        virtual void createFuzzySet(std::ofstream& file);
        /**
         * @brief Function used to create a the fuzzification for a given term
         * @param file File to write to
         */
        virtual void createFuzzyfication(std::ofstream& file);
        /**
         * @brief Function used to get the name of the defuzzification function
         * @return name of the defuzzification function
         */
        virtual std::string getDefuzzification() const;

        /**
         * @brief Function used to write all needed Type definitions to the file
         * @param file File to write to
         */
        static void writeTypeDefsToFile(std::ofstream& file);
        /**
         * @brief Function to create a method used to gernerate triangle fuzzy sets
         * @param file File to write to
         */
        static void writeDataStructureCreationMethodeToFile(std::ofstream& file);
        /**
         * @brief Funtion to create a methode used for fuzzfication of triangle fuzzy sets
         * @param file File to write to
         */
        static void writeFuzzificationMethodeToFile(std::ofstream& file);
        /**
         * @brief Funtion to create a methode used for defuzzification of triangle fuzzy sets
         * @param file File to write to
         */
        static void writeDefuzzificationMethodeToFile(std::ofstream& file);

    private:
        /// @brief Forbidden standard constructor
        TriangleTerm(); 
};

#endif
