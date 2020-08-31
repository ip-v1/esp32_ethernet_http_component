#ifndef _DATASHARE_H
#define _DATASHARE_H

typedef struct _Status {
  char sof;
  char sensorStateString[14]; // Sensor State:
  char sensorState;           // 0 or 1
  char c1;
  char triggerCountString[15]; // Trigger Count:
  char triggerCount[4];        // 0000
  char eof;
} Status;

unsigned int get_trigger_count();
Status *get_status(void);

char *get_data_share(void);
void set_data_share(char *data, unsigned char size);

void setup_ios(void);
void trigger_io(void);
char read_sensor_gpio();

void control_task(void *);
void start_task_control();

#endif
