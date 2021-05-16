/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    WriteAsm86.cpp

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#include <elf.h>
#include "../inc/CompilationStructs.h"
#include "../inc/Vector.h"
#include "../inc/Table.h"
#include "../inc/Translate86.h"

#pragma pack(push, 1)

void Translator::emitInt(int a)
{
    if (buffer == nullptr)
        return;

    *(int *)(buffer + pointer) = a;
    pointer += 4;
}

void Translator::emit(char a)
{
    if (buffer)
        buffer[pointer++] = a;
}

template <typename... Args>
void Translator::emit(char a, Args... b)
{
    if (buffer)
        buffer[pointer++] = a;

    emit(b...);
}

void Translator::pushLabels(void)
{
    int shift = 258; // stdlib
    for (int i = 0; i != flow->size(); i++)
    {
        auto instruction = flow->at(i);
        instruction->shift = shift;
        shift += translateInstruction(*instruction);
        if (instruction->type == InstructionType::label)
            labelTable.insert(holder->insert(instruction->field.labelName), instruction->shift);
    }


    // стандартная библиотека
    labelTable.insert(holder->insert("newLine"), 0);
    labelTable.insert(holder->insert("printInt"), 30);
    labelTable.insert(holder->insert("scanInt"), 144);

    bufferSize = shift;
    buffer = (char *)calloc(bufferSize, 1);
    pointer = 258;
}

void Translator::translateCode(void)
{
    buffer = nullptr;

    /*
     *  Пройдемся и найдем метки 
    */
    labelTable.initTable();
    pushLabels();

    /*
     *  Запишем стандартную библиотеку
    */
    writeStd();
    int shift = 0;

    for (int i = 0; i != flow->size(); i++)
    {
        auto instruction = flow->at(i);
        shift += translateInstruction(*instruction);
    }
}

