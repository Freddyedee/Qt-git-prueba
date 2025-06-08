// validaciones.cpp
#include "validacionesdenumeros.h"
#include <QRegularExpression>

bool validarSoloNumeros(QString texto) {
    QRegularExpression regex("^\\d+$"); // solo dígitos
    return regex.match(texto).hasMatch();
}

