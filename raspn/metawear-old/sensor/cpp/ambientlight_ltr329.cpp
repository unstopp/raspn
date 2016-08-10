#include "metawear/core/cpp/datasignal_private.h"
#include "metawear/core/cpp/metawearboard_def.h"

#include "metawear/sensor/ambientlight_ltr329.h"
#include "ambientlight_ltr329_register.h"

#include <cstdlib>
#include <cstring>

using std::forward_as_tuple;
using std::malloc;
using std::memcpy;
using std::memset;
using std::piecewise_construct;

struct Ltr329Config {
    uint8_t:2;
    uint8_t als_gain:3;
    uint8_t:3;
    uint8_t als_measurement_rate:3;
    uint8_t als_integration_time:3;
    uint8_t:2;
};

void init_ambient_light_module(MblMwMetaWearBoard *board) {
    Ltr329Config* new_config = (Ltr329Config*) malloc(sizeof(Ltr329Config));

    memset(new_config, 0, sizeof(Ltr329Config));
    new_config->als_measurement_rate = MBL_MW_ALS_LTR329_RATE_500MS;
    board->module_config.emplace(MBL_MW_MODULE_AMBIENT_LIGHT, new_config);

    board->sensor_data_signals[LTR329_ILLUMINANCE_RESPONSE_HEADER]= new MblMwDataSignal(LTR329_ILLUMINANCE_RESPONSE_HEADER, 
            board, DataInterpreter::UINT32, 1, 4, 0, 0);
    board->responses[LTR329_ILLUMINANCE_RESPONSE_HEADER]= response_handler_data_no_id;
}

MblMwDataSignal* mbl_mw_als_ltr329_get_illuminance_data_signal(const MblMwMetaWearBoard *board) {
    return board->sensor_data_signals.at(LTR329_ILLUMINANCE_RESPONSE_HEADER);
}

void mbl_mw_als_ltr329_set_gain(MblMwMetaWearBoard *board, MblMwAlsLtr329Gain gain) {
    switch(gain) {
        case MBL_MW_ALS_LTR329_GAIN_48X:
        case MBL_MW_ALS_LTR329_GAIN_96X:
            ((Ltr329Config*) board->module_config.at(MBL_MW_MODULE_AMBIENT_LIGHT))->als_gain= gain + 2;
            break;
        default:
            ((Ltr329Config*) board->module_config.at(MBL_MW_MODULE_AMBIENT_LIGHT))->als_gain= gain;
            break;
    }
}

void mbl_mw_als_ltr329_set_integration_time(MblMwMetaWearBoard *board, MblMwAlsLtr329IntegrationTime integration_time) {
    ((Ltr329Config*) board->module_config.at(MBL_MW_MODULE_AMBIENT_LIGHT))->als_integration_time= integration_time;
}

void mbl_mw_als_ltr329_set_measurement_rate(MblMwMetaWearBoard *board, MblMwAlsLtr329MeasurementRate measurement_rate) {
    ((Ltr329Config*) board->module_config.at(MBL_MW_MODULE_AMBIENT_LIGHT))->als_measurement_rate= measurement_rate;
}

void mbl_mw_als_ltr329_write_config(const MblMwMetaWearBoard *board) {
    uint8_t command[4]= {MBL_MW_MODULE_AMBIENT_LIGHT, ORDINAL(AmbientLightLtr329Register::CONFIG)};
    memcpy(command + 2, board->module_config.at(MBL_MW_MODULE_AMBIENT_LIGHT), sizeof(Ltr329Config));
    SEND_COMMAND;
}

void mbl_mw_als_ltr329_start(const MblMwMetaWearBoard *board) {
    uint8_t command[3]= {MBL_MW_MODULE_AMBIENT_LIGHT, ORDINAL(AmbientLightLtr329Register::ENABLE), 1};
    SEND_COMMAND;
}

void mbl_mw_als_ltr329_stop(const MblMwMetaWearBoard *board) {
    uint8_t command[3]= {MBL_MW_MODULE_AMBIENT_LIGHT, ORDINAL(AmbientLightLtr329Register::ENABLE), 0};
    SEND_COMMAND;
}
