/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Generate.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    21.12.2020 14:08

Edit Notes:
    
**********************************************************************/

#ifndef CPP_GENERATE
#define CPP_GENERATE
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "Vertex.h"
#include "VarTable.h"
#include "Lexer.h"


using Node::Vertex;
using Node::Type;
using Node::OperatorType;
using Node::StatementType;

class Generator
{
public:
    struct Function
    {
        int stackFrame;
        int nArgs;
    };

protected:
    VarTable varTable;
    StringsHolder::StringIter* currentFnc;
    int nFncProceeded;
    int currentNArgs;
    
    //Здесь хранятся размеры стекфреймов для функций и количество аргументов

    Table<Function>
             fncTable;
    int shift = 0;
    int shifts[2000];
    CompileError error;
    FILE* file;

    Vertex* errorVertex = nullptr;

    void generate(Vertex* vertex);

//#define DEF(type) void gen ## type(Vertex* vertex);
//
//    DEF(Main);
//    DEF(FuncLink);
//    DEF(FuncDecl);
//    DEF(ArgList);
//    DEF(StmtLink);
//    DEF(Statement);
//
//    DEF(Call);
//    DEF(Ret);
//    DEF(Asgn);
//    DEF(If);
//    DEF(Loop);
//    DEF(Dvar);

    //------------------------------------------------------
    //----------------------STATEMENTS----------------------
    //------------------------------------------------------

    void genCallArgList(Vertex* vertex)
    {
        if (vertex == nullptr)
            return;

        /*
        *   Слева - ArgList
        *   Справа - expression
        */

        genCallArgList(vertex->left);
        if(!error) generate(vertex->right);
    }


    void genCall(Vertex* vertex)
    {
        /*
        *   Слева - argList
        *   Справа - ничего
        */
        fprintf(file, ";calling %s at %d\n", vertex->field.fnc.iter.get(), vertex->row);
        auto fnc = fncTable.find(vertex->field.fnc.iter.get());
        auto stackFrame = 0;
        if (fnc == nullptr)
        {
            if (currentFnc && !strcmp(currentFnc->get(), vertex->field.fnc.iter.get()))
            {
                ;
            }
            else
            {
                error = CompileError::UNDEFINED_FNC;
                errorVertex = vertex;
                return;
            }
        }

        int nArgs = fnc ? fnc->value.nArgs : currentNArgs;

        if (nArgs != vertex->field.fnc.nArgs)
        {
            errorVertex = vertex; error = CompileError::WRONG_NARG;
            return;
        }

        
        genCallArgList(vertex->left);
        fprintf(file, ";end of evaluation - calling %s at %d\n", vertex->field.fnc.iter.get(), vertex->row);
        if (error) return;
        //rdx - rbp

        if (currentFnc && !strcmp(currentFnc->get(), vertex->field.fnc.iter.get()))
            fprintf(file, "mov [%d] rax\n", 2000 + nFncProceeded);

        else
            fprintf(file, "mov %d rax\n", fnc->value.stackFrame);
        fprintf(file, "sub rdx rax\npop rdx\n");

        //перенесем аргументы из стека на стекфрейм
        for (int i = nArgs - 1; i != -1; i--)
        {
            fprintf(file,
                "pop [rdx+%d]\n", i);
        }

        fprintf(file, "call %s\n", vertex->field.fnc.iter.get());

        if (currentFnc && !strcmp(currentFnc->get(), vertex->field.fnc.iter.get()))
            fprintf(file, "mov [%d] rax\n", 2000 + nFncProceeded);

        else
            fprintf(file, "mov %d rax\n", fnc->value.stackFrame);

        fprintf(file, "add rdx rax\npop rdx\n");
    }

    
    void genRet(Vertex* vertex)
    {
        /*
        *   Слева - expr
        *   Справа - ничего
        */

        generate(vertex->left);

        if (error) return;

        fprintf(file,
            "pop rax\n" //Результат
            "pop rbx\n" //Адрес возврата
            "push rax\n" //Свапаем их
            "push rbx\n"
            "ret\n");
    }


