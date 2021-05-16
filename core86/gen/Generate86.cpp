/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Generate86.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "../inc/Vertex.h"
#include "../inc/VarTable.h"
#include "../inc/Lexer.h"
#include "../inc/CompilationStructs.h"
#include "../inc/Generate86.h"

using Node::Vertex;
using Node::Type;
using Node::OperatorType;
using Node::StatementType;

void constConvolution(Vertex* vertex)
{
    if (vertex == nullptr)
        return;

    constConvolution(vertex->left);
    constConvolution(vertex->right);

    if(vertex->left == nullptr || vertex->right == nullptr)
        return;

    if(vertex->left->type != Type::Const || vertex->right->type != Type::Const)
        return;

    if(vertex->type == Type::Operator)
    {
        auto isInt = vertex->left->field.lit.isInt || vertex->right->field.lit.isInt;
        if(isInt)
        {
            long long result = 0;
            long long leftVal  = vertex->left->field.lit.value;
            long long rightVal = vertex->right->field.lit.value;
            if(!vertex->left->field.lit.isInt)
                leftVal = (long long)*(double*)(&leftVal);

            if(!vertex->right->field.lit.isInt)
                rightVal = (long long)*(double*)(&rightVal);

            switch(vertex->field.opType)
            {
                case OperatorType::Add:
                    result = leftVal + rightVal;
                    break;
                
                case OperatorType::And:
                    result = leftVal & rightVal;
                    break;
                
                case OperatorType::Div:
                    result = leftVal / rightVal;
                    break;

                case OperatorType::Eq:
                    result = leftVal == rightVal;
                    break;

                case OperatorType::Geq:
                    result = leftVal >= rightVal;
                    break;

                case OperatorType::Gtr:
                    result = leftVal > rightVal;
                    break;
                
                case OperatorType::Leq:
                    result = leftVal <= rightVal;
                    break;

                case OperatorType::Less:
                    result = leftVal < rightVal;
                    break;

                case OperatorType::Mul:
                    result = leftVal * rightVal;
                    break;

                case OperatorType::Neq:
                    result = leftVal != rightVal;
                    break;

                case OperatorType::Not:
                    result = ~rightVal;
                    break;

                case OperatorType::Or:
                    result = leftVal | rightVal;
                    break;

                case OperatorType::Sub:
                    result = leftVal - rightVal;
                    break;

                default:
                    result = -1;
                    break;
            }

            Vertex::deleteVertex(vertex->left);
            Vertex::deleteVertex(vertex->right);
            vertex->left  = nullptr;
            vertex->right = nullptr;
            vertex->type = Type::Const;
            vertex->field.lit = {result, true};
        }

        else
        {
            double result = 0;
            double leftVal  = *(double*)(&vertex->left->field.lit.value);
            double rightVal = *(double*)(&vertex->right->field.lit.value);

            switch(vertex->field.opType)
            {
                case OperatorType::Add:
                    result = leftVal + rightVal;
                    break;
                
                case OperatorType::And:
                    result = *(long long*)&leftVal & *(long long*)&rightVal;
                    break;
                
                case OperatorType::Div:
                    result = leftVal / rightVal;
                    break;

                case OperatorType::Eq:
                    result = leftVal == rightVal;
                    break;

                case OperatorType::Geq:
                    result = leftVal >= rightVal;
                    break;

                case OperatorType::Gtr:
                    result = leftVal > rightVal;
                    break;
                
                case OperatorType::Leq:
                    result = leftVal <= rightVal;
                    break;

                case OperatorType::Less:
                    result = leftVal < rightVal;
                    break;

                case OperatorType::Mul:
                    result = leftVal * rightVal;
                    break;

                case OperatorType::Neq:
                    result = leftVal != rightVal;
                    break;

                case OperatorType::Not:
                    result = ~*(long long*)&rightVal;
                    break;

                case OperatorType::Or:
                    result = *(long long*)&leftVal | *(long long*)&rightVal;
                    break;

                case OperatorType::Sub:
                    result = leftVal - rightVal;
                    break;

                default:
                    result = -1;
                    break;
            }

            Vertex::deleteVertex(vertex->left);
            Vertex::deleteVertex(vertex->right);
            vertex->left  = nullptr;
            vertex->right = nullptr;
            vertex->type = Type::Const;
            vertex->field.lit = {*(long long*)&result, false};
        }
    }
}


/*-----------------------------------------------------------*/
/*------------------------определения------------------------*/
/*-----------------------------------------------------------*/


