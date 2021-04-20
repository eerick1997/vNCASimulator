#include "mainwindow.h"
#include "QDateTime"
#include "cellular_automata.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <iostream>
#include <random>
#include <set>
#include <string>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), mw(nullptr),
      load_space(RANDOM_SPACE), grid_visible(true), timer(new QTimer(this)),
      polynomial_label(new QLabel()) {
    totalistic_von_neumann.resize(32, 0);
    alive_max_x = alive_max_y = entropy_max_x, entropy_max_y = 0;
    ui->setupUi(this);
    init_charts();

    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint |
                   Qt::WindowCloseButtonHint);
    setInitialSettings();
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));

    totalistic_von_neumann[0] = ui->TotalVN0->text().toInt();
    totalistic_von_neumann[1] = ui->TotalVN1->text().toInt();
    totalistic_von_neumann[2] = ui->TotalVN2->text().toInt();
    totalistic_von_neumann[3] = ui->TotalVN3->text().toInt();
    totalistic_von_neumann[4] = ui->TotalVN4->text().toInt();
    totalistic_von_neumann[5] = ui->TotalVN5->text().toInt();
    totalistic_von_neumann[6] = ui->TotalVN6->text().toInt();
    totalistic_von_neumann[7] = ui->TotalVN7->text().toInt();
    totalistic_von_neumann[8] = ui->TotalVN8->text().toInt();
    totalistic_von_neumann[9] = ui->TotalVN9->text().toInt();
    totalistic_von_neumann[10] = ui->TotalVN10->text().toInt();
    totalistic_von_neumann[11] = ui->TotalVN11->text().toInt();
    totalistic_von_neumann[12] = ui->TotalVN12->text().toInt();
    totalistic_von_neumann[13] = ui->TotalVN13->text().toInt();
    totalistic_von_neumann[14] = ui->TotalVN14->text().toInt();
    totalistic_von_neumann[15] = ui->TotalVN15->text().toInt();
    totalistic_von_neumann[16] = ui->TotalVN16->text().toInt();
    totalistic_von_neumann[17] = ui->TotalVN17->text().toInt();
    totalistic_von_neumann[18] = ui->TotalVN18->text().toInt();
    totalistic_von_neumann[19] = ui->TotalVN19->text().toInt();
    totalistic_von_neumann[20] = ui->TotalVN20->text().toInt();
    totalistic_von_neumann[21] = ui->TotalVN21->text().toInt();
    totalistic_von_neumann[22] = ui->TotalVN22->text().toInt();
    totalistic_von_neumann[23] = ui->TotalVN23->text().toInt();
    totalistic_von_neumann[24] = ui->TotalVN24->text().toInt();
    totalistic_von_neumann[25] = ui->TotalVN25->text().toInt();
    totalistic_von_neumann[26] = ui->TotalVN26->text().toInt();
    totalistic_von_neumann[27] = ui->TotalVN27->text().toInt();
    totalistic_von_neumann[28] = ui->TotalVN28->text().toInt();
    totalistic_von_neumann[29] = ui->TotalVN29->text().toInt();
    totalistic_von_neumann[30] = ui->TotalVN30->text().toInt();
    totalistic_von_neumann[31] = ui->TotalVN31->text().toInt();
}

MatrixWindow *MainWindow::newMatrixWindow() {
    if (mw == nullptr)
        mw = new MatrixWindow();
    return mw;
}

void MainWindow::setInitialSettings() {
    // Semi-totalistic rules
    born_min = ui->born_min->value();
    born_max = ui->born_max->value();
    survive_min = ui->survive_min->value();
    survive_max = ui->survive_max->value();
    // Dimensions
    width = ui->spin_width->value();
    height = ui->spin_height->value();
    // Space Displaying
    cell_size = ui->spinCell_size->value();
    speed = ui->spinTime->value();
    neighbor = ui->radio_von->isChecked();
    scale = ((100.00 - (double)ui->spinProjection->value()) / 100);
    // Densities
    density = ui->slider_density->value();
    totalistic_rules_density = ui->slider_totalistic_density->value();
    // Neighborhood
    space_type = ui->radioClosed->isChecked();
    ui->label_moore->installEventFilter(this);
    ui->label_von_neumann->installEventFilter(this);
    // Colors
    death_color = Qt::black;
    alive_color = Qt::white;
    projection_color = Qt::cyan;
    grid_color = Qt::white;
    // Allows to evaluate the polynomial using the totalistic rule
    totalistic_rules = false;
}

void MainWindow::on_drawButton_clicked() {
    mw = newMatrixWindow();
    connect(mw, SIGNAL(disableButtons()), this, SLOT(disableButtons()));
    mw->Widget_evolution_space->Cellular_automata = new cellular_automata(
                width, height, survive_min, survive_max, born_min, born_max, scale,
                neighbor, space_type, totalistic_rules, totalistic_von_neumann);
    mw->Widget_evolution_space->evolve = 0;
    mw->Widget_evolution_space->set_cell_size(cell_size);
    mw->Widget_evolution_space->set_show_grid(grid_visible);
    mw->Widget_evolution_space->set_alive_color(alive_color);
    mw->Widget_evolution_space->set_death_color(death_color);
    mw->Widget_evolution_space->set_projection_color(projection_color);
    mw->Widget_evolution_space->set_grid_color(grid_color);
    mw->Widget_evolution_space->set_speed(speed);
    mw->Widget_evolution_space->set_show_gradient(ui->checkGradient->isChecked());
    mw->setDimensions();
    mw->show();
    // Clear elements
    clearElements();
    // Initial conditions
    if (load_space == RANDOM_SPACE)
        mw->Widget_evolution_space->Cellular_automata->random_space(density);
    else if (load_space == FILE_SPACE)
        loadByFile();
    // Unlock buttons
    ui->nextGenerationButton->setEnabled(true);
    ui->pushButton->setEnabled(true);
    update_gui();
    // Getting the polinomial for the current CA
    build_chart_polynomial();
}

