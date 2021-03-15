#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define RANDOM_SPACE 0
#define FILE_SPACE 1

#include "matrixwindow.h"
#include <QColorDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QSizePolicy>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <set>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MatrixWindow *newMatrixWindow();
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void disableButtons();
  void on_drawButton_clicked();
  void on_born_min_valueChanged(int arg1);
  void on_spinCell_size_valueChanged(int arg1);
  void on_spin_width_valueChanged(int arg1);
  void on_spin_height_valueChanged(int arg1);
  void on_nextGenerationButton_clicked();
  void on_born_max_valueChanged(int arg1);
  void on_survive_min_valueChanged(int arg1);
  void on_survive_max_valueChanged(int arg1);
  void on_clearButton_clicked();
  void loop();
  void on_radio_moore_clicked();
  void on_radio_von_clicked();
  bool eventFilter(QObject *o, QEvent *e);
  void enableNeighborhood(bool);
  void on_spinTime_valueChanged(int arg1);
  void on_speedSlider_valueChanged(int position);
  void on_spinProjection_valueChanged(int arg1);
  void on_sliderProjection_valueChanged(int position);
  void on_sliderCellSize_valueChanged(int position);
  void on_radio_random_space_clicked();
  void on_radio_from_file_clicked();
  void on_button_choose_file_clicked();
  void on_spin_density_valueChanged(double arg1);
  void on_slider_density_valueChanged(int value);
  void init_charts();
  void build_chart_polynomial();
  void on_radioClosed_clicked();
  void on_radioOpen_clicked();
  void on_checkGrid_clicked(bool checked);
  void on_pushExport_clicked();
  void on_pushButton_clicked(bool checked);
  void on_colorDeathButton_pressed();
  void on_colorLivingButton_pressed();
  void on_colorProjectionButton_pressed();
  void on_colorGridButton_pressed();
  void clearElements();
  void setStateButtons(int8_t, int8_t);

  void update_name_rule();

  void on_TotalVN0_clicked();

  void on_TotalVN1_clicked();

  void on_TotalVN2_clicked();

  void on_TotalVN3_clicked();

  void on_TotalVN4_clicked();

  void on_TotalVN5_clicked();

  void on_TotalVN6_clicked();

  void on_TotalVN7_clicked();

  void on_TotalVN8_clicked();

  void on_TotalVN9_clicked();

  void on_TotalVN10_clicked();

  void on_TotalVN11_clicked();

  void on_TotalVN12_clicked();

  void on_TotalVN13_clicked();

  void on_TotalVN14_clicked();

  void on_TotalVN15_clicked();

  void on_TotalVN16_clicked();

  void on_TotalVN17_clicked();

  void on_TotalVN18_clicked();

  void on_TotalVN19_clicked();

  void on_TotalVN20_clicked();

  void on_TotalVN21_clicked();

  void on_TotalVN22_clicked();

  void on_TotalVN23_clicked();

  void on_TotalVN24_clicked();

  void on_TotalVN25_clicked();

  void on_TotalVN26_clicked();

  void on_TotalVN27_clicked();

  void on_TotalVN28_clicked();

  void on_TotalVN29_clicked();

  void on_TotalVN30_clicked();

  void on_TotalVN31_clicked();

  void on_check_Totalistic_clicked();

  void on_spin_totalistic_density_valueChanged(double arg1);

  void on_slider_totalistic_density_valueChanged(int value);

  void on_button_random_configuration_clicked();

  void on_button_clear_configuration_clicked();

  void on_TXTRuleName_textEdited(const QString &arg1);

  void on_checkGradient_clicked(bool checked);

  void on_check3D_clicked(bool checked);

private:
  // Attributes
  Ui::MainWindow *ui;
  MatrixWindow *mw;
  int32_t density, totalistic_rules_density;
  int16_t width, height, cell_size, speed;
  int8_t survive_min, survive_max, born_min, born_max, load_space;
  double scale, grid_visible;
  bool neighbor, space_type, is_running, totalistic_rules;
  QTimer *timer;
  QThread *thread;
  QColor death_color, alive_color, projection_color, grid_color;
  QVariant color_code;
  // Bucket
  std::vector<int8_t> totalistic_von_neumann;
  // Chart variables
  QtCharts::QLineSeries *series_polynomial, *series_rect, *series_entropy,
      *series_alive_cells;
  QtCharts::QChart *chart_polynomial, *chart_alive_cells, *chart_entropy;
  QtCharts::QChartView *chart_view_polynomial, *chart_view_alive_cells,
      *chart_view_entropy;
  QtCharts::QScatterSeries *series_intersection_points,
      *series_attractive_points, *series_repulsive_points,
      *series_indifferent_points, *series_critic_points;
  QString path, file_name;
  int32_t alive_max_x, alive_max_y;
  double entropy_max_x, entropy_max_y;
  std::set<int32_t> chart_points;
  QLabel *polynomial_label;
  QListWidget *classification;
  // Own methods
  QColor selectColor(QColor previousColor);
  void setInitialSettings();
  void loadByFile();
  void exportGame();
  void get_chart_points();
  void get_point_type(double point, polynomial *Polynomial);
  void update_gui();
};
#endif // MAINWINDOW_H
