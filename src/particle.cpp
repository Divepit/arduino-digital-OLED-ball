#include "particle.h"
#include "vector3.h"
#include <Arduino.h>

void Particle::update(const Vector3 &g, float dt)
{
    const float drag = 1.0f;

    Vector3 totalAcc = acc + g - vel * drag;

    pos = pos + vel * dt + totalAcc * 0.5f * dt * dt;
    vel = vel + totalAcc * dt;
}