void MainWindow::disableButtons() {
    ui->nextGenerationButton->setEnabled(false);
    ui->pushButton->setEnabled(false);
}

void MainWindow::loop() {
    if (mw != nullptr) {
        if (!mw->isVisible()) {
            timer->stop();
            delete mw;
            mw = nullptr;
            return;
        }

        mw->Widget_evolution_space->next_generation_update();
        update_gui();
    }
}

void MainWindow::update_gui() {
    cellular_automata *Cellular_automata =
            mw->Widget_evolution_space->Cellular_automata;
    int32_t generation = Cellular_automata->get_generation();
    int32_t alive_cells = Cellular_automata->get_alive_cells();

    double average = Cellular_automata->get_average();
    double density = Cellular_automata->get_density();

    double entropy = Cellular_automata->get_entropy();
    ui->lcdGeneration->display(generation);
    ui->lcdAlive->display(alive_cells);
    ui->lcdDensity->display(density);
    ui->lcdAverage->display(average);

    // Adding points to build a chart
    *series_alive_cells << QPoint(generation, alive_cells);
    *series_entropy << QPointF(generation, entropy);
    // Adjusting the X and Y axis
    alive_max_y = std::max(alive_max_y, alive_cells);
    entropy_max_y = std::max(entropy, entropy_max_y);
    // Seting new ranges to the charts
    chart_alive_cells->axes(Qt::Horizontal)
            .back()
            ->setRange(0, series_alive_cells->count());
    chart_alive_cells->axes(Qt::Vertical).back()->setRange(0, alive_max_y + 2);

    chart_entropy->axes(Qt::Horizontal)
            .back()
            ->setRange(0, series_alive_cells->count());
    chart_entropy->axes(Qt::Vertical).back()->setRange(0, entropy_max_y + 2);
}

void MainWindow::on_nextGenerationButton_clicked() { loop(); }

QColor MainWindow::selectColor(QColor previousColor) {
    QColor color =
            QColorDialog::getColor(previousColor, this, tr("Select color"));
    if (!color.isValid())
        return previousColor;
    return color;
}

void MainWindow::on_colorDeathButton_pressed() {
    death_color = selectColor(death_color);
    color_code = death_color;
    if (mw != nullptr)
        mw->Widget_evolution_space->set_death_color(death_color);
    ui->labelDeathColor->setStyleSheet("QLabel{ color: " + color_code.toString() +
                                       ";}");
}
void MainWindow::on_colorLivingButton_pressed() {
    alive_color = selectColor(alive_color);
    color_code = alive_color;
    if (mw != nullptr)
        mw->Widget_evolution_space->set_alive_color(alive_color);
    ui->labelLivingColor->setStyleSheet(
                "QLabel{ color: " + color_code.toString() + ";}");
}
void MainWindow::on_colorGridButton_pressed() {
    grid_color = selectColor(grid_color);
    color_code = grid_color;
    if (mw != nullptr)
        mw->Widget_evolution_space->set_grid_color(grid_color);
    ui->labelGridColor->setStyleSheet(
                "QLabel{ color: " + color_code.toString() + ";}");
}
void MainWindow::on_colorProjectionButton_pressed() {
    projection_color = selectColor(projection_color);
    color_code = projection_color;
    if (mw != nullptr)
        mw->Widget_evolution_space->set_projection_color(projection_color);
    ui->labelProjectionColor->setStyleSheet(
                "QLabel{ color: " + color_code.toString() + ";}");
}

void MainWindow::on_clearButton_clicked() {

    if (mw != nullptr and mw->isVisible()) {
        mw->Widget_evolution_space->Cellular_automata->clear();
        mw->Widget_evolution_space->update();
    }
    clearElements();
}

void MainWindow::on_pushButton_clicked(bool checked) {
    if (mw != nullptr and mw->isVisible()) {
        QIcon *icon = new QIcon();
        if (checked) {
            timer->start(ui->spinTime->value());
            icon->addPixmap(QPixmap(":icons/res/img/pause.png"), QIcon::Normal,
                            QIcon::On);
            ui->nextGenerationButton->setEnabled(false);
            ui->pushButton->setText("Pause");

        } else {
            if (timer->isActive())
                timer->stop();
            icon->addPixmap(QPixmap(":icons/res/img/play.png"), QIcon::Normal,
                            QIcon::On);
            ui->nextGenerationButton->setEnabled(true);
            ui->pushButton->setText("Play");
        }
        ui->pushButton->setIcon(*icon);
    }
}

void MainWindow::on_born_min_valueChanged(int arg1) {
    born_min = arg1;
    if (mw != nullptr) {
        mw->Widget_evolution_space->Cellular_automata->set_born_min(born_min);
        build_chart_polynomial();
    }
}

void MainWindow::on_born_max_valueChanged(int arg1) {
    born_max = arg1;
    ui->born_min->setMaximum(arg1);
    if (mw != nullptr) {
        mw->Widget_evolution_space->Cellular_automata->set_born_max(born_max);
        build_chart_polynomial();
    }
}

void MainWindow::on_survive_min_valueChanged(int arg1) {
    survive_min = arg1;
    if (mw != nullptr) {
        mw->Widget_evolution_space->Cellular_automata->set_survive_min(survive_min);
        build_chart_polynomial();
    }
}

void MainWindow::on_survive_max_valueChanged(int arg1) {
    survive_max = arg1;
    ui->survive_min->setMaximum(arg1);
    if (mw != nullptr) {
        mw->Widget_evolution_space->Cellular_automata->set_survive_max(survive_max);
        build_chart_polynomial();
    }
}