void Translator::writeStd(void)
{

    // скомпилированная стандартная библиотека

    // function         offset
    // -----------------------
    // newLine          0
    // printInt         30
    // scanInt          144

    static char stdLib[] =
        {
            (char)0x6A, (char)0x0A, (char)0x48, (char)0xC7, (char)0xC0, (char)0x01, (char)0x00, (char)0x00,
            (char)0x00, (char)0x48, (char)0xC7, (char)0xC2, (char)0x01, (char)0x00, (char)0x00, (char)0x00, 
            (char)0x48, (char)0x89, (char)0xE6, (char)0x48, (char)0xC7, (char)0xC7, (char)0x01, (char)0x00, 
            (char)0x00, (char)0x00, (char)0x0F, (char)0x05, (char)0x58, (char)0xC3, (char)0x4C, (char)0x8B, 
            (char)0x44, (char)0x24, (char)0x08, (char)0x49, (char)0x83, (char)0xF8, (char)0x00, (char)0x7D, 
            (char)0x20, (char)0x6A, (char)0x2D, (char)0x48, (char)0xC7, (char)0xC0, (char)0x01, (char)0x00, 
            (char)0x00, (char)0x00, (char)0x48, (char)0xC7, (char)0xC2, (char)0x01, (char)0x00, (char)0x00, 
            (char)0x00, (char)0x48, (char)0x89, (char)0xE6, (char)0x48, (char)0xC7, (char)0xC7, (char)0x01, 
            (char)0x00, (char)0x00, (char)0x00, (char)0x0F, (char)0x05, (char)0x58, (char)0x49, (char)0xF7, 
            (char)0xD8, (char)0x4D, (char)0x31, (char)0xC9, (char)0x48, (char)0xC7, (char)0xC3, (char)0x0A, 
            (char)0x00, (char)0x00, (char)0x00, (char)0x4C, (char)0x89, (char)0xC0, (char)0x48, (char)0x31, 
            (char)0xD2, (char)0x48, (char)0xF7, (char)0xFB, (char)0x48, (char)0x83, (char)0xC2, (char)0x30, 
            (char)0x52, (char)0x49, (char)0xFF, (char)0xC1, (char)0x48, (char)0x85, (char)0xC0, (char)0x75, 
            (char)0xED, (char)0x48, (char)0xC7, (char)0xC7, (char)0x01, (char)0x00, (char)0x00, (char)0x00, 
            (char)0x48, (char)0xC7, (char)0xC2, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x48, 
            (char)0x89, (char)0xE6, (char)0x48, (char)0xC7, (char)0xC0, (char)0x01, (char)0x00, (char)0x00, 
            (char)0x00, (char)0x0F, (char)0x05, (char)0x58, (char)0x49, (char)0xFF, (char)0xC9, (char)0x4D, 
            (char)0x85, (char)0xC9, (char)0x75, (char)0xDD, (char)0x48, (char)0x31, (char)0xC0, (char)0xC3, 
            (char)0x4D, (char)0x31, (char)0xC9, (char)0x48, (char)0x31, (char)0xDB, (char)0x49, (char)0xC7, 
            (char)0xC0, (char)0x0A, (char)0x00, (char)0x00, (char)0x00, (char)0x53, (char)0x48, (char)0x31, 
            (char)0xC0, (char)0x48, (char)0x31, (char)0xFF, (char)0x48, (char)0x89, (char)0xE6, (char)0x48, 
            (char)0xC7, (char)0xC2, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x0F, (char)0x05, 
            (char)0x48, (char)0x8B, (char)0x3C, (char)0x24, (char)0x48, (char)0x83, (char)0xFF, (char)0x2D, 
            (char)0x75, (char)0x15, (char)0x4D, (char)0x85, (char)0xC9, (char)0x74, (char)0x07, (char)0xCD, 
            (char)0x04, (char)0x58, (char)0x48, (char)0x31, (char)0xC0, (char)0xC3, (char)0x49, (char)0xC7,
            (char)0xC1, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0xEB, (char)0xCF, (char)0x48, 
            (char)0x83, (char)0xFF, (char)0x30, (char)0x7C, (char)0x13, (char)0x48, (char)0x83, (char)0xFF, 
            (char)0x39, (char)0x7F, (char)0x0D, (char)0x48, (char)0x83, (char)0xEF, (char)0x30, (char)0x49, 
            (char)0x0F, (char)0xAF, (char)0xD8, (char)0x48, (char)0x01, (char)0xFB, (char)0xEB, (char)0xB6, 
            (char)0x48, (char)0x83, (char)0xFF, (char)0x0A, (char)0x75, (char)0x0D, (char)0x4D, (char)0x85, 
            (char)0xC9, (char)0x74, (char)0x03, (char)0x48, (char)0xF7, (char)0xDB, (char)0x58, (char)0x48, 
            (char)0x89, (char)0xD8, (char)0xC3, (char)0xCD, (char)0x04, (char)0x58, (char)0x48, (char)0x31,
            (char)0xC0, (char)0xC3
        };


    memcpy(buffer, stdLib, sizeof(stdLib));
}

int Translator::translateTriple(Instruction instruction, char memregOpcode, char immOpcode, char immBase, char regmemOpcode)
{
    char firstByte = 0x48;
    Register first = Register::none;

    if (instruction.field.operand[0].type == OperandType::reg)
        first = instruction.field.operand[0].field.reg;
    else
        first = instruction.field.operand[0].field.mem.reg;

    firstByte += (int)first > 8;

    Register second = Register::none;

    if (instruction.field.operand[1].type == OperandType::reg)
        second = instruction.field.operand[1].field.reg;

    if (instruction.field.operand[1].type == OperandType::mem)
        second = instruction.field.operand[1].field.mem.reg;

    firstByte += 4 * ((int)second > 8);

    emit(firstByte);

    // mov rax, 3
    if (instruction.field.operand[1].type == OperandType::imm)
    {
        emit(immOpcode,
             immBase + ((int)first - 1) % 8);

        emitInt(instruction.field.operand[1].field.imm);
        return 7;
    }

    // mov rax, [rbp+3]
    if (instruction.field.operand[1].type == OperandType::mem)
    {
        emit(regmemOpcode,
             0x80 +
                 (((int)second - 1) % 8) +
                 8 * (((int)first - 1) % 8));

        emitInt(instruction.field.operand[1].field.mem.shift);
        return 7;
    }

    // mov [rbp+3], rax
    if (instruction.field.operand[0].type == OperandType::mem)
    {
        emit(memregOpcode,
             0x80 +
                 (((int)first - 1) % 8) +
                 8 * (((int)second - 1) % 8));

        emitInt(instruction.field.operand[0].field.mem.shift);
        return 7;
    }

    // mov rax, rbx
    emit(memregOpcode,
         0xc0 +
             (((int)first - 1) % 8) +
             8 * (((int)second - 1) % 8));

    return 3;
}