bool isUnary(Vertex* vertex)
{
    return vertex->type == Type::Operator &&
           vertex->field.opType == OperatorType::Not;
}

InstructionType opTypeToAsmInstruction(OperatorType type)
{
    switch (type)
    {
    case OperatorType::Eq:
        return InstructionType::sete;

    case OperatorType::Neq:
        return InstructionType::setne;

    case OperatorType::Geq:
        return InstructionType::setnl;

    case OperatorType::Gtr:
        return InstructionType::setg;

    case OperatorType::Leq:
        return InstructionType::setng;

    case OperatorType::Less:
        return InstructionType::setl;

    case OperatorType::And:
        return InstructionType::and_;

    case OperatorType::Or:
        return InstructionType::or_;

    case OperatorType::Not:
        return InstructionType::not_;

    case OperatorType::Add:
        return InstructionType::add;

    case OperatorType::Sub:
        return InstructionType::sub;

    case OperatorType::Mul:
        return InstructionType::imul;

    case OperatorType::Div:
        return InstructionType::idiv;

    default:
        return InstructionType::label;
    }
}

int countVars(Vertex *vertex)
{
    if (vertex == nullptr)
        return 0;

    int beneathMe = countVars(vertex->left) +
                    countVars(vertex->right);

    if(vertex->type != Type::VarType)
        return beneathMe;
    
    return beneathMe + vertex->field.varDecl.nElements + 1;
}

void Generator::insertStd(void)
{
    constexpr Function scanInt{0, 0};
    constexpr Function printInt{1, 1};
    constexpr Function newLine{0, 0};

    fncTable.insert(holder->insert("scanInt", 8), scanInt);
    fncTable.insert(holder->insert("printInt", 9), printInt);
    fncTable.insert(holder->insert("newLine", 8), newLine);
}

Compiled Generator::compile(Vertex *ast, StringsHolder *holder_, bool debug)
{
    holder = holder_;
    varTable.init();
    fncTable.initTable();

    currentFnc = nullptr;
    isInMain = false;
    currentNArgs = 0;
    shift = 0;
    error = CompileError::NO_ERROR_;
    flow.instructions = Vector<Instruction>::newVector();
    loops = Vector<Vertex*>::newVector();
    // TODO - вставить код стандартных функций
    insertStd();

    Instruction instruction = {};

    if(debug)
    {
        instruction.type = InstructionType::int_;
        flow.instructions->pushBack(instruction);
    }

    instruction.type = InstructionType::call;                            
    snprintf(instruction.field.labelName, 31, "main"); 
    flow.instructions->pushBack(instruction);

    generate(ast);

    if(error)
        errorMessage("C%d ошибка компиляции, %s\n", error, errorToStr(error));

    varTable.deInit();
    fncTable.freeTable();
    Vector<Vertex*>::deleteVector(loops);

    return flow;
}

//------------------------------------------------------
//----------------------STATEMENTS----------------------
//------------------------------------------------------

void Generator::genCallArgList(Vertex *vertex)
{
    if (vertex == nullptr)
        return;

    /*
        *   Слева - ArgList
        *   Справа - expression
        */

    if(vertex->right == nullptr)
        return;

    genExpr(vertex->right);
    
    

    auto stackTop = stackImit.getCurrent();
    stackImit.pop();
    // результат expr валяется где то
    // поэтому надо его запихать как аргумент
    // push stackTop

    if(stackTop != Register::stack)
    {
        Instruction instruction = {};
        instruction.type = InstructionType::push;
        instruction.field.operand[0] = {OperandType::reg, stackTop};
        flow.instructions->pushBack(instruction);
    }
    
    if (!error)
        genCallArgList(vertex->left);
    
}