void MainWindow::on_spin_width_valueChanged(int arg1) {
    width = arg1;
    if (mw != nullptr) {
        mw->Widget_evolution_space->Cellular_automata->set_width(width);
        mw->setDimensions();
    }
}

void MainWindow::on_spin_height_valueChanged(int arg1) {
    height = arg1;
    if (mw != nullptr) {
        mw->Widget_evolution_space->Cellular_automata->set_height(height);
        mw->setDimensions();
    }
}

void MainWindow::on_radio_moore_clicked() {
    if (!totalistic_rules) {
        ui->born_max->setMaximum(8);
        ui->born_min->setMaximum(ui->born_max->value());
        ui->survive_max->setMaximum(8);
        ui->survive_min->setMaximum(ui->survive_max->value());
        enableNeighborhood(false);
    } else
        ui->radio_von->click();
}

void MainWindow::on_radio_von_clicked() {
    ui->born_max->setMaximum(4);
    ui->born_min->setMaximum(ui->born_max->value());
    ui->survive_max->setMaximum(4);
    ui->survive_min->setMaximum(ui->survive_max->value());
    enableNeighborhood(true);
}

bool MainWindow::eventFilter(QObject *o, QEvent *e) {
    if (o == ui->label_moore and e->type() == QMouseEvent::MouseButtonPress) {
        enableNeighborhood(false);
        ui->radio_moore->click();
    } else if (o == ui->label_von_neumann and
               e->type() == QMouseEvent::MouseButtonPress) {
        enableNeighborhood(true);
        ui->radio_von->click();
    }

    return QObject::eventFilter(o, e);
}

void MainWindow::enableNeighborhood(bool active) {
    ui->label_moore->setEnabled(!active);
    ui->label_von_neumann->setEnabled(active);
    neighbor = active;
    if (mw != nullptr) {
        mw->Widget_evolution_space->Cellular_automata->set_neighbor_type(neighbor);
        build_chart_polynomial();
    }
}

void MainWindow::on_radioClosed_clicked() {
    space_type = true;
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->set_space_closed(space_type);
}

void MainWindow::on_radioOpen_clicked() {
    space_type = false;
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->set_space_closed(space_type);
}

/* ************************* Space Displaying section ******************** */

void MainWindow::on_spinTime_valueChanged(int arg1) {
    speed = arg1;
    if (timer->isActive())
        timer->start(speed);
    if (mw != nullptr)
        mw->Widget_evolution_space->set_speed(speed);
    ui->speedSlider->setValue(speed);
}

void MainWindow::on_speedSlider_valueChanged(int position) {
    speed = position;
    if (timer->isActive())
        timer->start(speed);
    if (mw != nullptr)
        mw->Widget_evolution_space->set_speed(speed);

    ui->spinTime->setValue(speed);
}

void MainWindow::on_spinProjection_valueChanged(int arg1) {
    scale = ((100.00 - (double)arg1) / 100);
    ui->sliderProjection->setValue(arg1);
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->set_scale(scale);
}

void MainWindow::on_sliderProjection_valueChanged(int position) {
    scale = ((100.00 - position) / 100);
    ui->spinProjection->setValue(position);
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->set_scale(scale);
}

void MainWindow::on_spinCell_size_valueChanged(int arg1) {
    cell_size = arg1;
    ui->sliderCellSize->setValue(cell_size);
    if (mw != nullptr) {
        mw->Widget_evolution_space->set_cell_size(cell_size);
        mw->setDimensions();
    }
}

void MainWindow::on_sliderCellSize_valueChanged(int position) {
    cell_size = position;
    ui->spinCell_size->setValue(cell_size);
    if (mw != nullptr) {
        mw->Widget_evolution_space->set_cell_size(cell_size);
        mw->setDimensions();
    }
}

/* ***************************************************************************
 */

void MainWindow::on_radio_random_space_clicked() {
    ui->spin_density->setEnabled(true);
    ui->slider_density->setEnabled(true);
    load_space = RANDOM_SPACE;
}

void MainWindow::on_radio_from_file_clicked() {
    ui->spin_density->setEnabled(false);
    ui->slider_density->setEnabled(false);
    load_space = FILE_SPACE;
}

void MainWindow::on_spin_density_valueChanged(double arg1) {
    ui->slider_density->setValue(arg1 * 100000);
    density = arg1 * 100000;
}

void MainWindow::on_slider_density_valueChanged(int value) {
    ui->spin_density->setValue((double)value / 100000.0);
    density = value;
}

void MainWindow::on_button_choose_file_clicked() {
    file_name = QFileDialog::getOpenFileName(this, tr("Select File"), "",
                                             tr("Binary Files (*.dat)"));
}

