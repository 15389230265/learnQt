#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QTreeWidgetItem>

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

    void on_pushButtonDelLeaf_clicked();

    void on_pushButtonDelSubtree_clicked();

private:
    Ui::Widget *ui;
    void RemoveSubtree(QTreeWidgetItem *curLevelItem);
};

#endif // WIDGET_H