int Translator::translatePushPop(Instruction instruction, char opcode)
{
    if (instruction.type == InstructionType::push && instruction.field.operand[0].type == OperandType::imm)
    {
        emit(0x68);
        emitInt(instruction.field.operand[0].field.imm);
        return 5;
    }

    assert("An attemt to push mem" && instruction.field.operand[0].type == OperandType::reg);
    auto regNum = (int)instruction.field.operand[0].field.reg - 1;
    if (regNum > 7)
    {
        emit(0x41, opcode + regNum % 8);
        return 2;
    }
    else
    {
        emit(opcode + regNum);
        return 1;
    }
}

int Translator::translateSet(Instruction instruction, char opcode)
{
    assert("An attemt to set non-register" && instruction.field.operand[0].type == OperandType::reg);
    auto regNum = (int)instruction.field.operand[0].field.reg - 1;
    if (regNum > 7)
    {
        emit(0x41, 0x0f, opcode, 0xc0 + regNum % 8);
        return 4;
    }
    else
    {
        emit(0x0f, opcode, 0xc0 + regNum % 8);
        return 3;
    }
}

int Translator::translateBranch(Instruction instruction, char opcode, bool isConditional)
{
    if (buffer == nullptr)
        return isConditional ? 6 : 5;

    auto label = labelTable.find(instruction.field.labelName);
    assert("Label not found in translateBranch!" && label);

    if (isConditional)
    {
        emit(0x0f, opcode);
        emitInt(label->value - instruction.shift - 6);
        return 6;
    }

    else
    {
        emit(opcode);
        emitInt(label->value - instruction.shift - 5);
        return 5;
    }
}

int Translator::translateImul(Instruction instruction)
{
    assert("An attempt to feed imul with non-reg!" &&
           instruction.field.operand[0].type == OperandType::reg &&
           instruction.field.operand[1].type == OperandType::reg);

    auto firstRegNum = (int)instruction.field.operand[0].field.reg - 1;
    auto secondRegNum = (int)instruction.field.operand[1].field.reg - 1;
    emit(0x48 + secondRegNum > 7 + (firstRegNum > 7) * 4,
         0x0f,
         0xaf,
         0xc0 + secondRegNum % 8 + (firstRegNum % 8) * 8);

    return 4;
}

int Translator::translateIdiv(Instruction instruction)
{
    assert("An attempt to feed idiv with non-reg!" &&
           instruction.field.operand[0].type == OperandType::reg);

    auto firstRegNum = (int)instruction.field.operand[0].field.reg - 1;

    emit(0x48 + firstRegNum > 7,
         0xf7,
         0xf8 + firstRegNum % 8);

    return 3;
}

int Translator::translateMovzx(Instruction instruction)
{
    assert("An attempt to feed movzx with non-reg!" &&
           instruction.field.operand[0].type == OperandType::reg);

    auto firstRegNum = (int)instruction.field.operand[0].field.reg - 1;

    emit(((firstRegNum > 7) ? 0x4d : 0x48),
         0x0f,
         0xb6,
         0xc0 + 9 * (firstRegNum % 8));

    return 4;
}

