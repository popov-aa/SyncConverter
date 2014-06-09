#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class FormatContainer;
class Converter;
class QSettings;

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:

    explicit MainWindow(QWidget * parent = 0);
    ~MainWindow();

private slots:

    void on_tbInputDir_clicked();
    void on_tbOutputDir_clicked();
    void on_pbTrigger_clicked();
    void on_tbOutputFormat_clicked();
    void on_pbQuit_clicked();

    void formatComboBoxUpdate();
    void triggerButtonUpdate();

    void fileConvertFailed(QString output);

private:

    Ui::MainWindow * ui;

    QSettings * m_settings;
    FormatContainer * m_formatContainer;
    Converter * m_converter;

    QString m_inputDirectory;
    QString m_outputDirectory;

};

#endif // MAINWINDOW_H
