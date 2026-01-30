#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "visualizar.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Crear_clicked();

    void on_Leer_clicked();

    void on_Eliminar_clicked();

    void on_Actualizar_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
