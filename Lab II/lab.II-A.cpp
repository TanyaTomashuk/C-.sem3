#include <iostream>
#include <cstddef>
#include <cstring>

class Grid {
private:
    float* memory;
    size_t x_size, y_size;

    float const* get_line(size_t y_idx) const
    {
        return memory + y_idx * x_size;
    }

    float* get_line(size_t y_idx)
    {
        return memory + y_idx * x_size;
    }

public:
    Grid(size_t x_size, size_t y_size) :
        x_size(x_size),
        y_size(y_size),
        memory(new float[x_size * y_size])
    {
        memset(memory, 0, sizeof(float) * x_size * y_size);
    }


    float operator()(size_t x_idx, size_t y_idx) const
    {
        return get_line(y_idx)[x_idx];
    }

    float& operator()(size_t x_idx, size_t y_idx)
    {
        return get_line(y_idx)[x_idx];
    }

    size_t get_xsize() const {
        return x_size;
    }

    size_t get_ysize() const {
        return y_size;
    }

    Grid& operator=(float value) {
        for (size_t i = 0; i != x_size * y_size; i++)
            memory[i] = value;
    }

    friend std::ostream& operator<<(std::ostream&, Grid const&);
    friend std::istream& operator>>(std::istream&, Grid&);

    ~Grid() {
        delete[] memory;
    }
};

std::ostream& operator<<(std::ostream& stream, Grid const& grid) {
    for (size_t x = 0; x < grid.x_size; x++)
        for (size_t y = 0; y < grid.y_size; y++)
            stream << grid(x, y) << " ";

    return stream;
}

std::istream& operator>>(std::istream& stream, Grid& grid) {
    for (size_t x = 0; x < grid.x_size; x++)
        for (size_t y = 0; y < grid.y_size; y++)
            stream >> grid(x, y);

    return stream;
}
