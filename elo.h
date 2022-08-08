//
//  elo.h
//  pgnstats
//
//  Created by anders on 09/08/2020.
//  Copyright © 2020 anders. All rights reserved.
//

#ifndef elo_h
#define elo_h

#include <math.h>
#include "definitions.h"

#define START_ELO 1200
#define K_FACTOR 20.f

int calculate_elo(int player, int opponent, float score) {
    float p = (float) (1.f / (1.f + pow(10, ((opponent - player) / 400.f))));
    return (int) (player + K_FACTOR * (score - p));
}

#endif /* elo_h */
