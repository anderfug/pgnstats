//
//  strings.c
//  fornax2_core
//
//  Created by Anders on 24/04/2019.
//  Copyright © 2019 Avividi. All rights reserved.
//


#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "stringu.h"

void stringu_copy(char *copy, const char *str) {
    strcpy(copy, str);
}

char* stringu_copy_alloc(const char* str) {
    
    unsigned long len = strlen(str);
    char* copy = malloc(len + 1u);
    stringu_copy(copy, str);
    return copy;
}

int stringu_split(char* src, char** dest, const char* delim) {
  int i = 0;
  char *ptr = strtok(src, delim);
  while(ptr != NULL) {
    dest[i] = ptr;
    i++;
    ptr = strtok(NULL, delim);
  }
  return i;
}

bool stringu_equals(const char *str1, const char *str2) {
  return !strcmp(str1, str2);
}

bool stringu_starts_with(const char *str, const char *prefix) {
  if(strncmp(str, prefix, strlen(prefix)) == 0) return true;
  return false;
}

long stringu_to_long(const char* str) {
  return strtol(str, NULL, 10);
}

char *stringu_trim(char *str) {
  char *end;
  
  while(isspace((unsigned char)*str)) str++;
  
  if(*str == 0)
    return str;
  
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;
  
  end[1] = '\0';
  
  return str;
}
