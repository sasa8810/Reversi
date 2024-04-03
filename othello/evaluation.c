//
//  evaluation.c
//  othello
//
//  Created by sasa on 2024/01/15.
//

#include "reversi.h"
#include "Objective-C-Wrapper.h"

int scoreboard[64] = {
    30, -12, 0, -1, -1, 0, -12, 30,
    -12, -15, -3, -3, -3, -3, -15, -12,
    0, -3, 0, -1, -1, 0, -3, 0,
    -1, -3, -1, -1, -1, -1, -3, -1,
    -1, -3, -1, -1, -1, -1, -3, -1,
    0, -3, 0, -1, -1, 0, -3, 0,
    -12, -15, -3, -3, -3, -3, -15, -12,
    30, -12, 0, -1, -1, 0, -12, 30
};

int score_stone(uint64_t *playerboard, uint64_t *oppenentboard) {
    int score = 0;
    uint64_t mask = 0x8000000000000000ULL;
    for (int i = 0; i<64; ++i) {
        if(*playerboard & mask) score += scoreboard[i];
        else if(*oppenentboard & mask) score -= scoreboard[i];
        mask >>= 1;
    }
    return score;
}

int score_putable(uint64_t *playerboard, uint64_t *oppenentboard) {
    int score = 0;
    uint64_t legalboard;
    legalboard = makelegalBoard(oppenentboard, playerboard);
    score += bit_count(&legalboard);
    legalboard = makelegalBoard(playerboard, oppenentboard);
    score -= bit_count(&legalboard);
    return score;
}

