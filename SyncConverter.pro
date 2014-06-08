QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SyncConverter
TEMPLATE = app

TEMP_DIR = .obj

OBJECTS_DIR = $$TEMP_DIR
MOC_DIR = $$TEMP_DIR
UI_DIR = $$TEMP_DIR
RCC_DIR = $$TEMP_DIR

INCLUDEPATH += src

HEADERS += \
    src/MainWindow.h \
    src/Converter.h \
    src/FormatContainer.h \
    src/FormatsDialog.h \
    src/FormatDialog.h

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/Converter.cpp \
    src/FormatContainer.cpp \
    src/FormatsDialog.cpp \
    src/FormatDialog.cpp

FORMS += \
    src/MainWindow.ui \
    src/FormatsDialog.ui \
    src/FormatDialog.ui
