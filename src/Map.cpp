#include <Map.hpp>

#include <fstream>
#include <cassert>

#include <resources.hpp>
#include <log.hpp>


const char hallway_marker = '#';
const char empty_marker = ' ';
const char sentinel = '.';
const char goal = 'G';
const char puzzle_floor = 'g';
const char start = 'S';
const char hole = 'H';
const char end = 'E';

MapCell::MapCell() : type(EMPTY) {
}

MapCell::~MapCell() {
}

Map::Map(uint c, uint r) : grid(boost::extents[c][r]),
                           columns(c),
                           rows(r) {

}

Map::~Map() {
    
}

void Map::initWalls() {
    for (int col = 0; col < columns; col++) {
        for (int row = 0; row < rows; row++) {
            MapCell &current = grid[col][row];
            if (current.type != EMPTY) {
                continue;
            }
            
            if (col != 0) {
                MapCell &left = grid[col-1][row];
                if (left.type != EMPTY && left.type != WALL) {
                    current.type = WALL;
                    current.name = "WALL";
                }
            }
            if (row != 0) {
                MapCell &up = grid[col][row-1];
                if (up.type != EMPTY && up.type != WALL) {
                    current.type = WALL;
                    current.name = "WALL";
                }
            }
            if (col != columns - 1) {
                MapCell &right = grid[col+1][row];
                if (right.type != EMPTY && right.type != WALL) {
                    current.type = WALL;
                    current.name = "WALL";
                }
            }
            if (row != rows - 1) {
                MapCell &down = grid[col][row+1];
                if (down.type != EMPTY && down.type != WALL) {
                    current.type = WALL;
                    current.name = "WALL";
                }
            }
        }
    }
}

static const uint32_t RED_SHIFT    = 16;
static const uint32_t GREEN_SHIFT  = 8;
static const uint32_t BLUE_SHIFT   = 0;

static const uint32_t COLOR_ROOM_FLOOR   = 0x0000FF;
static const uint32_t COLOR_BIG_LIGHT    = 0xFFFF00;
static const uint32_t COLOR_SMALL_LIGHT  = 0x00FFFF;
static const uint32_t COLOR_BOSS_FLOOR   = 0xFF0000;
static const uint32_t COLOR_START_POS    = 0x00FF00;
static const uint32_t COLOR_CORRIDOR     = 0x808080;
static const uint32_t COLOR_EMPTY        = 0xFFFFFF;

int Map::loadMapFromImage(const char *filename)
{
    FIBITMAP *img = resource::GenericLoader(filename, 0);
    uint bpp = FreeImage_GetBPP(img);
//    BYTE *data = FreeImage_GetBits(img);

    uint width = FreeImage_GetWidth(img);
    uint height = FreeImage_GetHeight(img);
    uint pitch = FreeImage_GetPitch(img);
    uint line = FreeImage_GetLine(img); // Line means "width measured in bytes"
    uint bytespp = line / width;

    FREE_IMAGE_TYPE imgtype = FreeImage_GetImageType(img);

    if (bpp < 24) {
        ERROR("Map file bit depth < 24: " << bpp);
        exit(-1);
    }

    if (imgtype != FIT_BITMAP) {
        ERROR("Map file is not bitmap!");
        exit(-1);
    }
    
    
    for (uint y = 0; y < height; y++) {\
        BYTE *bits = FreeImage_GetScanLine(img, y);
        for (uint x = 0; x < width; x++) {
            uint32_t pixel = 0;
            pixel |= (bits[FI_RGBA_RED] << RED_SHIFT);
            pixel |= (bits[FI_RGBA_GREEN] << GREEN_SHIFT);
            pixel |= (bits[FI_RGBA_BLUE] << BLUE_SHIFT);
            bits += bytespp;

            switch (pixel) {
            case COLOR_EMPTY: // Nothing to do
                break;
            case COLOR_ROOM_FLOOR:
                grid[x][y].type = HALLWAY;
                grid[x][y].name = "HALLWAY";
                break;
            case COLOR_BIG_LIGHT:
                grid[x][y].type = HALLWAY;
                grid[x][y].name = "HALLWAY";
                break;
            case COLOR_SMALL_LIGHT:
                grid[x][y].type = HALLWAY;
                grid[x][y].name = "HALLWAY";
                break;
            case COLOR_BOSS_FLOOR:
                grid[x][y].type = HALLWAY;
                grid[x][y].name = "HALLWAY";
                break;
            case COLOR_START_POS:
                grid[x][y].type = HALLWAY;
                grid[x][y].name = "HALLWAY";
                break;
            case COLOR_CORRIDOR:
                grid[x][y].type = HALLWAY;
                grid[x][y].name = "HALLWAY";
                break;
            default:
                ERROR("Pixel value not from accepted set " << std::hex << pixel);
                assert(0 && __FILE__ && __LINE__);
            }
        }
    }

    initWalls();
}

int Map::loadMapFromFile(std::string filename) {
    std::ifstream mapfile;
    mapfile.open(filename.c_str());
    
    if (!mapfile) {
        return -1;
    }
    
    bool done = false;
    int row = 0;
    while (mapfile && !done) {
        std::string line;
        std::getline(mapfile, line);
        std::cout << row << std::endl;
        
        for (int col = 0; col < columns && !done; col++) {
//            std::cout << col << " ";
            switch (line.at(col)) {
            case hallway_marker:
                grid[col][row].type = HALLWAY;
                grid[col][row].name = "HALLWAY";
                break;
            case goal:
                grid[col][row].type = HALLWAY;
                grid[col][row].name = "HALLWAY";
                break;
            case puzzle_floor:
                grid[col][row].type = HALLWAY;
                grid[col][row].name = "HALLWAY";
                break;
             case start:
                grid[col][row].type = HALLWAY;
                grid[col][row].name = "HALLWAY";
                break;
            case hole:
                grid[col][row].type = HALLWAY;
                grid[col][row].name = "HALLWAY";
                break;
            case end:
                grid[col][row].type = END;
                grid[col][row].name = "END";
                break;
            case empty_marker:
                break;
            case sentinel:
                done = true;
                break;
            default:
                break;
//               assert(0 && __FILE__ && __LINE__);
            }
        }
        row++;
    }

    initWalls();
    
    return 0;
}

CellType Map::getTypeForCell(uint col, uint row) const {
    return grid[col][row].type;
}

Entity *Map::getMapComponentForCell(uint col, uint row) const {
    return grid[col][row].component.get();
}

Neighbors Map::getNearbyWalls(uint col, uint row) const {
    Neighbors walls;
    if (col < 0 || col >= columns || row < 0 || row >= rows) {
        return walls;
    }
    
    if (col > 0) {
        const MapCell &cell = grid[col-1][row];
        if (cell.type == WALL) {
            walls.left = cell.component.get();
        }
    }

    if (row > 0) {
        const MapCell &cell = grid[col][row-1];
        if (cell.type == WALL) {
            walls.up = cell.component.get();
        }

    }

    if (col < columns - 1) {
        const MapCell &cell = grid[col+1][row];
        if (cell.type == WALL) {
            walls.right = cell.component.get();
        }
    }

    if (row < rows - 1) {
        const MapCell &cell = grid[col][row+1];
        if (cell.type == WALL) {
            walls.down = cell.component.get();
        }

    }

    return walls;
}


uint Map::getColumns() const {
    return columns;
}
uint Map::getRows() const {
    return rows;
}

MapCell& Map::get(uint col, uint row) {
    return grid[col][row];
}

const MapCell& Map::cget(uint col, uint row) const {
    return grid[col][row];
}
