/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Matrix.h
Project:    CS230 Engine
Author:     Jonathan Holmes Junseok Lee
Created:    March 8, 2023
*/

#include "Matrix.h"
#include "cmath"

Math::TransformationMatrix::TransformationMatrix() {
    Reset();
}



void Math::TransformationMatrix::Reset() {
    for (int i = 0; i < 3; i++) {
        matrix[i][i] = 1;
    }
}

Math::TransformationMatrix Math::TransformationMatrix::operator * (TransformationMatrix m) const {
    TransformationMatrix result;
    //takes in a transformation matrix as a right hand operand and a transformation matrix as the left. 

    result.matrix[0][0] = matrix[0][0] * m[0][0] + matrix[0][1] * m[1][0] + matrix[0][2] * m[2][0];
    result.matrix[0][1] = matrix[0][0] * m[0][1] + matrix[0][1] * m[1][1] + matrix[0][2] * m[2][1];
    result.matrix[0][2] = matrix[0][0] * m[0][2] + matrix[0][1] * m[1][2] + matrix[0][2] * m[2][2];
    result.matrix[1][0] = matrix[1][0] * m[0][0] + matrix[1][1] * m[1][0] + matrix[1][2] * m[2][0];
    result.matrix[1][1] = matrix[1][0] * m[0][1] + matrix[1][1] * m[1][1] + matrix[1][2] * m[2][1];
    result.matrix[1][2] = matrix[1][0] * m[0][2] + matrix[1][1] * m[1][2] + matrix[1][2] * m[2][2];
    result.matrix[2][0] = matrix[2][0] * m[0][0] + matrix[2][1] * m[1][0] + matrix[2][2] * m[2][0];
    result.matrix[2][1] = matrix[2][0] * m[0][1] + matrix[2][1] * m[1][1] + matrix[2][2] * m[2][1];
    result.matrix[2][2] = matrix[2][0] * m[0][2] + matrix[2][1] * m[1][2] + matrix[2][2] * m[2][2];

    return result;}

Math::TransformationMatrix& Math::TransformationMatrix::operator *= (Math::TransformationMatrix m) {

    (*this) = (*this) * m;
    return (*this);
}

Math::vec2 Math::TransformationMatrix::operator * (vec2 v) const {//operator overloading an operator overload. this is for vec2s.
    Math::vec2 result;
    result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2];
    result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2];
    return result;
}

Math::TranslationMatrix::TranslationMatrix(ivec2 translate) {
    Reset();
    matrix[0][2] = translate.x;
    matrix[1][2] = translate.y;
}

Math::TranslationMatrix::TranslationMatrix(vec2 translate) {
    Reset();
    matrix[0][2] = translate.x;
    matrix[1][2] = translate.y;
}


Math::ScaleMatrix::ScaleMatrix(double scale) // x and y are scaled by the same value
{
    Reset();
    matrix[0][0] = scale;
    matrix[1][1] = scale;
    matrix[2][2] = 1;
}

Math::ScaleMatrix::ScaleMatrix(vec2 scale)
{
    Reset();
    matrix[0][0] = scale.x;
    matrix[1][1] = scale.y;
    matrix[2][2] = 1;
}

Math::RotationMatrix::RotationMatrix(double theta) {
    Reset(); // Start with identity matrix

    double cosTheta = std::cos(theta);
    double sinTheta = std::sin(theta);

    matrix[0][0] = cosTheta;
    matrix[0][1] = -sinTheta;
    matrix[1][0] = sinTheta;
    matrix[1][1] = cosTheta;
    // matrix[2][2] remains 1, others remain 0
}