import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ['uart']

esp32sender_sensor_ns = cg.esphome_ns.namespace('esp32sender_sensor')
ESP32SenderSensor = esp32sender_sensor_ns.class_('ESP32SenderSensor', sensor.Sensor, uart.UARTDevice)

CONFIG_SCHEMA = sensor.sensor_schema().extend({
    cv.GenerateID(): cv.declare_id(ESP32SenderSensor),
    cv.GenerateID(CONF_UART_ID): cv.use_id(uart.UARTComponent),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config[CONF_UART_ID])
    yield sensor.register_sensor(var, config)
    cg.add(cg.global_ns.print("esp32sender_sensor_ns component loaded!"))
