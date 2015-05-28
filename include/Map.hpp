#ifndef MAP_HPP
#define MAP_HPP

#include <common.hpp>

// define BOOST_DISABLE_ASSERTS in production
#include <boost/multi_array.hpp>
#include <Entity.hpp>

#define MAP_DIM 2



enum CellType {
    HALLWAY,
    WALL,
    EMPTY,
};

struct MapCell {
    CellType type;
    Entity *component;
    MapCell();
    ~MapCell();
};


class Map {
private:
    boost::multi_array<MapCell, MAP_DIM> grid;
    uint columns;
    uint rows;

    void initWalls();

public:
    Map(uint columns, uint rows);
    ~Map();

    int loadMapFromFile(std::string filename);

    CellType getTypeForCell(uint col, uint row) const;
    void setMapComponentForCell(uint col, uint row, Entity *map_component);
    Entity *getMapComponentForCell(uint col, uint row) const;
    std::vector<Entity*> getNearbyWalls(uint col, uint row) const;
    uint getColumns() const;
    uint getRows() const;
};

#undef MAP_DIM // 

#endif
