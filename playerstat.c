//
//  playerstat.c
//  pgnstats
//
//  Created by anders on 03/08/2020.
//  Copyright © 2020 anders. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "playerstat.h"
#include "stringu.h"
#include "elo.h"

static PlayerStat players[MAX_PLAYERS];
static int player_count = 0;

static PlayerStat* add_profile(const char *name) {
    
    if (player_count >= MAX_PLAYERS - 1) {
        printf("too many players (> %d) \n", MAX_PLAYERS);
        exit(EXIT_FAILURE);
    }
    
    PlayerStat* player = &players[player_count];
    stringu_copy(player->name, name);
    player->index = player_count++;
    player->games = 0;
    player->wins = 0;
    player->losses = 0;
    player->draws = 0;
    player->score = 0;
    player->elo = START_ELO;
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        player->opponent_score[i] = 0;
        player->opponent_games[i] = 0;
    }
    return player;
}

void playerstat_process(const Game* game) {
    PlayerStat* white_player = NULL;
    PlayerStat* black_player = NULL;
    
    for (int i = 0; i < player_count; ++i) {
        if (stringu_equals(game->White, players[i].name)) {
            white_player = &players[i];
        }
        if (stringu_equals(game->Black, players[i].name)) {
            black_player = &players[i];
        }
    }
    if (white_player == NULL) {
        white_player = add_profile(game->White);
    }
    if (black_player == NULL) {
        black_player = add_profile(game->Black);
    }
    
    white_player->games++;
    black_player->games++;
    white_player->opponent_games[black_player->index]++;
    black_player->opponent_games[white_player->index]++;
    

    int white_elo = white_player->elo;
    int black_elo = black_player->elo;
    
    if (game->Result == PGN_WHITE_WIN) {
        white_player->wins++;
        white_player->score += 1.0f;
        white_player->opponent_score[black_player->index] += 1.0f;
        black_player->losses++;
        white_player->elo = calculate_elo(white_elo, black_elo, 1.0f);
        black_player->elo = calculate_elo(black_elo, white_elo, 0.0f);
    }
    else if(game->Result == PGN_BLACK_WIN) {
        black_player->wins++;
        black_player->score += 1.0f;
        black_player->opponent_score[white_player->index] += 1.0f;
        white_player->losses++;
        white_player->elo = calculate_elo(white_elo, black_elo, 0.0f);
        black_player->elo = calculate_elo(black_elo, white_elo, 1.0f);
    }
    else if (game->Result == PGN_DRAW) {
        white_player->draws++;
        white_player->score += 0.5f;
        white_player->opponent_score[black_player->index] += 0.5f;
        black_player->draws++;
        black_player->score += 0.5f;
        black_player->opponent_score[white_player->index] += 0.5f;
        white_player->elo = calculate_elo(white_elo, black_elo, 0.5f);
        black_player->elo = calculate_elo(black_elo, white_elo, 0.5f);
    }
}

static void sort_players_by_score(PlayerStat **result, PlayerStat *list, int size) {
    
    bool c[size];
    for (int j = 0; j < size; ++j) c[j] = false;
    
    for (int j = 0; j < size; ++j) {
        int best_i = -1;
        float best = -1.0f;
        for (int i = 0; i < size; ++i) {
            if (c[i]) continue;
            
            float score = list[i].score;
            if (score > best) {
                best = score;
                best_i = i;
            }
        }
        c[best_i] = true;
        result[j] = &list[best_i];
    }
}

static int longest_player_name(PlayerStat *list, int size) {
    int longest = 1;
    for (int i = 0; i < size; ++i) {
        int next = (int) strlen(list[i].name);
        longest = next > longest ? next : longest;
    }
    return longest - 1;
}

void playerstat_print_summary(void) {
    printf("found %d players:\n", player_count);
    
    PlayerStat* sorted[MAX_PLAYERS];
    sort_players_by_score(sorted, players, player_count);
    
    int padding_names = longest_player_name(players, player_count) + 1;
    char placement_count[32];
    sprintf(placement_count, "%d.", player_count);
    int padding_placement = (int) strlen(placement_count);
    
    for (int i = 0; i < player_count; ++i) {
        PlayerStat* player = sorted[i];
        
        char placement[32];
        sprintf(placement, "%d.", i + 1);
        
        float percentage = player->score / (((float) player->games) / 100);
        printf("%-*s %-*s ", padding_placement, placement, padding_names, player->name);
        printf("%5.1f%%  ", percentage);
        printf("%.1f/%d  ", player->score, player->games);
        printf("(+%d -%d =%d)", player->wins, player->losses, player->draws);
        printf(" (%d)\n", player->elo);
//        printf("games %d\n", player->games);
//        printf("score %f\n\n", player->score);
    }
}

static void playerstat_print_individual_cross(int rank, const PlayerStat* player, PlayerStat** sorted) {
    printf("%d. %s\n", rank, player->name);
    
    int padding_names = longest_player_name(players, player_count) + 1;
    
    for (int i = 0; i < player_count; ++i) {
        PlayerStat* opponent = sorted[i];
        if (stringu_equals(player->name, opponent->name)) continue;
        int games = (int) player->opponent_games[opponent->index];
        if (games <= 0) continue;
        float score = player->opponent_score[opponent->index];
        float percentage = games <= 0 ? 0 : score / (((float) games) / 100);
        printf("    %-*s", padding_names, opponent->name);
        printf("%5.1f%%  ", percentage);
        printf("%.1f/%d\n", score, games);
    }
    
}

void playerstat_print_cross(void) {
    PlayerStat* sorted[MAX_PLAYERS];
    sort_players_by_score(sorted, players, player_count);
    
    for (int i = 0; i < player_count; ++i) {
        playerstat_print_individual_cross(i + 1, sorted[i], sorted);
    }
}
