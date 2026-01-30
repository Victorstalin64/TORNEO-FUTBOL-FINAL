#ifndef ELIMINAREQUIPO_H
#define ELIMINAREQUIPO_H

#include <QDialog>

namespace Ui {
class eliminarequipo;
}

class eliminarequipo : public QDialog
{
    Q_OBJECT

public:
    explicit eliminarequipo(QWidget *parent = nullptr);
    ~eliminarequipo();

private slots:

    void on_btnEliminar_clicked();
    void on_btnCancelar_clicked();
    void on_btnBuscar_clicked();
private:
    Ui::eliminarequipo *ui;
};

#endif // ELIMINAREQUIPO_H