void Generator::genCall(Vertex *vertex)
{
    /*
        *   Слева - argList
        *   Справа - ничего
    */

    auto fnc = fncTable.find(vertex->field.fnc.iter.get());

    if (fnc == nullptr)
    {
        error = CompileError::UNDEFINED_FNC;
        errorVertex = vertex;
        return;
    }

    int nArgs = fnc->value.nArgs; 

    if (nArgs != vertex->field.fnc.nArgs)
    {
        errorVertex = vertex;
        error = CompileError::WRONG_NARG;
        return;
    }

    Instruction instruction = {};

    // сохраняем регистровый стек
    auto stackTop = std::min(stackImit.pointer,
                             10);
    
    for(int i = 0; i < stackTop; i++)
    {
        instruction.zeroAll();
        instruction.type = InstructionType::push;
        instruction.field.operand[0] = {OperandType::reg, stackImit.registers[i]};
        flow.instructions->pushBack(instruction);
    }


    genCallArgList(vertex->left);

    if (error)
        return;

    // call vertex->field.fnc.iter.get()
    instruction.type = InstructionType::call;
    strncpy(instruction.field.labelName, vertex->field.fnc.iter.get(), 31);
    flow.instructions->pushBack(instruction);

    // если у нас функция не от void, то мы очищаем стек от аргументов
    if (nArgs)
    {
        instruction.type = InstructionType::add;
        instruction.field.operand[0] = {OperandType::reg, Register::rsp};
        instruction.field.operand[1].type = OperandType::imm;
        instruction.field.operand[1].field.imm = 8 * nArgs;
        flow.instructions->pushBack(instruction);
    }

    for (int i = stackTop - 1; i >= 0; i--)
    {
        instruction.zeroAll();
        instruction.type = InstructionType::pop;
        instruction.field.operand[0] = {OperandType::reg, stackImit.registers[i]};
        flow.instructions->pushBack(instruction);
    }

    // и, наконец, перенесем rax на наш стек...
    auto nextReg = stackImit.getNext();
    stackImit.push();

    if (nextReg == Register::stack)
    {
        // push rax
        instruction.type = InstructionType::push;
        instruction.field.operand[0] = {OperandType::reg, Register::rax};
    }

    else
    {
        // mov nextReg, rax
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, nextReg};
        instruction.field.operand[1] = {OperandType::reg, Register::rax};
    }

    flow.instructions->pushBack(instruction);
}

void Generator::genRet(Vertex *vertex)
{
    /*
        *   Слева - expr
        *   Справа - ничего
    */

    generate(vertex->left);
    stackImit.pop();

    if (error)
        return;

    if(isInMain)
    {
        // mov rax, 60
        Instruction instruction = {};
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, Register::rax};
        instruction.field.operand[1].type = OperandType::imm;
        instruction.field.operand[1].field.imm = 60;
        flow.instructions->pushBack(instruction);

        // mov rdi, rbx
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, Register::rdi};
        instruction.field.operand[1] = {OperandType::reg, Register::rbx};
        flow.instructions->pushBack(instruction);

        // syscall (exit)
        flow.instructions->pushBack({InstructionType::syscall});

        return;
    }

    // то, что мы сгенерировали, лежит в rbx
    // вернем через rax

    // mov rax, rbx
    Instruction instruction = {};
    instruction.type = InstructionType::mov;
    instruction.field.operand[0] = {OperandType::reg, Register::rax};
    instruction.field.operand[1] = {OperandType::reg, Register::rbx};
    flow.instructions->pushBack(instruction);

    if (currentNVars + currentNArgs)
    {
        instruction.zeroAll();

        if (currentNVars)
        {
            // add rsp, 8 * currentNVars
            instruction.type = InstructionType::add;
            instruction.field.operand[0] = {OperandType::reg, Register::rsp};
            instruction.field.operand[1].type = OperandType::imm;
            instruction.field.operand[1].field.imm = 8 * currentNVars;
            flow.instructions->pushBack(instruction);
        }

        // pop rbp
        instruction.zeroAll();
        instruction.type = InstructionType::pop;
        instruction.field.operand[0] = {OperandType::reg, Register::rbp};
        flow.instructions->pushBack(instruction);
    }

    // ret
    instruction.zeroAll();
    instruction.type = InstructionType::ret;
    flow.instructions->pushBack(instruction);
}

#define INSERT_JMP(__cond, __label)                                        \
    instruction.type = InstructionType::__cond;                            \
    snprintf(instruction.field.labelName, 31, "." __label "_p%u", vertex); \
    flow.instructions->pushBack(instruction);

#define INSERT_LABEL(__label)                                              \
    instruction.type = InstructionType::label;                             \
    snprintf(instruction.field.labelName, 31, "." __label "_p%u", vertex); \
    flow.instructions->pushBack(instruction);

void Generator::genIf(Vertex *vertex)
{
    /*
        *   Слева - условие
        *   Справа - IfElse
        */

    generate(vertex->left);
    if (error)
        return;

    // теперь в rbx лежит то, что мы сгенерили

    // test rbx, rbx
    Instruction instruction = {};
    instruction.type = InstructionType::test;
    instruction.field.operand[0] = {OperandType::reg, Register::rbx};
    instruction.field.operand[1] = {OperandType::reg, Register::rbx};
    flow.instructions->pushBack(instruction);
    stackImit.pop();

    // je .else_p...
    INSERT_JMP(je, "else");

    //Левый стейтмент

    varTable.pushNamespace();
    generate(vertex->right->left);
    if (error)
        return;
    varTable.popNamespace();

    // jmp .endif_p...
    INSERT_JMP(jmp, "endif");

    // .else_p...:
    INSERT_LABEL("else");

    generate(vertex->right->right);
    if (error)
        return;

    // .endif_p...:
    INSERT_LABEL("endif");
}