void MainWindow::init_charts() {
    // Creating objects
    series_polynomial = new QLineSeries();
    series_rect = new QLineSeries();
    series_entropy = new QLineSeries();
    series_alive_cells = new QLineSeries();
    series_attractive_points = new QScatterSeries();
    series_repulsive_points = new QScatterSeries();
    series_critic_points = new QScatterSeries();
    series_indifferent_points = new QScatterSeries();

    chart_polynomial = new QChart();
    chart_alive_cells = new QChart();
    chart_entropy = new QChart();

    chart_view_polynomial = new QChartView();
    chart_view_alive_cells = new QChartView();
    chart_view_entropy = new QChartView();

    //List of points
    classification = new QListWidget();

    // Setting parameters
    // Attractive points
    series_attractive_points->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series_attractive_points->setMarkerSize(10.0);
    series_attractive_points->setPointLabelsFormat("@xPoint");
    series_attractive_points->setPointLabelsVisible(true);
    series_attractive_points->setName("Attractive points");
    // Repulsive points
    series_repulsive_points->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series_repulsive_points->setMarkerSize(10.0);
    series_repulsive_points->setPointLabelsFormat("@xPoint");
    series_repulsive_points->setPointLabelsVisible(true);
    series_repulsive_points->setName("Repulsive points");
    // Critic points
    series_critic_points->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series_critic_points->setMarkerSize(10.0);
    series_critic_points->setPointLabelsFormat("@xPoint");
    series_critic_points->setPointLabelsVisible(true);
    series_critic_points->setName("Critic points");
    // Indifferent points
    series_indifferent_points->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series_indifferent_points->setMarkerSize(10.0);
    series_indifferent_points->setPointLabelsFormat("@xPoint");
    series_indifferent_points->setPointLabelsVisible(true);
    series_indifferent_points->setName("Indifferent points");

    series_polynomial->setName("Polynomial");
    series_rect->setName("Identity");
    chart_polynomial->addSeries(series_polynomial);
    chart_polynomial->addSeries(series_rect);
    chart_polynomial->addSeries(series_attractive_points);
    chart_polynomial->addSeries(series_repulsive_points);
    chart_polynomial->addSeries(series_critic_points);
    chart_polynomial->addSeries(series_indifferent_points);
    chart_polynomial->createDefaultAxes();
    chart_polynomial->axes(Qt::Horizontal).back()->setRange(0.0, 1.1);
    chart_polynomial->axes(Qt::Vertical).back()->setRange(0.0, 1.1);
    chart_view_polynomial->setChart(chart_polynomial);
    chart_view_polynomial->setRenderHint(QPainter::Antialiasing);
    // chart_view_polynomial->setRubberBand( QChartView::HorizontalRubberBand );

    series_alive_cells->setName("Alive cells");
    chart_alive_cells->addSeries(series_alive_cells);
    chart_alive_cells->createDefaultAxes();
    chart_view_alive_cells->setChart(chart_alive_cells);
    chart_view_alive_cells->setRenderHint(QPainter::Antialiasing);

    series_entropy->setName("Entropy");
    chart_entropy->addSeries(series_entropy);
    chart_entropy->createDefaultAxes();
    chart_view_entropy->setChart(chart_entropy);
    chart_view_entropy->setRenderHint(QPainter::Antialiasing);
    // 750
    chart_view_polynomial->setFixedSize(1000, 520);
    chart_view_alive_cells->setFixedSize(1000, 520);
    chart_view_entropy->setFixedSize(1000, 520);

    classification->setFixedSize(1000,60);
    // Adding objects into the GUI
    ui->scroll_charts->setWidgetResizable(true);
    polynomial_label->setAlignment(Qt::AlignHCenter);
    ui->layout_charts->insertWidget(0, polynomial_label);
    ui->layout_charts->addWidget(chart_view_polynomial);
    ui->layout_charts->addWidget(classification);
    ui->layout_charts->addWidget(chart_view_alive_cells);
    ui->layout_charts->addWidget(chart_view_entropy);
    ui->scroll_content_charts->setLayout(ui->layout_charts);
}

void MainWindow::build_chart_polynomial() {
    if (mw != nullptr) {
        series_polynomial->clear();
        series_rect->clear();
        series_attractive_points->clear();
        series_repulsive_points->clear();
        series_critic_points->clear();
        series_indifferent_points->clear();
        polynomial *Polynomial =
                mw->Widget_evolution_space->Cellular_automata->Polynomial;
        if (totalistic_rules)
            Polynomial->build_polynomial(mw->Widget_evolution_space->Cellular_automata
                                         ->totalistic_von_neumann);
        else
            Polynomial->build_polynomial();
        *series_rect << QPointF(0, 0) << QPointF(1, 1);
        for (double x = 0; x <= 1; x += 0.001)
            *series_polynomial << QPointF(x, Polynomial->evaluate(x));
        // Displaying polynomial
        polynomial_label->setText(
                    QString::fromUtf8((Polynomial->get_text()).c_str()));
        classification->clear();
        get_chart_points();

    }
}

void MainWindow::on_checkGrid_clicked(bool checked) {
    grid_visible = checked;
    if (mw != nullptr)
        mw->Widget_evolution_space->set_show_grid(grid_visible);
}

void MainWindow::on_pushExport_clicked() { exportGame(); }

