#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sd_card.h"
#define MAX_PROBES 256
#define BYTE 8
#define LENGTH 18
#define DEFAULT "00:00:00:00:00:00\0"

typedef struct process{
    char mac_address[17];
    size_t num_probes;
} process;

void init_record(process *record);

uint32_t fnv1a_hash(char *data);

uint8_t check_hash(uint32_t hash, char *mac_address, process *record);

void insertion(uint32_t hash, char *mac_address, process *record);

uint32_t random_probe(uint32_t R);

void read_records(process *record);