int score_fixedstone(uint64_t *playerboard, uint64_t *oppenentboard) {
    int fixedstone = 0;
    //左上
    //右方向
    if(*playerboard & 0xfe00000000000000ULL) fixedstone+=7;
    else if(*playerboard & 0xfc00000000000000ULL) fixedstone+=6;
    else if(*playerboard & 0xf800000000000000ULL) fixedstone+=5;
    else if(*playerboard & 0xf000000000000000ULL) fixedstone+=4;
    else if(*playerboard & 0xe000000000000000ULL) fixedstone+=3;
    else if(*playerboard & 0xc000000000000000ULL) fixedstone+=2;
    else if(*playerboard & 0x8000000000000000ULL) fixedstone+=1;
    //下方向
    if(*playerboard & 0x8080808080808000ULL) fixedstone+=7;
    else if(*playerboard & 0x8080808080800000ULL) fixedstone+=6;
    else if(*playerboard & 0x8080808080000000ULL) fixedstone+=5;
    else if(*playerboard & 0x8080808000000000ULL) fixedstone+=4;
    else if(*playerboard & 0x8080800000000000ULL) fixedstone+=3;
    else if(*playerboard & 0x8080008000000000ULL) fixedstone+=2;
    else if(*playerboard & 0x8000000000000000ULL) fixedstone+=1;
    //右上
    //左方向
    if(*playerboard & 0x7f00000000000000ULL) fixedstone+=7;
    else if(*playerboard & 0x3f00000000000000ULL) fixedstone+=6;
    else if(*playerboard & 0x1f00000000000000ULL) fixedstone+=5;
    else if(*playerboard & 0x0f00000000000000ULL) fixedstone+=4;
    else if(*playerboard & 0x0700000000000000ULL) fixedstone+=3;
    else if(*playerboard & 0x0300000000000000ULL) fixedstone+=2;
    else if(*playerboard & 0x0100000000000000ULL) fixedstone+=1;
    //下方向
    if(*playerboard & 0x0101010101010100ULL) fixedstone+=7;
    else if(*playerboard & 0x0101010101010000ULL) fixedstone+=6;
    else if(*playerboard & 0x0101010101000000ULL) fixedstone+=5;
    else if(*playerboard & 0x0101010100000000ULL) fixedstone+=4;
    else if(*playerboard & 0x0101010000000000ULL) fixedstone+=3;
    else if(*playerboard & 0x0101000000000000ULL) fixedstone+=2;
    else if(*playerboard & 0x0100000000000000ULL) fixedstone+=1;
    //左下
    //上方向
    if(*playerboard & 0x0080808080808080ULL) fixedstone+=7;
    else if(*playerboard & 0x0000808080808080ULL) fixedstone+=6;
    else if(*playerboard & 0x0000008080808080ULL) fixedstone+=5;
    else if(*playerboard & 0x0000000080808080ULL) fixedstone+=4;
    else if(*playerboard & 0x0000008000808080ULL) fixedstone+=3;
    else if(*playerboard & 0x0000008000008080ULL) fixedstone+=2;
    else if(*playerboard & 0x0000008000000080ULL) fixedstone+=1;
    //左方向
    if(*playerboard & 0x00000000000000feULL) fixedstone+=7;
    else if(*playerboard & 0x00000000000000fcULL) fixedstone+=6;
    else if(*playerboard & 0x00000000000000f8ULL) fixedstone+=5;
    else if(*playerboard & 0x00000000000000f0ULL) fixedstone+=4;
    else if(*playerboard & 0x00000000000000e0ULL) fixedstone+=3;
    else if(*playerboard & 0x00000000000000c0ULL) fixedstone+=2;
    else if(*playerboard & 0x0000000000000080ULL) fixedstone+=1;
    //右下
    //右方向
    if(*playerboard & 0x000000000000007fULL) fixedstone+=7;
    else if(*playerboard & 0x000000000000003fULL) fixedstone+=6;
    else if(*playerboard & 0x000000000000001fULL) fixedstone+=5;
    else if(*playerboard & 0x000000000000000fULL) fixedstone+=4;
    else if(*playerboard & 0x0000000000000007ULL) fixedstone+=3;
    else if(*playerboard & 0x0000000000000003ULL) fixedstone+=2;
    else if(*playerboard & 0x0000000000000001ULL) fixedstone+=1;
    //上方向
    if(*playerboard & 0x001010101010101ULL) fixedstone+=7;
    else if(*playerboard & 0x000010101010101ULL) fixedstone+=6;
    else if(*playerboard & 0x000000101010101ULL) fixedstone+=5;
    else if(*playerboard & 0x000000001010101ULL) fixedstone+=4;
    else if(*playerboard & 0x000000000010101ULL) fixedstone+=3;
    else if(*playerboard & 0x000000000000101ULL) fixedstone+=2;
    else if(*playerboard & 0x000000000000001ULL) fixedstone+=1;
    
    //一列
    //上
    if(*playerboard & 0xff00000000000000ULL) fixedstone-=6;
    //左
    if(*playerboard & 0x8080808080808080ULL) fixedstone-=6;
    //右
    if(*playerboard & 0x0101010101010101ULL) fixedstone-=6;
    //下
    if(*playerboard & 0x00000000000000ffULL) fixedstone-=6;
    
    //左上
    //右方向
    if(*oppenentboard & 0xfe00000000000000ULL) fixedstone-=7;
    else if(*oppenentboard & 0xfc00000000000000ULL) fixedstone-=6;
    else if(*oppenentboard & 0xf800000000000000ULL) fixedstone-=5;
    else if(*oppenentboard & 0xf000000000000000ULL) fixedstone-=4;
    else if(*oppenentboard & 0xe000000000000000ULL) fixedstone-=3;
    else if(*oppenentboard & 0xc000000000000000ULL) fixedstone-=2;
    else if(*oppenentboard & 0x8000000000000000ULL) fixedstone-=1;
    //下方向
    if(*oppenentboard & 0x8080808080808000ULL) fixedstone-=7;
    else if(*oppenentboard & 0x8080808080800000ULL) fixedstone-=6;
    else if(*oppenentboard & 0x8080808080000000ULL) fixedstone-=5;
    else if(*oppenentboard & 0x8080808000000000ULL) fixedstone-=4;
    else if(*oppenentboard & 0x8080800000000000ULL) fixedstone-=3;
    else if(*oppenentboard & 0x8080008000000000ULL) fixedstone-=2;
    else if(*oppenentboard & 0x8000000000000000ULL) fixedstone-=1;
    //右上
    //左方向
    if(*oppenentboard & 0x7f00000000000000ULL) fixedstone-=7;
    else if(*oppenentboard & 0x3f00000000000000ULL) fixedstone-=6;
    else if(*oppenentboard & 0x1f00000000000000ULL) fixedstone-=5;
    else if(*oppenentboard & 0x0f00000000000000ULL) fixedstone-=4;
    else if(*oppenentboard & 0x0700000000000000ULL) fixedstone-=3;
    else if(*oppenentboard & 0x0300000000000000ULL) fixedstone-=2;
    else if(*oppenentboard & 0x0100000000000000ULL) fixedstone-=1;
    //下方向
    if(*oppenentboard & 0x0101010101010100ULL) fixedstone-=7;
    else if(*oppenentboard & 0x0101010101010000ULL) fixedstone-=6;
    else if(*oppenentboard & 0x0101010101000000ULL) fixedstone-=5;
    else if(*oppenentboard & 0x0101010100000000ULL) fixedstone-=4;
    else if(*oppenentboard & 0x0101010000000000ULL) fixedstone-=3;
    else if(*oppenentboard & 0x0101000000000000ULL) fixedstone-=2;
    else if(*oppenentboard & 0x0100000000000000ULL) fixedstone-=1;
    //左下
    //上方向
    if(*oppenentboard & 0x0080808080808080ULL) fixedstone-=7;
    else if(*oppenentboard & 0x0000808080808080ULL) fixedstone-=6;
    else if(*oppenentboard & 0x0000008080808080ULL) fixedstone-=5;
    else if(*oppenentboard & 0x0000000080808080ULL) fixedstone-=4;
    else if(*oppenentboard & 0x0000008000808080ULL) fixedstone-=3;
    else if(*oppenentboard & 0x0000008000008080ULL) fixedstone-=2;
    else if(*oppenentboard & 0x0000008000000080ULL) fixedstone-=1;
    //左方向
    if(*oppenentboard & 0x00000000000000feULL) fixedstone-=7;
    else if(*oppenentboard & 0x00000000000000fcULL) fixedstone-=6;
    else if(*oppenentboard & 0x00000000000000f8ULL) fixedstone-=5;
    else if(*oppenentboard & 0x00000000000000f0ULL) fixedstone-=4;
    else if(*oppenentboard & 0x00000000000000e0ULL) fixedstone-=3;
    else if(*oppenentboard & 0x00000000000000c0ULL) fixedstone-=2;
    else if(*oppenentboard & 0x0000000000000080ULL) fixedstone-=1;
    //右下
    //右方向
    if(*oppenentboard & 0x000000000000007fULL) fixedstone-=7;
    else if(*oppenentboard & 0x000000000000003fULL) fixedstone-=6;
    else if(*oppenentboard & 0x000000000000001fULL) fixedstone-=5;
    else if(*oppenentboard & 0x000000000000000fULL) fixedstone-=4;
    else if(*oppenentboard & 0x0000000000000007ULL) fixedstone-=3;
    else if(*oppenentboard & 0x0000000000000003ULL) fixedstone-=2;
    else if(*oppenentboard & 0x0000000000000001ULL) fixedstone-=1;
    //上方向
    if(*oppenentboard & 0x001010101010101ULL) fixedstone-=7;
    else if(*oppenentboard & 0x000010101010101ULL) fixedstone-=6;
    else if(*oppenentboard & 0x000000101010101ULL) fixedstone-=5;
    else if(*oppenentboard & 0x000000001010101ULL) fixedstone-=4;
    else if(*oppenentboard & 0x000000000010101ULL) fixedstone-=3;
    else if(*oppenentboard & 0x000000000000101ULL) fixedstone-=2;
    else if(*oppenentboard & 0x000000000000001ULL) fixedstone-=1;
    //一列
    //上
    if(*oppenentboard & 0xff00000000000000ULL) fixedstone+=6;
    //左
    if(*oppenentboard & 0x8080808080808080ULL) fixedstone+=6;
    //右
    if(*oppenentboard & 0x0101010101010101ULL) fixedstone+=6;
    //下
    if(*oppenentboard & 0x00000000000000ffULL) fixedstone+=6;
    return fixedstone;
}


bool is_all_oppenent(uint64_t *playerboard) {
    return (*playerboard == 0);
}

int countscore(uint64_t *playerboard, uint64_t *oppenentboard) {
    if(is_all_oppenent(playerboard)) return -9999;
//    if(nowIndex+DEPTH >= 60) return (int)bitcount(playerboard)-(int)bitcount(oppenentboard);
    if(nowIndex+DEPTH >= 60) return bit_count(playerboard)-bit_count(oppenentboard);
    if(nowIndex+DEPTH >= 44) return 2*score_stone(playerboard, oppenentboard)+55*score_fixedstone(playerboard, oppenentboard);
    return 2*score_stone(playerboard, oppenentboard)+5*score_fixedstone(playerboard, oppenentboard)/*+score_putable(playerboard, oppenentboard)*/;
}
