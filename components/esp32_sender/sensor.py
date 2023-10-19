import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ['uart']

custom_sensor_ns = cg.esphome_ns.namespace('custom_sensor')
CustomSensor = custom_sensor_ns.class_('CustomSensor', sensor.Sensor, uart.UARTDevice)

CONFIG_SCHEMA = sensor.sensor_schema().extend({
    cv.GenerateID(): cv.declare_id(CustomSensor),
    cv.GenerateID(CONF_UART_ID): cv.use_id(uart.UARTComponent),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config[CONF_UART_ID])
    yield sensor.register_sensor(var, config)
