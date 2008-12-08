#include <stdio.h>

#include "cube.h"

const char cube_solved[] = "\x00nnbyon\x01nnnyon\x02nnnyog\x03nnbynn" \
                           "\x04nnnyng\x05nrbynn\x06nrnynn\x07nrnyng" \
                           "\x08nnbnon\x09nnnnog\x0Anrbnnn\x0Bnrnnng" \
                           "\x0Cwnbnon\x0Dwnnnon\x0Ewnnnog\x0Fwnbnnn" \
                           "\x10wnnnng\x11wrbnnn\x12wrnnnn\x13wrnnng";

const long cube_turn_avoid[] = {
                             /* |17<----------->0| */
                    0010101, /* 000001000001000001 */
                    0020202, /* 000010000010000010 */
                    0040404, /* 000100000100000100 */
                    0111111, /* 001001001001001001 */
                    0222222, /* 010010010010010010 */
                    0444444, /* 100100100100100100 */
                    0010101, /* 000001000001000001 */
                    0020202, /* 000010000010000010 */
                    0040404, /* 000100000100000100 */
                    0111111, /* 001001001001001001 */
                    0222222, /* 010010010010010010 */
                    0444444, /* 100100100100100100 */
                    0010101, /* 000001000001000001 */
                    0020202, /* 000010000010000010 */
                    0040404, /* 000100000100000100 */
                    0111111, /* 001001001001001001 */
                    0222222, /* 010010010010010010 */
                    0444444, /* 100100100100100100 */
                    };

/*
 * Turns the cube.  See comments by declaration in cube.h for more details
 */
char *cube_turn(char *to_twist, int dir)
{
    int turndir;
    char temp;
    int i;
    int swap[4];
    char *cubie;

    if (dir >= 12) {
        /* half turn */
        turndir = 2;
        dir -= 12;
    } else if (dir >= 6) {
        /* CC-wise turn */
        turndir = -1;
        dir -= 6;
    } else {
        /* C-wise turn */
        turndir = 1;
    }
    switch (dir) {
        case 0:
            swap[0] = TOP;
            swap[1] = RIGHT;
            swap[2] = DOWN;
            swap[3] = LEFT;
            break;
        case 1:
            swap[0] = BACK;
            swap[1] = RIGHT;
            swap[2] = FRONT;
            swap[3] = LEFT;
            break;
        case 2:
            swap[0] = TOP;
            swap[1] = FRONT;
            swap[2] = DOWN;
            swap[3] = BACK;
            break;
        case 3:
            swap[0] = TOP;
            swap[1] = LEFT;
            swap[2] = DOWN;
            swap[3] = RIGHT;
            break;
        case 4:
            swap[0] = FRONT;
            swap[1] = RIGHT;
            swap[2] = BACK;
            swap[3] = LEFT;
            break;
        case 5:
            swap[0] = TOP;
            swap[1] = BACK;
            swap[2] = DOWN;
            swap[3] = FRONT;
            break;
        default:
            /* To squelch warnings: */
            swap[0] = 0;
            swap[1] = 0;
            swap[2] = 0;
            swap[3] = 0;
            fprintf(stderr, "WARNING: CUBE TURN SWITCH CASE RAN OFF DEFAULT\n");
            break;

    }
    if (turndir == 1) {
        for (i=0; i<20; i++) {
            cubie = CUBIE(to_twist, i);
            if (cubie[dir] != 'n') {
                /* Turn this cubie clockwise */
                temp = cubie[swap[0]];
                cubie[swap[0]] = cubie[swap[3]];
                cubie[swap[3]] = cubie[swap[2]];
                cubie[swap[2]] = cubie[swap[1]];
                cubie[swap[1]] = temp;
            }
        }
    } else if (turndir == -1) {
        for (i=0; i<20; i++) {
            cubie = CUBIE(to_twist, i);
            if (cubie[dir] != 'n') {
                /* Turn this cubie counter-clockwise */
                temp = cubie[swap[0]];
                cubie[swap[0]] = cubie[swap[1]];
                cubie[swap[1]] = cubie[swap[2]];
                cubie[swap[2]] = cubie[swap[3]];
                cubie[swap[3]] = temp;
            }
        }
    } else if (turndir == 2) {
        for (i=0; i<20; i++) {
            cubie = CUBIE(to_twist, i);
            if (cubie[dir] != 'n') {
                /* Turn this cubie twice */
                temp = cubie[swap[0]];
                cubie[swap[0]] = cubie[swap[1]];
                cubie[swap[1]] = cubie[swap[2]];
                cubie[swap[2]] = cubie[swap[3]];
                cubie[swap[3]] = temp;
                temp = cubie[swap[0]];
                cubie[swap[0]] = cubie[swap[1]];
                cubie[swap[1]] = cubie[swap[2]];
                cubie[swap[2]] = cubie[swap[3]];
                cubie[swap[3]] = temp;
            }
        }
    }

    return to_twist;
}
    
