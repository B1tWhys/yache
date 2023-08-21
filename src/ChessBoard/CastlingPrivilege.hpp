//
// Created by Skyler Arnold on 8/26/23.
//

#ifndef YACHE_CASTLINGPRIVILEGE_HPP
#define YACHE_CASTLINGPRIVILEGE_HPP

enum CastlingPrivilege {
    WHITE_KING_SIDE = 1 << 0,
    WHITE_QUEEN_SIDE = 1 << 1,
    BLACK_KING_SIDE = 1 << 3,
    BLACK_QUEEN_SIDE = 1 << 4
};


#endif //YACHE_CASTLINGPRIVILEGE_HPP
