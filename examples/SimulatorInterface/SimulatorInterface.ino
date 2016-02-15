/** @file */

#include <SBUS.h>
#include <TimerThree.h>

SBUS sbus(Serial3);

#define SBUS_LOW -75
#define SBUS_HIGH 75

enum Channel
{
  CH_ZERO,

  CH_THROT,
  CH_ROLL,
  CH_PITCH,
  CH_YAW
};

/**
 * @brief Setup routine.
 */
void setup()
{
  Serial.begin(9600);

  Timer3.initialize(1000);
  Timer3.attachInterrupt(up);
  sbus.begin();
}

/**
 * @brief Main routine.
 */
void loop()
{
  delay(5);

  Joystick.X(map(sbus.getNormalizedChannel(CH_PITCH), SBUS_LOW, SBUS_HIGH, 0, 1023));
  Joystick.Y(map(sbus.getNormalizedChannel(CH_ROLL), SBUS_LOW, SBUS_HIGH, 0, 1023));
  Joystick.Z(map(sbus.getNormalizedChannel(CH_THROT), SBUS_LOW, SBUS_HIGH, 0, 1023));
  Joystick.Zrotate(map(sbus.getNormalizedChannel(CH_YAW), SBUS_LOW, SBUS_HIGH, 0, 1023));
  Joystick.sliderLeft(map(sbus.getNormalizedChannel(5), SBUS_LOW, SBUS_HIGH, 0, 1023));
  Joystick.sliderRight(map(sbus.getNormalizedChannel(6), SBUS_LOW, SBUS_HIGH, 0, 1023));
}

void up()
{
  sbus.process();
}
