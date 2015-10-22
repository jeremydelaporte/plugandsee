
#ifndef SMARTOUTLETCONFIG_H_
#define SMARTOUTLETCONFIG_H_

#define FANION 0x7e

#define RELAYSTATUSOFF "relay status off\n"
#define RELAYSTATUSON  "relay status on\n"
#define RELAYOFFOK     "relay off ok\n"
#define RELAYOFFNOK    "relay off nok\n"
#define RELAYONOK      "relay on ok\n"
#define RELAYONNOK     "relay on nok\n"

#define OFF 0
#define ON  1

#define TEMPINSIDE_MOCK "temp inside - 35.6\n"

#define RELAY_PORT_NUM  1
#define RELAY_BIT_VALUE 13

#define ACS712 5

#define FREQUENCY 50 // In Hz
#define PERIOD (1/FREQUENCY)*1000

#endif /* SMARTOUTLETCONFIG_H_ */