void MainWindow::loadByFile() {
    QFile file(file_name);
    if (file.open(QIODevice::ReadOnly)) {
        cellular_automata *Cellular_automata =
                mw->Widget_evolution_space->Cellular_automata;
        QDataStream in(&file);
        qint64 generation_aux, c_alive_cells_aux;
        qint32 alive_aux, a;
        qint16 width_aux, height_aux, cell_size_aux, speed_aux;
        qint8 survive_min_aux, survive_max_aux, born_min_aux, born_max_aux,
                totalistic_value;
        QColor alive_cell_color_aux, death_cell_color_aux,
                projection_cell_color_aux, grid_color_aux;
        qint64 limit;
        qreal x, y;
        double projection_scale;
        bool show_grid_aux, show_gradient_aux;
        /******** Get Values ********/
        in >> width_aux >> height_aux >> survive_min_aux >> survive_max_aux >>
                born_min_aux >> born_max_aux >> neighbor >> space_type >>
                totalistic_rules_density >> totalistic_rules >> projection_scale >>
                cell_size_aux >> speed_aux >> generation_aux >> alive_aux >>
                c_alive_cells_aux >> alive_cell_color_aux >> death_cell_color_aux >>
                projection_cell_color_aux >> grid_color_aux >> show_grid_aux >>
                show_gradient_aux;
        width = (int16_t)width_aux;
        height = (int16_t)height_aux;
        survive_min = (int8_t)survive_min_aux;
        survive_max = (int8_t)survive_max_aux;
        born_min = (int8_t)born_min_aux;
        born_max = (int8_t)born_max_aux;
        scale = (100 - (double)projection_scale) / 100;
        cell_size = (int16_t)cell_size_aux;
        speed = (int16_t)speed_aux;
        death_color = death_cell_color_aux;
        alive_color = alive_cell_color_aux;
        grid_color = grid_color_aux;
        projection_color = projection_cell_color_aux;
        Cellular_automata->set_width(width);
        Cellular_automata->set_height(height);
        Cellular_automata->set_survive_min(survive_min);
        Cellular_automata->set_survive_max(survive_max);
        Cellular_automata->set_born_min(born_min);
        Cellular_automata->set_born_max(born_max);
        Cellular_automata->set_neighbor_type(neighbor);
        Cellular_automata->set_space_closed(space_type);
        Cellular_automata->set_scale(scale);
        Cellular_automata->set_generation((int64_t)generation_aux);
        Cellular_automata->set_alive_cells((int32_t)alive_aux);
        Cellular_automata->set_c_alive_cells((int64_t)c_alive_cells_aux);

        mw->Widget_evolution_space->set_alive_color(alive_cell_color_aux);
        mw->Widget_evolution_space->set_death_color(death_cell_color_aux);
        mw->Widget_evolution_space->set_projection_color(projection_cell_color_aux);
        mw->Widget_evolution_space->set_grid_color(grid_color_aux);
        mw->Widget_evolution_space->set_cell_size(cell_size);
        mw->Widget_evolution_space->set_speed(speed);
        mw->Widget_evolution_space->set_show_grid(show_grid_aux);
        mw->Widget_evolution_space->set_show_gradient(show_gradient_aux);
        mw->Widget_evolution_space->update();

        ui->spin_width->setValue(width);
        ui->spin_height->setValue(height);
        ui->survive_min->setValue(survive_min);
        ui->survive_max->setValue(survive_max);
        ui->born_min->setValue(born_min);
        ui->born_max->setValue(born_max);
        ui->radio_von->setChecked(neighbor);
        if (space_type)
            ui->radioClosed->click();
        else
            ui->radioOpen->click();
        ui->spinProjection->setValue(projection_scale);
        ui->spinCell_size->setValue(cell_size);
        ui->spinTime->setValue(speed);
        ui->check_Totalistic->setChecked(totalistic_rules);
        mw->Widget_evolution_space->Cellular_automata->set_totalistic_rules(
                    totalistic_rules);
        ui->lcdGeneration->display(int32_t(generation_aux));
        ui->lcdAlive->display(int32_t(alive_aux));
        ui->checkGrid->setChecked(show_grid_aux);
        ui->checkGradient->setChecked(show_gradient_aux);

        // Load colors
        color_code = alive_cell_color_aux;
        ui->labelLivingColor->setStyleSheet(
                    "QLabel{ color: " + color_code.toString() + ";}");
        color_code = death_cell_color_aux;
        ui->labelDeathColor->setStyleSheet(
                    "QLabel{ color: " + color_code.toString() + ";}");
        color_code = projection_cell_color_aux;
        ui->labelProjectionColor->setStyleSheet(
                    "QLabel{ color: " + color_code.toString() + ";}");
        color_code = grid_color_aux;
        ui->labelGridColor->setStyleSheet(
                    "QLabel{ color: " + color_code.toString() + ";}");

        enableNeighborhood(neighbor);
        /*************  Totalistic values  ********/
        for (int16_t i = 0; i <= 31; i++) {
            in >> totalistic_value;
            setStateButtons(i, totalistic_value);
            totalistic_von_neumann[i] = totalistic_value;
        }
        /*************  Matrix values  ************/
        matrix m = Cellular_automata->get_evolution_space();
        for (int16_t i = 0; i < width; i++) {
            for (int16_t j = 0; j < height; j++) {
                in >> a;
                m[i][j] = (int32_t)a;
            }
        }

        /***************** Chart series entropy ****************/
        in >> limit;
        in >> entropy_max_y;
        for (int i = 0; i < limit; i++) {
            in >> x >> y;
            *series_entropy << QPointF(x, y);
        }

        /***************** Chart series alive ****************/
        in >> limit;
        in >> alive_max_y;
        for (int i = 0; i < limit; i++) {
            in >> x >> y;
            *series_alive_cells << QPoint(x, y);
        }

        Cellular_automata->set_evolution_space(m);

        // Seting new ranges to the charts
        chart_alive_cells->axes(Qt::Horizontal)
                .back()
                ->setRange(0, series_alive_cells->count());
        chart_alive_cells->axes(Qt::Vertical).back()->setRange(0, alive_max_y + 2);

        chart_entropy->axes(Qt::Horizontal)
                .back()
                ->setRange(0, series_alive_cells->count());
        chart_entropy->axes(Qt::Vertical).back()->setRange(0, entropy_max_y + 2);

        file.close();
    } else
        QMessageBox::warning(this, tr("Error"), tr("Please select a valid file.\n"),
                             QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::exportGame() {
    if (mw == nullptr) {
        QMessageBox::warning(this, tr("Error"), tr("Please create a CA first.\n"),
                             QMessageBox::Ok, QMessageBox::Ok);
    } else {

        QString name;
        if (totalistic_rules)
            name = "CA-" + ui->TXTRuleName->text() + "-T.dat";
        else
            name = "CA-S" + QString::number(survive_min) +
                    QString::number(survive_max) + "B" + QString::number(born_min) +
                    QString::number(born_max) + "-ST.dat";
        path = QFileDialog::getSaveFileName(this, "Save file", name,
                                            "Binary File (*.dat);;All Files (*)");
        if (path.isEmpty()) {
            QMessageBox::warning(this, tr("Error"),
                                 tr("Please select a path first.\n"), QMessageBox::Ok,
                                 QMessageBox::Ok);
            return;
        }
        cellular_automata *Cellular_automata =
                mw->Widget_evolution_space->Cellular_automata;
        QFile file(path);

        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);

            /*************  Set Values  **************/
            out << (qint16)width << (qint16)height << (qint8)survive_min
                << (qint8)survive_max << (qint8)born_min << (qint8)born_max
                << neighbor << space_type << totalistic_rules_density
                << (bool)totalistic_rules << (double)ui->spinProjection->value()
                << (qint16)cell_size << (qint16)speed
                << (qint64)
                   mw->Widget_evolution_space->Cellular_automata->get_generation()
                << (qint32)mw->Widget_evolution_space->Cellular_automata
                   ->get_alive_cells()
                << (qint64)mw->Widget_evolution_space->Cellular_automata
                   ->get_c_alive_cells()
                << (QColor &)alive_color << (QColor &)death_color
                << (QColor &)projection_color << (QColor &)grid_color
                << (bool)mw->Widget_evolution_space->show_grid
                << (bool)mw->Widget_evolution_space->show_gradient;

            /*************  Totalistic values  ********/
            for (int16_t i = 0; i <= 31; i++)
                out << (qint8)totalistic_von_neumann[i];

            /*****************************************/
            matrix m = Cellular_automata->get_evolution_space();
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++)
                    out << (qint32)m[i][j];
            }

            /***************** Chart series entropy ****************/
            out << (qint64)series_entropy->points().size();
            out << (double)entropy_max_y;
            for (const auto point : series_entropy->points())
                out << (qreal)point.x() << (qreal)point.y();

            /***************** Chart series alive ****************/
            out << (qint64)series_alive_cells->points().size();
            out << (qint32)alive_max_y;
            for (const auto point : series_alive_cells->points())
                out << (qreal)point.x() << (qreal)point.y();

            file.close();
            QMessageBox msgBox;
            msgBox.setWindowTitle("Successful!");
            msgBox.setText("Your CA has been saved successfully.");
            msgBox.exec();
        } else
            QMessageBox::warning(this, tr("Error"), tr("Please create a CA first.\n"),
                                 QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::get_chart_points() {

    if (mw != nullptr) {
        polynomial *Polynomial =
                mw->Widget_evolution_space->Cellular_automata->Polynomial;
        chart_points.clear();
        double polynomial_evaluate;
        for (double x = 0.0; x <= 1.000001; x += 0.000001) {
            polynomial_evaluate = Polynomial->evaluate(x);

            int v_abs = abs((int32_t)(x * 1000000) -
                            (int32_t)(polynomial_evaluate * 1000000));
            if (v_abs < 2)
                chart_points.insert((int32_t)(x * 1000000));
        }

        int16_t count = 0;
        int32_t last_value = 0;

        double point = 0, acum = 0;

        if (chart_points.size() == 0)
            return;

        for (int32_t current_point : chart_points) {
            if (count == 0) {
                acum = (current_point / 1000000.0);
                last_value = current_point;
            } else {
                if ((current_point - last_value) == 1) {
                    acum += (current_point / 1000000.0);
                    last_value = current_point;
                } else {
                    point = (double)(acum / count);
                    get_point_type(point, Polynomial);
                    acum = (current_point / 1000000.0);
                    last_value = current_point;
                    count = 0;
                }
            }
            count++;
        }
        point = (double)(acum / count);
        get_point_type(point, Polynomial);
    }
    return;

}

void MainWindow::get_point_type(double point, polynomial *Polynomial) {
    qDebug() << point;
    double x = abs((double)Polynomial->evaluate_derivate(point));
    QString type = "";

    if (x > 1){
        *series_repulsive_points << QPointF(point, point);
        type = "Repulsive point ";
    }

    else if (x < 1) {
        if (x >= -EPS and x <= EPS){
            *series_critic_points << QPointF(point, point);
            type = "Critic point ";
        }
        else{
            *series_attractive_points << QPointF(point, point);
            type = "Attractive point ";
        }
    }

    else {
        *series_indifferent_points << QPointF(point, point);
        type = "Indifferent point ";
    }


    new QListWidgetItem(type + "at (" + QString::number(point) + ", " + QString::number(point) + ")", classification);
    return;
}

void MainWindow::clearElements() {
    ui->lcdGeneration->display(0);
    ui->lcdAlive->display(0);
    ui->lcdAverage->display(0);
    ui->lcdDensity->display(0);
    series_alive_cells->clear();
    series_entropy->clear();
}

MainWindow::~MainWindow() { delete ui; }

// Buttons Totalistic VN Event

void MainWindow::on_TotalVN0_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[0];
    totalistic_von_neumann[0] = new_state;
    ui->TotalVN0->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[0] =
                totalistic_von_neumann[0];
    update_name_rule();
}

