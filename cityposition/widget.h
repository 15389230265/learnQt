#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    //私有槽函数都是手动添加的，
    //onProvinceIndexChange(int) 用于关联省份组合框的序号变化信号，
    //onCityIndexChange(int) 用于关联市县组合框的序号变化信号
private slots:
    void onProvinceIndexChange(int index);
    void onCityIndexChange(int index);

private:
    Ui::Widget *ui;
    QVector<QString> m_vProvinces;
    QVector<QVector<QString>> m_vCities;
    QVector<QVector<double>> m_vLongitudes;
    QVector<QVector<double>> m_vLatitudes;
    void loadPositions();
};

#endif // WIDGET_H
