/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Convolute.cpp

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#include "../inc/Vertex.h"

using Node::Vertex;
using Node::Type;
using Node::OperatorType;

void constConvolution(Vertex *vertex)
{
    if (vertex == nullptr)
        return;

    constConvolution(vertex->left);
    constConvolution(vertex->right);

    if (vertex->left == nullptr || vertex->right == nullptr)
        return;

    if (vertex->left->type != Type::Const || vertex->right->type != Type::Const)
        return;

    if (vertex->type == Type::Operator)
    {
        auto isInt = vertex->left->field.lit.isInt || vertex->right->field.lit.isInt;
        if (isInt)
        {
            long long result = 0;
            long long leftVal = vertex->left->field.lit.value;
            long long rightVal = vertex->right->field.lit.value;
            if (!vertex->left->field.lit.isInt)
                leftVal = (long long)*(double *)(&leftVal);

            if (!vertex->right->field.lit.isInt)
                rightVal = (long long)*(double *)(&rightVal);

            switch (vertex->field.opType)
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
            vertex->left = nullptr;
            vertex->right = nullptr;
            vertex->type = Type::Const;
            vertex->field.lit = {result, true};
        }

        else
        {
            double result = 0;
            double leftVal = *(double *)(&vertex->left->field.lit.value);
            double rightVal = *(double *)(&vertex->right->field.lit.value);

            switch (vertex->field.opType)
            {
            case OperatorType::Add:
                result = leftVal + rightVal;
                break;

            case OperatorType::And:
                result = *(long long *)&leftVal & *(long long *)&rightVal;
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
                result = ~*(long long *)&rightVal;
                break;

            case OperatorType::Or:
                result = *(long long *)&leftVal | *(long long *)&rightVal;
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
            vertex->left = nullptr;
            vertex->right = nullptr;
            vertex->type = Type::Const;
            vertex->field.lit = {*(long long *)&result, false};
        }
    }
}