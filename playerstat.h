//
//  playerstat.h
//  pgnstats
//
//  Created by anders on 03/08/2020.
//  Copyright © 2020 anders. All rights reserved.
//

#ifndef playerstat_h
#define playerstat_h

#include "definitions.h"

#define MAX_PLAYERS 1024

typedef struct {
    int index;
    char name[VALUE_BUFFER];
    int games;
    int wins;
    int draws;
    int losses;
    float score;
    float opponent_score[MAX_PLAYERS];
    float opponent_games[MAX_PLAYERS];
} PlayerStat;

void playerstat_process(const Game* game);
void playerstat_print_summary(void);
void playerstat_print_cross(void);

#endif /* playerstat_h */
