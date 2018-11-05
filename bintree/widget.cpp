#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置树形控件只有 1 列
    ui->treeWidget->setColumnCount(1);
    //创建A条目，添加到顶级条目
    QTreeWidgetItem *itemA = new QTreeWidgetItem();
    itemA->setText(0, "A");
    ui->treeWidget->addTopLevelItem(itemA);
    //创建 B、C条目，添加给 A
    QTreeWidgetItem *itemB = new QTreeWidgetItem();
    itemB->setText(0, "B");
    itemA->addChild(itemB);
    QTreeWidgetItem *itemC = new QTreeWidgetItem();
    itemC->setText(0, "C");
    itemA->addChild(itemC);
    //创建D、E条目，构造函数指定父条目为 B，自动设置父子关系
    QTreeWidgetItem *itemD = new QTreeWidgetItem(itemB);
    itemD->setText(0, "D");
    QTreeWidgetItem *itemE = new QTreeWidgetItem(itemB);
    itemE->setText(0, "E");
    //创建F、G条目，构造函数指定父条目为 C，自动设置父子关系
    QTreeWidgetItem *itemF = new QTreeWidgetItem(itemC);
    itemF->setText(0, "F");
    QTreeWidgetItem *itemG = new QTreeWidgetItem(itemC);
    itemG->setText(0, "G");
    //展开所有子孙节点
    ui->treeWidget->expandAll();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonPreorder_clicked()
{
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    qDebug()<<tr("先序遍历：");
    PreorderTraversal(itemA);
}

void Widget::PreorderTraversal(QTreeWidgetItem *curItem){
    if(NULL == curItem){
        return;
    }
    int nChildCount = curItem->childCount();
    if( nChildCount < 1 ){
        qDebug()<<curItem->text(0);
        return;
    }
    qDebug()<<curItem->text(0);
    for(int i=0; i<nChildCount; i++){
        QTreeWidgetItem *curChild = curItem->child(i);
        PreorderTraversal(curChild);
    }
    return;
}

void Widget::on_pushButtonPostorder_clicked()
{
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    qDebug()<<tr("后序遍历：");
    PostorderTraversal(itemA);
}

void Widget::PostorderTraversal(QTreeWidgetItem *curItem){
    if(NULL == curItem){
        return;
    }
    int nChildCount = curItem->childCount();
    if( nChildCount < 1 ){
        qDebug()<<curItem->text(0);
        return;
    }

    for(int i=0; i<nChildCount; i++){
        QTreeWidgetItem *curChild = curItem->child(i);
        PostorderTraversal(curChild);
    }
    qDebug()<<curItem->text(0);
    return;
}

void Widget::on_pushButtonMidorder_clicked()
{
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    qDebug()<<tr("中序遍历：");
    MidorderTraversal(itemA);
}

void Widget::MidorderTraversal(QTreeWidgetItem *curItem){
    if(NULL == curItem){
        return;
    }
    int nChildCount = curItem->childCount();
    if( nChildCount < 1 ){
        qDebug()<<curItem->text(0);
        return;
    }
    QTreeWidgetItem *bigSon = curItem->child(0);
    MidorderTraversal(bigSon);
    qDebug()<<curItem->text(0);
    for(int i=1; i<nChildCount; i++){
        QTreeWidgetItem *litteSon = curItem->child(i);
        MidorderTraversal(litteSon);
    }
    return;
}

void Widget::on_pushButtonIterator_clicked()
{
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    qDebug()<<tr("迭代器遍历：（同先序）");
    IteratorTraversal(itemA);
}

void Widget::IteratorTraversal(QTreeWidgetItem *curItem){
    if(NULL == curItem){
        return;
    }
    QTreeWidgetItemIterator it(curItem);
    while (NULL != (*it)) {
        qDebug()<< (*it)->text(0);
        ++it;
    }
    return;
}

void Widget::on_pushButtonLevels_clicked()
{
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    qDebug()<<tr("按层遍历：（没有用递归实现，使用队列实现）");
    LevelsTraversal(itemA);
}

void Widget::LevelsTraversal(QTreeWidgetItem *curItem){
    if(NULL == curItem){
        return;
    }
    QList<QTreeWidgetItem *> list;
    list.append(curItem);
    while (list.count() > 0) {
        QTreeWidgetItem *itemFirst = list.takeFirst();
        qDebug()<<itemFirst->text(0);
        int nChildCount = itemFirst->childCount();
        for(int i=0; i<nChildCount; i++){
            list.append(itemFirst->child(i));
        }
    }
    return;
}