void Generator::genLoop(Vertex *vertex)
{
    /*
        *   Слева - условие
        *   Справа - стейтмент
        */

    /*
        *   желаемая конструкция цикла с учетом предсказаний конвейера:   
        *
        *   ...gen expr...
        *   test    rbx, rbx
        *   je      break
        *   loop:
        *   ...statement...
        *   ...gen expr...
        *   test    rbx, rbx
        *   jne     loop
        *   break:
        */
    
    loops->pushBack(vertex);
    Instruction instruction = {};

    // ищем условие
    generate(vertex->left);
    if (error)
        return;

    // результат в left

    // test rbx, rbx
    instruction.type = InstructionType::test;
    instruction.field.operand[0] = {OperandType::reg, Register::rbx};
    instruction.field.operand[1] = {OperandType::reg, Register::rbx};
    flow.instructions->pushBack(instruction);
    stackImit.pop();

    // je .break_...
    INSERT_JMP(je, "break");

    // .loop_p...:
    INSERT_LABEL("loop");

    // генерация тела цикла
    generate(vertex->right);
    if (error)
        return;

    // ищем условие
    generate(vertex->left);
    if (error)
        return;

    // результат в left

    // test rbx, rbx
    instruction.type = InstructionType::test;
    instruction.field.operand[0] = {OperandType::reg, Register::rbx};
    instruction.field.operand[1] = {OperandType::reg, Register::rbx};
    flow.instructions->pushBack(instruction);
    stackImit.pop();

    // jne .loop_...
    INSERT_JMP(jne, "loop");

    // .break_p...:
    INSERT_LABEL("break");

    loops->popBack();
}

void Generator::genAsgn(Vertex *vertex)
{
    /*
        *   Cлева - идентификатор переменной
        *   Справа - выражение
        */

    assert("Expected Id on the left in getAsgn" && vertex->left);
    auto var = varTable.get(vertex->left->field.iter);

    if (var.shift == -1)
    {
        errorVertex = vertex;
        error = CompileError::UNDEFINED_VAR;
        return;
    }

    generate(vertex->right);
    if (error)
        return;

    if(vertex->left->left == nullptr)
    {
        // mov [rbp+var.shift], rbx
        Instruction instruction = {};
        instruction.type = InstructionType::mov;
        instruction.field.operand[0].type = OperandType::mem;
        instruction.field.operand[0].field.mem.reg = Register::rbp;
        instruction.field.operand[0].field.mem.shift = var.shift;
        instruction.field.operand[1] = {OperandType::reg, Register::rbx};
        flow.instructions->pushBack(instruction);
        stackImit.pop();
    }

    else
    {
        generate(vertex->left->left);

        // mov rax, [rbp+var.shift]
        Instruction instruction = {};
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, Register::rax};
        instruction.field.operand[1].type = OperandType::mem;
        instruction.field.operand[1].field.mem.reg = Register::rbp;
        instruction.field.operand[1].field.mem.shift = var.shift;
        flow.instructions->pushBack(instruction);

        // mov rdi, rcx
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, Register::rdi};
        instruction.field.operand[1] = {OperandType::reg, Register::rcx};
        flow.instructions->pushBack(instruction);

        // lea rax, [rax + 8*rdi]
        instruction.type = InstructionType::lea;
        flow.instructions->pushBack(instruction);

        // mov [rax+0], rbx
        instruction.type = InstructionType::mov;
        instruction.field.operand[0].type = OperandType::mem;
        instruction.field.operand[0].field.mem.reg = Register::rax;
        instruction.field.operand[0].field.mem.shift = 0;
        instruction.field.operand[1] = {OperandType::reg, Register::rbx};
        flow.instructions->pushBack(instruction);
        stackImit.pop();
        stackImit.pop();
    }
    
}

