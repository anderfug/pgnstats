//
//  main.c
//  fornax2_core
//
//  Created by anders on 02/08/2020.
//  Copyright © 2020 Avividi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stringu.h"
#include "pgnstream.h"
#include "definitions.h"
#include "playerstat.h"


bool find_arg(const char* arg, int argc, const char * argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (stringu_equals(arg, argv[i])) return true;
  }
  return false;;
}

void print_usage(const char* name) {
  printf("usage: %s --standings --cross < pgn_file_path\n", name);
}

int main(int argc, const char * argv[]) {
  
  if (find_arg("--version", argc, argv) || find_arg("-v", argc, argv)) {
    printf("pgnstats v0.1\n");
    return EXIT_SUCCESS;
  }
  else if (find_arg("--help", argc, argv) || find_arg("-h", argc, argv)) {
    print_usage(argv[0]);
    return EXIT_SUCCESS;
  }
  
  Game game;
  long games = 0;
  
  printf("Collecting input ...\n");
  
  while (pgnstream_fget(&game, stdin) != NULL) {
    playerstat_process(&game);
    games++;
  }
  
  bool usage = true;
  
  printf("Total games: %ld\n", games);
  if (find_arg("--standings", argc, argv)) {
    printf("Standings\n");
    playerstat_print_summary();
    usage = false;
  }
  if (find_arg("--cross", argc, argv)) {
    printf("\nCross results\n");
    playerstat_print_cross();
    usage = false;
  }
  
  if (usage) {
    print_usage(argv[0]);
  }
  
  return EXIT_SUCCESS;
}
