#include "widget_evolution_space.h"
#include <QPainterPath>
#include <QDebug>
#include <QTimer>

widget_evolution_space::widget_evolution_space(QWidget *parent)
    : QWidget(parent), project(true), show_grid(true) {
    grid_pen.setWidthF(0.5);
    min_x = min_y = 0;
    max_y = max_y = 2000;
}


void widget_evolution_space::set_min_x(int32_t value) {
    min_x = value;
}

void widget_evolution_space::set_min_y(int32_t value) {
    min_y = value;
}

void widget_evolution_space::set_max_x(int32_t value) {
    max_x = value;
}

void widget_evolution_space::set_max_y(int32_t value) {
    max_y = value;
}

int32_t widget_evolution_space::get_matrix_x_position(int32_t x) {
    return x / cell_size;
}

int32_t widget_evolution_space::get_matrix_y_position(int32_t y) {
    qreal offset = (show_cubes) ? cell_size / 2 : 0.0;
    return (y - offset) / cell_size;
}

void widget_evolution_space::mousePressEvent(QMouseEvent *event) {
    int32_t x_position = get_matrix_x_position(event->x());
    int32_t y_position = get_matrix_y_position(event->y());
    if ((x_position >= 0 and x_position < Cellular_automata->get_width()) and
            (y_position >= 0 and y_position < Cellular_automata->get_height()))
        Cellular_automata->change_cell(x_position, y_position), update();
}

inline int16_t widget_evolution_space::get_max_value(int16_t value, int16_t limit) {
    return value >= limit ? limit : value;
}


void widget_evolution_space::render_evolution_space(QPainter &painter) {
    if(show_cubes) {
        draw_dead_cell(painter);
        draw_with_projection(painter);
    } else draw_evolution_space(painter);
}

void widget_evolution_space::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    grid_pen.setBrush(grid_color);
    painter.setPen(grid_pen);
    render_evolution_space(painter);
}

void widget_evolution_space::draw_dead_cell(QPainter &painter) {
    qreal x_position, y_position, offset = cell_size / 2;

    const int16_t width = Cellular_automata->get_width();
    const int16_t height = Cellular_automata->get_height();
    const int16_t x_start = get_matrix_x_position(min_x);
    const int16_t y_start = get_matrix_y_position(min_y);
    const int16_t x_limit = get_max_value(get_matrix_x_position(max_x)+ min_x, width);
    const int16_t y_limit = get_max_value(get_matrix_y_position(max_y)+ min_y, height);

    for(int row = x_start; row < x_limit; row++) {
        for(int col = y_start; col < y_limit; col++) {
            int32_t &current_cell = Cellular_automata->evolution_space[row][col];
            x_position = row * cell_size;
            y_position = col * cell_size;

            if(current_cell == 0)
                draw_cube(painter, x_position, y_position + offset, cell_size, death_color, death_color);
        }
    }
}

void widget_evolution_space::draw_cube(QPainter &painter, qreal x, qreal y, qreal size, QColor &color, QColor &face_color) {
    qreal offset = size / 2;
    QPainterPath cube_path;
    QPolygonF cube_faces;
    cube_faces << QPointF(x + size, y) << QPointF(x, y) << QPointF(x + offset, y - offset)  << QPointF(x + size + offset, y - offset)
               << QPointF(x + size + offset, y + size - offset) << QPointF(x + size, y + size)<< QPointF(x + size, y) << QPointF(x + size + offset, y - offset) ;
    painter.setPen(QPen(death_color));
    cube_path.addPolygon(cube_faces);
    painter.fillPath(cube_path, color);
    painter.drawPolygon(cube_faces);
    painter.fillRect(QRect(x, y, size, size), face_color);
    painter.drawRect(QRect(x, y, size, size));
}

void widget_evolution_space::draw_with_projection(QPainter &painter) {
    qreal x_position, y_position, offset = cell_size / 2.0;
    int32_t R, G, B;
    uint32_t code_color;
    const int16_t width = Cellular_automata->get_width();
    const int16_t height = Cellular_automata->get_height();
    const int16_t x_start = get_matrix_x_position(min_x);
    const int16_t y_start = get_matrix_y_position(min_y);
    const int16_t x_limit = get_max_value(get_matrix_x_position(max_x)+ min_x, width);
    const int16_t y_limit = get_max_value(get_matrix_y_position(max_y)+ min_y, height);

    alive_color.getRgb(&R, &G, &B);
    code_color = from_RGB_to_int(R, G, B);

    for (int32_t row = x_start; row < x_limit; row++) {
        for (int32_t col = y_limit - 1; col >= y_start; col--) {
            int32_t &current_cell = Cellular_automata->evolution_space[row][col];
            x_position = (qreal)(cell_size * row);
            y_position = (qreal)(cell_size * col);

            if(current_cell == 0)
                continue;

            if(current_cell < 0)
                draw_cube(painter, x_position, y_position + offset, cell_size, projection_color, projection_color);
            else {
                if(show_gradient) {
                    QColor gradientColor = get_gradient_color(code_color, current_cell);
                    draw_cube(painter, x_position, y_position + offset, cell_size, projection_color, gradientColor);
                } else draw_cube(painter, x_position, y_position + offset, cell_size, projection_color, alive_color);
            }
        }
    }
}