void Generator::genDvar(Vertex *vertex)
{
    /*
        *   Слева - имя переменной
        *   Справа - тип
        *   Быдлокод по причине не успеваю, нужны таблицы типов!
        */

    assert("Expected Id on the left and right in Dvar" && vertex->left && vertex->right);

    if (strcmp("int", vertex->right->field.varDecl.iter.get()))
    {
        error = CompileError::UNDEFINED_TYPE;
        return;
    }

    if(vertex->right->field.varDecl.nElements == 0)
        varTable.insert(vertex->left->field.iter, -(shift += 8), true);

    else
    {
        shift += 8 * vertex->right->field.varDecl.nElements;
        //debugMessage("nElements = %d", vertex->right->field.varDecl.nElements);

        Instruction instruction = {};

        // mov rax, rbp
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, Register::rax};
        instruction.field.operand[1] = {OperandType::reg, Register::rbp};
        flow.instructions->pushBack(instruction);

        // sub rax, shift
        instruction.type = InstructionType::sub;
        instruction.field.operand[0] = {OperandType::reg, Register::rax};
        instruction.field.operand[1] = {.type = OperandType::imm,
                                        .field = {.imm = shift}};
        flow.instructions->pushBack(instruction);

        // mov [rbp + (-shift-8)], rax
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {.type = OperandType::mem, 
                                        .field = {.mem = {Register::rbp, -shift - 8}}};
        instruction.field.operand[1] = {OperandType::reg, Register::rax};
        flow.instructions->pushBack(instruction);

        varTable.insert(vertex->left->field.iter, -(shift += 8), true, true);
    }

    
}

void Generator::genCont(Vertex* vertex)
{
    if (!loops->size())
    {
        error = CompileError::CONT_WITHOUT_LOOP;
        return;
    }

    Instruction instruction = {};
    vertex = *loops->at(loops->size() - 1);
    INSERT_JMP(jmp, "loop");
}

void Generator::genBreak(Vertex* vertex)
{
    if (!loops->size())
    {
        error = CompileError::BREAK_WITHOUT_LOOP;
        return;
    }

    Instruction instruction = {};
    vertex = *loops->at(loops->size() - 1);
    INSERT_JMP(jmp, "break");
}

//------------------------------------------------------
//---------------------!!STATEMENTS---------------------
//------------------------------------------------------

bool Generator::genConst(Vertex *vertex)
{
    assert("Only int is possible" && vertex->field.lit.isInt);
    long long literal = vertex->field.lit.value;
    auto nextReg = stackImit.getNext();
    stackImit.push();

    Instruction instruction = {};

    if (nextReg == Register::stack)
    {
        // push literal
        instruction.type = InstructionType::push;
        instruction.field.operand[0].type = OperandType::imm;
        instruction.field.operand[0].field.imm = literal;
    }

    else
    {
        // mov nextReg, literal
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, nextReg};
        instruction.field.operand[1].type = OperandType::imm;
        instruction.field.operand[1].field.imm = literal;
    }

    flow.instructions->pushBack(instruction);

    return false;
}

bool Generator::genVarv(Vertex *vertex)
{
    auto var = varTable.get(vertex->field.iter);
    if (var.shift == -1)
    {
        errorVertex = vertex;
        error = CompileError::UNDEFINED_VAR;
        return false;
    }



    Instruction instruction = {};

    if(vertex->left == nullptr)
    {
        auto nextReg = stackImit.getNext();
        stackImit.push();

        if (nextReg == Register::stack)
        {
            // mov rax, [rbp+var.shift]
            instruction.type = InstructionType::mov;
            instruction.field.operand[0] = {OperandType::reg, Register::rax};
            instruction.field.operand[1].type = {OperandType::mem};
            instruction.field.operand[1].field.mem.reg = Register::rbp;
            instruction.field.operand[1].field.mem.shift = var.shift;
            flow.instructions->pushBack(instruction);

            // push rax
            instruction.zeroAll();
            instruction.type = InstructionType::push;
            instruction.field.operand[0] = {OperandType::reg, Register::rax};
            flow.instructions->pushBack(instruction);
        }

        else
        {
            // mov nextReg, [rbp+var.shift]
            instruction.type = InstructionType::mov;
            instruction.field.operand[0] = {OperandType::reg, nextReg};
            instruction.field.operand[1].type = {OperandType::mem};
            instruction.field.operand[1].field.mem.reg = Register::rbp;
            instruction.field.operand[1].field.mem.shift = var.shift;
            flow.instructions->pushBack(instruction);
        }
    }

    else
    {
        generate(vertex->left);

        auto currentReg = stackImit.getCurrent();
        if(currentReg == Register::stack)
        {
            // pop rdi
            instruction.zeroAll();
            instruction.type = InstructionType::pop;
            instruction.field.operand[0] = {OperandType::reg, Register::rdi};
            flow.instructions->pushBack(instruction);
        }
        else
        {
            // mov rdi, currentReg
            instruction.zeroAll();
            instruction.type = InstructionType::mov;
            instruction.field.operand[0] = {OperandType::reg, Register::rdi};
            instruction.field.operand[1] = {OperandType::reg, currentReg};
            flow.instructions->pushBack(instruction);
        }

        // mov rax, [rbp+var.shift]
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, Register::rax};
        instruction.field.operand[1].type = {OperandType::mem};
        instruction.field.operand[1].field.mem.reg = Register::rbp;
        instruction.field.operand[1].field.mem.shift = var.shift;
        flow.instructions->pushBack(instruction);

        // lea rax, [rax + 8*rdi]
        instruction.type = InstructionType::lea;
        flow.instructions->pushBack(instruction);

        // текущий регистр уже не нужен
        if (currentReg == Register::stack)
        {
            // mov rax, [rax]
            instruction.type = InstructionType::mov;
            instruction.field.operand[0] = {OperandType::reg, Register::rax};
            instruction.field.operand[1].type = {OperandType::mem};
            instruction.field.operand[1].field.mem.reg = Register::rax;
            instruction.field.operand[1].field.mem.shift = 0;
            flow.instructions->pushBack(instruction);

            // push rax
            instruction.zeroAll();
            instruction.type = InstructionType::push;
            instruction.field.operand[0] = {OperandType::reg, Register::rax};
            flow.instructions->pushBack(instruction);
        }

        else
        {
            // mov nextReg, [rax]
            instruction.type = InstructionType::mov;
            instruction.field.operand[0] = {OperandType::reg, currentReg};
            instruction.field.operand[1].type = {OperandType::mem};
            instruction.field.operand[1].field.mem.reg = Register::rax;
            instruction.field.operand[1].field.mem.shift = 0;
            flow.instructions->pushBack(instruction);
        }
    }

    return var.isInt;
}

