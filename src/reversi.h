//
//  reversi.h
//  othello
//
//  Created by sasa on 2023/09/30.
//

#ifndef reversi_h
#define reversi_h

#define BLACK_TURN 0
#define WHITE_TURN 1
#define UP_BOARD 0xFF00000000000000ULL
#define DOWN_BOARD 0x00000000000000FFULL
#define LEFT_BOARD 0x8080808080808080ULL
#define RIGHT_BOARD 0x0101010101010101ULL
#define MIN_INF -2147483646
#define MAX_INF 2147483646

#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <bit>
#ifndef USE_UNORDERED_DENSE_DIRECTLY
#include <ankerl/unordered_dense.h>
#else
// Use unordered_dense.h from https://github.com/martinus/unordered_dense/releases/tag/v4.4.0 directly
#include "unordered_dense.h"
#endif
#include <numeric>
#include <cmath>
#include <execution>
#include <thread>

extern int DEPTH;
extern int search_depth;
extern size_t Level;
extern int px, py;
extern int whitec;
extern int blackc;
extern int tmpx, tmpy;
extern uint64_t tmpbit;
extern int think_percent;
extern int think_count;
extern size_t botplayer;
extern int nowTurn;
extern int nowIndex;
extern int firstDEPTH;
extern int afterIndex;
extern uint64_t legalboard;
extern uint64_t rev;
extern bool search_mode_enabled;
extern int box[8][8];

struct board_root{
public:
    uint64_t playerboard;
    uint64_t opponentboard;
    uint64_t put;
    int score;

    bool operator<(const board_root& b) const {
        return this->score > b.score;
    }
    bool operator==(const board_root& other) const {
        return this->playerboard == other.playerboard && this->opponentboard == other.opponentboard;
    }
    bool operator!=(const board_root& other) const {
        return this->playerboard != other.playerboard || this->opponentboard != other.opponentboard;
    }
};

struct board{
public:
    uint64_t playerboard;
    uint64_t opponentboard;
    int score;

    bool operator<(const board& b) const {
        return this->score > b.score;
    }
    bool operator==(const board& other) const {
        return this->playerboard == other.playerboard && this->opponentboard == other.opponentboard;
    }
    bool operator!=(const board& other) const {
        return this->playerboard != other.playerboard || this->opponentboard != other.opponentboard;
    }
};

struct board_finish{
public:
    uint64_t playerboard;
    uint64_t opponentboard;
    uint64_t legalboard;
    int score;

    bool operator<(const board_finish& b) const {
        return this->score < b.score;
    }
    bool operator==(const board_finish& other) const {
        return this->playerboard == other.playerboard && this->opponentboard == other.opponentboard;
    }
};

struct board_finish_root{
public:
    uint64_t playerboard;
    uint64_t opponentboard;
    uint64_t put;
    uint64_t legalboard;
    int score;

    bool operator<(const board_finish_root& b) const {
        return this->score < b.score;
    }
    bool operator==(const board_finish_root& other) const {
        return this->playerboard == other.playerboard && this->opponentboard == other.opponentboard;
    }
};

extern board b;

extern ankerl::unordered_dense::map<std::pair<uint64_t, uint64_t>, std::pair<int, int>> transpose_table;
extern ankerl::unordered_dense::map<std::pair<uint64_t, uint64_t>, std::pair<int, int>> former_transpose_table;

extern ankerl::unordered_dense::map<std::pair<uint64_t, uint64_t>, int> fixedstone_table;

//main functions
void reset();
int winner();
int ai();
int putstone(int_fast8_t y, int_fast8_t x);
inline uint64_t cordinate_to_bit(int_fast8_t x, int_fast8_t y);
inline bool canput(const uint64_t &put, const uint64_t &legalboard);
inline uint64_t makelegalboard(const uint64_t &p, const uint64_t &o);
bool isPass();
bool isFinished();
void swapboard();
inline uint64_t Flip(const uint64_t &put, const uint64_t &playerboard, const uint64_t &opponentboard);

int nega_alpha(int_fast8_t depth, int alpha, int beta, uint64_t &playerboard, uint64_t &opponentboard);
int nega_alpha_moveorder(int_fast8_t depth, int alpha, int beta, uint64_t &playerboard, uint64_t &opponentboard);
int nega_scout(int_fast8_t depth, int alpha, int beta, uint64_t &playerboard, uint64_t &opponentboard);
int nega_scout_finish(int alpha, int beta, uint64_t &playerboard, uint64_t &opponentboard, uint64_t legalboard);
int nega_alpha_moveorder_finish(int alpha, int beta, uint64_t &playerboard, uint64_t &opponentboard, uint64_t legalboard);
int nega_alpha_finish(int alpha, int beta, uint64_t &playerboard, uint64_t &opponentboard);

int search(uint64_t &playerboard, uint64_t &opponentboard);
int search_nega_scout(uint64_t &playerboard, uint64_t &opponentboard);
int search_finish(uint64_t &playerboard, uint64_t &opponentboard);
int search_finish_scout(uint64_t &playerboard, uint64_t &opponentboard);

uint64_t delta_swap(uint64_t& x, uint64_t mask, int delta);
uint64_t flipHorizontal(uint64_t x);
uint64_t flipVertical(uint64_t x);
uint64_t flipDiagonalA1H8(uint64_t x);
uint64_t flipDiagonalA8H1(uint64_t x);
uint64_t rotateClockwise90(uint64_t x);

void fixedstone_table_init();

//evaluation
inline int score_stone(const uint64_t &playerboard, const uint64_t &opponentboard);
inline int score_putable(const uint64_t &playerboard, const uint64_t &opponentboard);
inline int score_fixedstone(const uint64_t &playerboard, const uint64_t &opponentboard);
inline int countscore(const uint64_t &playerboard, const uint64_t &opponentboard);
inline int score_fixedstone_table(const uint64_t &playerboard, const uint64_t &opponentboard);
inline int score_null_place(const uint64_t &playerboard, const uint64_t &opponentboard);


#endif /* othello_h */
