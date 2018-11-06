#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    CreateMenu();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::CreateMenu(){
    m_menuContext = new QMenu(tr("ContextMenu")); //右键菜单其实不显示ContextMenu文本
    //创建“添加条目”菜单项并添加到菜单
    QAction *actAdd = new QAction(tr("添加条目"), this);
    m_menuContext->addAction(actAdd);
    QAction *actEdit = new QAction(tr("编辑条目"), this);
    m_menuContext->addAction(actEdit);
    QAction *actDel = new QAction(tr("删除条目"), this);
    m_menuContext->addAction(actDel);
    QAction *actClearAll = new QAction(tr("清空所有"), this);
    m_menuContext->addAction(actClearAll);
    //设置列表控件可以有自定义右键菜单
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    //关联弹出菜单信号
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(onCustomContextMenuRequested(QPoint)));
    //为四个菜单项关联点击信号到槽函数
    connect(actAdd, SIGNAL(triggered()), this, SLOT(onAddItemTriggered()));
    connect(actEdit, SIGNAL(triggered()), this, SLOT(onEditItemTriggered()));
    connect(actDel, SIGNAL(triggered()), this, SLOT(onDelItemTriggered()));
    connect(actClearAll, SIGNAL(triggered()), this, SLOT(onClearAllTriggered()));
    return;
}

//弹出右键菜单的槽函数
void Widget::onCustomContextMenuRequested(const QPoint & pos){
    //控件内的相对坐标转为屏幕坐标
    //是列表控件发出的信号，就用列表控件的转换函数
    QPoint screenPos = ui->listWidget->mapToGlobal(pos);
    //弹出菜单
    QAction *actRet = m_menuContext->exec(screenPos);
    if(NULL != actRet){
        qDebug()<<tr("返回的菜单项：") + actRet->text();
    }
}

//添加条目菜单项的槽函数
void Widget::onAddItemTriggered(){
    QListWidgetItem *itemNew = new QListWidgetItem(tr("新建条目"));
    itemNew->setFlags(itemNew->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(itemNew);
    ui->listWidget->setCurrentItem(itemNew);
    //显示条目的编辑框
    ui->listWidget->editItem(itemNew);
}

void Widget::onEditItemTriggered(){
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    if(NULL == curItem){
        qDebug()<<tr("没有选中的条目。");
        return;
    }
    curItem->setFlags(curItem->flags() | Qt::ItemIsEditable);
    ui->listWidget->editItem(curItem);
}

void Widget::onDelItemTriggered(){
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    if(NULL == curItem){
        qDebug()<<tr("没有选中的条目。");
        return;
    }
    delete curItem; curItem = NULL;
}

void Widget::onClearAllTriggered(){
    int nCount = ui->listWidget->count();
//    qDebug()<<nCount;
    if(nCount < 1){
        return;
    }
    int buttonRet = QMessageBox::question(this, tr("清空所有"), tr("请确认是否清空所有条目？"));
    if(QMessageBox::Yes == buttonRet){
        ui->listWidget->clear();
    }
    else{
        return;
    }
}
