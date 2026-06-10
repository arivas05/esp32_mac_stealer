#include "fnv1a.h"



void init_record(process *record){
    for(size_t i = 0; i<MAX_PROBES; i++){
        strcpy(record[i].mac_address, DEFAULT);
        record[i].num_probes = 0;
    }
}

uint32_t fnv1a_hash(char *data) {
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < LENGTH; i++) {
        hash ^= data[i];
        hash *= 16777619u;
    }
    hash %= MAX_PROBES;
    return hash;
}

uint8_t check_hash(uint32_t hash, char *mac_address, process *record){
    //printf("%s %s\n", record[hash].mac_address, DEFAULT);
    if(record[hash].num_probes == 0 && strcmp(record[hash].mac_address,DEFAULT) == 0){
        printf("Found a new MAC Address\n");
        return 1;
    } else if(record[hash].num_probes > 0 && strcmp(record[hash].mac_address,DEFAULT) == 0){
        printf("MAC Address repeat\n");
        return 3;
    } else if(record[hash].num_probes > 0 && strcmp(record[hash].mac_address,DEFAULT) != 0){
        printf("Collision\n");
        return 2;
    } else {
        return 0;
    }
}

void insertion(uint32_t hash, char *mac_address, process *record){
    uint8_t ret = check_hash(hash, mac_address, record);
    switch(ret){
        case 0:
            perror("ERROR"); break;
        case 1:
            strcpy(record[hash].mac_address, mac_address); 
            s_example_write_file(outputfile, mac_address); 
            record[hash].num_probes+=1; break;
        case 2:{
            uint8_t attempts = 0;
            while (attempts < MAX_PROBES) {
                record[hash].num_probes += 1;
                hash = random_probe(hash);
                uint8_t r2 = check_hash(hash, mac_address, record);
                if (r2 == 1) {
                    strcpy(record[hash].mac_address, mac_address);
                    s_example_write_file(outputfile, mac_address);
                    record[hash].num_probes += 1;
                    break;
                } else if (r2 == 3) {
                    perror("Probing ERROR"); break;  // duplicate found during probing
                }
                attempts++;
            }
            break;
        }
        case 3:
            break;
    }
    return;
}

uint32_t random_probe(uint32_t R){
    R *= 13;
    R %= MAX_PROBES;
    return R;
}

void read_records(process *record){
    for(size_t i = 0; i <MAX_PROBES; i++){
        printf("MAC Address: %s and # of probes %ld\n", record[i].mac_address, record[i].num_probes);
    }
    return; 
}


 







