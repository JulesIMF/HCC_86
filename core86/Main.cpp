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
    Frontend:
        HCC

    Backend:
        x86 (JulesIMF, SystemV)

**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cassert>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include "inc/ErrorMessage.h"

struct CmdParameters
{
    char const *outputFile = nullptr;
    char const *outputAsmFile = nullptr;
    char const* inputFile = nullptr;
    bool toDumpLex = false, 
         toDumpAst = false,
         convolute = false,
         getSource = false,
         debug     = false,
         intDebug  = false;

    static void printHelp()
    {
        printf(
            "./hcc [flags] <source> [flags]\n"
            "-o <filename>\tspecifies output biniary file name\n"
            "-ast\t\tgenerates AST tree image\n"
            "-con\t\tconvolutes constants\n"
            "-lexer\t\tprints lexer dump\n"
            "-s\t\tproduces intel-syntax asm file (without std library source)\n"
            "-g\t\tinserts trap interruption (int 3) before the entry\n"
            "-help\t\toutputs this message\n"
        );
    }

    static CmdParameters getCmdParameters(int nCmd, char const** cmd)
    {
        CmdParameters parameters;
        for (int i = 1; i != nCmd; i++)
        {
            if (!strcmp("-o", cmd[i]))
            {
                i++;
                if (i == nCmd) 
                {
                    warningMessage("ожидается имя файла после \"-o\"");
                    break;
                }

                parameters.outputFile = cmd[i];
                continue;
            }

            if (!strcmp("-debug", cmd[i]))
            {
                setDebug();
                continue;
            }

            if (!strcmp("-ast", cmd[i]))
            {
                parameters.toDumpAst = true;
                continue;
            }

            if (!strcmp("-help", cmd[i]))
            {
                printHelp();
                exit(0);
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

            if (!strcmp("-con", cmd[i]))
            {
                setDebug();
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
        return 1;
    }
    
    char buffer[1024] = {};

    snprintf(buffer, sizeof(buffer) - 1, "./bin/hccfronthcc %s %s", parameters.inputFile, "tree");
    if (system(buffer))
        return 0;

    snprintf(buffer, sizeof(buffer) - 1, "./bin/hccmiddle %s %s %s", "tree", "tree", parameters.toDumpAst ? "-ast" : "");
    if (system(buffer))
        return 0;
    if(!parameters.getSource)
        snprintf(buffer, sizeof(buffer) - 1, "./bin/hccback86 %s %s", "tree", parameters.outputFile);
    else
        snprintf(buffer, sizeof(buffer) - 1, "./bin/hccback86 %s %s -s", "tree", parameters.outputAsmFile);
        
    if (system(buffer))
        return 0;

    system("rm tree");
}