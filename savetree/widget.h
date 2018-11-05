#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QFile>
#include <QDataStream>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonAddTop_clicked();

    void on_pushButtonAddChild_clicked();

    void on_pushButtonEditHeader_clicked();

    void on_pushButtonSaveFile_clicked();

    void on_pushButtonClearTree_clicked();

    void on_pushButtonLoadFile_clicked();

private:
    Ui::Widget *ui;
    QFile m_file;
    QDataStream m_ds;
    void SaveTree(QTreeWidgetItem *curItem);
    void LoadTree(QTreeWidgetItem *curItem);
    static const int MAX_COLS = 1000;
};

#endif // WIDGET_H