    void genIf(Vertex* vertex)
    {
        /*
        *   Слева - условие
        *   Справа - IfElse
        */

        generate(vertex->left); if (error) return;
        fprintf(file,
            "pop rax\n" //expr
            "cmp rax 0\n"
            "je _else_p%u\n", vertex);

        

        //Левый стейтмент
        assert(("Expected IfElse on the right in " __FUNCTION__ && vertex->right));
        varTable.pushNamespace();
        generate(vertex->right->left); if (error) return;
        varTable.popNamespace();
        fprintf(file,
            "jmp _endif_p%u\n"
            "_else_p%u:\n",
            vertex, vertex);
        generate(vertex->right->right); if (error) return;

        fprintf(file, "_endif_p%u:\n", vertex);
    }


    void genLoop(Vertex* vertex)
    {
        /*
        *   Слева - условие
        *   Справа - стейтмент
        */
        fprintf(file,
            "_loop_p%u:\n", vertex);

        generate(vertex->left); if (error) return;
        
        fprintf(file,
            "pop rax\n"
            "cmp rax 0\n"
            "je _break_p%u\n", vertex);

        generate(vertex->right); if (error) return;

        fprintf(file,
            "jmp _loop_p%u\n"
            "_break_p%u:\n",
            vertex, vertex);
    }


    void genAsgn(Vertex* vertex)
    {
        /*
        *   Cлева - идентификатор переменной
        *   Справа - выражение
        */

        assert("Expected Id on the left in getAsgn"  && vertex->left);
        auto var = varTable.get(vertex->left->field.iter);
        if (var.shift == -1)
        {
            errorVertex = vertex; error = CompileError::UNDEFINED_VAR;
            return;
        }
        
        generate(vertex->right); if (error) return;
        fprintf(file,
            "pop [rdx+%d]\n", var.shift);
    }


    void genDvar(Vertex* vertex)
    {
        /*
        *   Слева - имя переменной
        *   Справа - имя типа
        *   Быдлокод по причине не успеваю, нужны таблицы типов!
        */

        assert("Expected Id on the left and right in Dvar"  && vertex->left && vertex->right);

        varTable.insert(vertex->left->field.iter, shift++, !strcmp("Целковый", vertex->right->field.iter.get()));
    }


    //------------------------------------------------------
    //---------------------!!STATEMENTS---------------------
    //------------------------------------------------------
    

    bool genOperator(Vertex* vertex);

    bool genConst(Vertex* vertex)
    {
        fprintf(file, ";const at %d\n", vertex->row);
        if (vertex->field.lit.isInt)
        {
            fprintf(file,
                "push %lld\n", vertex->field.lit.value);
            return true;
        }
        double val = *(double*)(&vertex->field.lit.value);
        fprintf(file,
            "push %lf\n", val);

        return false;

    }

    bool genVarv(Vertex* vertex)
    {
        fprintf(file, ";var %s at %d\n", vertex->field.iter.get(), vertex->row);
        auto var = varTable.get(vertex->field.iter);
        if (var.shift == -1)
        {
            errorVertex = vertex; error = CompileError::UNDEFINED_VAR;
            return false;
        }

        fprintf(file,
            "push [rdx+%d]\n", var.shift);

        return var.isInt;
    }


    bool genExpr(Vertex* vertex)
    {
        switch (vertex->type)
        {
        case Type::Var:
            return genVarv(vertex);

        case Type::Const:
            return genConst(vertex);

        case Type::Operator:
            return genOperator(vertex);

        case Type::Call:
            return genCall(vertex), false;

        default:
            assert(("Expected expr in " __FUNCTION__ && false));
        }

        return false;
    }

    /**
     * 
     * \param vertex
     * \return true если внизу только int, false инчае
     */
    

    //-----------------------------------------------------------------------------------------

    void genMain(Vertex* vertex)
    {
        /*
        *   Генерируем все функции, а потом генерируем точку входа
        */
        generate(vertex->left);

        fprintf(file, ";main\n");

        if (!error)
        {
            fprintf(file, "main:\n");
            generate(vertex->right);
            fprintf(file, "ret\n");
        }
    }


    void genFuncLink(Vertex* vertex)
    {
        /*
        *   Слева FuncLink с функциями, определенными раньше, справа - FuncDecl
        */
        generate(vertex->left);
        if(!error) generate(vertex->right);
    }


