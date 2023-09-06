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

bool ChessBoard::squareIsOccupied(Coordinate coordinate) const {
    return board[coordinate.getRank()][coordinate.getFile()] != EMPTY;
}

SquareState ChessBoard::squareState(Coordinate coordinate) const {
    return board[coordinate.getRank()][coordinate.getFile()];
}

string ChessBoard::boardString() const {
    string result = string();
    result.append("| |a|b|c|d|e|f|g|h|\n");
    result.append("|-|-|-|-|-|-|-|-|-|\n");
    for (int rank = 7; rank >= 0; rank--) {
        char buf[21];
        snprintf(buf,
                 sizeof(buf),
                 "|%d|%c|%c|%c|%c|%c|%c|%c|%c|\n",
                 rank + 1,
                 squareToAsciiPiece(Coordinate(rank, 0)),
                 squareToAsciiPiece(Coordinate(rank, 1)),
                 squareToAsciiPiece(Coordinate(rank, 2)),
                 squareToAsciiPiece(Coordinate(rank, 3)),
                 squareToAsciiPiece(Coordinate(rank, 4)),
                 squareToAsciiPiece(Coordinate(rank, 5)),
                 squareToAsciiPiece(Coordinate(rank, 6)),
                 squareToAsciiPiece(Coordinate(rank, 7)));
        result.append(buf);
    }
    return result;
}

