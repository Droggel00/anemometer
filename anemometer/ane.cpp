#include "ane.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace ane {

static const char *const TAG = "ane.sensor";

void AnemometerSensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Anemometer");
  //this->pin_->setup();
  this->pin_->pin_mode(INPUT_PULLUP);
  return; 
}



void AnemometerSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Anemometer: ");

  LOG_SENSOR("  ", "Wind speed:", this->wind_speed_sensor_);
  LOG_PIN("  Pin: ", this->pin_);
}







  
void AnemometerSensor::update()  {
    this->read_windspeed();
}

float AnemometerSensor::get_setup_priority() const { return esphome::setup_priority::AFTER_CONNECTION; }

//messe 3 Sekunden lang, wie oft der Magnet sich am Sensor vorbei bewegt.
void AnemometerSensor::read_windspeed() {
  static int counter;
  const int sensorPin = this->pin_;
  static boolean was_low;
  counter = 0;
  unsigned long start;
  
  start = millis();
  while(millis() <= (start+3000))
  {
      if(digitalRead(sensorPin)==0 && !was_low)
      { 
          counter++;
          was_low = true;           
      }
      if(digitalRead(sensorPin)==1 && was_low)
      {
          was_low = false;
      }
      yield();    //yield, damit Watchdog nicht anspringt
  }
  this->publish_state(float(counter)/float(3) * 2.4);

}






}  // namespace anemometer
}  // namespace esphome
