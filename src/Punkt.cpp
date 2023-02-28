#include "Punkt.h"

Punkt::Punkt() : x{0},y{0} {}

Punkt::Punkt(const int X, const int Y) : x{X},y{Y} {}

int Punkt::get_x() const {return x;}

int Punkt::get_y() const {return y;}

bool Punkt::drinnen(const Punkt A, const Punkt B)
{
    bool check = true;
    if (A.get_x() < B.get_x()) {
        if (x < A.get_x() || x > B.get_x()) check = false;
    }
    else {
        if (x < B.get_x() || x > A.get_x()) check = false;
    }
    if (A.get_y() < B.get_y()) {
        if (y < A.get_y() || y > B.get_y()) check = false;
    }
    else{
        if (y < B.get_y() || y > A.get_y()) check = false;
    }
    return check; 
}