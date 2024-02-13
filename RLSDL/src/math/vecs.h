#ifndef VECS_H
#define VECS_H

struct Vec2 {
    float X;
    float Y;
    Vec2() : X(0.0f), Y(0.0f) { }
    Vec2(float x, float y) : X(x), Y(y) { }    
};

struct Vec3 {
    float X;
    float Y;
    float Z;
    Vec3() : X(0.0f), Y(0.0f), Z(0.0f) { }
    Vec3(float x, float y, float z) : X(x), Y(y), Z(z) { }    
};

struct Vec4 {
    float X;
    float Y;
    float Z;
    float W;
    Vec4() : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) { }
    Vec4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) { }    
};

#endif