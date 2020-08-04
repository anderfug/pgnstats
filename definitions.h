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
    WHITE_WIN,
    BLACK_WIN,
    DRAW,
    ONGOING,
    UNKNOWN,
    NIL
} Result;

typedef struct {
    Result Result;
    char White[VALUE_BUFFER];
    char Black[VALUE_BUFFER];
} Game;


#endif /* definitions_h */
