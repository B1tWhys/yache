//
// Created by Skyler Arnold on 8/20/23.
//

#ifndef YACHE_SQUARESTATE_HPP
#define YACHE_SQUARESTATE_HPP

#define OCCUPIED (1 << 7)
#define WHITE_PIECE (1 << 6)

enum SquareState: unsigned char {
    EMPTY = 0,
    WHITE_PAWN                  = WHITE_PIECE | OCCUPIED + 1,
    WHITE_EN_PASSANT_TARGET     = WHITE_PIECE + 2,
    WHITE_ROOK                  = WHITE_PIECE | OCCUPIED + 3,
    WHITE_KNIGHT                = WHITE_PIECE | OCCUPIED + 4,
    WHITE_BISHOP                = WHITE_PIECE | OCCUPIED + 5,
    WHITE_KING                  = WHITE_PIECE | OCCUPIED + 6,
    WHITE_QUEEN                 = WHITE_PIECE | OCCUPIED + 7,

    BLACK_PAWN                  = OCCUPIED + 1,
    BLACK_EN_PASSANT_TARGET     = 2,
    BLACK_ROOK                  = OCCUPIED + 3,
    BLACK_KNIGHT                = OCCUPIED + 4,
    BLACK_BISHOP                = OCCUPIED + 5,
    BLACK_KING                  = OCCUPIED + 6,
    BLACK_QUEEN                 = OCCUPIED + 7,
};


#endif //YACHE_SQUARESTATE_HPP
