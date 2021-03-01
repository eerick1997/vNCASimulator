#include "cellular_automata.h"
#include "QDateTime"
#include "widget_evolution_space.h"
#include <QDebug>
#include <random>
#include <vector>

cellular_automata::cellular_automata(int16_t width, int16_t height,
                                     int8_t survive_min, int8_t survive_max,
                                     int8_t born_min, int8_t born_max,
                                     double scale, bool neighbor_type,
                                     bool space_closed, bool totalistic_rules,
                                     std::vector<int8_t> totalistic_von_neumann)
    : width(width), height(height), survive_min(survive_min),
      survive_max(survive_max), born_min(born_min), born_max(born_max),
      scale(scale), neighbor_type(neighbor_type), space_closed(space_closed),
      totalistic_rules(totalistic_rules),
      totalistic_von_neumann(totalistic_von_neumann) {
  generation = alive_cells = c_alive_cells = 0;
  Polynomial = new polynomial(survive_min, survive_max, born_min, born_max,
                              neighbor_type);

  evolution_space.resize(MAX_SIZE, column(MAX_SIZE, 0));
  aux_space.resize(MAX_SIZE, column(MAX_SIZE, 0));
}

// Getters
int64_t cellular_automata::get_generation() { return generation; }

int16_t cellular_automata::get_width() { return width; }

int16_t cellular_automata::get_height() { return height; }

int32_t cellular_automata::get_alive_cells() { return alive_cells; }

int32_t cellular_automata::get_dead_cells() {
  return (width * height) - alive_cells;
}

int64_t cellular_automata::get_c_alive_cells() { return c_alive_cells; }

int8_t cellular_automata::get_survive_min() { return survive_min; }

int8_t cellular_automata::get_survive_max() { return survive_min; }

int8_t cellular_automata::get_born_min() { return born_min; }

int8_t cellular_automata::get_born_max() { return born_max; }

double cellular_automata::get_entropy() {
  double x = get_density();
  //qDebug() << "gen = " << generation << " p = " << x << " q = " << (1 - x) << " res = " << (x > 0 ? -(x * log2(x) + (1 - x) * log2(1 - x)) : 0)
  return x > 0 ? -(x * log2(x) + (1 - x) * log2(1 - x)) : 0;
}

double cellular_automata::get_average() {
  return generation > 0 ? (double)alive_cells / generation : 0;
}

matrix cellular_automata::get_evolution_space() { return evolution_space; }

bool cellular_automata::get_neighbor_type() { return neighbor_type; }

double cellular_automata::get_scale() { return scale; }

bool cellular_automata::get_is_closed() { return space_closed; }

double cellular_automata::get_density() {
  return (double)alive_cells / (width * height);
}

bool cellular_automata::get_totalistic_rules() { return totalistic_rules; }
// Setters
void cellular_automata::set_generation(int64_t n_generation) {
  generation = n_generation;
}

void cellular_automata::set_width(int16_t n_width) { width = n_width; }

void cellular_automata::set_height(int16_t n_height) { height = n_height; }

void cellular_automata::set_alive_cells(int32_t n_alive_cells) {
  alive_cells = n_alive_cells;
}

void cellular_automata::set_c_alive_cells(int64_t n_c_alive_cells) {
  c_alive_cells = n_c_alive_cells;
}

void cellular_automata::set_evolution_space(matrix n_evolution_space) {
  evolution_space = aux_space = n_evolution_space;
}

void cellular_automata::set_survive_min(int8_t n_survive_min) {
  survive_min = n_survive_min;
  Polynomial->set_s_min(n_survive_min);
}

void cellular_automata::set_survive_max(int8_t n_survive_max) {
  survive_max = n_survive_max;
  Polynomial->set_s_max(n_survive_max);
}

void cellular_automata::set_born_min(int8_t n_born_min) {
  born_min = n_born_min;
  Polynomial->set_b_min(n_born_min);
}

void cellular_automata::set_born_max(int8_t n_born_max) {
  born_max = n_born_max;
  Polynomial->set_b_max(n_born_max);
}

void cellular_automata::set_neighbor_type(bool new_type) {
  neighbor_type = new_type;
  Polynomial->set_n(new_type == MOORE ? MOORE_NEIGHBOR : VON_NEUMANN_NEIGHBOR);
}

void cellular_automata::set_scale(double new_scale) { scale = new_scale; }

void cellular_automata::set_space_closed(bool state) { space_closed = state; }

void cellular_automata::set_totalistic_rules(bool totalistic) {
  totalistic_rules = totalistic;
}

// Own methods
void cellular_automata::next_generation() {
  generation++;
  if (totalistic_rules)
    next_generation_totalistic();
  else
    next_generation_semitotalistic();
}

void cellular_automata::next_generation_totalistic() {
  int32_t c_width = width, c_height = height;
  int8_t bitmask = 0;
  alive_cells = 0;
  for (int32_t x = 0; x < c_width; x++) {
    for (int32_t y = 0; y < c_height; y++) {
      if (x < (c_width * scale) and y >= (c_height * (1 - scale))) {
        bitmask = get_alive_neighbors_totalistic(x, y);
        if (totalistic_von_neumann[bitmask] > 0) {
          if (evolution_space[x][y] > 0) {
            if (evolution_space[x][y] < limit_ttl)
              aux_space[x][y] = evolution_space[x][y] + increment;
          } else
            aux_space[x][y] = 1;
          alive_cells++;
        } else
          aux_space[x][y] = 0;
      }
    }
  }
  c_alive_cells += alive_cells;
  swap(aux_space, evolution_space);
}

