/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Files.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#pragma once
#include <stdio.h>
#include "Line.h"
/**
 * \brief Загружает файл в RAM и вставляет 0 после него, при этом после 0 есть еще один доступный байт.
 *
 * \param fileName загружаемый файл
 * \param fileSize указатель на переменную, в которую будет записан размер файла
 * \param nStrings указатель на переменную, в которую будет записано количество строк
 * \return указатель на область памяти, в которую загружен файл, 0 в случае ошибки
 */
char* translateFileIntoRam(char const* fileName, int* pFileSize, int* nStrings);


/**
 * \brief Выводит массив строк в файл.
 * \param fileName строка с именем файла ("?" для stdout)
 * \param strings массив строк
 * \param nStrings кличество строк в массиве
 * \param mode режим открытия файла
 * \return 0 в случае успешного исполнения, 1 в случае ошибки открытия файла
 */
int write(char const* fileName, Line* strings, int nStrings, char const* mode);


/**
 * \brief Возвращает размер файла
 * \param file принимаемый файл
 * \return размер файла в байтах.
 */
int getFileSize(FILE* file);


/**
 * \brief Разбивает source на строки в destination.
 * \param source указатель на транслированный файл
 * \param fileSize размер транслированного файла
 * \param destination указатель на массив со строками
 * \param nStrings количество строк
 * \warning source не перекопируется!!
 * \warning массив *stringsLengths перевыделяется!!
 * \return 0 в случае успешного выполнения, 1 если переданы противоречивые аргументы, 2 если есть строка длиннее 100
 */
int separateStrings(void* source, int fileSize, Line* destination, int nStrings);
