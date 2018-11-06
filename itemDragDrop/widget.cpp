#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    for(int i=0; i<5; i++){
        QListWidgetItem *itemL = new QListWidgetItem(ui->listWidget);
        itemL->setText(tr("listItem %1").arg(i));
    }
    ui->treeWidget->setColumnCount(2);
    //各列均匀拉伸
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i=0; i<5; i++){
        QTreeWidgetItem *itemT = new QTreeWidgetItem(ui->treeWidget);
        itemT->setText(0, tr("treeItem %1, 0").arg(i));
        itemT->setText(1, tr("t%1, 1").arg(i));
    }
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(3);
    //各列均匀拉伸
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            QTableWidgetItem *itemTA = new QTableWidgetItem();
            itemTA->setText(tr("tableItem %1 %2").arg(i).arg(j));
            ui->tableWidget->setItem(i, j, itemTA);
        }
    }
    ui->radioButtonInter->setChecked(true);
    on_radioButtonInter_clicked(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_radioButtonInter_clicked(bool checked)
{
    if(checked){
        //列表控件启用内部移动
        ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);
        ui->treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
        ui->tableWidget->setDragDropMode(QAbstractItemView::InternalMove);
    }
}

void Widget::on_radioButtonOuter_clicked(bool checked)
{
    if(checked){
        //列表控件启用跨界拖拽
        SetOuterDragDrop(ui->listWidget);
        SetOuterDragDrop(ui->treeWidget);
        SetOuterDragDrop(ui->tableWidget);
    }
}

//启用跨界拖拽
void Widget::SetOuterDragDrop(QAbstractItemView *view){
    view->setSelectionMode(QAbstractItemView::SingleSelection); //单选模式
    //可以拖出源条目
    view->setDragEnabled(true);
    //视口可以接收拖入
    view->viewport()->setAcceptDrops(true);
    //启用拖拽的显示效果
    view->setDropIndicatorShown(true);
    //使用能拖能拽的模式
    view->setDragDropMode(QAbstractItemView::DragDrop);
}
