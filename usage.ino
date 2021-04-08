#include "BH1750.h"
BH1750 sensor(0x23, Wire);

double light;

void setup()
{
  sensor.begin();

  sensor.set_sensor_mode(BH1750::forced_mode_high_res2);

  Serial.begin();
  Particle.variable("light", light);
}

void loop()
{
  sensor.make_forced_measurement();

  Serial.println(String::format("%f", sensor.get_light_level()));
  
  light = sensor.get_light_level();
  
  String s = String(light, 2);
  Particle.publish("light", s, PRIVATE);
  delay(5000);
}
