#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "crear.h"
#include "visualizar.h"
#include "eliminarequipo.h"
#include "updateequipo.h"
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Crear_clicked()
{
    crear *v = new crear(this);
    v->setAttribute(Qt::WA_DeleteOnClose);
    v->setModal(true);
    v->show();
}

void MainWindow::on_Leer_clicked()
{
    QFile archivo("equipos.txt");

    if (!archivo.exists() || archivo.size() == 0) {
        QMessageBox::warning(this, "Aviso", "Aún no existen equipos registrados");
        return;
    }

    Visualizar *ventana = new Visualizar();
    ventana->setAttribute(Qt::WA_DeleteOnClose);
    ventana->setWindowModality(Qt::ApplicationModal);
    ventana->show();
}

void MainWindow::on_Eliminar_clicked()
{
    QFile archivo("equipos.txt");

    if (!archivo.exists() || archivo.size() == 0) {
        QMessageBox::warning(this, "Aviso", "Aún no existen equipos registrados");
        return;
    }

    eliminarequipo *ventanaE = new eliminarequipo(this);
    ventanaE->setWindowFlags(Qt::Window);
    ventanaE->setAttribute(Qt::WA_DeleteOnClose);
    ventanaE->show();
}

void MainWindow::on_Actualizar_clicked()
{
    QFile archivo("equipos.txt");

    if (!archivo.exists() || archivo.size() == 0) {
        QMessageBox::warning(this, "Aviso", "Aún no existen equipos registrados");
        return;
    }

    updateequipo *ventanaU = new updateequipo(this);
    ventanaU->setWindowFlags(Qt::Window);
    ventanaU->setAttribute(Qt::WA_DeleteOnClose);
    ventanaU->show();
}
