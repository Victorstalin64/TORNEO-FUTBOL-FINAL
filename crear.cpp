#include "crear.h"
#include "ui_crear.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

crear::crear(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::crear)
{
    ui->setupUi(this);

    QRegularExpression regAlfaNumerico("^[a-zA-Z0-9áéíóúÁÉÍÓÚñÑ\\s]*$");
    QRegularExpressionValidator *valAlfaNumerico = new QRegularExpressionValidator(regAlfaNumerico, this);
    ui->lineEdit_id->setValidator(valAlfaNumerico);
    ui->lineEdit_nombre->setValidator(valAlfaNumerico);

    QRegularExpression regSoloLetras("^[a-zA-ZáéíóúÁÉÍÓÚñÑ\\s]*$");
    QRegularExpressionValidator *valLetras = new QRegularExpressionValidator(regSoloLetras, this);
    ui->lineEdit_ciudad->setValidator(valLetras);
    ui->lineEdit_dt->setValidator(valLetras);

    QRegularExpression regSoloNumeros("^[0-9]*$");
    QRegularExpressionValidator *valNumeros = new QRegularExpressionValidator(regSoloNumeros, this);
    ui->lineEdit_puntos->setValidator(valNumeros);
}

crear::~crear()
{
    delete ui;
}

void crear::on_toolButton_clicked()
{
    QString id = ui->lineEdit_id->text();
    QString nombre = ui->lineEdit_nombre->text();
    QString ciudad = ui->lineEdit_ciudad->text();
    QString dt = ui->lineEdit_dt->text();
    QString puntosStr = ui->lineEdit_puntos->text();

    if(id.isEmpty() || nombre.isEmpty() || ciudad.isEmpty() || dt.isEmpty() || puntosStr.isEmpty()){
        QMessageBox::warning(this, "Error", "Por favor, llene todos los campos.");
        return;
    }

    int puntos = puntosStr.toInt();

    QFile archivo("equipos.txt");

    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        while (!in.atEnd()) {
            QString linea = in.readLine();
            QStringList datos = linea.split(",");
            if (datos.size() > 0 && datos[0] == id) {
                QMessageBox::warning(this, "Error", "El ID ya existe. Use uno diferente.");
                archivo.close();
                return;
            }
        }
        archivo.close();
    }

    if (archivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&archivo);
        out << id << "," << nombre << "," << ciudad << "," << dt << "," << puntos << "\n";
        archivo.close();

        QMessageBox::information(this, "Éxito", "Equipo guardado correctamente.");
        this->accept();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo para guardar.");
    }
}
