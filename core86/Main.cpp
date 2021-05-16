/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Main.cpp

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cassert>
#include <clocale>
#include "inc/StringsHolder.h"
#include "inc/List.h"
#include "inc/Files.h"
#include "inc/Parse.h"
#include "inc/AstDump.h"
#include "inc/Generate86.h"
#include "inc/WriteAsm86.h"
#include "inc/Translate86.h"

char const* getSourceFromMemory(char const* fileName)
{
    char* tran = nullptr;
    int fileSize = 0, nStrings = 0;
    tran = (char*)translateFileIntoRam(
        fileName,
        &fileSize,
        &nStrings);
    if (tran == nullptr)
        errorMessage("не найден файл \"%s\"\n", fileName);

    return tran;
}


struct CmdParameters
{
    char const *outputFile = nullptr;
    char const *outputAsmFile = nullptr;
    char const* inputFile = nullptr;
    bool toDumpLex = false, 
         toDumpAst = false,
         convolute = false,
         getSource = false,
         debug     = false;

    static CmdParameters getCmdParameters(int nCmd, char const** cmd)
    {
        CmdParameters parameters;
        for (int i = 1; i != nCmd; i++)
        {
            if (!strcmp("-o", cmd[i]))
            {
                i++;
                if (i == nCmd) break;

                parameters.outputFile = cmd[i];
                continue;
            }

            if (!strcmp("-ast", cmd[i]))
            {
                parameters.toDumpAst = true;
                continue;
            }

            if (!strcmp("-g", cmd[i]))
            {
                parameters.debug = true;
                continue;
            }

            if (!strcmp("-lexer", cmd[i]))
            {
                parameters.toDumpLex = true;
                continue;
            }

            if (!strcmp("-con", cmd[i]))
            {
                parameters.convolute = true;
                continue;
            }

            if (!strcmp("-s", cmd[i]))
            {
                parameters.getSource = true;
                continue;
            }

            if(cmd[i][0] == '-')
            {
                warningMessage("нераспознанный флаг \"%s\"\n", cmd[i]);
                continue;
            }

            parameters.inputFile = cmd[i];
        }

        if (parameters.outputAsmFile == nullptr && parameters.inputFile)
        {
            auto length = strlen(parameters.inputFile);
            auto outputFile = (char*)calloc(length + 1, 1);
            strcpy(outputFile, parameters.inputFile);
            outputFile[length - 3] = 'a';
            outputFile[length - 2] = 's';
            outputFile[length - 1] = 'm';
            parameters.outputAsmFile = outputFile;
        }

        if (parameters.outputFile == nullptr && parameters.inputFile)
        {
            auto length = strlen(parameters.inputFile);
            auto outputFile = (char *)calloc(length - 3, 1);
            strncpy(outputFile, parameters.inputFile, length - 4);
            parameters.outputFile = outputFile;
        }

        return parameters;
    }
};



int main(int nCmd, char const** cmd)
{
    auto parameters = CmdParameters::getCmdParameters(nCmd, cmd);

    if (parameters.inputFile == nullptr)
    {
        errorMessage("не указан исходный файл\n");
        
        return -1;
    }

    auto source = getSourceFromMemory(parameters.inputFile);

    if(source == nullptr)
        return -1;
    
    Parse parser;
    auto ast = parser.getParsed(source, parameters.toDumpLex);
    parser.deleteParser();

    if(parameters.convolute)
        constConvolution(ast.AST);

    if (!ast.error)
    {
        if(parameters.toDumpAst)
        {
            astDump(ast.AST);
            return 0;
        }
    }
    else
        return (int)ast.error;

    Generator generator;
    auto flow = generator.compile(ast.AST, ast.holder, parameters.debug);

    if(parameters.getSource)
    {
        auto asmGenError = AssemblerGenerator::writeToAsmFile(parameters.outputAsmFile, flow);
            if(asmGenError != AssemblerGenerator::WriteAsmError::NO_ERROR)
                ;
        
        return 0;
    }

    Translator translator;
    translator.translate(parameters.outputFile, flow.instructions, ast.holder);
}

