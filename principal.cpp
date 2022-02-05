#include "principal.h"
#include "ui_principal.h"

#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Instanciando la imagen (creando)
    m_imagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    // Rellenar la imagen de color blanco
    m_imagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    m_painter = new QPainter(m_imagen);
    m_painter->setRenderHint(QPainter::Antialiasing);
    // Inicializar otras variables
    m_puedeDibujar = false;
    m_color = Qt::black;
    m_ancho = DEFAULT_ANCHO;
    m_numLineas = 0;
}

Principal::~Principal()
{
    delete ui;
    delete m_painter;
    delete m_imagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    // Crear el painter de la ventana principal
    QPainter painter(this);
    // Dibujar la imagen
    painter.drawImage(0, 0, *m_imagen);
    // Aceptar el evento
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    m_puedeDibujar = true;
    m_inicial = event->pos();
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
    // Validar si se puede dibujar
    if ( !m_puedeDibujar ) {
        event->accept();
        return;
    }
    // Capturar el punto donde se suelta el mouse
    m_final = event->pos();
    // Crear un pincel y establecer atributos
    QPen pincel;
    pincel.setColor(m_color);
    pincel.setWidth(m_ancho);
    // Dibujar una linea
    m_painter->setPen(pincel);
    m_painter->drawLine(m_inicial, m_final);
    // Mostrar el número de líneas en la barra de estado
    ui->statusbar->showMessage("Número de líneas: " + QString::number(++m_numLineas));
    // Actualizar la interfaz
    update();
    // actualizar el punto inicial
    m_inicial = m_final;
}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    m_puedeDibujar = false;
    // Aceptar el vento
    event->accept();

}


void Principal::on_actionAncho_triggered()
{
    m_ancho = QInputDialog::getInt(this,
                                  "Ancho del pincel",
                                  "Ingrese el ancho del pincel de dibujo",
                                  m_ancho,
                                  1, 100);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionColor_triggered()
{
    m_color = QColorDialog::getColor(m_color,
                                    this,
                                    "Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    m_imagen->fill(Qt::white);
    m_numLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imágenes (*.png)");
    if ( !nombreArchivo.isEmpty() ){
        if (m_imagen->save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}

void Principal::on_actionLineas_triggered()
{

}

