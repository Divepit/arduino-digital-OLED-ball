#pragma once
#include <Arduino.h>
#include "vector3.h"
#include "particle.h"

static constexpr int PIXELS_PER_METER_X = 5565;
static constexpr int PIXELS_PER_METER_Y = 5333;
static constexpr uint8_t IMU_ADDR = 0x68;
static constexpr int MAX_PARTICLES = 1;

class Simulation
{
private:
    Vector3 gravity;
    const Vector3 minBounds;
    const Vector3 maxBounds;
    unsigned long t_now;
    unsigned long t_prev;
    float dt;
    void enforceVerticalConstraints(Vector3 &pos, Vector3 &vel, float radius);
    void enforceHorizontalConstraints(Vector3 &pos, Vector3 &vel, float radius);
    static Vector3 readAcceleration();

public:
    Particle particles[MAX_PARTICLES];
    Simulation() = default;
    Simulation(const Vector3 &minBounds, const Vector3 &maxBounds) : gravity(Vector3(0, 0, 0)), minBounds(minBounds), maxBounds(maxBounds), t_now(millis()), t_prev(millis()), dt(0.0f) {}
    ~Simulation() = default;
    void step();
    void addParticle(const Particle &p);
};