bool Generator::genExpr(Vertex *vertex)
{
    if(vertex == nullptr)
        return false;

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
        assert(("Expected expr in genExpr" && false));
    }

    return false;
}

//-----------------------------------------------------------------------------------------

void Generator::genMain(Vertex *vertex)
{
    /*
     *   Генерируем все функции, а потом генерируем точку входа
    */
    generate(vertex->left);

    isInMain = true;

    Instruction instruction = {};

    if (!error)
    {
        instruction.type = InstructionType::label;

        // main:
        strncpy(instruction.field.labelName, "main", 31);
        flow.instructions->pushBack(instruction);

        // mov rbp, rsp
        instruction.zeroAll();
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, Register::rbp};
        instruction.field.operand[1] = {OperandType::reg, Register::rsp};
        flow.instructions->pushBack(instruction);
        
        currentNVars = countVars(vertex->right);
        
        // sub rsp, 8 * currentNVARS
        instruction.zeroAll();
        instruction.type = InstructionType::sub;
        instruction.field.operand[0] = {OperandType::reg, Register::rsp};
        instruction.field.operand[1].type = OperandType::imm;
        instruction.field.operand[1].field.imm = 8 * currentNVars;
        flow.instructions->pushBack(instruction);

        generate(vertex->right);
        if (error)
            return;

        // mov rax, 60
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, Register::rax};
        instruction.field.operand[1].type = OperandType::imm;
        instruction.field.operand[1].field.imm = 60;
        flow.instructions->pushBack(instruction);

        // syscall (exit)
        flow.instructions->pushBack({InstructionType::syscall});
    }
}

void Generator::genFuncLink(Vertex *vertex)
{
    /*
        *   Слева FuncLink с функциями, определенными раньше, справа - FuncDecl
        */
    generate(vertex->left);
    if (!error)
        generate(vertex->right);
}

