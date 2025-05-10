/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Matrix.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Vec2.h"

namespace Math {
    class TransformationMatrix {
    public:
        TransformationMatrix(); // same deal as reset
        

        const double* operator[](int index) const { return matrix[index]; }
        TransformationMatrix operator * (TransformationMatrix m) const;
        TransformationMatrix& operator *= (TransformationMatrix m);
        Math::vec2 operator*(vec2 v) const;
        void Reset(); // resets the matrix to the identity matrix (multiplication returns the same matrix)
    protected:
        double matrix[3][3]{}; // 2d array that holds the raw matrix data.
    };

    class TranslationMatrix : public TransformationMatrix {
    public:
        TranslationMatrix(ivec2 translate);
        TranslationMatrix(vec2 translate);
        
    };
    class ScaleMatrix : public TransformationMatrix {
    public:
        ScaleMatrix(double scale);
        ScaleMatrix(vec2 scale);
    };
    class RotationMatrix : public TransformationMatrix {
    public:
        RotationMatrix(double theta);
    };

}