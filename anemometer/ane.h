#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ane {


/// This class implements support for a Hall-Effekt Sensor Based Anenometer
class AnemometerSensor : public sensor::Sensor, public PollingComponent {
 public:
 
  void set_pin(InternalGPIOPin *pin) { pin_ = pin; }
//  void set_wind_speed_sensor(sensor::Sensor *wind_speed_sensor) { wind_speed_sensor_ = wind_speed_sensor; }

  void setup() override;
  void update() override;
  void dump_config() override;
  float get_setup_priority() const override;

 protected:
  void read_windspeed();


  InternalGPIOPin *pin_;
//sensor::Sensor *wind_speed_sensor_;
};

}  // namespace an
}  // namespace esphome