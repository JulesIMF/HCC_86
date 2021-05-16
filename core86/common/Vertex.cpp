/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Vertex.cpp

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/
#include <cstdlib>
#include "../inc/Vertex.h"

using namespace Node;

Vertex* Vertex::newVertex(Type type, size_t row, size_t column, Vertex* left, Vertex* right)
{
    auto vertex = (Vertex*)calloc(1, sizeof(Vertex));
    vertex->type   = type;
    vertex->row    = row;
    vertex->column = column;
    vertex->left   = left;
    vertex->right  = right;
    return vertex;
}

void Vertex::deleteVertex(Vertex* vertex)
{
    free(vertex);
}