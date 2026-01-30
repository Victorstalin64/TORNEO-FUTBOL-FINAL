#include "visualizar.h"
#include "ui_visualizar.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>

Visualizar::Visualizar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Visualizar)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

Visualizar::~Visualizar()
{
    delete ui;
}

void Visualizar::on_btnCargar_clicked()
{
    ui->tableWidget->setRowCount(0);

    QFile archivo("equipos.txt");

    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);

        while (!in.atEnd()) {
            QString linea = in.readLine();
            QStringList datos = linea.split(",");
            if (datos.size() >= 5) {
                int fila = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(fila);

                ui->tableWidget->setItem(fila, 0, new QTableWidgetItem(datos[0]));
                ui->tableWidget->setItem(fila, 1, new QTableWidgetItem(datos[1]));
                ui->tableWidget->setItem(fila, 2, new QTableWidgetItem(datos[2]));
                ui->tableWidget->setItem(fila, 3, new QTableWidgetItem(datos[3]));

                // Para que ordene correctamente como número y no como texto
                QTableWidgetItem *itemPuntos = new QTableWidgetItem();
                itemPuntos->setData(Qt::DisplayRole, datos[4].toInt());
                ui->tableWidget->setItem(fila, 4, itemPuntos);
            }
        }
        archivo.close();

        // ordenar por puntos
        ui->tableWidget->sortItems(4, Qt::DescendingOrder);
    }
}
