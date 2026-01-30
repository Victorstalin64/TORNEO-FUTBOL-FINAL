#include "eliminarequipo.h"
#include "ui_eliminarequipo.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>

eliminarequipo::eliminarequipo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eliminarequipo)
{
    ui->setupUi(this);
}

eliminarequipo::~eliminarequipo()
{
    delete ui;
}

void eliminarequipo::on_btnBuscar_clicked()
{
    QString idABuscar = ui->lineEditIdEquipo->text();
    if(idABuscar.isEmpty()){
        QMessageBox::warning(this,"Error","Ingrese un ID para buscar");
        return;
    }

    QFile archivo("equipos.txt");
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this,"Error","No se pudo abrir el archivo");
        return;
    }

    QTextStream in(&archivo);
    bool encontrado = false;
    while(!in.atEnd()){
        QString linea = in.readLine();
        QStringList datos = linea.split(",");

        if(datos.size() >= 5 && datos[0] == idABuscar){
            ui->lineEditNombre->setText(datos[1]);
            ui->lineEditCiudad->setText(datos[2]);
            ui->lineEditDT->setText(datos[3]);
            ui->spinBoxPuntos->setValue(datos[4].toInt());
            encontrado = true;
            break;
        }
    }
    archivo.close();

    if(!encontrado) QMessageBox::warning(this,"Error","ID no encontrado");
}

void eliminarequipo::on_btnEliminar_clicked()
{
    QString idAEliminar = ui->lineEditIdEquipo->text();
    if(idAEliminar.isEmpty()) return;

    QMessageBox msgBox(QMessageBox::Question, "Eliminar",
                       "¿Seguro que quieres eliminar este equipo?",
                       QMessageBox::Yes | QMessageBox::No, this);
    msgBox.setButtonText(QMessageBox::Yes, "Sí");
    msgBox.setButtonText(QMessageBox::No, "No");

    int res = msgBox.exec();

    if(res == QMessageBox::No) return;

    QFile archivo("equipos.txt");
    QStringList lineasRestantes;
    bool encontrado = false;

    if(archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&archivo);
        while(!in.atEnd()){
            QString linea = in.readLine();
            QStringList datos = linea.split(",");
            if(datos.size() > 0 && datos[0] != idAEliminar) {
                lineasRestantes.append(linea);
            } else {
                encontrado = true;
            }
        }
        archivo.close();
    }

    if (!encontrado) {
        QMessageBox::warning(this, "Error", "No se encontró ningún equipo con ese ID.");
        return;
    }

    if(archivo.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        QTextStream out(&archivo);
        for(const QString &l : lineasRestantes) out << l << "\n";
        archivo.close();

        QMessageBox::information(this, "Éxito", "Equipo eliminado");
        this->close();
    }
}

void eliminarequipo::on_btnCancelar_clicked() {
    this->close();
}
