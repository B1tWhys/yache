#ifndef _YACHE_CB_COORDINATE
#define _YACHE_CB_COORDINATE

#include <iostream>
using namespace std;

class Coordinate {
public:
    Coordinate(unsigned char rank, unsigned char file);
    explicit Coordinate(const std::string &notation);
    explicit Coordinate(unsigned char cords);
    unsigned char getRank() const;
    unsigned char getFile() const;
    bool isValidSquare() const;
    unsigned char cords;
    bool operator==(const Coordinate other) const;

    friend ostream &operator<<(ostream &output, const Coordinate &coordinate) {
        output << (char)(coordinate.getFile() + 'a') << (char)(coordinate.getRank() + '1');
        return output;
    }
};

#endif