void Generator::genFuncDecl(Vertex *vertex)
{
    /*
        *   Слева ArgList (ecли есть), в котором мы запихаем аргументы
        *   Справа Statement
        */

    shift = 0;
    varTable.pushNamespace();

    currentFnc = &(vertex->field.fnc.iter);
    currentNArgs = vertex->field.fnc.nArgs;
    currentNVars = countVars(vertex);

    Function function = {shift, vertex->field.fnc.nArgs};
    fncTable.insert(
        vertex->field.fnc.iter,
        function);

    Instruction instruction = {};
    instruction.type = InstructionType::label;
    snprintf(instruction.field.labelName, 31, "%s", vertex->field.fnc.iter.get());;
    flow.instructions->pushBack(instruction);

    if (currentNVars + currentNArgs)
    {
        // push rbp
        instruction.zeroAll();
        instruction.type = InstructionType::push;
        instruction.field.operand[0] = {OperandType::reg, Register::rbp};
        flow.instructions->pushBack(instruction);

        // mov rbp, rsp
        instruction.type = InstructionType::mov;
        instruction.field.operand[0] = {OperandType::reg, Register::rbp};
        instruction.field.operand[1] = {OperandType::reg, Register::rsp};
        flow.instructions->pushBack(instruction);

        if (currentNVars)
        {
            // sub rsp, 8 * currentNVars
            instruction.type = InstructionType::sub;
            instruction.field.operand[0] = {OperandType::reg, Register::rsp};
            instruction.field.operand[1].type = OperandType::imm;
            instruction.field.operand[1].field.imm = 8 * currentNVars;
            flow.instructions->pushBack(instruction);
        }
    }

    generate(vertex->left);
    shift = 0;

    if (!error)
        generate(vertex->right);
    else
        return;

    if (currentNVars + currentNArgs)
    {
        instruction.zeroAll();

        if (currentNVars)
        {
            // add, 8 * currentNVars
            instruction.type = InstructionType::add;
            instruction.field.operand[0] = {OperandType::reg, Register::rsp};
            instruction.field.operand[1].type = OperandType::imm;
            instruction.field.operand[1].field.imm = 8 * currentNVars;
            flow.instructions->pushBack(instruction);
        }

        // pop rbp
        instruction.zeroAll();
        instruction.type = InstructionType::pop;
        instruction.field.operand[0] = {OperandType::reg, Register::rbp};
        flow.instructions->pushBack(instruction);
    }

    // ret
    instruction.zeroAll();
    instruction.type = InstructionType::ret;
    flow.instructions->pushBack(instruction);


    varTable.popNamespace();

    shift = 0;
    currentFnc = nullptr;
    currentNArgs = 0;
    currentNVars = 0;
}

void Generator::genArgList(Vertex *vertex)
{
    /*
        *   Слева - ранние аргументы
        *   Справа - идентификатор
        */

    // пихаем аргументы в обратном порядке, чтобы сохранить cdecl
    generate(vertex->left);
    assert("Expected Id on the right in genArgList" && vertex->right->type == Type::Id);
    varTable.insert(vertex->right->field.iter, 8 + (shift += 8), true);
}

void Generator::genStmtLink(Vertex *vertex)
{
    if (vertex->field.newScope)
        varTable.pushNamespace();

    generate(vertex->left);
    if (!error)
        generate(vertex->right);
    else
        return;

    if (vertex->field.newScope)
        varTable.popNamespace();
}

void Generator::genStatement(Vertex *vertex)
{
    /*
    *   Здесь все зависит от stType
    */

    debugMessage("nextReg = %d", stackImit.pointer);
    switch (vertex->field.stType)
    {   
    case StatementType::Break:
        genBreak(vertex);
        return;
    case StatementType::Cont:
        genCont(vertex);
        return;
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
        stackImit.pop();
        return;

    default:
        assert("Expected stType" && false);
    }
}

