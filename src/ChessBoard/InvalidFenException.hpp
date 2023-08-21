//
// Created by Skyler Arnold on 8/20/23.
//

#ifndef YACHE_INVALIDFENEXCEPTION_HPP
#define YACHE_INVALIDFENEXCEPTION_HPP

#include <exception>
#include <string>

class InvalidFenException : public std::exception {
public:
    std::string fen;

    InvalidFenException(std::string fen) {
        this->fen = fen;
    }
};


#endif //YACHE_INVALIDFENEXCEPTION_HPP
