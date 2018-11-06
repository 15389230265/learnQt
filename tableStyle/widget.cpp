#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(4);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            QTableWidgetItem *itemNew = new QTableWidgetItem();
            itemNew->setText(tr("tableItem %1, %2").arg(i).arg(j));
            ui->tableWidget->setItem(i, j, itemNew);
        }
    }
}

Widget::~Widget()
{
    delete ui;
}

//如果样式表需要设置多次或子控件需要定制，那么一般建议用类名和大括号包裹样式表。
void Widget::on_pushButtonAlternatingRowColors_clicked()
{
    //启用双色交替行显示
    ui->tableWidget->setAlternatingRowColors(true);
    //定制样式表，交替行采用天蓝色，表格的网格线用深绿色
    QString strStyle = " QTableWidget{ alternate-background-color: skyblue; "
            "gridline-color: darkgreen; } ";
    //添加给表格控件，旧的样式表保留
    ui->tableWidget->setStyleSheet(ui->tableWidget->styleSheet() + strStyle);
}

void Widget::on_pushButtonSelectionCustom_clicked()
{
    //selection-color 是选中条目的前景色
    //selection-background-color 是选中条目的背景色
    QString strStyle = " QTableWidget { selection-color: red; "
            "selection-background-color: yellow; } ";
    ui->tableWidget->setStyleSheet(ui->tableWidget->styleSheet() + strStyle);
    //设置当前条目为高亮色
    QTableWidgetItem *curItem = ui->tableWidget->currentItem();
    if(NULL != curItem){
        curItem->setSelected(true);
    }
}

void Widget::on_pushButtonItemCustom_clicked()
{
    // QTableWidget::item 就是所有条目的样式表配置
    // color 是前景色，background-color 是背景色
    QString strStyle = " QTableWidget::item { "
            "color: blue; "
            "background-color: lightgreen; "
            "} ";
    //会覆盖前面的双色交替行、选中高亮颜色的配置。
    ui->tableWidget->setStyleSheet(ui->tableWidget->styleSheet() + strStyle);
}

void Widget::on_pushButtonCornerButtonCustom_clicked()
{
    // QTableCornerButton::section 就是设置表格左上角的按钮风格
    QString strStyle = " QTableCornerButton::section { "
            "background: green; "
            "border: 2px outset green; "
            "} ";
    ui->tableWidget->setStyleSheet(ui->tableWidget->styleSheet() + strStyle);
}

void Widget::on_pushButtonHeaderCustom_clicked()
{
    //QHeaderView 就是表头的类，定制该类的样式表
    //前景色背景色的一般都是 color  和 background-color
    QString strStyle = " QHeaderView { "
            "color: darkblue; "
            "background-color: cyan; "
            "} ";
    ui->tableWidget->setStyleSheet(ui->tableWidget->styleSheet() + strStyle);
}

void Widget::on_pushButtonCclearStyle_clicked()
{
    qDebug()<<"old style sheet: \r\n"<<ui->tableWidget->styleSheet()<<endl;
    ui->tableWidget->setStyleSheet("");
    ui->tableWidget->setAlternatingRowColors(false);
}