void MainWindow::on_TotalVN1_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[1];
    totalistic_von_neumann[1] = new_state;
    ui->TotalVN1->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[1] =
                totalistic_von_neumann[1];
    update_name_rule();
}

void MainWindow::on_TotalVN2_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[2];
    totalistic_von_neumann[2] = new_state;
    ui->TotalVN2->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[2] =
                totalistic_von_neumann[2];
    update_name_rule();
}

void MainWindow::on_TotalVN3_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[3];
    totalistic_von_neumann[3] = new_state;
    ui->TotalVN3->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[3] =
                totalistic_von_neumann[3];
    update_name_rule();
}

void MainWindow::on_TotalVN4_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[4];
    totalistic_von_neumann[4] = new_state;
    ui->TotalVN4->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[4] =
                totalistic_von_neumann[4];
    update_name_rule();
}

void MainWindow::on_TotalVN5_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[5];
    totalistic_von_neumann[5] = new_state;
    ui->TotalVN5->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[5] =
                totalistic_von_neumann[5];
    update_name_rule();
}

void MainWindow::on_TotalVN6_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[6];
    totalistic_von_neumann[6] = new_state;
    ui->TotalVN6->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[6] =
                totalistic_von_neumann[6];
    update_name_rule();
}

void MainWindow::on_TotalVN7_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[7];
    totalistic_von_neumann[7] = new_state;
    ui->TotalVN7->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[7] =
                totalistic_von_neumann[7];
    update_name_rule();
}

