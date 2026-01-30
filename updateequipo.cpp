#include "updateequipo.h"
#include "ui_updateequipo.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

updateequipo::updateequipo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateequipo)
{
    ui->setupUi(this);

    QRegularExpression soloLetras("^[a-zA-ZáéíóúÁÉÍÓÚñÑ\\s]*$");
    QRegularExpressionValidator *validadorTexto = new QRegularExpressionValidator(soloLetras, this);

    ui->lineEditNuevoNombre->setValidator(validadorTexto);
    ui->lineEditNuevaCiudad->setValidator(validadorTexto);
    ui->lineEditNuevoDT->setValidator(validadorTexto);

    QRegularExpression soloNumeros("^[0-9]*$");
    QRegularExpressionValidator *validadorSoloNumeros = new QRegularExpressionValidator(soloNumeros, this);
    ui->lineEditNuevoId->setValidator(validadorSoloNumeros);
    ui->lineEditBuscarId->setValidator(validadorSoloNumeros);
}

updateequipo::~updateequipo()
{
    delete ui;
}

void updateequipo::on_btnBuscar_clicked()
{
    QString idABuscar = ui->lineEditBuscarId->text();
    if(idABuscar.isEmpty()){
        QMessageBox::warning(this,"Error","Ingrese un ID para buscar");
        return;
    }

    QFile archivo("equipos.txt");
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this,"Error","No se encontró el archivo equipos.txt");
        return;
    }

    QTextStream in(&archivo);
    bool encontrado = false;
    while(!in.atEnd()){
        QString linea = in.readLine();
        QStringList datos = linea.split(",");

        if(datos.size() >= 5 && datos[0] == idABuscar){
            ui->lineEditNuevoId->setText(datos[0]);
            ui->lineEditNuevoNombre->setText(datos[1]);
            ui->lineEditNuevaCiudad->setText(datos[2]);
            ui->lineEditNuevoDT->setText(datos[3]);
            ui->spinBoxPuntos->setValue(datos[4].toInt());
            encontrado = true;
            break;
        }
    }
    archivo.close();

    if(!encontrado) {
        QMessageBox::warning(this,"Error","ID no encontrado");
    }
}

void updateequipo::on_Actualizar_clicked()
{
    QString idOriginal = ui->lineEditBuscarId->text();
    QString nuevoId = ui->lineEditNuevoId->text();
    QString nombre = ui->lineEditNuevoNombre->text();
    QString ciudad = ui->lineEditNuevaCiudad->text();
    QString dt = ui->lineEditNuevoDT->text();
    int puntosVal = ui->spinBoxPuntos->value();
    QString puntos = QString::number(puntosVal);

    if(nuevoId.isEmpty() || nombre.isEmpty() || ciudad.isEmpty() || dt.isEmpty()){
        QMessageBox::warning(this, "Error", "No pueden estar los campos vacios");
        return;
    }

    if(puntosVal < 0){
        QMessageBox::warning(this, "Error", "Los puntos no pueden ser menor que cero");
        return;
    }

    QFile archivo("equipos.txt");
    QStringList lineas;
    bool modificado = false;

    if(archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&archivo);
        while(!in.atEnd()){
            QString linea = in.readLine();
            QStringList datos = linea.split(",");
            if(datos.size() >= 1 && datos[0] == idOriginal){
                lineas.append(nuevoId + "," + nombre + "," + ciudad + "," + dt + "," + puntos);
                modificado = true;
            } else {
                lineas.append(linea);
            }
        }
        archivo.close();
    }

    if(modificado && archivo.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        QTextStream out(&archivo);
        for(const QString &l : lineas){
            out << l << "\n";
        }
        archivo.close();
        QMessageBox::information(this,"Éxito","Equipo actualizado");
        this->accept();
    } else {
        QMessageBox::warning(this,"Error","No se pudo actualizar el archivo");
    }
}

void updateequipo::on_btnCancelar_clicked()
{
    this->close();
}