unsigned char ChessBoard::squareToAsciiPiece(Coordinate coordinate) const {
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

std::vector<Move> ChessBoard::pseudoLegalMoves() const {
    std::vector<Move> moves;

    for (char rank = 0; rank < 8; rank++) {
        for (char file = 0; file < 8; file++) {
            const Coordinate coordinate = Coordinate(rank, file);
            SquareState squareState = this->squareState(coordinate);
            switch (squareState) {
                case EMPTY:
                    break;
                case WHITE_PAWN:
                    if (isWhiteTurn) this->addWhitePawnMovesFrom(coordinate, &moves);
                    break;
                case WHITE_EN_PASSANT_TARGET:
                    break;
                case WHITE_ROOK:
                    if (isWhiteTurn) this->addWhiteRookMovesFrom(coordinate, &moves);
                    break;
                case WHITE_KNIGHT:
                    if (isWhiteTurn) this->addKnightMovesFrom(coordinate, &moves);
                    break;
                case WHITE_BISHOP:
                    break;
                case WHITE_KING:
                    break;
                case WHITE_QUEEN:
                    break;
                case BLACK_PAWN:
                    if (!isWhiteTurn) this->addBlackPawnMovesFrom(coordinate, &moves);
                    break;
                case BLACK_EN_PASSANT_TARGET:
                    break;
                case BLACK_ROOK:
                    if (!isWhiteTurn) this->addBlackRookMovesFrom(coordinate, &moves);
                    break;
                case BLACK_KNIGHT:
                    if (!isWhiteTurn) this->addKnightMovesFrom(coordinate, &moves);
                    break;
                case BLACK_BISHOP:
                    break;
                case BLACK_KING:
                    break;
                case BLACK_QUEEN:
                    break;
            }
        }
    }

    return moves;
}

void ChessBoard::addWhitePawnMovesFrom(Coordinate coordinate, std::vector<Move> *moves) const {
    const Coordinate &nextSquare = Coordinate(coordinate.getRank() + 1, coordinate.getFile());
    if (nextSquare.getRank() < 8 && !squareIsOccupied(nextSquare)) {
        moves->emplace_back(coordinate, nextSquare, EMPTY);
        if (coordinate.getRank() == 1) {
            moves->emplace_back(coordinate, Coordinate(coordinate.getRank() + 2, coordinate.getFile()), EMPTY);
        }
    }
}

void ChessBoard::addBlackPawnMovesFrom(Coordinate coordinate, std::vector<Move> *moves) const {
    const Coordinate &nextSquare = Coordinate(coordinate.getRank() - 1, coordinate.getFile());
    if (coordinate.getRank() > 1 && !squareIsOccupied(nextSquare)) {
        moves->emplace_back(coordinate, nextSquare, EMPTY);
        if (coordinate.getRank() == 6) {
            moves->emplace_back(coordinate, Coordinate(coordinate.getRank() - 2, coordinate.getFile()), EMPTY);
        }
    }
}

void ChessBoard::addWhiteRookMovesFrom(Coordinate from, std::vector<Move> *moves) const {
    for (int rank = from.getRank() + 1; rank < 8; rank++) {
        Coordinate target = Coordinate(rank, from.getFile());
        SquareState tgtSquareState = squareState(target);
        if ((tgtSquareState & WHITE_PIECE) && (tgtSquareState & OCCUPIED)) {
            break;
        }
        moves->emplace_back(from, target, tgtSquareState);
        if (tgtSquareState & OCCUPIED) {
            break;
        }
    }

    for (int rank = ((char)from.getRank()) - 1; rank >= 0; rank--) {
        Coordinate target = Coordinate(rank, from.getFile());
        SquareState tgtSquareState = squareState(target);
        if ((tgtSquareState & WHITE_PIECE) && (tgtSquareState & OCCUPIED))
            break;
        moves->emplace_back(from, target, tgtSquareState);
        if (tgtSquareState & OCCUPIED) {
            break;
        }
    }

    for (int file = from.getFile() + 1; file < 8; file++) {
        Coordinate target = Coordinate(from.getRank(), file);
        SquareState tgtSquareState = squareState(target);
        if ((tgtSquareState & WHITE_PIECE) && (tgtSquareState & OCCUPIED))
            break;
        moves->emplace_back(from, target, tgtSquareState);
        if (tgtSquareState & OCCUPIED) {
            break;
        }
    }

    for (int file = ((char)from.getFile()) - 1; file >= 0; file--) {
        Coordinate target = Coordinate(from.getRank(), file);
        SquareState tgtSquareState = squareState(target);
        if ((tgtSquareState & WHITE_PIECE) && (tgtSquareState & OCCUPIED))
            break;
        moves->emplace_back(from, target, tgtSquareState);
        if (tgtSquareState & OCCUPIED) {
            break;
        }
    }
}

void ChessBoard::addBlackRookMovesFrom(Coordinate from, std::vector<Move> *moves) const {
    for (int rank = from.getRank() + 1; rank < 8; rank++) {
        Coordinate target = Coordinate(rank, from.getFile());
        SquareState tgtSquareState = squareState(target);
        if (!(tgtSquareState & WHITE_PIECE) && (tgtSquareState & OCCUPIED)) {
            break;
        }
        moves->emplace_back(from, target, tgtSquareState);
        if (tgtSquareState & OCCUPIED) {
            break;
        }
    }

    for (int rank = ((char)from.getRank()) - 1; rank >= 0; rank--) {
        Coordinate target = Coordinate(rank, from.getFile());
        SquareState tgtSquareState = squareState(target);
        if (!(tgtSquareState & WHITE_PIECE) && (tgtSquareState & OCCUPIED))
            break;
        moves->emplace_back(from, target, tgtSquareState);
        if (tgtSquareState & OCCUPIED) {
            break;
        }
    }

    for (int file = from.getFile() + 1; file < 8; file++) {
        Coordinate target = Coordinate(from.getRank(), file);
        SquareState tgtSquareState = squareState(target);
        if (!(tgtSquareState & WHITE_PIECE) && (tgtSquareState & OCCUPIED))
            break;
        moves->emplace_back(from, target, tgtSquareState);
        if (tgtSquareState & OCCUPIED) {
            break;
        }
    }

    for (int file = ((char)from.getFile()) - 1; file >= 0; file--) {
        Coordinate target = Coordinate(from.getRank(), file);
        SquareState tgtSquareState = squareState(target);
        if (!(tgtSquareState & WHITE_PIECE) && (tgtSquareState & OCCUPIED))
            break;
        moves->emplace_back(from, target, tgtSquareState);
        if (tgtSquareState & OCCUPIED) {
            break;
        }
    }
}



void ChessBoard::addKnightMovesFrom(Coordinate coordinate, std::vector<Move> *moves) const {
    // these are starting from up 2 right 1, moving around clockwise
    Coordinate target = Coordinate(coordinate.getRank() + 2, coordinate.getFile() + 1);
    if (target.isValidSquare()) moves->emplace_back(coordinate, target, EMPTY);
    target = Coordinate(coordinate.getRank() + 1, coordinate.getFile() + 2);
    if (target.isValidSquare()) moves->emplace_back(coordinate, target, EMPTY);
    target = Coordinate(coordinate.getRank() - 1, coordinate.getFile() + 2);
    if (target.isValidSquare()) moves->emplace_back(coordinate, target, EMPTY);
    target = Coordinate(coordinate.getRank() - 2, coordinate.getFile() + 1);
    if (target.isValidSquare()) moves->emplace_back(coordinate, target, EMPTY);
    target = Coordinate(coordinate.getRank() - 2, coordinate.getFile() - 1);
    if (target.isValidSquare()) moves->emplace_back(coordinate, target, EMPTY);
    target = Coordinate(coordinate.getRank() - 1, coordinate.getFile() - 2);
    if (target.isValidSquare()) moves->emplace_back(coordinate, target, EMPTY);
    target = Coordinate(coordinate.getRank() + 1, coordinate.getFile() - 2);
    if (target.isValidSquare()) moves->emplace_back(coordinate, target, EMPTY);
    target = Coordinate(coordinate.getRank() + 2, coordinate.getFile() - 1);
    if (target.isValidSquare()) moves->emplace_back(coordinate, target, EMPTY);
}

void ChessBoard::makeMove(const Move *move) {
    SquareState *toSquare = &board[move->getToCoordinate().getRank()][move->getToCoordinate().getFile()];
    SquareState *fromSquare = &board[move->getFromCoordinate().getRank()][move->getFromCoordinate().getFile()];

    *toSquare = *fromSquare;
    isWhiteTurn = !isWhiteTurn;
}