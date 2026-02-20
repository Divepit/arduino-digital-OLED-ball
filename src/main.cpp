#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "vector3.h"
#include "particle.h"
#include "simulation.h"

constexpr uint8_t SCREEN_WIDTH = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;
constexpr float BALL_RADIUS = 3.0f;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Simulation simulation(Vector3(0.0f, 0.0f, 0.0f), Vector3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  Particle ball = Particle(BALL_RADIUS);

  ball.pos.x = random((int)BALL_RADIUS, SCREEN_WIDTH - (int)BALL_RADIUS);
  ball.pos.y = random((int)BALL_RADIUS, SCREEN_HEIGHT - (int)BALL_RADIUS);
  ball.pos.z = 0.0f;
  simulation.addParticle(ball);
}

void loop()
{
  display.clearDisplay();
  simulation.step();

  display.drawCircle(
      simulation.particles[0].pos.x,
      simulation.particles[0].pos.y,
      simulation.particles[0].radius,
      SSD1306_WHITE);

  display.display();
}
