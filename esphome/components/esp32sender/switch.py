import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch, uart
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ['uart']

custom_switch_ns = cg.esphome_ns.namespace('custom_switch')
CustomSwitch = custom_switch_ns.class_('CustomSwitch', switch.Switch, uart.UARTDevice)

CONFIG_SCHEMA = switch.SWITCH_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(CustomSwitch),
    cv.GenerateID(CONF_UART_ID): cv.use_id(uart.UARTComponent),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config[CONF_UART_ID])
    yield switch.register_switch(var, config)
    cg.add(cg.global_ns.print("Custom switch component loaded!"))
