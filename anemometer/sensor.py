import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    CONF_PIN,
    STATE_CLASS_MEASUREMENT,
    UNIT_KILOMETER_PER_HOUR,
    ICON_WEATHER_WINDY,

)

ane_ns = cg.esphome_ns.namespace("ane")
AnemometerSensor = ane_ns.class_("AnemometerSensor", sensor.Sensor ,cg.PollingComponent )


#CONFIG_SCHEMA = ( 
#    cv.Schema(
#        {
#            cv.GenerateID(): cv.declare_id(Anemometer),
#            cv.Optional(CONF_WIND_SPEED): sensor.sensor_schema(
#                unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
#                icon=ICON_WEATHER_WINDY,
#                accuracy_decimals=1,
#                state_class=STATE_CLASS_MEASUREMENT,
#            ),
#            cv.Required(CONF_PIN): cv.All(pins.internal_gpio_input_pin_schema)
#        }
#    ).extend(cv.polling_component_schema("60s"))
#)
CONFIG_SCHEMA = (
    sensor.sensor_schema(
        unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
        icon=ICON_WEATHER_WINDY,
        accuracy_decimals=1,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.GenerateID(): cv.declare_id(AnemometerSensor),
            cv.Required(CONF_PIN): cv.All(pins.internal_gpio_input_pin_schema)


        }
    )
    .extend(cv.polling_component_schema("60s"))

)
        

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var,config)
    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))


    
#    if CONF_WIND_SPEED in config:
#        conf = config[CONF_WIND_SPEED]
#        sens = await sensor.new_sensor(conf)
#        cg.add(var.set_wind_speed_sensor(sens))