void MainWindow::on_TotalVN8_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[8];
    totalistic_von_neumann[8] = new_state;
    ui->TotalVN8->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[8] =
                totalistic_von_neumann[8];
    update_name_rule();
}

void MainWindow::on_TotalVN9_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[9];
    totalistic_von_neumann[9] = new_state;
    ui->TotalVN9->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[9] =
                totalistic_von_neumann[9];
    update_name_rule();
}

void MainWindow::on_TotalVN10_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[10];
    totalistic_von_neumann[10] = new_state;
    ui->TotalVN10->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[10] =
                totalistic_von_neumann[10];
    update_name_rule();
}

void MainWindow::on_TotalVN11_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[11];
    totalistic_von_neumann[11] = new_state;
    ui->TotalVN11->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[11] =
                totalistic_von_neumann[11];
    update_name_rule();
}

void MainWindow::on_TotalVN12_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[12];
    totalistic_von_neumann[12] = new_state;
    ui->TotalVN12->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[12] =
                totalistic_von_neumann[12];
    update_name_rule();
}

void MainWindow::on_TotalVN13_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[13];
    totalistic_von_neumann[13] = new_state;
    ui->TotalVN13->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[13] =
                totalistic_von_neumann[13];
    update_name_rule();
}

void MainWindow::on_TotalVN14_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[14];
    totalistic_von_neumann[14] = new_state;
    ui->TotalVN14->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[14] =
                totalistic_von_neumann[14];
    update_name_rule();
}

void MainWindow::on_TotalVN15_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[15];
    totalistic_von_neumann[15] = new_state;
    ui->TotalVN15->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[15] =
                totalistic_von_neumann[15];
    update_name_rule();
}

void MainWindow::on_TotalVN16_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[16];
    totalistic_von_neumann[16] = new_state;
    ui->TotalVN16->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[16] =
                totalistic_von_neumann[16];
    update_name_rule();
}

void MainWindow::on_TotalVN17_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[17];
    totalistic_von_neumann[17] = new_state;
    ui->TotalVN17->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[17] =
                totalistic_von_neumann[17];
    update_name_rule();
}

void MainWindow::on_TotalVN18_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[18];
    totalistic_von_neumann[18] = new_state;
    ui->TotalVN18->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[18] =
                totalistic_von_neumann[18];
    update_name_rule();
}

void MainWindow::on_TotalVN19_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[19];
    totalistic_von_neumann[19] = new_state;
    ui->TotalVN19->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[19] =
                totalistic_von_neumann[19];
    update_name_rule();
}

void MainWindow::on_TotalVN20_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[20];
    totalistic_von_neumann[20] = new_state;
    ui->TotalVN20->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[20] =
                totalistic_von_neumann[20];
    update_name_rule();
}

void MainWindow::on_TotalVN21_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[21];
    totalistic_von_neumann[21] = new_state;
    ui->TotalVN21->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[21] =
                totalistic_von_neumann[21];
    update_name_rule();
}

void MainWindow::on_TotalVN22_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[22];
    totalistic_von_neumann[22] = new_state;
    ui->TotalVN22->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[22] =
                totalistic_von_neumann[22];
    update_name_rule();
}

void MainWindow::on_TotalVN23_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[23];
    totalistic_von_neumann[23] = new_state;
    ui->TotalVN23->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[23] =
                totalistic_von_neumann[23];
    update_name_rule();
}

void MainWindow::on_TotalVN24_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[24];
    totalistic_von_neumann[24] = new_state;
    ui->TotalVN24->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[24] =
                totalistic_von_neumann[24];
    update_name_rule();
}

void MainWindow::on_TotalVN25_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[25];
    totalistic_von_neumann[25] = new_state;
    ui->TotalVN25->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[25] =
                totalistic_von_neumann[25];
    update_name_rule();
}

void MainWindow::on_TotalVN26_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[26];
    totalistic_von_neumann[26] = new_state;
    ui->TotalVN26->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[26] =
                totalistic_von_neumann[26];
    update_name_rule();
}

void MainWindow::on_TotalVN27_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[27];
    totalistic_von_neumann[27] = new_state;
    ui->TotalVN27->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[27] =
                totalistic_von_neumann[27];
    update_name_rule();
}

void MainWindow::on_TotalVN28_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[28];
    totalistic_von_neumann[28] = new_state;
    ui->TotalVN28->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[28] =
                totalistic_von_neumann[28];
    update_name_rule();
}

void MainWindow::on_TotalVN29_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[29];
    totalistic_von_neumann[29] = new_state;
    ui->TotalVN29->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[29] =
                totalistic_von_neumann[29];
    update_name_rule();
}

void MainWindow::on_TotalVN30_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[30];
    totalistic_von_neumann[30] = new_state;
    ui->TotalVN30->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[30] =
                totalistic_von_neumann[30];
    update_name_rule();
}

void MainWindow::on_TotalVN31_clicked() {
    int8_t new_state = 1 - totalistic_von_neumann[31];
    totalistic_von_neumann[31] = new_state;
    ui->TotalVN31->setText(new_state == 1 ? "1" : "0");
    if (mw != nullptr)
        mw->Widget_evolution_space->Cellular_automata->totalistic_von_neumann[31] =
                totalistic_von_neumann[31];
    update_name_rule();
}

void MainWindow::on_check_Totalistic_clicked() {
    totalistic_rules = ui->check_Totalistic->isChecked();
    ui->radio_von->click();
    if (mw != nullptr) {
        mw->Widget_evolution_space->Cellular_automata->set_totalistic_rules(
                    totalistic_rules);
        build_chart_polynomial();
    }
}
void MainWindow::on_spin_totalistic_density_valueChanged(double arg1) {
    ui->slider_totalistic_density->setValue(arg1 * 100000);
    totalistic_rules_density = arg1 * 100000;
}

