/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Line.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#ifndef JULESIMF_LINE_INCLUDED
#define JULESIMF_LINE_INCLUDED
/**
 * Структура, хранящая указатель на строку и ее предподсчитанный размер.
 */
typedef struct string_view_
{
	char* string;
	int nSyllables;
	int size;
} Line;
#endif // !JULESIMF_LINE_INCLUDED