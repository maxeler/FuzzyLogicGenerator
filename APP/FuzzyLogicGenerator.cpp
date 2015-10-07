#include <string>
#include <iostream>
#include <cstdlib>
#include "engine.h"

void showUsage() {
    std::cout << "Usage:" << std::endl << "FuzzyLogicGenerator -i <FileName.fll> [-t <ticksPerInVar>]" << std::endl;
}

int main (int argc, char* argv[]) 
{
    // first parse parameters
    std::string inputFile;
    unsigned int baseTicks = 100;
    if(argc == 1) 
    {
        showUsage();
    }
    for (int i = 1; i < argc; i++) 
    {
        std::string parameters = argv[i];
        if (parameters.compare("-i") == 0) 
        {
            if (argc > i + 1) 
            {
                inputFile = std::string(argv[i + 1]);
                i++;
            } 
            else 
            {
                showUsage();
            }
        } 
        else if (parameters.compare("-t") == 0) 
        {
            if (argc > i + 1) 
            {
                baseTicks = atoi(argv[i + 1]);
                i++;
            } 
            else 
            {
                showUsage();
            }
        } 
        else 
        {
            showUsage();
        }
    }

    // Create Engine
    try
    {
        Engine engine(inputFile, baseTicks);
        //engine.debugPrint();
        engine.createKernel();
        engine.createManager();
        engine.createEngineParameters();
        engine.createCPUCode();
        engine.createTestData();
        engine.createProject();
    }
    catch (std::string error) 
    {
        std::cerr << error;
        return -1;
    }
}
