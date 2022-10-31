#include "functions.h"

char *init_game_board(char game_board[8][8]) {
    // Remplir tout le tableau de tiret (case vide)
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            game_board[i][j] = '-';
        }
    }

    // Faire l'initialisation des pions
    game_board[3][3] = 'X';
    game_board[3][4] = 'O';
    game_board[4][3] = 'O';
    game_board[4][4] = 'X';
}

void print_game(char game_board[8][8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%c", game_board[i][j]);
        }
        printf("\n");
    }
}

char get_adv_pion(char pion) {
    if(pion == 'X') {
        return 'O';
    } else {
        return 'X';
    }
}

// TODO : Mettre les fonctions compute dans un fichier à part
int compute_vertical_moves(char game_board[8][8], int pion_x, int pion_y, char actual_player, char (*legal_moves)[2]) {
    int vm_index = 0;  // Index pour le tableau des mouvements possibles
    if(game_board[pion_x][pion_y] != actual_player) {
        return vm_index;
    }
    bool adv_pion_found = false;
    for(int i = pion_y+1; i < 8; i++) { // On regarde vers le bas
        if(game_board[pion_x][i] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[pion_x][i] == get_adv_pion(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[pion_x][i] == '-') {
                legal_moves[vm_index][0] = pion_x;
                legal_moves[vm_index][1] = i;
                vm_index++;
                break;
            }
        }  
    }
    adv_pion_found = false;
    for(int i = pion_y-1; i >= 0; i--) { // On regarde vers le haut
        if(game_board[pion_x][i] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[pion_x][i] == get_adv_pion(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[pion_x][i] == '-') {
                legal_moves[vm_index][0] = pion_x;
                legal_moves[vm_index][1] = i;
                vm_index++;
                break;
            }
        }  
    }
    return vm_index;
}

int compute_horizontal_moves(char game_board[8][8], int pion_x, int pion_y, char actual_player, char (*legal_moves)[2]) {
    int hm_index = 0;  // Index pour le tableau des mouvements possibles
    if(game_board[pion_x][pion_y] != actual_player) {
        return hm_index;
    }
    bool adv_pion_found = false;
    for(int i = pion_x+1; i < 8; i++) { // On regarde vers le bas
        if(game_board[i][pion_y] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[i][pion_y] == get_adv_pion(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[i][pion_y] == '-') {
                legal_moves[hm_index][0] = i;
                legal_moves[hm_index][1] = pion_y;
                hm_index++;
                break;
            }
        }  
    }
    adv_pion_found = false;
    for(int i = pion_x-1; i >= 0; i--) { // On regarde vers le haut
        if(game_board[i][pion_y] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[i][pion_y] == get_adv_pion(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[i][pion_y] == '-') {
                legal_moves[hm_index][0] = i;
                legal_moves[hm_index][1] = pion_y;
                hm_index++;
                break;
            }
        }  
    }
    return hm_index;
}

// int compute_diagonal_moves(char game_board[8][8], int pion_x, int pion_y, char actual_player, char (*legal_moves)[2]) {
// TODO
// }

void compute_legal_moves(char game_board[8][8], char actual_player, char (*legal_moves_board)[8]) {
    char legal_moves[64][2];
    int lm_index = 0;  // Index pour le tableau des mouvements possibles
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(game_board[i][j] == actual_player) {
                char vertical_moves[2][2];
                int vm_index = compute_vertical_moves(game_board, i, j, actual_player, vertical_moves);
                for(int k = 0; k < vm_index; k++) {
                    legal_moves[lm_index][0] = vertical_moves[k][0];
                    legal_moves[lm_index][1] = vertical_moves[k][1];
                    lm_index++;
                }

                char horizontal_moves[2][2];
                int hm_index = compute_horizontal_moves(game_board, i, j, actual_player, horizontal_moves);
                for(int k = 0; k < hm_index; k++) {
                    legal_moves[lm_index][0] = horizontal_moves[k][0];
                    legal_moves[lm_index][1] = horizontal_moves[k][1];
                    lm_index++;
                }

                // char diagonal_moves[2][2];
                // int dm_index = compute_diagonal_moves(game_board, i, j, actual_player, diagonal_moves);
                // for(int k = 0; k < dm_index; k++) {
                //     legal_moves[lm_index][0] = diagonal_moves[k][0];
                //     legal_moves[lm_index][1] = diagonal_moves[k][1];
                //     lm_index++;
                // }
                
            }
        }
    }

    for(int i = 0; i < lm_index; i++) {
        legal_moves_board[legal_moves[i][1]][legal_moves[i][0]] = '*';
        // printf("%d %d\n", legal_moves[i][0], legal_moves[i][1]); // DEBUG
    }

    return;
}

bool coup_valide(char game_board[8][8], int x, int y, char joueur) {
    return true;
}

char *jouer_coup(char game_board[8][8], int x, int y, char joueur) {

    if (coup_valide(game_board, x, y, joueur)) {
        // Jouer le coup

    }
}

void board_copy(char game_board[8][8], char (*game_board_copy)[8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            game_board_copy[i][j] = game_board[i][j];
        }
    }
}