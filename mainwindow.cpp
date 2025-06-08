#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QMessageBox>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Aceptar_clicked()
{
    QString entrada = ui->Line_edit_Ingreso_de_relacion->text();


    // Validación básica
    if (entrada.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingresa una relación válida");
        return;
    }

    //creacion de .dot

    QFile file ("grafo.dot");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text )) {

        QTextStream out (&file);
        out << "digraph G {\n";         // usa "graph G {" si es no dirigido

        QStringList pares = entrada.split(")");

        for(QString par:pares){
            par = par.trimmed().remove("(").remove(")");
            QStringList nodos = par.split(",");
            if(nodos.size()==2){
                out << " " << nodos[0] << "->" << nodos[1] << ";\n";
            }
        }

        out << "}\n";
        file.close();

    }

    //Se llama para que genere imagen

    QProcess proceso;
    proceso.start("dot", QStringList() << "-Tpng" << "grafo.dot" << "-o" << "grafo.png");
    if (!proceso.waitForFinished()) {
        QMessageBox::critical(this, "ERROR", "No se pudo ejecutar Graphviz. Verifica que esté instalado.");
        return;
    }

    // muestra de imagen en label

    QPixmap imagen("grafo.png");
    if(!imagen.isNull()){
        ui->labelImagen -> setPixmap(imagen.scaled(250,250,Qt::KeepAspectRatio));

    }else{
        QMessageBox::critical(this, "ERROR", "No se pudo cargar el grafo generado");
    }

}


void MainWindow::on_pushButton_closeapp_clicked()
{
    this->close(); // cerrar la aplicacion

}