void widget_evolution_space::draw_evolution_space(QPainter &painter) {
    qreal x_position, y_position;
    int32_t R, G, B;
    uint32_t code_color;

    const int16_t width = Cellular_automata->get_width();
    const int16_t height = Cellular_automata->get_height();
    const int16_t x_start = get_matrix_x_position(min_x);
    const int16_t y_start = get_matrix_y_position(min_y);
    const int16_t x_limit = get_max_value(get_matrix_x_position(max_x)+ min_x, width);
    const int16_t y_limit = get_max_value(get_matrix_y_position(max_y)+ min_y, height);

    alive_color.getRgb(&R, &G, &B);
    code_color = from_RGB_to_int(R, G, B);

    for (int32_t x = x_start; x < width and x <= x_limit; x++) {
        for (int32_t y = y_start; y < height and y <= y_limit; y++) {

            const int32_t current_cell = Cellular_automata->evolution_space[x][y];

            x_position = (qreal)(cell_size * x);
            y_position = (qreal)(cell_size * y);

            QRectF r(x_position, y_position, (qreal)cell_size, (qreal)cell_size);
            if (current_cell == 0)
                painter.fillRect(r, death_color);
            else if (current_cell < 0)
                painter.fillRect(r, projection_color);
            else {
                if (show_gradient)
                    painter.fillRect(
                                r, QBrush(QColor(get_gradient_color(code_color, current_cell))));
                else
                    painter.fillRect(r, alive_color);
            }
            if (show_grid)
                painter.drawRect(r);
        }
    }
}

void widget_evolution_space::set_alive_color(const QColor &color) {
    alive_color = color;
    update();
}

void widget_evolution_space::set_death_color(const QColor &color) {
    death_color = color;
    update();
}

void widget_evolution_space::set_projection_color(const QColor &color) {
    projection_color = color;
    update();
}

void widget_evolution_space::set_grid_color(const QColor &color) {
    grid_color = color;
    update();
}

void widget_evolution_space::set_cell_size(int16_t n_cell_size) {
    cell_size = n_cell_size;
    update();
}

void widget_evolution_space::set_speed(int16_t n_speed) {
    speed = n_speed;
    update();
}

void widget_evolution_space::next_generation_update() {
    Cellular_automata->run();
    //Cellular_automata->wait();
    repaint();
}

void widget_evolution_space::set_project(bool state) { Cellular_automata->project = state; }

void widget_evolution_space::set_show_grid(bool state) {
    show_grid = state;
    update();
}

void widget_evolution_space::set_show_gradient(bool state) {
    show_gradient = state;
    update();
}

void widget_evolution_space::set_3d_mode(bool state) {
    show_cubes = state;
    update();
}

inline void widget_evolution_space::from_int_to_RGB(const int32_t code_color,
                                                    int32_t *R, int32_t *G,
                                                    int32_t *B) {
    *R = (code_color >> 16) & 0xFFu;
    *G = (code_color >> 8) & 0XFFu;
    *B = code_color & 0XFFu;
}

inline uint32_t widget_evolution_space::from_RGB_to_int(const int32_t R,
                                                        const int32_t G,
                                                        const int32_t B) {
    return 0X00FFFFFFu & ((R << 16) | (G << 8) | B);
}

/**Warning: This function can be as complex as you want depending of the value
if the constant numeber_of_states, alse if that constant is biggest than
limit_ttl you can get an infinite loop, so be aware of that.**/
inline uint32_t
widget_evolution_space::get_gradient_color(const int32_t current_color,
                                           const int32_t current_cell) {
    int32_t range = Cellular_automata->limit_ttl / number_of_states;
    int32_t offset =
            range * ((current_color + current_cell > 0X00FFFFFF) ? -1 : 1);
    for (int nth_state = 1; nth_state <= number_of_states; nth_state++)
        if (current_cell >= range * (nth_state - 1) and
                current_cell <= range * nth_state)
            return current_color + offset * (nth_state - 1);
    return current_color + offset * number_of_states;
}

widget_evolution_space::~widget_evolution_space() { delete Cellular_automata; }
