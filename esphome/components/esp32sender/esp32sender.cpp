#include "esphome/core/log.h"
#include "esp32sender.h"

namespace esphome {
namespace esp32sender_sensor {


ESP32SenderSensor::ESP32SenderSensor(UARTComponent *parent) : UARTDevice(parent) {}

void ESP32SenderSensor::loop() {
  while (available()) {
    if (read() == 0x7E) {
      byte id = read();
      float value;
      read((byte*)&value, sizeof(float));
      switch (id) {
        case 0x11:
          voltage1_sensor->publish_state(value);
          break;
        case 0x12:
          voltage2_sensor->publish_state(value);
          break;
        case 0x13:
          current1_sensor->publish_state(value);
          break;
        case 0x14:
          current2_sensor->publish_state(value);
          break;
        case 0x15:
          power1_sensor->publish_state(value);
          break;
        case 0x16:
          power2_sensor->publish_state(value);
          break;
        case 0x21:
          energy1_sensor->publish_state(value);
          break;
        case 0x22:
          energy2_sensor->publish_state(value);
          break;
        case 0x30:
          zmpt101b_sensor->publish_state(value);
          break;
        case 0x40:
          last_ping_time = millis();
          ping_received = true;
          break;
      }
      read();  // Read END_BYTE
    }
  }

  if (ping_received && (millis() - last_ping_time > PING_TIMEOUT)) {
    ESP_LOGW("ESP32Sender", "No ping received from sender for more than 5 seconds.");
    ping_received = false;
  }
}
}
namespace esp32sender_switch {

ESP32SenderSwitch::ESP32SenderSwitch(UARTComponent *parent) : UARTDevice(parent) {}

void ESP32SenderSwitch::write_state(bool state) {
  byte relayNum = (byte)(this->relay1->state ? 0 : 1);
  write(0x7E);
  write(relayNum);
  write(state ? 1 : 0);
  write(0x7F);
}

} 
} //namespace esphome