bool Generator::genOperator(Vertex *vertex)
{
    generate(vertex->left);
    generate(vertex->right);
    Register rightOp = stackImit.getCurrent();
    stackImit.pop();
    Register leftOp = stackImit.getCurrent();
    stackImit.pop();
    Instruction instruction = {};
    // если правый операнд на стеке, то его все равно придется убрать...
    // и если левый тоже на стеке, то с ними нельзя провести операцию без удаления правого в регистр
    // так давайте его и запихаем в rdi и сделаем вид, что так все и было!
    if (rightOp == Register::stack)
    {
        // pop rdi
        instruction.type = InstructionType::pop;
        instruction.field.operand[0] = {OperandType::reg, Register::rdi};
        flow.instructions->pushBack(instruction);
        rightOp = Register::rdi; // делаем вид, что мы ни при чем
    }
    // можно было бы оставить левый операнд на стеке, но...
    // все таки от одного лишнего pop-push мы не обеднеем
    if (leftOp == Register::stack)
    {
        // pop rax
        instruction.type = InstructionType::pop;
        instruction.field.operand[0] = {OperandType::reg, Register::rax};
        flow.instructions->pushBack(instruction);
        rightOp = Register::rax; // опять делаем вид, что мы ни при чем
    }
    /*****************************************************************************************************************
       *                                        ТЕПЕРЬ ВСЕ ОПЕРАНДЫ В РЕГИСТРАХ!                                        *
       *                                       УРА! МЫ МОЖЕМ ДЕЛАТЬ ВСЕ ЧТО ХОТИМ                                       *
       *                                             БЕЗ СМС И РЕГИСТРАЦИИ!!                                            *
       *****************************************************************************************************************/

    OperatorType opType = vertex->field.opType;

    switch (opType)
    {
    // сравнения
    case OperatorType::Eq:
    case OperatorType::Neq:
    case OperatorType::Geq:
    case OperatorType::Gtr:
    case OperatorType::Less:
    case OperatorType::Leq:
        // cmp leftOp, rightOp
        instruction.zeroAll();
        instruction.type = InstructionType::cmp;
        instruction.field.operand[0] = {OperandType::reg, leftOp};
        instruction.field.operand[1] = {OperandType::reg, rightOp};
        flow.instructions->pushBack(instruction);
        // set... leftOpL
        instruction.zeroAll();
        instruction.type = opTypeToAsmInstruction(opType);
        instruction.field.operand[0] = {OperandType::reg, leftOp};
        flow.instructions->pushBack(instruction);

        // movzx leftOp, leftOpL
        instruction.zeroAll();
        instruction.type = InstructionType::movzx;
        instruction.field.operand[0] = {OperandType::reg, leftOp};
        instruction.field.operand[1] = {OperandType::reg, leftOp};
        flow.instructions->pushBack(instruction);

        break;
    case OperatorType::Mul:
    case OperatorType::Add:
    case OperatorType::And:
    case OperatorType::Or:
    case OperatorType::Sub:
        // opType leftOp, rightOp
        instruction.zeroAll();
        instruction.type = opTypeToAsmInstruction(opType);
        instruction.field.operand[0] = {OperandType::reg, leftOp};
        instruction.field.operand[1] = {OperandType::reg, rightOp};
        flow.instructions->pushBack(instruction);

        break;

    case OperatorType::Not:
        // test rightOp, rightOp
        instruction.zeroAll();
        instruction.type = InstructionType::test;
        instruction.field.operand[0] = {OperandType::reg, rightOp};
        instruction.field.operand[1] = {OperandType::reg, rightOp};
        flow.instructions->pushBack(instruction);

        // set... rightOp
        instruction.zeroAll();
        instruction.type = InstructionType::sete;
        instruction.field.operand[0] = {OperandType::reg, rightOp};
        flow.instructions->pushBack(instruction);

        // movzx rightOp, rightOp
        instruction.zeroAll();
        instruction.type = InstructionType::movzx;
        instruction.field.operand[0] = {OperandType::reg, rightOp};
        instruction.field.operand[1] = {OperandType::reg, rightOp};
        flow.instructions->pushBack(instruction);

        break;

    case OperatorType::Div:
        // mov rax, leftOp
        if (leftOp != Register::rax)
        {
            instruction.zeroAll();
            instruction.type = InstructionType::mov;
            instruction.field.operand[0] = {OperandType::reg, Register::rax};
            instruction.field.operand[1] = {OperandType::reg, leftOp};
            flow.instructions->pushBack(instruction);
        }

        // xor rdx, rdx
        instruction.zeroAll();
        instruction.type = InstructionType::xor_;
        instruction.field.operand[0] = {OperandType::reg, Register::rdx};
        instruction.field.operand[1] = {OperandType::reg, Register::rdx};
        flow.instructions->pushBack(instruction);

        // idiv rightOp
        instruction.zeroAll();
        instruction.type = InstructionType::idiv;
        instruction.field.operand[0] = {OperandType::reg, rightOp};
        flow.instructions->pushBack(instruction);

        // mov leftOp, rax
        if (leftOp != Register::rax)
        {
            instruction.zeroAll();
            instruction.type = InstructionType::mov;
            instruction.field.operand[0] = {OperandType::reg, leftOp};
            instruction.field.operand[1] = {OperandType::reg, Register::rax};
            flow.instructions->pushBack(instruction);
        }

        break;

    default:
        assert("Unproceeded operator in genOperator" && false);
    }

    // если мы взяли левый операнд со стека, то туда его и надо вернуть
    if (leftOp == Register::rax)
    {
        // push rax
        instruction.type = InstructionType::push;
        instruction.field.operand[0] = {OperandType::reg, Register::rax};
        flow.instructions->pushBack(instruction);
    }
    stackImit.push();

    return false;
}

void Generator::generate(Node::Vertex *vertex)
{
    if (vertex == nullptr)
        return;
    if (error)
        return;

#define CASE(TYPE)         \
    case Node::Type::TYPE: \
        gen##TYPE(vertex); \
        return;

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