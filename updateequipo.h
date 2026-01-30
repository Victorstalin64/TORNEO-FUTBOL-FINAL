#ifndef UPDATEEQUIPO_H
#define UPDATEEQUIPO_H

#include <QDialog>

namespace Ui {
class updateequipo;
}

class updateequipo : public QDialog
{
    Q_OBJECT

public:
    explicit updateequipo(QWidget *parent = nullptr);
    ~updateequipo();

private slots:
    void on_btnBuscar_clicked();
    void on_Actualizar_clicked();
    void on_btnCancelar_clicked();   // 👈 NUEVO

private:
    Ui::updateequipo *ui;
};

#endif // UPDATEEQUIPO_H
