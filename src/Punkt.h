#ifndef SRC_PUNKT_H
#define SRC_PUNKT_H

class Punkt
{
    public:
        Punkt();
        Punkt(const int X, const int Y);
        int get_x() const;
        int get_y() const;

        bool drinnen(const Punkt A, const Punkt B);

    private:
        int x;
        int y;
};

#endif /* SRC_PUNKT_H_ */