//
//  stringu.h
//  fornax2_core
//
//  Created by Anders on 24/04/2019.
//  Copyright © 2019 Avividi. All rights reserved.
//

#ifndef stringu_h
#define stringu_h

#include <stdbool.h>

void stringu_copy(char *copy, const char *str);
char* stringu_copy_alloc(const char* str);
int stringu_split(char* src, char** dest, const char* delim);
bool stringu_equals(const char *str1, const char *str2);
bool stringu_starts_with(const char *str, const char *prefix);
long stringu_to_long(const char* str);
char *stringu_trim(char *str);
#endif /* stringu_h */
