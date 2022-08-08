//
//  definitions.h
//  pgnstats
//
//  Created by anders on 03/08/2020.
//  Copyright © 2020 anders. All rights reserved.
//

#ifndef definitions_h
#define definitions_h

#define VALUE_BUFFER 1024

typedef enum {
    PGN_WHITE_WIN,
    PGN_BLACK_WIN,
    PGN_DRAW,
    PGN_ONGOING,
    PGN_UNKNOWN,
    PGN_NIL
} PgnResult;

typedef struct {
    PgnResult Result;
    char White[VALUE_BUFFER];
    char Black[VALUE_BUFFER];
} Game;


#endif /* definitions_h */
