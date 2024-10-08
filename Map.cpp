#include "Map.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <queue>
#include <random>

using namespace godot;

void Map::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("movementPlayer1", "start", "goal"), &Map::movementPlayer1);
}

void Map::_ready()
{
    ground_tile_map = Object::cast_to<TileMap>(find_child("Ground"));
    if (!ground_tile_map) {
        UtilityFunctions::print("Ground TileMap node not found!");
        return;
    }

    Vector2i map_size = ground_tile_map->get_used_rect().size;
    if (map_size.x <= 0 || map_size.y <= 0) {
        UtilityFunctions::print("Invalid map size!");
        return;
    }
    adjacency_matrix.resize(map_size.x, std::vector<int>(map_size.y, -1));
    fill_adjacency_matrix();
}

void Map::fill_adjacency_matrix()
{
    Rect2i used_area = ground_tile_map->get_used_rect();
    for (int x = used_area.position.x; x < used_area.position.x + used_area.size.x; ++x) {
        for (int y = used_area.position.y; y < used_area.position.y + used_area.size.y; ++y) {
            if (x < 0 || x >= adjacency_matrix.size() || y < 0 || y >= adjacency_matrix[x].size()) {
                continue;
            }
            Vector2i cell_position(x, y);
            int tile_id = ground_tile_map->get_cell_source_id(0, cell_position);
            adjacency_matrix[x][y] = (tile_id != -1) ? tile_id : -1;
        }
    }
    print_adjacency_matrix();
}

void Map::print_adjacency_matrix()
{
    for (int x = 0; x < adjacency_matrix.size(); ++x) {
        String row;
        for (int y = 0; y < adjacency_matrix[x].size(); ++y) {
            row += String::num_int64(adjacency_matrix[x][y]) + " ";
        }
        UtilityFunctions::print(row);
    }
}

bool Map::is_valid_position(const Vector2i& pos)
{
    Vector2i scaled_pos = pos / 128;
    return scaled_pos.x >= 0 && scaled_pos.x < adjacency_matrix.size() &&
        scaled_pos.y >= 0 && scaled_pos.y < adjacency_matrix[0].size() &&
        adjacency_matrix[scaled_pos.x][scaled_pos.y] != -1;
}

TypedArray<Vector2i> Map::bfsPath(const Vector2i& start, const Vector2i& goal)
{
    TypedArray<Vector2i> path;
    Vector2i start_tile = start / 128;
    Vector2i goal_tile = goal / 128;
    UtilityFunctions::print("Posición inicial BFS (en tiles): ", start_tile);
    UtilityFunctions::print("Posición objetivo BFS (en tiles): ", goal_tile);
    UtilityFunctions::print("Posición inicial en píxeles: ", start);
    UtilityFunctions::print("Posición inicial en tiles: ", start_tile);
    UtilityFunctions::print("Posición objetivo en píxeles: ", goal);
    UtilityFunctions::print("Posición objetivo en tiles: ", goal_tile);
    if (!is_valid_position(start_tile)) {
        UtilityFunctions::print("Posición inicial no válida.");
        return path;
    }
    if (!is_valid_position(goal_tile)) {
        UtilityFunctions::print("Posición objetivo no válida.");
        return path;
    }
    std::queue<Vector2i> queue;
    std::unordered_map<Vector2i, Vector2i, Vector2iHash> came_from;
    queue.push(start_tile);
    came_from[start_tile] = start_tile;
    std::vector<Vector2i> directions = { Vector2i(1, 0), Vector2i(-1, 0), Vector2i(0, 1), Vector2i(0, -1) };
    while (!queue.empty()) {
        Vector2i current = queue.front();
        queue.pop();
        if (current == goal_tile) {
            while (current != start_tile) {
                path.push_back(current * 128);
                current = came_from[current];
            }
            path.push_back(start * 128);
            UtilityFunctions::print("Camino encontrado.");
            return path;
        }
        for (const auto& dir : directions) {
            Vector2i neighbor = current + dir;
            if (is_valid_position(neighbor) && came_from.find(neighbor) == came_from.end()) {
                queue.push(neighbor);
                came_from[neighbor] = current;
            }
        }
    }
    UtilityFunctions::print("No se encontró camino en BFS.");
    return path;
}

Vector2i Map::randomMovement(const Vector2i& start)
{
    Vector2i scaled_start = start / 128;
    std::vector<Vector2i> directions = { Vector2i(1, 0), Vector2i(-1, 0), Vector2i(0, 1), Vector2i(0, -1) };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, directions.size() - 1);

    UtilityFunctions::print("Posición inicial: ", scaled_start);

    for (int i = 0; i < 4; ++i) {
        Vector2i new_pos = scaled_start + directions[dis(gen)];
        UtilityFunctions::print("Intentando mover a la nueva posición: ", new_pos);

        if (is_valid_position(new_pos * 128)) {
            UtilityFunctions::print("Nueva posición válida encontrada: ", new_pos);
            return new_pos * 128;
        }
        else {
            UtilityFunctions::print("Nueva posición inválida: ", new_pos);
        }
    }

    UtilityFunctions::print("No se encontró una posición válida. Manteniendo la posición actual: ", start);
    return start;
}

TypedArray<Vector2i> Map::movementPlayer1(const Vector2i& start, const Vector2i& goal)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    if (dis(gen) == 0) {
        UtilityFunctions::print("Using BFS");
        return bfsPath(start, goal);
    }
    else {
        UtilityFunctions::print("Using Random Movement");
        return { randomMovement(start) };
    }
}
