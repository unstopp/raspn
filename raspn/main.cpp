//
//  main.cpp
//  raspn
//
//  Created by Marius Chirita on 8/9/16.
//  Copyright © 2016 NSHIFTED. All rights reserved.
//

//using namespace std;

#include <iostream>
#include <stdint.h>

#include "metawear/platform/btle_connection.h"
#include "metawear/core/metawearboard.h"

static void write_gatt_char(const void* caller, const MblMwGattChar *characteristic,
                            const uint8_t *value, uint8_t length) {
    // Code to write the value to the characteristic goes here
}

static void read_gatt_char(const void* caller, const MblMwGattChar *characteristic) {
    // Code to read the value from the characteristic goes here
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    MblMwBtleConnection btle_conn = { write_gatt_char, read_gatt_char };
    MblMwMetaWearBoard* board = mbl_mw_metawearboard_create(&btle_conn);

    
    return 0;
}