int Translator::translateInstruction(Instruction instruction)
{
    switch (instruction.type)
    {
    case InstructionType::label:
        return 0;

    case InstructionType::mov:
        return translateTriple(instruction, 0x89, 0xc7, 0xc0, 0x8b);

    case InstructionType::add:
        return translateTriple(instruction, 0x01, 0x81, 0xc0);

    case InstructionType::sub:
        return translateTriple(instruction, 0x29, 0x81, 0xe8);

    case InstructionType::and_:
        return translateTriple(instruction, 0x21);

    case InstructionType::or_:
        return translateTriple(instruction, 0x09);

    case InstructionType::xor_:
        return translateTriple(instruction, 0x31);

    case InstructionType::cmp:
        return translateTriple(instruction, 0x39);

    case InstructionType::test:
        return translateTriple(instruction, 0x85);

    case InstructionType::push:
        return translatePushPop(instruction, 0x50);

    case InstructionType::pop:
        return translatePushPop(instruction, 0x58);

    case InstructionType::sete:
        return translateSet(instruction, 0x94);

    case InstructionType::setne:
        return translateSet(instruction, 0x95);

    case InstructionType::setl:
        return translateSet(instruction, 0x9c);

    case InstructionType::setnl:
        return translateSet(instruction, 0x9d);

    case InstructionType::setg:
        return translateSet(instruction, 0x9f);

    case InstructionType::setng:
        return translateSet(instruction, 0x9e);

    case InstructionType::call:
        return translateBranch(instruction, 0xe8);

    case InstructionType::jmp:
        return translateBranch(instruction, 0xe9);

    case InstructionType::je:
        return translateBranch(instruction, 0x84, true /*isConditonal*/);

    case InstructionType::jne:
        return translateBranch(instruction, 0x85, true /*isConditonal*/);

    case InstructionType::imul:
        return translateImul(instruction);

    case InstructionType::idiv:
        return translateIdiv(instruction);
    
    case InstructionType::movzx:
        return translateMovzx(instruction);

    case InstructionType::ret:
        emit(0xc3);
        return 1;

    case InstructionType::int_:
        emit(0xcc);
        return 1;

    case InstructionType::syscall:
        emit(0x0f, 0x05);
        return 2;

    default:
        errorMessage("неизвестная инструкция для translateInstruction, index = %d\n", instruction.type);
        abort();
    }
}

void Translator::translate(char const *fileName, Vector<Instruction> *flow_, StringsHolder *holder_)
{
    flow    = flow_;
    holder  = holder_;

    FILE *output = fopen(fileName, "w");

    if (output == nullptr)
    {
        errorMessage("не удаось открыть файл \"%s\" для записи\n", fileName);
        return;
    }

    translateCode();

    Elf64_Addr globalOffset = 0x400000;
    Elf64_Addr textOffset   = 0x1000;

    // этот буфер нужен для вывода хедеров и пустого пространства
    // fwrite ест только выровненные адреса
    char* microBuffer = (char*)calloc(textOffset, 1);


    /*
    *   вывод elfHeader
    */
    Elf64_Ehdr elfHeader = {};
    *(int *)elfHeader.e_ident       = 0x464c457f;
    elfHeader.e_ident[EI_CLASS]     = ELFCLASS64;
    elfHeader.e_ident[EI_DATA]      = ELFDATA2LSB;
    elfHeader.e_ident[EI_VERSION]   = EV_CURRENT;
    elfHeader.e_ident[EI_OSABI]     = ELFOSABI_NONE;
    elfHeader.e_type                = ET_EXEC;
    elfHeader.e_machine             = EM_X86_64;
    elfHeader.e_version             = EV_CURRENT;
    elfHeader.e_entry               = globalOffset + 0x102;
    elfHeader.e_phoff               = sizeof(elfHeader);
    elfHeader.e_ehsize              = sizeof(Elf64_Ehdr);
    elfHeader.e_phnum               = 1;
    elfHeader.e_phentsize           = sizeof(Elf64_Phdr);
    elfHeader.e_shentsize           = sizeof(Elf64_Shdr);

    memcpy(microBuffer, &elfHeader, sizeof(elfHeader));
    fwrite(microBuffer, sizeof(elfHeader), 1, output);

    
    /*
    *   вывод programHeader
    */
    Elf64_Phdr programHeader        = {};
    programHeader.p_type            = PT_LOAD;
    programHeader.p_flags           = PF_X | PF_R ;
    programHeader.p_offset          = textOffset;
    programHeader.p_vaddr           = globalOffset;
    programHeader.p_filesz          = bufferSize;
    programHeader.p_memsz           = bufferSize;
    programHeader.p_align           = 0;

    memcpy(microBuffer, &programHeader, sizeof(programHeader));
    fwrite(microBuffer, sizeof(programHeader), 1, output);

    /*
    *   вывод identy
    */
    int const identySize = textOffset - 
                           sizeof(elfHeader) - 
                           sizeof(programHeader) * elfHeader.e_phnum;

    memset(microBuffer, 0, textOffset);
    fwrite(microBuffer, 1, identySize, output);

    /*
    *   вывод кода
    */
    fwrite(buffer, 1, bufferSize, output);
    fclose(output);

    /*
    *   превращаем файл в исполняемый
    */
    sprintf(microBuffer, "chmod +x ./%s", fileName);
    system(microBuffer);

    free(buffer);
    free(microBuffer);
    labelTable.freeTable();
}
