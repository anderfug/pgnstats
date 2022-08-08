//
//  pgnstream.c
//  pgnstats
//
//  Created by anders on 03/08/2020.
//  Copyright © 2020 anders. All rights reserved.
//

#include "pgnstream.h"
#include "stringu.h"
#define LINE_BUFFER 8192
static char buffer[LINE_BUFFER];

static void parse_metadata(Game *game, char *line) {
    if (*line != '[') return;
    char* start = line + 1;
    
    while (*line++ != '"');
    char value[VALUE_BUFFER];
    char *point = value;
    while (*line != '"') {
        *point++ = *line++;
    }
    *point = '\0';
    
    stringu_trim(value);

    if (stringu_starts_with(start, "White ")) {
        stringu_copy(game->White, value);
    }
    else if (stringu_starts_with(start, "Black ")) {
        stringu_copy(game->Black, value);
    }
    else if (stringu_starts_with(start, "Result ")) {
        if (stringu_equals("1-0", value)) {
            game->Result = PGN_WHITE_WIN;
        }
        else if (stringu_equals("0-1", value)) {
            game->Result = PGN_BLACK_WIN;
        }
        else if (stringu_equals("1/2-1/2", value)) {
            game->Result = PGN_DRAW;
        }
        else if (stringu_equals("*", value)) {
            game->Result = PGN_ONGOING;
        }
        else {
            game->Result = PGN_UNKNOWN;
        }
    }
}

Game* pgnstream_fget(Game* game, FILE* stream) {
    
    game->Result = PGN_NIL;
    bool foundGame = false;
    
    while (fgets(buffer, LINE_BUFFER, stream) != NULL) {
        
        stringu_trim(buffer);
    
        if (*buffer == '\n') continue;
        else if (*buffer == '[') {
            parse_metadata(game, buffer);
            foundGame = true;
        }
        else if (foundGame) {
            break;
        }
    }
    
    return game->Result == PGN_NIL ? NULL : game;
}
