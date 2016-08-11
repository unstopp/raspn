#include<iostream>

#include "metawear\platform\btle_connection.h"

static void write_gatt_char(const void* caller, const MblMwGattChar *characteristic,
	const uint8_t *value, uint8_t length) {
	// Code to write the value to the characteristic goes here
}

static void read_gatt_char(const void* caller, const MblMwGattChar *characteristic) {
	// Code to read the value from the characteristic goes here
}

int main(int argc, char **argv) {
	MblMwBtleConnection btle_conn = { write_gatt_char, read_gatt_char };
}