#ifndef _DATASHARE_H
#define _DATASHARE_H

char *get_data_share(void);
void set_data_share(char *data, unsigned char size);

void setup_trigger_pin(void);
void trigger_io(void);

#endif
