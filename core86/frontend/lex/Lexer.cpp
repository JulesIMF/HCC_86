/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Lexer.cpp

Abstract:
    Реализует функцию-лексер (лексический анализатор).

Author:
    JulesIMF

Last Edit:
    20.12.2020 7:53

Edit Notes:

**********************************************************************/

#include <cstring>
#include <cstdio>
#include "../../common/Keywords.h"
#include "../../inc/Vertex.h"
#include "../../inc/Vector.h"
#include "../../inc/StringsHolder.h"
#include "../../inc/ErrorMessage.h"
#include "../../inc/Lexer.h"



static int countUntilSlashN(char const* place)
{
    int ans = 0;
    while (*place != '\0' &&
        *place != '\n' &&
        ans != 20) ans++, place++;

    return ans;
}

static bool is_digit(char c)
{
    return '0' <= c && c <= '9';
}

static bool is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

static bool is_alpha(char c)
{
    return
        'a' <= c && c <= 'z' ||
        'A' <= c && c <= 'Z' ||
        -64 <= c && c <= -1 ||
        c == '_' ||
        c == -72 || c == -88;
}

constexpr size_t cexprStrlen(char const* str)
{
    return (*str) ? cexprStrlen(str + 1) + 1 : 0;
}

bool Lexer::possible(char const *token)
{
    if (!strncmp(source, token, cexprStrlen(token)))
    {
        source += cexprStrlen(token);
        column += cexprStrlen(token);
        return true;
    }
    else
        return false;
}

void Lexer::checkSpace(void)
{
    if (is_space(*source))
        source++;
    else
        error = CompileError::EXPECTED_SPACE;
}

void Lexer::checkNoAlpha(void)
{
    if (is_alpha(*source))
        error = CompileError::UNEXPECTED_ALPHA;
}

void Lexer::checkNoDigit(void)
{
    if (is_digit(*source))
        error = CompileError::UNEXPECTED_DIGIT;
}

