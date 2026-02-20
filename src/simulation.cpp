#include "simulation.h"
#include <Wire.h>

Vector3 Simulation::readAcceleration()
{
    Vector3 data;

    Wire.beginTransmission(IMU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom((uint8_t)IMU_ADDR, (uint8_t)6, (uint8_t)true);

    const int32_t ax = (Wire.read() << 8) | Wire.read();
    const int32_t ay = (Wire.read() << 8) | Wire.read();
    const int32_t az = (Wire.read() << 8) | Wire.read();

    data.x = PIXELS_PER_METER_X * 9.80665f * ay / 16384.0f;
    data.y = PIXELS_PER_METER_Y * -9.80665f * ax / 16384.0f;
    data.z = -9.80665f * az / 16384.0f;

    if (fabsf(data.x) < 100)
        data.x = 0.0f;
    if (fabsf(data.y) < 100)
        data.y = 0.0f;
    if (fabsf(data.z) < 100)
        data.z = 0.0f;

    return data;
}

void Simulation::enforceVerticalConstraints(Vector3 &pos, Vector3 &vel, float radius)
{
    if (pos.y < minBounds.y + radius)
    {
        pos.y = minBounds.y + radius;
        vel.y = 0.0f;
    }
    if (pos.y > maxBounds.y - radius - 1)
    {
        pos.y = maxBounds.y - radius - 1;
        vel.y = 0.0f;
    }
}

void Simulation::enforceHorizontalConstraints(Vector3 &pos, Vector3 &vel, float radius)
{
    if (pos.x < minBounds.x + radius)
    {
        pos.x = minBounds.x + radius;
        vel.x = 0.0f;
    }
    if (pos.x > maxBounds.x - radius - 1)
    {
        pos.x = maxBounds.x - radius - 1;
        vel.x = 0.0f;
    }
}

void Simulation::step()
{
    t_now = millis();
    dt = (t_now - t_prev) / 1000.0;
    gravity = readAcceleration();
    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
        if (particles[i].radius > 0.0f)
        {
            particles[i].update(gravity, dt);
            enforceVerticalConstraints(particles[i].pos, particles[i].vel, particles[i].radius);
            enforceHorizontalConstraints(particles[i].pos, particles[i].vel, particles[i].radius);
        }
    }
    t_prev = t_now;
}

void Simulation::addParticle(const Particle &p)
{
    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
        if (particles[i].radius == 0.0f)
        {
            particles[i] = p;
            break;
        }
    }
}
