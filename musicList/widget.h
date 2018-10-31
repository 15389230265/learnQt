#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    void on_pushButtonAdd_clicked();

    void on_pushButtonDel_clicked();

    void on_pushButtonOutput_clicked();

    void on_pushButtonSerch_clicked();

    void on_checkBoxAutoSort_clicked(bool checked);

    void on_checkBoxReverse_clicked(bool checked);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
