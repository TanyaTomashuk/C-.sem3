class Piece {
    public:
        char v;
        unsigned short int h;
        virtual bool available(Cell& x){
            return true;
        }
};

unsigned short int convert(char v){
    switch(v){
        case 'A':
            return 1;
        case 'B':
            return 2;
        case 'C':
            return 3;
        case 'D':
            return 4;
        case 'E':
            return 5;
        case 'F':
            return 6;
        case 'G':
            return 7;
        case 'H':
            return 8;
    }
    return 0;
}

class King: public Piece {
    public:
        King(const Cell cell){
            h = cell.h;
            v = cell.v;
        }
        bool available(Cell& cell){
            unsigned short int x = cell.h;
            unsigned short int y = convert(cell.v);
            unsigned short int x_fig = h;
            unsigned short int y_fig = convert(v);
            if ((-1 <= (x_fig - x) <= 1) && (-1 <= (y_fig - y) <= 1) &&
             (((x_fig - x)*(x_fig - x) + (y_fig - y)*(y_fig - y)) != 0)){
                return true;
            }
            return false;
        }
};

class Bishop: public Piece {
    public:
        Bishop(const Cell cell){
            h = cell.h;
            v = cell.v;
        }
        bool available(Cell& cell){
            unsigned short int x = cell.h;
            unsigned short int y = convert(cell.v);
            unsigned short int x_fig = h;
            unsigned short int y_fig = convert(v);
            if (((x_fig - x) == (y_fig - y)) || ((x_fig - x) == (y - y_fig))){
                return true;
            }
            return false;
        }
};

class Rook: public Piece {
    public:
        Rook(const Cell cell){
            h = cell.h;
            v = cell.v;
        }
        bool available(Cell& cell){
            unsigned short int x = cell.h;
            unsigned short int y = convert(cell.v);
            unsigned short int x_fig = h;
            unsigned short int y_fig = convert(v);
            if ((x_fig == x) || (y_fig == y)){
                return true;
            }
            return false;
        }
};

class Queen: public Piece {
    public:
        Queen(const Cell cell){
            h = cell.h;
            v = cell.v;
        }
        bool available(Cell& cell){
            unsigned short int x = cell.h;
            unsigned short int y = convert(cell.v);
            unsigned short int x_fig = h;
            unsigned short int y_fig = convert(v);
            if (((x_fig == x) || (y_fig == y)) || (((x_fig - x) == (y_fig - y)) || ((x_fig - x) == (y - y_fig)))){
                return true;
            }
            return false;
        }
};
