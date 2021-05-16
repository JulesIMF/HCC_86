/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    ErrorMessage.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#ifndef JULESIMF_ERRORMESSAGE
#define JULESIMF_ERRORMESSAGE

int errorMessage(char const* format, ...);

int warningMessage(char const* format, ...);

void printfMagenta(char const* format, ...);

#endif // !JULESIMF_ERRORMESSAGE
