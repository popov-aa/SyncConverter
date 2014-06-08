#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Converter.h"
#include "FormatContainer.h"
#include "FormatsDialog.h"

#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_inputDirectory("INPUT_DIRECTORY"),
    m_outputDirectory("OUTPUT_DIRECTORY"),
    m_action(Stop)
{
    ui->setupUi(this);

    m_settings = new QSettings(QApplication::organizationName(), QApplication::applicationName());
    m_formatContainer = new FormatContainer(m_settings, this);
    m_converter = new Converter(this);

    ui->leInputDir->setText(m_settings->value(m_inputDirectory).toString());
    ui->leOutputDir->setText(m_settings->value(m_outputDirectory).toString());

    formatComboBoxUpdate();
    triggerButtonUpdate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tbInputDir_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this, tr("Open input directory..."), QDir::homePath());
    if (!dirpath.isEmpty())
    {
        ui->leInputDir->setText(dirpath);
        m_settings->setValue(m_inputDirectory, dirpath);
    }
}

void MainWindow::on_tbOutputDir_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this, tr("Open output directory..."), QDir::homePath());
    if (!dirpath.isEmpty())
    {
        ui->leOutputDir->setText(dirpath);
        m_settings->setValue(m_outputDirectory, dirpath);
    }
}

void MainWindow::on_pbTrigger_clicked()
{
    switch (m_action)
    {
        case Start:
        {
            if (ui->leInputDir->text().isEmpty())
            {
                QMessageBox::warning(this, tr("Warning..."), tr("Input directory is empty."));
            }
            else if (ui->leOutputDir->text().isEmpty())
            {
                QMessageBox::warning(this, tr("Warning..."), tr("Output directory is empty."));
            }
            else if (ui->cbOutputFormat->currentIndex() == -1)
            {
                QMessageBox::warning(this, tr("Warning..."), tr("Format is not selected."));
            }
            else
            {
                m_converter->convertDirectory(
                            ui->leInputDir->text(),
                            ui->leOutputDir->text(),
                            ui->cbOutputFormat->currentText(),
                            m_formatContainer->format(ui->cbOutputFormat->currentText())
                            );
                m_action = Stop;
                return triggerButtonUpdate();
            }
        }
        case Stop:
        {
            m_converter->stop();
            m_action = Start;
            return triggerButtonUpdate();
        }
    }
}

void MainWindow::triggerButtonUpdate()
{
    switch (m_action)
    {
        case Start: ui->pbTrigger->setText(tr("Start")); break;
        case Stop: ui->pbTrigger->setText(tr("Stop")); break;
    }
}

void MainWindow::on_tbOutputFormat_clicked()
{
    FormatsDialog formatsDialog(m_formatContainer, this);
    formatsDialog.exec();
    formatComboBoxUpdate();
}

void MainWindow::formatComboBoxUpdate()
{
    ui->cbOutputFormat->clear();
    ui->cbOutputFormat->addItems(m_formatContainer->names());
}

void MainWindow::on_pbQuit_clicked()
{
    QApplication::quit();
}
