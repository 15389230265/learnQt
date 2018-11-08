#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLinkedList>
#include <QList>
#include <QVector>
#include <QElapsedTimer> //耗费计时
#include <QLocale> //本地化类，用于打印逗号分隔的数字

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
    void on_pushButtonPrepend_clicked();

    void on_pushButtonMidInsert_clicked();

    void on_pushButtonAppend_clicked();

    void on_pushButtonRandAccess_clicked();

private:
    Ui::Widget *ui;
    QLinkedList<int> m_linkdList;
    QList<int> m_list;
    QVector<int> m_vector;
    QElapsedTimer m_calcTimer;
    QLocale m_locale;
};

#endif // WIDGET_H
