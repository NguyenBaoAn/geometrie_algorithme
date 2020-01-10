#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // default value
    insert_x = 0;
    insert_y = 0;
    insert_z = 0;
    collapse_face = 0;
    collapse_vertice = 0;
    
    
    ui->setupUi(this);
    connect(ui->exitButton, SIGNAL(released()), this, SLOT(onButton()));

    connect(ui->wireFrameButton, SIGNAL(released()), this, SLOT(wireFrameDisplay()));
    connect(ui->colorButton, SIGNAL(released()), this, SLOT(colorMesh()));
    connect(ui->insertButton, SIGNAL(released()), this, SLOT(insert()));
    connect(ui->flipButton, SIGNAL(released()), this, SLOT(flip()));
    connect(ui->insert_x, SIGNAL(valueChanged(double)), this, SLOT(set_insert_x(double)));
    connect(ui->insert_y, SIGNAL(valueChanged(double)), this, SLOT(set_insert_y(double)));
    connect(ui->insert_z, SIGNAL(valueChanged(double)), this, SLOT(set_insert_z(double)));

    connect(ui->collapse_face, SIGNAL(valueChanged(int)), this, SLOT(set_collapse_face(int)));
    connect(ui->collapse_vertice, SIGNAL(valueChanged(int)), this, SLOT(set_collapse_vertice(int)));
    connect(ui->collapseButton, SIGNAL(released()), this, SLOT(collapse()));

    // connect(ui->collapse_vertice, SIGNAL(valueChanged(string)), this, SLOT(set_collapse_vertice(int)));
    connect(ui->load_mesh, SIGNAL(released()), this, SLOT(load_mesh()));
    connect(ui->cleanButton, SIGNAL(released()), this, SLOT(clean()));

    connect(ui->simplifyButton, SIGNAL(released()), this, SLOT(simplify()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButton()
{
    ui->exitButton->setText("Released");
}

void MainWindow::wireFrameDisplay()
{
    ui->widget->setWireframe(true);
}

void MainWindow::colorMesh() {
    ui->widget->setWireframe(false);
}

void MainWindow::insert() {
    ui->widget->insert(insert_x, insert_y, insert_z);
}

void MainWindow::flip() {
    ui->widget->flip(ui->flip_faceA->value(), ui->flip_faceB->value());
}

void MainWindow::collapse() {
    ui->widget->collapse(collapse_face,collapse_vertice);
}

void MainWindow::set_insert_x(double x) {
    insert_x = x;
}
void MainWindow::set_insert_y(double y) {
    insert_y = y;
}
void MainWindow::set_insert_z(double z) {
    insert_z = z;
}

void MainWindow::set_collapse_face(int face) {
    this->collapse_face = face;
}
void MainWindow::set_collapse_vertice(int vertice) {
    this->collapse_vertice = vertice;
}

void MainWindow::load_mesh() {
    QString qs = ui->mesh_filename->text();
    std::string utf8_text = qs.toUtf8().constData();

    ui->widget->loadMesh(utf8_text);
}

void MainWindow::clean() {
    ui->widget->clean();
}

void MainWindow::simplify() {
    ui->widget->simplify(ui->simplify_nb->value());
}