bool Lexer::expected(char const *token)
{
    if (!strncmp(source, token, cexprStrlen(token)))
    {
        source += cexprStrlen(token);
        return true;
    }
    else
        return false;
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

#define isdef(token)                                           \
    bool Lexer::is_##token(void)                               \
    {                                                          \
        if (!strncmp(source, _##token, cexprStrlen(_##token))) \
        {                                                      \
            source += cexprStrlen(_##token);                   \
            column += cexprStrlen(_##token);                   \
            return true;                                       \
        }                                                      \
        return false;                                          \
    }

isdef(begin);
isdef(end);
isdef(expr);
isdef(if);
isdef(else);
isdef(loop);
isdef(def);
isdef(with);
isdef(asgn);
isdef(dvar);
isdef(main);
isdef(return);
isdef(call);
isdef(break);
isdef(cont);
isdef(fdelim);
isdef(add);
isdef(sub);
isdef(mul);
isdef(div);
isdef(not );
isdef(eq);
isdef(neq);
isdef(less);
isdef(gtr);
isdef(leq);
isdef(geq);
isdef(or);
isdef(and);
isdef(left);
isdef(right);
isdef(lefts);
isdef(rights);
isdef(comma);
isdef(comment);
#undef isdef

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

long long Lexer::getNumber(bool *isInt)
{
    long long ans = 0;
    while (is_digit(*source))
    {
        ans *= 10;
        ans += *source - '0';
        source++;
        column++;
    }

    *isInt = true;

    if (possible("."))
    {
        *isInt = false;
        double mantiss = 0.1;
        double dAns = ans;
        while (is_digit(*source))
        {
            dAns += mantiss * (*source - '0');
            mantiss /= 10.0;
            source++;
            column++;
        }

        ans = *((long long *)(&dAns));
    }

    return ans;
}

StringsHolder::StringIter Lexer::getId(Lexed *lexed)
{
    size_t size = 0;

    auto idBegin = source;

    if (is_alpha(*source))
        size++, source++, column++;

    else
        assert(("expected alpha", 0));

    while (is_alpha(*source) || is_digit(*source))
        size++, source++, column++;

    return lexed->holder->insert(idBegin, size);
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

Lexed Lexer::getLexed(char const *source_)
{
    //__asm__("int $3\n");
    row = column = 1;
    Lexed lexed;
    source = source_;
    lexed.holder = StringsHolder::newStringsHolder();
    lexed.tokens.init();

    while (*source && !error)
    {
        using namespace Node;
#define DELIM(delim)                                               \
    auto vertex = Vertex::newVertex(Type::Delimiter, row, column); \
    vertex->field.delimiter = delim;                               \
    lexed.tokens.pushBack(vertex);                                 \
    continue;


        if (is_comment())
        {
            while (*source && *source != '\n')
                source++;
        }

        if (is_begin())
        {
            DELIM('{')
        }

        if (is_end())
        {
            DELIM('}')
        }

        if (is_fdelim())
        {
            DELIM('|')
        }

        if (is_left())
        {
            DELIM('(')
        }

        if (is_right())
        {
            DELIM(')')
        }

        if (is_lefts())
        {
            DELIM('[')
        }

        if (is_rights())
        {
            DELIM(']')
        }

        if (is_comma())
        {
            DELIM(',')
        }

#define SIMPLE(type)                                                   \
    lexed.tokens.pushBack(Vertex::newVertex(Type::type, row, column)); \
    continue;

        if (is_expr())
        {
            SIMPLE(StmtBegin);
        }

#define STMT(type)                                                 \
    auto vertex = Vertex::newVertex(Type::Statement, row, column); \
    vertex->field.stType = StatementType::type;                    \
    lexed.tokens.pushBack(vertex);                                 \
    continue;

        if (is_if())
        {
            STMT(Cond);
        }

        if (is_else())
        {
            STMT(Else);
        }

        if (is_loop())
        {
            STMT(Loop);
        }

        if (is_def())
        {
            SIMPLE(FuncDecl)
        }

        if (is_with())
        {
            SIMPLE(With)
        }

        if (is_asgn())
        {
            STMT(Asgn)
        }

        if (is_dvar())
        {
            STMT(Dvar)
        }

        if (is_main())
        {
            SIMPLE(Main)
        }

        if (is_return())
        {
            STMT(Ret)
        }

        if (is_cont())
        {
            STMT(Cont)
        }

        if (is_break())
        {
            STMT(Break)
        }

        if (is_call())
        {
            SIMPLE(Call)
        }

#define OPER(type)                                                \
    auto vertex = Vertex::newVertex(Type::Operator, row, column); \
    vertex->field.opType = OperatorType::type;                    \
    lexed.tokens.pushBack(vertex);                                \
    continue;

        if (is_add())
        {
            OPER(Add);
        }

        if (is_sub())
        {
            OPER(Sub);
        }

        if (is_mul())
        {
            OPER(Mul);
        }

        if (is_not())
        {
            OPER(Not);
        }

        if (is_neq())
        {
            OPER(Neq);
        }

        if (is_eq())
        {
            OPER(Eq);
        }

        if (is_leq())
        {
            OPER(Leq);
        }

        if (is_geq())
        {
            OPER(Geq);
        }

        if (is_less())
        {
            OPER(Less);
        }

        if (is_gtr())
        {
            OPER(Gtr);
        }

        if (is_gtr())
        {
            OPER(Gtr);
        }

        if (is_or())
        {
            OPER(Or);
        }

        if (is_and())
        {
            OPER(And);
        }

        if (is_div())
        {
            OPER(Div);
        }

        if (is_digit(*source))
        {
            bool isInt = true;
            auto number = getNumber(&isInt);
            auto vertex = Vertex::newVertex(Type::Const, row, column);
            vertex->field.lit.value = number;
            vertex->field.lit.isInt = isInt;
            lexed.tokens.pushBack(vertex);
            continue;
        }

        if (is_alpha(*source))
        {
            auto iter = getId(&lexed);
            auto vertex = Vertex::newVertex(Type::Id, row, column);
            vertex->field.iter = iter;
            lexed.tokens.pushBack(vertex);
            continue;
        }

        if (is_space(*source))
        {
            column++;
            if (*source == '\n')
                row++, column = 1;
            source++;
            continue;
        }

        error = CompileError::UNRECOGNIZED_TOKEN;
    }

    lexed.tokens.pushBack(Node::Vertex::newVertex(Node::Type::PgmEnd, row, column));

    if (!error)
        return lexed;

    errorMessage("L%d %s на месте %d:%d (str:col) во время разбора слов\n", error, errorToStr(error), row, column);
    lexed.noError = false;
    return lexed;
}

#undef OPER
#undef STMT
#undef SIMPLE

void lexedDump(Lexed lexed)
{
    auto size = lexed.tokens.size();
    auto tokens = lexed.tokens;

    printf("ind|row|col\tType\tParams\n\n");
    for (int i = 0; i != size; i++)
    {
        printf("%-3d%-3d:%-3d\t", i, (*tokens.at(i))->row, (*tokens.at(i))->column);
        auto type = (*tokens.at(i))->type;
        switch (type)
        {
        case Node::Type::ArgList:
            printf("ArgDeclList\n");
            break;

        case Node::Type::Call:
            printf("call\n");
            break;

        case Node::Type::StmtBegin:
            printf("stmtBegin\n");
            break;

        case Node::Type::PgmEnd:
            printf("pgmEnd\n");
            break;

        case Node::Type::Const:
            printf("const\t%s\t%lld\n", (*tokens.at(i))->field.lit.isInt ? "int" : "float", (*tokens.at(i))->field.lit.value);
            break;
        case Node::Type::Delimiter:
            printf("delim\t%c\n", (*tokens.at(i))->field.delimiter);
            break;
        case Node::Type::FuncDecl:
            printf("funcDecl\n");
            break;

        case Node::Type::FuncLink:
            printf("funcLink\n");
            break;

        case Node::Type::Id:
            printf("id\t%s\n", (*tokens.at(i))->field.iter.get());
            break;

        case Node::Type::Main:
            printf("main\n");
            break;

        case Node::Type::Operator:
            printf("operator\t%c\n", (*tokens.at(i))->field.opType);
            break;

        case Node::Type::Statement:
            printf("statement\t%c\n", (*tokens.at(i))->field.stType);
            break;

        case Node::Type::StmtLink:
            printf("stmtLink\n");
            break;

        case Node::Type::With:
            printf("with\n");
            break;

        case Node::Type::VarType:
            printf("varDecl\n");
            break;

        default:
            assert("???" && 0);
        }
    }
}
