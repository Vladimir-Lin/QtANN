NAME         = QtANN
TARGET       = $${NAME}
QT           = core
QT          -= gui
QT          -= gui
CONFIG(static,static|shared) {
# static version does not support Qt Script now
QT          -= script
} else {
QT          += script
}
QT          += network
QT          += sql

load(qt_build_config)
load(qt_module)

INCLUDEPATH += $${PWD}/../../include/$${NAME}

HEADERS     += $${PWD}/../../include/$${NAME}/qtann.h

SOURCES     += $${PWD}/nQtAnnNeuron.cpp
SOURCES     += $${PWD}/nQtAnnLayer.cpp
SOURCES     += $${PWD}/nQtAnnConnection.cpp
SOURCES     += $${PWD}/nQtAnnTrain.cpp
SOURCES     += $${PWD}/nANN.cpp

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

TRNAME       = $${NAME}
include ($${PWD}/../../Translations.pri)
