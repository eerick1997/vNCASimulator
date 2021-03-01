#ifndef WIDGET_EVOLUTION_SPACE_H
#define WIDGET_EVOLUTION_SPACE_H

#include "cellular_automata.h"
#include "qevent.h"
#include <QPainter>
#include <QWidget>
#include <iostream>

class widget_evolution_space : public QWidget {
  Q_OBJECT
public:
  explicit widget_evolution_space(QWidget *parent = 0);
  cellular_automata *Cellular_automata;
signals:
protected:
  void paintEvent(QPaintEvent *);
  void mousePressEvent(QMouseEvent *);

public slots:
  void set_alive_color(const QColor &);
  void set_death_color(const QColor &);
  void set_projection_color(const QColor &);
  void set_grid_color(const QColor &);
  void draw_evolution_space(QPainter &);
  void next_generation_update();
  void set_project(bool);
  void set_show_grid(bool);
  void set_show_gradient(bool);
  void draw_with_projection(QPainter&);
  void draw_cube(QPainter&, qreal, qreal, qreal, QColor&, QColor&);
  void draw_dead_cell(QPainter&);

private:
  bool project;
  inline uint32_t get_gradient_color(const int32_t, const int32_t);
  inline void from_int_to_RGB(const int32_t, int32_t *, int32_t *, int32_t *);
  inline uint32_t from_RGB_to_int(const int32_t, const int32_t, const int32_t);
  const int number_of_states = 8;

public:
  QColor alive_color, death_color, projection_color, grid_color;
  bool evolve, show_grid, show_gradient;
  QPen grid_pen;
  int16_t cell_size, speed;
  void set_cell_size(int16_t);
  void set_speed(int16_t);
  ~widget_evolution_space();
};
#endif // WIDGET_EVOLUTION_SPACE_H
