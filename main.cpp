#include "principal.h"

#include <QApplication>

#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Objeto para manejar las traducciones
    QTranslator traducion;
    // Solicitando al usuario que seleccione un idioma
    QStringList idiomas;
    idiomas << "Español"<<"Ingles"<<"German";
    QString idiomaSeleccionado = QInputDialog::getItem(NULL,
                                                       "Idioma",
                                                       "Seleccione un idioma para iniciar",
                                                       idiomas);
    // Dependiendo del idioma seleccionado, carga el archivo de traducción
    if (idiomaSeleccionado == "Ingles"){
        traducion.load(":/miPaint_en.qm");
    }else if(idiomaSeleccionado == "German"){
        traducion.load(":/miPaint_ger.qm");
    }
    // Si es diferente de español, se instala la traducción en TODA la aplicación
    if (idiomaSeleccionado != "Español"){
        a.installTranslator(&traducion);
    }
    // Muestra la ventana principal
    Principal w;
    w.show();
    return a.exec();
}
