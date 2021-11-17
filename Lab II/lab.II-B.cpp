#include <iostream>
#include <cstddef>
#include <cstring>

class Grid {
private:
    float* memory;
    size_t x_size, y_size;

    size_t get_index(size_t x_idx, size_t y_idx) const {
        return y_idx * x_size + x_idx;
    }

    float const* get_line(size_t y_idx) const {
        return memory + get_index(0, y_idx);
    }

    float* get_line(size_t y_idx) {
        return memory + get_index(0, y_idx);
    }

    float get_mean() {
        float res = 0;
        for (int i = 0; i != x_size * y_size; i++)
            res += grid_memory[i] ? grid_memory[i]->get_mean() : memory[i];
        
        return res / (float)(x_size * y_size);
    }

public:
    // Class management
    Grid(size_t x_size, size_t y_size) :
        x_size(x_size),
        y_size(y_size),
        memory(new float[x_size * y_size]),
        grid_memory(new Grid* [x_size * y_size])
    {
        memset(memory, 0, sizeof(float) * x_size * y_size);
        memset(grid_memory, 0, sizeof(Grid*) * x_size * y_size);
    }
    
    Grid& operator=(Grid const& grid) {
        free_grid_memory();
        memcpy(memory, grid.memory, x_size * y_size * sizeof(float));

        for (size_t i = 0; i != x_size * y_size; i++)
            if (grid.grid_memory[i])
                grid_memory[i] = new Grid(*grid.grid_memory[i]);
        
        return *this;
    }

    Grid(Grid const& grid) : 
        Grid(grid.x_size, grid.y_size)
    {
        *this = grid;
    }

    Grid& operator=(Grid&& grid) {
        std::swap(x_size, grid.x_size);
        std::swap(y_size, grid.y_size);
        std::swap(memory, grid.memory);
        std::swap(grid_memory, grid.grid_memory);

        return *this;
    }

    Grid(Grid&& grid) : 
        x_size(0),
        y_size(0),
        memory(nullptr),
        grid_memory(nullptr)
    {
        *this = grid;
    }

    ~Grid() {
        delete[] memory;
        free_grid_memory();
        delete[] grid_memory;
    }


    float operator()(size_t x_idx, size_t y_idx) const
    {
        if (is_subrid(x_idx, y_idx))
            return grid_memory[get_index(x_idx, y_idx)]->get_mean();

        return get_line(y_idx)[x_idx];
    }

    float& operator()(size_t x_idx, size_t y_idx)
    {
        if (is_subrid(x_idx, y_idx))
            get_line(y_idx)[x_idx] = grid_memory[get_index(x_idx, y_idx)]->get_mean();

        return get_line(y_idx)[x_idx]; // what to do if there is a sub grid?
    }

    size_t get_xsize() const {
        return x_size;
    }

    size_t get_ysize() const {
        return y_size;
    }

    Grid& operator=(float value) {
        free_grid_memory();
        for (size_t i = 0; i != x_size * y_size; i++)
            memory[i] = value;

        return *this;
    }

    // Subgrid

private:
    Grid** grid_memory;
    float special_position = 0;

    void free_grid_memory() {
        if (grid_memory == nullptr)
            return;
            
        for (int i = 0; i != x_size * y_size; i++)
            if (grid_memory[i]) {
                delete grid_memory[i];
                grid_memory[i] = nullptr;
            }
    }

public:
    Grid& make_subgrid(
        size_t x_idx, size_t y_idx,
        size_t x_sub_size, size_t y_sub_size)
    {
        collapse_subgrid(x_idx, y_idx, x_sub_size, y_sub_size); // collapse_subgrid ignores last 2 parameters
        grid_memory[get_index(x_idx, y_idx)] = new Grid(x_sub_size, y_sub_size);

        return *this;
    }

    Grid& collapse_subgrid(
        size_t x_idx, size_t y_idx,
        size_t x_sub_size, size_t y_sub_size)
    {
        if (is_subrid(x_idx, y_idx))
        {
            float mean = grid_memory[get_index(x_idx, y_idx)]->get_mean();
            delete grid_memory[get_index(x_idx, y_idx)];
            memory[get_index(x_idx, y_idx)] = mean;
            grid_memory[get_index(x_idx, y_idx)] = nullptr;
        }

        return *this;
    }

    Grid& get_subgrid(size_t x_idx, size_t y_idx) {
        return *grid_memory[get_index(x_idx, y_idx)];
    }

    Grid const& get_subgrid(size_t x_idx, size_t y_idx) const {
        return *grid_memory[get_index(x_idx, y_idx)];
    }

    bool is_subrid(size_t x_idx, size_t y_idx) const { // called as in the origin --- mb should be called "is_subgrid"????
        return (bool)grid_memory[get_index(x_idx, y_idx)];
    }

    friend std::ostream& operator<<(std::ostream&, Grid const&);
    friend std::istream& operator>>(std::istream&, Grid&);
};

std::ostream& operator<<(std::ostream& stream, Grid const& grid) {
    for (size_t y = 0; y < grid.y_size; y++) {
        for (size_t x = 0; x < grid.x_size; x++) {
            if (grid.is_subrid(x, y))
            {
                stream << "(" << grid.get_subgrid(x, y) << ")" << " ";
            }
            else
                stream << grid(x, y) << " ";
        }

        stream << "\n";
    }

    return stream;
}

std::istream& operator>>(std::istream& stream, Grid& grid) {
    grid.free_grid_memory();
    for (size_t y = 0; y < grid.y_size; y++)
        for (size_t x = 0; x < grid.x_size; x++)
            stream >> grid(x, y);

    return stream;
}

int main()
{
    Grid grid(3, 3);
    std::cin >> grid;

    std::cout << grid.is_subrid(0, 0) << "\n";

    grid.make_subgrid(0, 0, 2, 2).get_subgrid(0, 0).make_subgrid(0, 0, 2, 2);

    std::cout << grid.is_subrid(0, 0) << "\n";

    // grid = 0.6;
    std::cout << grid;
    Grid aGrid(1, 1);
    aGrid.make_subgrid(0, 0, 3, 3).get_subgrid(0, 0) = grid;
    std::cout << aGrid;
    std::cout << aGrid(0, 0);
}
