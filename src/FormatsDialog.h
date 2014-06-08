#ifndef FORMATSDIALOG_H
#define FORMATSDIALOG_H

class FormatContainer;
class QTreeWidgetItem;

#include <QDialog>

namespace Ui
{
    class FormatsDialog;
}

class FormatsDialog : public QDialog
{

    Q_OBJECT

public:

    FormatsDialog(FormatContainer * formatContainer,
                  QWidget * parent = 0);
    ~FormatsDialog();

private slots:

    void on_twFormats_currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous);

    void on_tbAdd_clicked();

    void on_tbEdit_clicked();

    void on_tbRemove_clicked();

private:

    void reload();
    void updateItem(const QString & name);

private:

    Ui::FormatsDialog * ui;

    FormatContainer * m_formatContainer;

    QHash<QString,QTreeWidgetItem*> m_items;

};

#endif // FORMATSDIALOG_H