int8_t cellular_automata::get_alive_neighbors_totalistic(int32_t x, int32_t y) {
  int8_t bitmask = 0;
  int32_t x_position, y_position;
  for (int i = 0; i < 5; i++) {
    x_position = get_x_position(x + coordinates[i][0]);
    y_position = get_y_position(y + coordinates[i][1]);
    if (x_position < 0 or y_position < 0)
      continue;
    bitmask |= ((evolution_space[x_position][y_position] > 0) << i);
  }
  return bitmask;
}

void cellular_automata::next_generation_semitotalistic() {
  int32_t c_width = width, c_height = height;
  alive_cells = 0;
  int16_t neighbors = 0;
  for (int32_t x = 0; x < c_width; x++) {
    for (int32_t y = 0; y < c_height; y++) {
      int32_t &c_cell = evolution_space[x][y], &c_new_cell = aux_space[x][y];
      if (x < (c_width * scale) and y >= (c_height * (1 - scale))) {
        neighbors = neighbor_type == MOORE
                        ? get_alive_neighbors_moore(x, y)
                        : get_alive_neighbors_von_neumann(x, y);
        if (c_cell > 0 and neighbors >= survive_min and
            neighbors <= survive_max) {
          if (c_cell < limit_ttl)
            c_new_cell += increment;
          alive_cells++;
        } else if (c_cell < 1 and neighbors >= born_min and
                   neighbors <= born_max)
          c_new_cell = 1, alive_cells++;
        else
          c_new_cell = 0;
      } else
        c_new_cell = c_cell;
    }
  }
  c_alive_cells += alive_cells;
  swap(aux_space, evolution_space);
}

int16_t cellular_automata::get_alive_neighbors_moore(int32_t x, int32_t y) {
  int32_t x_position = 0, y_position = 0;
  int16_t neighbors = 0;
  for (int32_t i = -1; i <= 1; i++) {
    for (int32_t j = -1; j <= 1; j++) {
      x_position = x + i, y_position = y + j;
      if (x_position == x and y_position == y)
        continue;
      if (space_closed) {
        x_position = mod(x_position, width * scale);
        y_position = mod(y_position, height);
      } else {
        if (x_position >= width or x_position < 0)
          continue;
        if (y_position >= height or y_position < 0)
          continue;
      }
      if (evolution_space[x_position][y_position] > 0)
        neighbors++;
    }
  }
  return neighbors;
}

int16_t cellular_automata::get_alive_neighbors_von_neumann(int32_t x,
                                                           int32_t y) {
  int32_t x_position = 0, y_position = 0;
  int16_t neighbors = 0;
  for (auto n : offset) {
    x_position = get_x_position(x + n);
    if (x_position < 0)
      continue;

    if (evolution_space[x_position][y] > 0)
      neighbors++;
  }

  for (auto n : offset) {
    y_position = get_y_position(y + n);
    if (y_position < 0)
      continue;

    if (evolution_space[x][y_position] > 0)
      neighbors++;
  }
  return neighbors;
}

void cellular_automata::clear() {
  for (int32_t x = 0; x < width; x++)
    for (int32_t y = 0; y < height; y++)
      evolution_space[x][y] = aux_space[x][y] = 0;
  generation = 0;
}

void cellular_automata::random_space(int32_t probability) {
  unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
  std::mt19937 generator(ms);
  std::uniform_int_distribution<> distribution(1, 100000);
  for (int32_t x = 0; x < width; x++) {
    for (int32_t y = 0; y < height; y++) {
      if (x < (width * scale) and y >= (height * (1 - scale))) {
        evolution_space[x][y] =
            (distribution(generator) <= probability ? 1 : 0);
        alive_cells += evolution_space[x][y];
      }
    }
  }
}

void cellular_automata::change_cell(int32_t x, int32_t y) {
  int32_t &c_cell = evolution_space[x][y];
  c_cell = (c_cell <= 0) ? 1 : 0;
}

void cellular_automata::projection() {
  int32_t c_height = height, c_width = width;
  for (int32_t y = 0; y < c_height; y++) {
    for (int32_t x = 0; x < c_width; x++) {
      if (x < (c_width - 1) and y > 0) {

        if (aux_space[x][y] < 1 and evolution_space[x + 1][y - 1] < 1)
          evolution_space[x + 1][y - 1] = aux_space[x][y];

        if (aux_space[x][y] > 0 and evolution_space[x + 1][y - 1] < 1)
          evolution_space[x + 1][y - 1] = -1;
      }
    }
  }
}

inline int32_t cellular_automata::mod(int32_t a, int32_t m) {
  if (a < 0)
    a += m;
  return a %= m;
}

inline int32_t cellular_automata::get_x_position(const int32_t x) {
  int32_t x_position = x;
  if (space_closed)
    x_position = mod(x_position, width * scale);
  else if (x_position >= width or x_position < 0)
    x_position = -1;
  return x_position;
}

inline int32_t cellular_automata::get_y_position(const int32_t y) {
  int32_t y_position = y;
  if (space_closed)
    y_position = mod(y_position, height);
  else if (y_position >= height or y_position < 0)
    y_position = -1;
  return y_position;
}

cellular_automata::~cellular_automata() {
  delete Polynomial;
  evolution_space.clear();
  aux_space.clear();
}
