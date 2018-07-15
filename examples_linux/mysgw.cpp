/*
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2018 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

#include <iostream>
#include <cstdio>
#include <unistd.h>

// For more options run ./configure --help

// Config file
//#define MY_LINUX_CONFIG_FILE "/etc/mysensors.conf"

// How many clients should be able to connect to this gateway (default 1)
#define MY_GATEWAY_MAX_CLIENTS 10
#define RFM69_REGISTER_DETAIL

#include <MySensors.h>

#define CHILD_ID 1

bool state;

MyMessage msg(CHILD_ID, V_STATUS);

void setup()
{
	// Setup locally attached sensors
	state = loadState(CHILD_ID);
}

void presentation()
{
	// Present locally attached sensors here
	sendSketchInfo("Battery Light Local", "1.9");
	present(CHILD_ID, S_BINARY);
}

void loop()
{
	// Send locally attached sensors data here
	send(msg.set(state?1:0));
	sendBatteryLevel(55);
	wait(5000);
}

void receive(const MyMessage &message)
{
	if (message.type==V_STATUS) {
		state = message.getBool();
		saveState(CHILD_ID, state?1:0);
		send(msg.set(state?1:0));
	}
}

