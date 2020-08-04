//
//  pgnstream.h
//  pgnstats
//
//  Created by anders on 03/08/2020.
//  Copyright © 2020 anders. All rights reserved.
//

#ifndef pgnstream_h
#define pgnstream_h

#include <stdio.h>
#include "definitions.h"

Game* pgnstream_fget(Game* game, FILE* stream);

#endif /* pgnstream_h */