    void genFuncDecl(Vertex* vertex)
    {
        /*
        *   Слева argList (ecли есть), в котором мы запихаем аргументы
        *   Справа Statement
        */
        shift = 0;
        varTable.pushNamespace();

        currentFnc = &(vertex->field.fnc.iter);
        currentNArgs = vertex->field.fnc.nArgs;

        generate(vertex->left);
        fprintf(file, ";funcDecl\n%s:\n", vertex->field.fnc.iter.get());
        if (!error) generate(vertex->right); else return;

        fprintf(file,
            "pop rax\n"
            "push 0\n"
            "push rax\n"
            "ret\n");

        varTable.popNamespace();
        Function function { shift, vertex->field.fnc.nArgs };
        fncTable.insert(
            vertex->field.fnc.iter,
            function);
        shifts[nFncProceeded++] = shift;
        shift = 0;
        currentFnc = nullptr;
    }


    void genArgList(Vertex* vertex)
    {
        /*
        *   Слева - ранние аргументы
        *   Справа - идентификатор
        */

        generate(vertex->left);
        assert("Expected Id on the right in genArgList"  && vertex->right->type == Type::Id);
        varTable.insert(vertex->right->field.iter, shift++);
    }


    void genStmtLink(Vertex* vertex)
    {
        if (vertex->field.newScope)
            varTable.pushNamespace();

        generate(vertex->left);
        if (!error) generate(vertex->right); else return;

        if (vertex->field.newScope)
            varTable.popNamespace();
    }


    void genStatement(Vertex* vertex)
    {
        /*
        *   Здесь все зависит от stType
        */

        fprintf(file, ";statement '%c' at %d\n", vertex->field.stType, vertex->row);
        switch (vertex->field.stType)
        {
        case StatementType::Asgn:
            genAsgn(vertex);
            return;

        case StatementType::Cond:
            genIf(vertex);
            return;

        case StatementType::Dvar:
            genDvar(vertex);
            return;

        case StatementType::Loop:
            genLoop(vertex);
            return;

        case StatementType::Ret:
            genRet(vertex);
            return;

        case StatementType::Call:
            vertex->field.fnc.iter = vertex->right->field.iter;
            genCall(vertex);
            fprintf(file, "pop rsp\n");
            return;

        default:
            assert("Expected stType" && false);
        }
    }


public:

    struct CompileInfo
    {
        CompileError error;
        Vertex* errorVertex = nullptr;
    };

    CompileInfo compile(Node::Vertex* ast, StringsHolder* holder, char const* filename = "obj.hcc", char const* asmName = "obj.asm")
    {
        //Подрабатываем конструктором Generator
        varTable.init();
        fncTable.initTable();
        constexpr Function inputFnc      { 0, 0 };
        constexpr Function outputFnc     { 1, 1 };
        constexpr Function pause         { 0, 0 };
        constexpr Function intOutputFnc  { 1, 1 };
        constexpr Function sqrt          { 1, 1 };

        fncTable.insert(holder->insert("КорняЗла" , 8), sqrt);
        fncTable.insert(holder->insert("Пророка"  , 7), outputFnc);
        fncTable.insert(holder->insert("Машиаха"  , 7), intOutputFnc);
        fncTable.insert(holder->insert("Ангелов"  , 7), inputFnc);
        fncTable.insert(holder->insert("Монаха"   , 6), pause);

        error = CompileError::NO_ERROR_;

        //-----------------------------------------------------------------

        file = fopen(asmName, "w");

        fprintf(file,
            "mov 5000 rdx\n"
            "call _init_table\n"
            "call main\n"
            "hlt\n"
            );

        generate(ast);
        if (!error)
        {
            fprintf(file, "_init_table:\n");
            for (int i = 0; i != nFncProceeded; i++)
            {
                fprintf(file, "mov %d [%d]\n",
                    shifts[i], 2000 + i);
            }
            fprintf(file, 
                "ret\n\n"
                "Пророка:\n"
                "push [rdx]\n"
                "out lf\n"
                "pop rsp\n"
                "pop rax\n"
                "push 0\n"
                "push rax\n"
                "ret\n\n"
                "Машиаха:\n"
                "push [rdx]\n"
                "out\n"
                "pop rsp\n"
                "pop rax\n"
                "push 0\n"
                "push rax\n"
                "ret\n\n"
                "Ангелов:\n"
                "in\n"
                "pop rax\n"
                "pop rbx\n"
                "push rax\n"
                "push rbx\n"
                "ret\n\n"
                "КорняЗла:\n"
                "sqrt [rdx]\n"
                "pop rax\n"
                "pop rbx\n"
                "push rax\n"
                "push rbx\n"
                "ret\n\n"
                "Монаха:\n"
                "getch\n"
                "pop rax\n"
                "pop rbx\n"
                "push rax\n"
                "push rbx\n"
                "ret\n\n"

            );
            fclose(file);
            char request[256] = "Jasm ";
            snprintf(request + 5, 256 - 5 - 1 /*sizeof(request) - sizeof("Jasm")*/, "%s", asmName);
            system(request);
        }

        CompileInfo info = { error, errorVertex };
        return info;
    }
};


