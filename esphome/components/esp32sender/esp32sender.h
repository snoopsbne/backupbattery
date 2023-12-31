#pragma once

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace esp32sender_sensor {

asdjka aslkdjklas dklasidjalskdjkasldjkd   ;


class ESP32SenderSensor : public Component, public Sensor, public UARTDevice {
 public:
  ESP32SenderSensor(UARTComponent *parent);
  Sensor *voltage1_sensor = new Sensor();
  Sensor *current1_sensor = new Sensor();
  Sensor *power1_sensor = new Sensor();
  Sensor *energy1_sensor = new Sensor();
  Sensor *voltage2_sensor = new Sensor();
  Sensor *current2_sensor = new Sensor();
  Sensor *power2_sensor = new Sensor();
  Sensor *energy2_sensor = new Sensor();
  Sensor *zmpt101b_sensor = new Sensor();
  bool ping_received = false;
  uint32_t last_ping_time = 0;
  const uint32_t PING_TIMEOUT = 5000;  // 5 seconds

  void loop() override;
};
}

namespace esp32sender_switch {

class ESP32SenderSwitch : public Component, public switch::Switch, public UARTDevice {
 public:
  ESP32SenderSwitch(UARTComponent *parent);
  Switch *relay1 = new Switch();
  Switch *relay2 = new Switch();
  Switch *relay3 = new Switch();
  Switch *relay4 = new Switch();
  Switch *relay5 = new Switch();
  Switch *relay6 = new Switch();
  Switch *relay7 = new Switch();
  Switch *relay8 = new Switch();

  void write_state(bool state) override;
};

}
}