void MainWindow::on_slider_totalistic_density_valueChanged(int value) {
    ui->spin_totalistic_density->setValue((double)value / 100000.0);
    totalistic_rules_density = value;
}

void MainWindow::on_button_clear_configuration_clicked() {
    for (int8_t i = 0; i < 32; i++)
        setStateButtons(i, 0);
}

void MainWindow::on_button_random_configuration_clicked() {
    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 generator(ms);
    std::uniform_int_distribution<> distribution(1, 100000);

    for (int8_t i = 0; i < 32; i++) {
        int32_t numero_generado = distribution(generator);
        setStateButtons(i, 0); // At first we must set 0
        if (numero_generado <= totalistic_rules_density)
            setStateButtons(i, 1);
    }
    build_chart_polynomial();
}

void MainWindow::update_name_rule() {
    uint32_t value = 0;
    for (int16_t i = 31; i >= 0; i--)
        value |= (totalistic_von_neumann[i] << i);
    ui->TXTRuleName->setText(QString::fromUtf8(std::to_string(value).c_str()));
}

void MainWindow::setStateButtons(int8_t buttonIndex, int8_t state) {
    // 0 To clear buttons - 1 To set value
    switch (buttonIndex) {
    case 0: {
        if (totalistic_von_neumann[0] != state)
            ui->TotalVN0->click();
        break;
    }
    case 1: {
        if (totalistic_von_neumann[1] != state)
            ui->TotalVN1->click();
        break;
    }
    case 2: {
        if (totalistic_von_neumann[2] != state)
            ui->TotalVN2->click();
        break;
    }

    case 3: {
        if (totalistic_von_neumann[3] != state)
            ui->TotalVN3->click();
        break;
    }

    case 4: {
        if (totalistic_von_neumann[4] != state)
            ui->TotalVN4->click();
        break;
    }

    case 5: {
        if (totalistic_von_neumann[5] != state)
            ui->TotalVN5->click();
        break;
    }

    case 6: {
        if (totalistic_von_neumann[6] != state)
            ui->TotalVN6->click();
        break;
    }

    case 7: {
        if (totalistic_von_neumann[7] != state)
            ui->TotalVN7->click();
        break;
    }

    case 8: {
        if (totalistic_von_neumann[8] != state)
            ui->TotalVN8->click();
        break;
    }

    case 9: {
        if (totalistic_von_neumann[9] != state)
            ui->TotalVN9->click();
        break;
    }

    case 10: {
        if (totalistic_von_neumann[10] != state)
            ui->TotalVN10->click();
        break;
    }

    case 11: {
        if (totalistic_von_neumann[11] != state)
            ui->TotalVN11->click();
        break;
    }

    case 12: {
        if (totalistic_von_neumann[12] != state)
            ui->TotalVN12->click();
        break;
    }

    case 13: {
        if (totalistic_von_neumann[13] != state)
            ui->TotalVN13->click();
        break;
    }

    case 14: {
        if (totalistic_von_neumann[14] != state)
            ui->TotalVN14->click();
        break;
    }

    case 15: {
        if (totalistic_von_neumann[15] != state)
            ui->TotalVN15->click();
        break;
    }

    case 16: {
        if (totalistic_von_neumann[16] != state)
            ui->TotalVN16->click();
        break;
    }

    case 17: {
        if (totalistic_von_neumann[17] != state)
            ui->TotalVN17->click();
        break;
    }

    case 18: {
        if (totalistic_von_neumann[18] != state)
            ui->TotalVN18->click();
        break;
    }

    case 19: {
        if (totalistic_von_neumann[19] != state)
            ui->TotalVN19->click();
        break;
    }

    case 20: {
        if (totalistic_von_neumann[20] != state)
            ui->TotalVN20->click();
        break;
    }

    case 21: {
        if (totalistic_von_neumann[21] != state)
            ui->TotalVN21->click();
        break;
    }

    case 22: {
        if (totalistic_von_neumann[22] != state)
            ui->TotalVN22->click();
        break;
    }

    case 23: {
        if (totalistic_von_neumann[23] != state)
            ui->TotalVN23->click();
        break;
    }

    case 24: {
        if (totalistic_von_neumann[24] != state)
            ui->TotalVN24->click();
        break;
    }

    case 25: {
        if (totalistic_von_neumann[25] != state)
            ui->TotalVN25->click();
        break;
    }

    case 26: {
        if (totalistic_von_neumann[26] != state)
            ui->TotalVN26->click();
        break;
    }

    case 27: {
        if (totalistic_von_neumann[27] != state)
            ui->TotalVN27->click();
        break;
    }

    case 28: {
        if (totalistic_von_neumann[28] != state)
            ui->TotalVN28->click();
        break;
    }

    case 29: {
        if (totalistic_von_neumann[29] != state)
            ui->TotalVN29->click();
        break;
    }

    case 30: {
        if (totalistic_von_neumann[30] != state)
            ui->TotalVN30->click();
        break;
    }

    case 31: {
        if (totalistic_von_neumann[31] != state)
            ui->TotalVN31->click();
        break;
    }

    default: {
        break;
    }
    }
    update_name_rule();
}

void MainWindow::on_TXTRuleName_textEdited(const QString &arg1) {
    uint32_t number = arg1.toUInt();
    for(int16_t i = 31; i >= 0; i--)
        setStateButtons(i, ((number >> i) & 1));
}

void MainWindow::on_checkGradient_clicked(bool checked) {
    if (mw != nullptr)
        mw->Widget_evolution_space->set_show_gradient(checked);
}

void MainWindow::on_check3D_clicked(bool checked){
    if(mw != nullptr)
        mw->Widget_evolution_space->set_3d_mode(checked);
}
