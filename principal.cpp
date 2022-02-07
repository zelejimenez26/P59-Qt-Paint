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
    m_opcion=1;
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

    if(m_opcion==1){
        m_inicial=event->pos();
    }else if(m_opcion==2){
        if(m_vtOpcion){
            m_inicial = event->pos();
        }else{
            m_final=event->pos();
            QPen pincel;
            pincel.setWidth(m_ancho);
            pincel.setColor(m_color);
            m_painter->setPen(pincel);
            //Dibujar lineas rectas
            m_painter->drawLine(m_inicial, m_final);
            //Actualizar la interfaz
            update();
        }
    }else if(m_opcion==3){
        if(m_vtOpcion){
            m_inicial = event->pos();
        }else{
            m_final=event->pos();
            //Para dibujar rectangulo
            int ancho=m_final.x() - m_inicial.x();
            int alto=m_final.y() - m_inicial.y();
            QPen pincel;
            pincel.setWidth(m_ancho);
            pincel.setColor(m_color);
            m_painter->setPen(pincel);
            //Dibujar rectangulo
            m_painter->drawRect(m_inicial.x(), m_inicial.y(), ancho, alto);
            //Actualizar la interfaz
            update();
        }
    }else if(m_opcion==4){
        if(m_vtOpcion){
            m_inicial = event->pos();
        }else{
            m_final=event->pos();
            //Para dibujar circulo
            int ancho=m_final.x() - m_inicial.x();
            int alto=m_final.y() - m_inicial.y();
            QPen pincel;
            pincel.setWidth(m_ancho);
            pincel.setColor(m_color);
            m_painter->setPen(pincel);
            //Dibujar circulo
            QRectF rectangulo(m_inicial.x(), m_inicial.y(), ancho, alto);
            m_painter->drawEllipse(rectangulo);
            //Actualizar la interfaz
            update();
        }
    }
    m_vtOpcion=!m_vtOpcion;
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{

    // Validar si se puede dibujar
    if (m_puedeDibujar ) {
        event->accept();
        return;
    }

    if(m_opcion==1){
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
    }
    // Actualizar la interfaz
    update();
    // Actualizar el punto inicial
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

/* Establecer una opcion para cada tipo de dibujo.
 *
 * El dibujo de tipo libre sera tomado como la opcion 1 o la opcion por
 * defecto que se ejecuta cuando inicia el programa.
 */

void Principal::on_actionLineas_triggered()
{
    m_opcion=2;
}


void Principal::on_actionLibre_triggered()
{
    m_opcion=1;
}


void Principal::on_actionRect_nculos_triggered()
{
    m_opcion=3;
}


void Principal::on_actionCircunferencias_triggered()
{
    m_opcion=4;
}

