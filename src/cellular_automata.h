#include "polynomial.h"
#include <QByteArray>
#include <QDataStream>
#include <QPainter>
#include <QThread>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <array>

#define MAX_SIZE 2000

#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H

using matrix = std::vector<std::vector<int>>;

class cellular_automata : public QThread{

protected:
    void run();

private:
  // Attributes
  int64_t generation, c_alive_cells;
  int16_t width, height;
  int32_t alive_cells;
  int8_t survive_min, survive_max, born_min, born_max;
  double scale;
  bool neighbor_type, space_closed, totalistic_rules;
  const std::vector<std::vector<int32_t>> coordinates = {
      {0, -1}, {-1, 0}, {0, 0}, {1, 0}, {0, 1}};
  const std::vector<int8_t> offset = {-1, 1};

public:
  // Main matrix
  matrix evolution_space, aux_space;
  // Constructor
  cellular_automata(int16_t, int16_t, int8_t, int8_t, int8_t, int8_t, double,
                    bool, bool, bool, std::vector<int8_t>);
  // Some constants
  const int limit_ttl = 100000;
  const int increment = 100;
  // Bucket
  std::vector<int8_t> totalistic_von_neumann;
  // Getters
  int64_t get_generation();
  int16_t get_width();
  int16_t get_height();
  int32_t get_alive_cells();
  int32_t get_dead_cells();
  int64_t get_c_alive_cells();
  int8_t get_survive_min();
  int8_t get_survive_max();
  int8_t get_born_min();
  int8_t get_born_max();
  double get_entropy();
  double get_average();
  matrix get_evolution_space();
  bool get_neighbor_type();
  double get_scale();
  bool get_is_closed();
  double get_density();
  std::vector<int8_t> get_totalistic_von_neumann();
  bool get_totalistic_rules();
  bool project, envolve;

  // Setters
  void set_generation(int64_t);
  void set_width(int16_t);
  void set_height(int16_t);
  void set_alive_cells(int32_t);
  void set_c_alive_cells(int64_t);
  void set_evolution_space(matrix);
  void set_survive_min(int8_t);
  void set_survive_max(int8_t);
  void set_born_min(int8_t);
  void set_born_max(int8_t);
  void set_neighbor_type(bool);
  void set_space_closed(bool);
  void set_totalistic_von_neumann(std::vector<int8_t>);
  void set_totalistic_rules(bool);
  // Own methods
  void next_generation();

  int16_t get_alive_neighbors_moore(int32_t, int32_t);
  int16_t get_alive_neighbors_von_neumann(int32_t, int32_t);
  void clear();
  void change_cell(int32_t, int32_t);
  void projection();
  inline int32_t mod(int32_t, int32_t);
  void random_space(int32_t);
  void set_scale(double);
  polynomial *Polynomial;
  void next_generation_semitotalistic();
  void next_generation_totalistic();
  int8_t get_alive_neighbors_totalistic(int32_t, int32_t);

  inline int32_t get_x_position(const int32_t);
  inline int32_t get_y_position(const int32_t);

  // Destructor
  ~cellular_automata();
};

#endif // CELLULAR_AUTOMATA_H
