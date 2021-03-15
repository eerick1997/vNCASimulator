#ifndef MATRIXWINDOW_H
#define MATRIXWINDOW_H

#include "cellular_automata.h"
#include "widget_evolution_space.h"
#include <QPainter>
#include <QScrollArea>
#include <QWidget>
#include <QScrollBar>
#include <QScrollEvent>

namespace Ui {
class MatrixWindow;
}

class MatrixWindow : public QWidget {
  Q_OBJECT
public:
  widget_evolution_space *Widget_evolution_space;
  void setDimensions();
  explicit MatrixWindow(QWidget *parent = nullptr);
  ~MatrixWindow();

private slots:
  void verticalScrollBarChanged(int);
  void horizontalScrollBarChanged(int);

signals:
  void disableButtons();

private:
  void closeEvent(QCloseEvent *event);
  Ui::MatrixWindow *ui;
  void resizeEvent(QResizeEvent *event);
};

#endif // MATRIXWINDOW_H
