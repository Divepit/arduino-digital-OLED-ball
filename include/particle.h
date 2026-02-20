#pragma once
#include "vector3.h"

class Particle
{

public:
    Vector3 pos;
    Vector3 vel;
    Vector3 acc;
    float radius;
    float mass;

    Particle() : pos(0.0f, 0.0f, 0.0f), vel(0.0f, 0.0f, 0.0f), acc(0.0f, 0.0f, 0.0f), radius(2.0f), mass(1.0f) {}
    Particle(float x, float y, float z, float r, float m = 1.0) : pos(x, y, z), vel(0.0f, 0.0f, 0.0f), acc(0.0f, 0.0f, 0.0f), radius(r), mass(m) {}
    explicit Particle(float r) : Particle(0.0f, 0.0f, 0.0f, r, 1.0f) {}

    void update(const Vector3 &a, float dt);
};