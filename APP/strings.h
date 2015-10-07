#ifndef STRINGS_H
#define STRINGS_H

#include <string>

/**
 * @brief this class is used to save different strings which will than be coppied into the created source files
 */
class Strings
{
    private:
        static const char* importString;
        static const char* defuzzificationStructString;
        static const char* triangleTypeString;
        static const char* triangleDataStructureCreationMethodeString;
        static const char* triangleFuzzificationMethodeString;
        static const char* triangleDefuzzificationMethodeString;

        static const char* managerImportString;
        static const char* managerString1;
        static const char* managerString2;
        static const char* managerString3;

        static const char* engineParametersImportString;
        static const char* engineParametersString1;
        static const char* engineParametersString2;
        static const char* engineParametersString3;

        static const char* cpuIncludeString;

    public:
        static std::string getImportString() {return std::string(importString);}
        static std::string getDefuzzificationStructString() {return std::string(defuzzificationStructString);}
        static std::string getTriangleTypeString() {return std::string(triangleTypeString);}
        static std::string getTriangleDataStructureCreationMethodeString() 
            {return std::string(triangleDataStructureCreationMethodeString);}
        static std::string getTriangleFuzzificationMethodeString() {return std::string(triangleFuzzificationMethodeString);}
        static std::string getTriangleDefuzzificationMethodeString() {return std::string(triangleDefuzzificationMethodeString);}

        static std::string getManagerImportString() {return std::string(managerImportString);}
        static std::string getManagerString1() {return std::string(managerString1);}
        static std::string getManagerString2() {return std::string(managerString2);}
        static std::string getManagerString3() {return std::string(managerString3);}

        static std::string getEngineParametersImportString() {return std::string(engineParametersImportString);}
        static std::string getEngineParametersString1() {return std::string(engineParametersString1);}
        static std::string getEngineParametersString2() {return std::string(engineParametersString2);}
        static std::string getEngineParametersString3() {return std::string(engineParametersString3);}
        
        static std::string getCPUIncludes() {return std::string(cpuIncludeString);}

    private:
        Strings();
};

#endif
