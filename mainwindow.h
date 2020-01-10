#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void onButton();
    void wireFrameDisplay();
    void colorMesh();
    void insert();
    void flip();
    void collapse();

    void set_insert_x(double x);
    void set_insert_y(double y);
    void set_insert_z(double z);

    void set_collapse_face(int face);
    void set_collapse_vertice(int vertice);

    void load_mesh();
    void clean();
    void simplify();
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    double insert_x;
    double insert_y;
    double insert_z;

    int collapse_face;
    int collapse_vertice;
};

#endif // MAINWINDOW_H
