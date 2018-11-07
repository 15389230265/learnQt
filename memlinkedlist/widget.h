#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLinkedList>

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
    void on_pushButtonAllocate_clicked();

    void on_pushButtonFind_clicked();

    void on_pushButtonFree_clicked();

private:
    Ui::Widget *ui;
    QLinkedList<QString> m_memFree;
    QLinkedList<QString> m_memUsed;
    void updateListWidgets();
};

#endif // WIDGET_H
