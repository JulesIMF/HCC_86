/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    AstDump.h

Abstract:    
    Модуль, генерирующий изображение AST дерева    
Author:
    JulesIMF

Last Edit:
    20.12.2020 2:27

Edit Notes:
    
**********************************************************************/

#include <cstdlib>
#include <cassert>
#include <cstdio>
#include "../../inc/Vertex.h"


void putVertex(FILE* file, Node::Vertex* vertex)
{
    static int visited = 0;
    //printf("visit = %lu\n", visited++);
    using namespace Node;
    
    switch (vertex->type)
    {
    case Type::Id:
        fprintf(file, "v%p[label = \"%lu:%lu\\nId\\n\\\"%s\\\"\", shape = \"record\", style = \"bold\", fontsize = 15]; ",
            vertex, vertex->row, vertex->column, vertex->field.iter.get()); break;

    case Type::Var:
        fprintf(file, "v%p[label = \"%lu:%lu\\nVar\\n\\\"%s\\\"\", shape = \"record\", style = \"bold\", fontsize = 15]; ",
            vertex, vertex->row, vertex->column, vertex->field.fnc.iter.get()); break;

    case Type::Operator:
        fprintf(file, "v%p[label = \"%lu:%lu\\nOperator\\nopType = '%c'\", shape = \"octagon\", style = \"filled, bold\", fillcolor = \"yellow\", fontsize = 15];",
            vertex, vertex->row, vertex->column, vertex->field.opType); break;

    case Type::Statement:
        fprintf(file, "v%p[label = \"%lu:%lu\\nStatement\\nstType = '%c'\", shape = \"diamond\", style = \"filled, bold\", fillcolor = \"darkorchid1\", fontsize = 15];",
            vertex, vertex->row, vertex->column, vertex->field.stType); break;

    case Type::Call:
        fprintf(file, "v%p[label = \"%lu:%lu\\nCall\\nid = \\\"%s\\\", nArgs = %lu\", shape = \"octagon\", style = \"filled, bold\", fillcolor = \"yellow\", fontsize = 15];",
            vertex, vertex->row, vertex->column, vertex->field.fnc.iter.get(), vertex->field.fnc.nArgs); break;

    case Type::Const:
        fprintf(file, "v%p[label = \"%lu:%lu\\nConst\\nval = %lu, %s\", shape = \"record\", style = \"bold\", fontsize = 15];",
            vertex, vertex->row, vertex->column, vertex->field.lit.value, vertex->field.lit.isInt ? "int" : "float"); break;

    case Type::ArgList:
        fprintf(file, "v%p[label = \"%lu:%lu\\nArgList\", shape = \"parallelogram\", fillcolor = \"orange\", style = \"filled, bold\", fontsize = 15];",
            vertex, vertex->row, vertex->column); break;

    case Type::IfElse:
        fprintf(file, "v%p[label = \"%lu:%lu\\nIf-Else\", shape = \"parallelogram\", fillcolor = \"orange\", style = \"filled, bold\", fontsize = 15];",
            vertex, vertex->row, vertex->column); break;

    case Type::StmtLink:
        fprintf(file, "v%p[label = \"%lu:%lu\\nStmtLink\\nnewScope = %s\", shape = \"parallelogram\", fillcolor = \"mediumspringgreen\", style = \"filled, bold\", fontsize = 15];",
            vertex, vertex->row, vertex->column, vertex->field.newScope ? "true" : "false"); break;

    case Type::FuncLink:
        fprintf(file, "v%p[label = \"%lu:%lu\\nFuncLink\", shape = \"parallelogram\", fillcolor = \"orange\", style = \"filled, bold\", fontsize = 15];",
            vertex, vertex->row, vertex->column); break;

    case Type::Main:
        fprintf(file, "v%p[label = \"%lu:%lu\\nMain\", shape = \"parallelogram\", fillcolor = \"forestgreen\", style = \"filled, bold\", fontsize = 15];",
            vertex, vertex->row, vertex->column); break;

    case Type::FuncDecl:
        fprintf(file, "v%p[label = \"%lu:%lu\\nFuncDecl\\nid = \\\"%s\\\", nArgs = %lu\", shape = \"parallelogram\", style = \"filled, bold\", fillcolor = \"forestgreen\", fontsize = 15];",
            vertex, vertex->row, vertex->column, vertex->field.fnc.iter.get(), vertex->field.fnc.nArgs); break;

    case Type::VarType:
        fprintf(file, "v%p[label = \"%lu:%lu\\VarType\\nid = \\\"%s\\\", nElements = %lu\", shape = \"parallelogram\", style = \"filled, bold\", fillcolor = \"forestgreen\", fontsize = 15];",
            vertex, vertex->row, vertex->column, vertex->field.varDecl.iter.get(), vertex->field.varDecl.nElements); break;

    case Type::PgmEnd:
        fprintf(file, "v%p[label = \"%lu:%lu\\nPgmEnd\", shape = \"parallelogram\", fillcolor = \"blue\", style = \"filled, bold\", fontsize = 15];",
            vertex, vertex->row, vertex->column); break;

    default:
        assert(!"Unknown type");
    }
    fprintf(file, "\n");
    if (vertex->left)
    {
        fprintf(file, "v%p->v%p [color = \"red\"]\n", vertex, vertex->left);
        putVertex(file, vertex->left);
    }

    if (vertex->right)
    {
        fprintf(file, "v%p->v%p [color = \"blue\"]\n", vertex, vertex->right);
        putVertex(file, vertex->right);
    }
}


void astDump(Node::Vertex* astTree)
{
    FILE *file = fopen("dbg/astsrc/ast.dot", "w");
    assert(file);
    fprintf(file, "digraph\n{\ndpi = 300;\n");
    putVertex(file, astTree);
    fprintf(file, "}");
    fclose(file);
    system("dot -Tpng dbg/astsrc/ast.dot -o ast.png > /dev/null");

    // Следующий трюк работает только под Шиндовс
    //system("start ast.png");
}
