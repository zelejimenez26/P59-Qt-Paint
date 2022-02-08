#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>

#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QInputDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void on_actionAncho_triggered();

    void on_actionSalir_triggered();

    void on_actionColor_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();


    void on_actionLineas_triggered();

    void on_actionLibre_triggered();

    void on_actionRect_nculos_triggered();

    void on_actionCircunferencias_triggered();

private:
    Ui::Principal *ui;
    QImage *m_imagen;        // Imagen sobre la que se va a dibujar
    QPainter *m_painter;     // Painter de la imagen
    QPoint m_inicial;        // Punto incial para dibujar la línea
    QPoint m_final;          // Punto final para dibujar la línea
    bool m_puedeDibujar;     // Determina si debe o no dibujar
    int m_ancho;             // Define el ancho del pincel
    QColor m_color;          // Define el color del pincel
    int m_numLineas;         // Cuenta el número de líneas

    int m_opcion;            // Para definir las demas opciones de dibujo
    bool m_vtOpcion=true;    // Verifica el momento de elegir una opcion

};
#endif // PRINCIPAL_H
