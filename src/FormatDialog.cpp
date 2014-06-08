#include "FormatDialog.h"
#include "ui_FormatDialog.h"

#include <QMessageBox>

FormatDialog::FormatDialog(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::FormatDialog)
{
    ui->setupUi(this);
}

FormatDialog::~FormatDialog()
{
    delete ui;
}

QString FormatDialog::extension() const
{
    return ui->leExtension->text();
}

QString FormatDialog::format() const
{
    return ui->leFormat->text();
}

void FormatDialog::setExtension(const QString & extension)
{
    ui->leExtension->setText(extension);
}

void FormatDialog::setFormat(const QString & format)
{
    ui->leFormat->setText(format);
}

void FormatDialog::setUsedExtensions(const QStringList & usedExtensions)
{
    m_usedExtensions = usedExtensions;
}

void FormatDialog::setExtensionReadOnly(bool isReadOnly)
{
    ui->leExtension->setReadOnly(isReadOnly);
}

void FormatDialog::on_buttonBox_accepted()
{
    if (ui->leExtension->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Extension is empty."));
    }
    else if (ui->leFormat->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Format is empty."));
    }
    else if (m_usedExtensions.contains(ui->leExtension->text()))
    {
        QMessageBox::warning(this, tr("Warning..."), tr("Extension \"%1\" is exists already.").arg(ui->leExtension->text()));
    }
    else
    {
        accept();
    }
}
