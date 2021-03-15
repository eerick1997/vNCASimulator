#include "matrixwindow.h"
#include "cellular_automata.h"
#include "ui_matrixwindow.h"
#include <QDebug>

MatrixWindow::MatrixWindow(QWidget *parent)
    : QWidget(parent), Widget_evolution_space(new widget_evolution_space(this)),
      ui(new Ui::MatrixWindow) {
  ui->setupUi(this);
  ui->scrollArea->setWidget(Widget_evolution_space);
  ui->scrollArea->setWidgetResizable(true);

  connect(ui->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(verticalScrollBarChanged(int)));
  connect(ui->scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollBarChanged(int)));
}

void MatrixWindow::verticalScrollBarChanged(int value) {
    Widget_evolution_space->set_min_y(value);
}

void MatrixWindow::horizontalScrollBarChanged(int value) {
    Widget_evolution_space->set_min_x(value);
}

void MatrixWindow::setDimensions() {
  const int16_t cell_size = Widget_evolution_space->cell_size;
  const int16_t width = Widget_evolution_space->Cellular_automata->get_width();
  const int16_t height = Widget_evolution_space->Cellular_automata->get_height();
  const qreal offset = cell_size / 2;

  Widget_evolution_space->setFixedSize(width * cell_size + offset, height * cell_size + offset);
}

void MatrixWindow::resizeEvent(QResizeEvent *event) {
  int16_t x = event->size().width();
  int16_t y = event->size().height();
  int16_t x_fix = (x - 40 > 0) ? x - 40 : ui->scrollArea->width();
  int16_t y_fix = (y - 44 > 0) ? y - 44 : ui->scrollArea->height();

  Widget_evolution_space->set_max_x(x_fix);
  Widget_evolution_space->set_max_y(y_fix);

  ui->scrollArea->setFixedSize(x_fix, y_fix);
}

void MatrixWindow::closeEvent(QCloseEvent *event) {
  emit disableButtons();
  QWidget::closeEvent(event);
}

MatrixWindow::~MatrixWindow() {
  delete ui;
  delete Widget_evolution_space;
}