void Generator::generate(Node::Vertex* vertex)
{
    if (vertex == nullptr) return;
    if (error) return;
#define CASE(TYPE) case Node::Type::TYPE: gen ## TYPE(vertex); return;
    switch (vertex->type)
    {
        CASE(Main);
        CASE(FuncLink);
        CASE(FuncDecl);
        CASE(ArgList);
        CASE(StmtLink);
        CASE(Statement);
    default:
        genExpr(vertex);
        return;
    }
#undef CASE
}


bool Generator::genOperator(Vertex* vertex)
{
    /*
    *   Cлева и справа expressions, даже у унарных
    */

    bool isInt = true;
    isInt &= genExpr(vertex->left);
    isInt &= genExpr(vertex->right);

    fprintf(file, ";operator '%c' at %d\n", vertex->field.opType, vertex->row);

    fprintf(file,
        "pop rbx\n" /*левый операнд*/
        "pop rax\n" /*правый операнд*/);

    /*Можно бы подумать как это сделать красиво,
      но наверное здесь это не очень обязательно*/

    if (isInt)
    {
        switch (vertex->field.opType)
        {
        case OperatorType::Add:
            fprintf(file, "add rax rbx\n");
            return isInt;

        case OperatorType::Sub:
            fprintf(file, "sub rax rbx\n");
            return isInt;

        case OperatorType::Mul:
            fprintf(file, "mul rax rbx\n");
            return isInt;

        case OperatorType::Div:
            fprintf(file, "div rax rbx\n");
            return isInt;

        case OperatorType::Not:
            fprintf(file,
                "cmp rax 0\n"
                "je _nt_zero_p%u\n"
                "push 1.0\n"
                "jmp _nt_one_p%u\n"
                "_nt_zero_p%u:\n"
                "push 0.0\n"
                "_nt_one_p%u:\n",
                vertex, vertex,
                vertex, vertex
            );
            return isInt;

        case OperatorType::Or:
            fprintf(file,
                "cmp rax 0\n"
                "jne _or_one_p%u\n"
                "cmp rbx 0\n"
                "jne _or_one_p%u\n"
                "push 0\n"
                "jmp _or_zero_p%u\n"
                "_or_one_p%u:\n"
                "push 1.0\n"
                "_or_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex, vertex);
            return isInt;

        case OperatorType::And:
            fprintf(file,
                "cmp rax 0\n"
                "je _nd_zero_p%u\n"
                "cmp rbx 0\n"
                "je _nd_zero_p%u\n"
                "push 1.0\n"
                "jmp _nd_one_p%u\n"
                "_nd_zero_p%u:\n"
                "push 0\n"
                "_nd_one_p%u:\n",
                vertex, vertex,
                vertex, vertex, vertex);
            return isInt;

        case OperatorType::Eq:
            fprintf(file,
                "cmp rax rbx\n"
                "je _eq_one_p%u\n"
                "push 0\n"
                "jmp _eq_zero_p%u\n"
                "_eq_one_p%u:\n"
                "push 1.0\n"
                "_eq_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Neq:
            fprintf(file,
                "cmp rax rbx\n"
                "jne _ne_one_p%u\n"
                "push 0\n"
                "jmp _ne_zero_p%u\n"
                "_ne_one_p%u:\n"
                "push 1.0\n"
                "_ne_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Less:
            fprintf(file,
                "cmp rax rbx\n"
                "jl _l_one_p%u\n"
                "push 0\n"
                "jmp _l_zero_p%u\n"
                "_l_one_p%u:\n"
                "push 1.0\n"
                "_l_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Gtr:
            fprintf(file,
                "cmp rax rbx\n"
                "jg _g_one_p%u\n"
                "push 0\n"
                "jmp _g_zero_p%u\n"
                "_g_one_p%u:\n"
                "push 1.0\n"
                "_g_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Leq:
            fprintf(file,
                "cmp rax rbx\n"
                "jle _le_one_p%u\n"
                "push 0\n"
                "jmp _le_zero_p%u\n"
                "_le_one_p%u:\n"
                "push 1.0\n"
                "_le_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Geq:
            fprintf(file,
                "cmp rax rbx\n"
                "jge _ge_one_p%u\n"
                "push 0\n"
                "jmp _ge_zero_p%u\n"
                "_ge_one_p%u:\n"
                "push 1.0\n"
                "_ge_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        default:
            assert("Expected OpType in " __FUNCTION__ && false);
        }
    }
    else
    {
        switch (vertex->field.opType)
        {
        case OperatorType::Add:
            fprintf(file, "fadd rax rbx\n");
            return isInt;

        case OperatorType::Sub:
            fprintf(file, "fsub rax rbx\n");
            return isInt;

        case OperatorType::Mul:
            fprintf(file, "fmul rax rbx\n");
            return isInt;

        case OperatorType::Div:
            fprintf(file, "fdiv rax rbx\n");
            return isInt;

        case OperatorType::Not:
            fprintf(file,
                "fcmp rax 0\n"
                "je _nt_zero_p%u\n"
                "push 1.0\n"
                "jmp _nt_one_p%u\n"
                "_nt_zero_p%u:\n"
                "push 0.0\n"
                "_nt_one_p%u:\n",
                vertex, vertex,
                vertex, vertex
            );
            return isInt;

        case OperatorType::Or:
            fprintf(file,
                "fcmp rax 0\n"
                "jne _or_one_p%u\n"
                "cmp rbx 0\n"
                "jne _or_one_p%u\n"
                "push 0\n"
                "jmp _or_zero_p%u\n"
                "_or_one_p%u:\n"
                "push 1.0\n"
                "_or_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex, vertex);
            return isInt;

        case OperatorType::And:
            fprintf(file,
                "fcmp rax 0\n"
                "je _nd_zero_p%u\n"
                "cmp rbx 0\n"
                "je _nd_zero_p%u\n"
                "push 1.0\n"
                "jmp _nd_one_p%u\n"
                "_nd_zero_p%u:\n"
                "push 0\n"
                "_nd_one_p%u:\n",
                vertex, vertex,
                vertex, vertex, vertex);
            return isInt;

        case OperatorType::Eq:
            fprintf(file,
                "fcmp rax rbx\n"
                "je _eq_one_p%u\n"
                "push 0\n"
                "jmp _eq_zero_p%u\n"
                "_eq_one_p%u:\n"
                "push 1.0\n"
                "_eq_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Neq:
            fprintf(file,
                "fcmp rax rbx\n"
                "jne _ne_one_p%u\n"
                "push 0\n"
                "jmp _ne_zero_p%u\n"
                "_ne_one_p%u:\n"
                "push 1.0\n"
                "_ne_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Less:
            fprintf(file,
                "fcmp rax rbx\n"
                "jl _l_one_p%u\n"
                "push 0\n"
                "jmp _l_zero_p%u\n"
                "_l_one_p%u:\n"
                "push 1.0\n"
                "_l_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Gtr:
            fprintf(file,
                "fcmp rax rbx\n"
                "jg _g_one_p%u\n"
                "push 0\n"
                "jmp _g_zero_p%u\n"
                "_g_one_p%u:\n"
                "push 1.0\n"
                "_g_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Leq:
            fprintf(file,
                "fcmp rax rbx\n"
                "jle _le_one_p%u\n"
                "push 0\n"
                "jmp _le_zero_p%u\n"
                "_le_one_p%u:\n"
                "push 1.0\n"
                "_le_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        case OperatorType::Geq:
            fprintf(file,
                "fcmp rax rbx\n"
                "jge _ge_one_p%u\n"
                "push 0\n"
                "jmp _ge_zero_p%u\n"
                "_ge_one_p%u:\n"
                "push 1.0\n"
                "_ge_zero_p%u:\n",
                vertex, vertex,
                vertex, vertex);
            return isInt;

        default:
            assert("Expected OpType in " __FUNCTION__ && false);
        }
    }

    return false;
}

#endif
