#include "FormatsDialog.h"
#include "ui_FormatsDialog.h"

#include "FormatContainer.h"
#include "FormatDialog.h"

#include <QTreeWidgetItem>
#include <QMessageBox>

FormatsDialog::FormatsDialog(FormatContainer * formatContainer,
                             QWidget * parent) :
    QDialog(parent),
    ui(new Ui::FormatsDialog),
    m_formatContainer(formatContainer)
{
    ui->setupUi(this);

    ui->tbAdd->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->tbEdit->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->tbRemove->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogCloseButton));

    reload();
}

FormatsDialog::~FormatsDialog()
{
    delete ui;
}

void FormatsDialog::on_twFormats_currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous)
{
    ui->tbEdit->setEnabled(current);
    ui->tbRemove->setEnabled(current);
}

void FormatsDialog::on_tbAdd_clicked()
{
    FormatDialog formatDialog(this);
    formatDialog.setUsedExtensions(m_formatContainer->names());
    if (formatDialog.exec() == QDialog::Accepted)
    {
        m_formatContainer->insertFormat(formatDialog.extension(), formatDialog.format());
        reload();
    }
}

void FormatsDialog::on_tbEdit_clicked()
{
    FormatDialog formatDialog(this);
    formatDialog.setExtensionReadOnly(true);
    if (formatDialog.exec() == QDialog::Accepted)
    {
        m_formatContainer->insertFormat(formatDialog.extension(), formatDialog.format());
        reload();
    }
}

void FormatsDialog::on_tbRemove_clicked()
{
    QTreeWidgetItem * item = ui->twFormats->currentItem();

    if (m_items.values().contains(item))
    {
        QString name = m_items.key(item);
        m_formatContainer->removeFormat(name);
    }

    reload();
}

void FormatsDialog::reload()
{
    qDeleteAll(m_items);
    m_items.clear();

    foreach (QString name, m_formatContainer->names())
    {
        m_items[name] = new QTreeWidgetItem(ui->twFormats);
        updateItem(name);
    }
}

void FormatsDialog::updateItem(const QString & name)
{
    QTreeWidgetItem * item = m_items[name];
    item->setText(0, name);
    item->setText(1, m_formatContainer->format(name));
}
