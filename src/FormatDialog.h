#ifndef FORMATDIALOG_H
#define FORMATDIALOG_H

#include <QDialog>

namespace Ui
{
    class FormatDialog;
}

class FormatDialog : public QDialog
{

    Q_OBJECT

public:

    explicit FormatDialog(QWidget * parent = 0);
    ~FormatDialog();

    QString extension() const;
    QString format() const;

public slots:

    void setExtension(const QString & extension);
    void setFormat(const QString & format);

    void setUsedExtensions(const QStringList & usedExtensions);
    void setExtensionReadOnly(bool isReadOnly);

private slots:

    void on_buttonBox_accepted();

private:

    Ui::FormatDialog * ui;
    QStringList m_usedExtensions;

};

#endif // FORMATDIALOG_H
