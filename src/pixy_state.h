#ifndef PIXY_STATE_H
#define	PIXY_STATE_H

#include "debug.h"
#include "pixy_queue.h"

#define INITIAL 0
#define SYNC 1
#define CHECK_SUM_1 2
#define CHECK_SUM_2 3
#define SIGNATURE_1 4
#define SIGNATURE_2 5
#define X_CENTER_1 6
#define X_CENTER_2 7
#define Y_CENTER_1 8
#define Y_CENTER_2 9
#define WIDTH_1 10
#define WIDTH_2 11
#define HEIGHT_1 12
#define HEIGHT_2 13

typedef struct
{
    int state;
    unsigned char saved_byte;
    unsigned char new_byte;
    unsigned char pixel_width;
    unsigned char pixel_height;
    unsigned char signature;
    unsigned int distance;
} state_values;

state_values pixy_state(state_values app_struct);

#endif	/* PIXY_STATE_H */