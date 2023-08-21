#include "ChessBoard.hpp"
#include "SquareState.hpp"
#include "InvalidFenException.hpp"
#include <regex>
#include "CastlingPrivilege.hpp"

using namespace std;

ChessBoard::ChessBoard(const string &fen) {
    const basic_regex<char> fenRegex =
            regex(R"#(([rnbqkpRNBQKP\d]+)/([rnbqkpRNBQKP\d]+)/([rnbqkpRNBQKP\d]+)/([rnbqkpRNBQKP\d]+)/([rnbqkpRNBQKP\d]+)/([rnbqkpRNBQKP\d]+)/([rnbqkpRNBQKP\d]+)/([rnbqkpRNBQKP\d ]+) ([wb]) (-|\w+) (-|\w\d))#");
    smatch match;
    if (!regex_match(fen, match, fenRegex)) {
        throw InvalidFenException(fen);
    }
    for (int group = 0; group < 8; group++) {
        int rank = 7 - group;
        string fenChars = match.str(group + 1);
        int file = 0;
        for (char &ch: fenChars) {
            if (ch >= '0' && ch <= '9') { // it's a number
                int intVal = ch - '0';
                file += intVal;
            } else {
                SquareState *square = &board[rank][file];
                switch (ch) {
                    case 'P':
                        *square = WHITE_PAWN;
                        break;
                    case 'R':
                        *square = WHITE_ROOK;
                        break;
                    case 'N':
                        *square = WHITE_KNIGHT;
                        break;
                    case 'B':
                        *square = WHITE_BISHOP;
                        break;
                    case 'K':
                        *square = WHITE_KING;
                        break;
                    case 'Q':
                        *square = WHITE_QUEEN;
                        break;

                    case 'p':
                        *square = BLACK_PAWN;
                        break;
                    case 'r':
                        *square = BLACK_ROOK;
                        break;
                    case 'n':
                        *square = BLACK_KNIGHT;
                        break;
                    case 'b':
                        *square = BLACK_BISHOP;
                        break;
                    case 'k':
                        *square = BLACK_KING;
                        break;
                    case 'q':
                        *square = BLACK_QUEEN;
                        break;
                    default:
                        throw InvalidFenException(fen);
                }
                file++;
            }
        }
    }

    isWhiteTurn = match.str(9)[0] == 'w';

    string enPassantTarget = match.str(11);
    if (enPassantTarget != "-") {
        unsigned char file = enPassantTarget[0];
        unsigned char rank = enPassantTarget[1];
        int fileIdx = file - 'a';
        int rankIdx = rank - '0' - 1;

        board[rankIdx][fileIdx] = isWhiteTurn ? WHITE_EN_PASSANT_TARGET : BLACK_EN_PASSANT_TARGET;
    }

    castlingPrivileges = 0;
    string castlingFen = match.str(10);
    if (castlingFen.find('K') != string::npos) castlingPrivileges |= WHITE_KING_SIDE;
    if (castlingFen.find('Q') != string::npos) castlingPrivileges |= WHITE_QUEEN_SIDE;
    if (castlingFen.find('k') != string::npos) castlingPrivileges |= BLACK_KING_SIDE;
    if (castlingFen.find('q') != string::npos) castlingPrivileges |= BLACK_QUEEN_SIDE;

}

ChessBoard::~ChessBoard() = default;

bool ChessBoard::squareIsOccupied(Coordinate coordinate) {
    return board[coordinate.rank][coordinate.file] != EMPTY;
}

SquareState ChessBoard::squareState(Coordinate coordinate) {
    return board[coordinate.rank][coordinate.file];
}

string ChessBoard::boardString() {
    string result = string();
    result.append("| |a|b|c|d|e|f|g|h|\n");
    result.append("|-|-|-|-|-|-|-|-|-|\n");
    for (int rank = 7; rank >= 0; rank--) {
        char buf[21];
        snprintf(buf,
                 sizeof(buf),
                 "|%d|%c|%c|%c|%c|%c|%c|%c|%c|\n",
                 rank + 1,
                 squareToAsciiPiece({.rank = rank, .file = 0}),
                 squareToAsciiPiece({.rank = rank, .file = 1}),
                 squareToAsciiPiece({.rank = rank, .file = 2}),
                 squareToAsciiPiece({.rank = rank, .file = 3}),
                 squareToAsciiPiece({.rank = rank, .file = 4}),
                 squareToAsciiPiece({.rank = rank, .file = 5}),
                 squareToAsciiPiece({.rank = rank, .file = 6}),
                 squareToAsciiPiece({.rank = rank, .file = 7}));
        result.append(buf);
    }
    return result;
}

unsigned char ChessBoard::squareToAsciiPiece(Coordinate coordinate) {
    switch (this->squareState(coordinate)) {
        case EMPTY:
            return ' ';
        case WHITE_PAWN:
            return 'P';
        case WHITE_EN_PASSANT_TARGET:
            return ' ';
        case WHITE_ROOK:
            return 'R';
        case WHITE_KNIGHT:
            return 'N';
        case WHITE_BISHOP:
            return 'B';
        case WHITE_KING:
            return 'K';
        case WHITE_QUEEN:
            return 'Q';

        case BLACK_PAWN:
            return 'p';
        case BLACK_EN_PASSANT_TARGET:
            return ' ';
        case BLACK_ROOK:
            return 'r';
        case BLACK_KNIGHT:
            return 'n';
        case BLACK_BISHOP:
            return 'b';
        case BLACK_KING:
            return 'k';
        case BLACK_QUEEN:
            return 'q';
    }
}
