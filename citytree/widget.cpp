#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAddTop_clicked()
{
    QString strName = ui->lineEditName->text();
    QString strLon = ui->lineEditLon->text();
    QString strLat = ui->lineEditLat->text();
    if(strName.isEmpty()  || strLon.isEmpty() || strLat.isEmpty()){
        QMessageBox::information(this, tr("输入检查"), tr("三个编辑框均需要输入信息！"));
        return;
    }
    QTreeWidgetItem *itemNew = new QTreeWidgetItem();
    itemNew->setText(0, strName);
    itemNew->setText(1, strLon);
    itemNew->setText(2, strLat);
    ui->treeWidget->addTopLevelItem(itemNew);
    ui->treeWidget->setFocus();
}

void Widget::on_pushButtonAddChild_clicked()
{
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem();
    if( NULL == curItem ){
        QMessageBox::information(this, tr("无选中节点"), tr("请先选中一个节点，然后为其添加子节点！"));
        return;
    }
    QString strName = ui->lineEditName->text();
    QString strLon = ui->lineEditLon->text();
    QString strLat = ui->lineEditLat->text();
    if(strName.isEmpty()  || strLon.isEmpty() || strLat.isEmpty()){
        QMessageBox::information(this, tr("输入检查"), tr("三个编辑框均需要输入信息！"));
        return;
    }
    QTreeWidgetItem *itemChild = new QTreeWidgetItem();
    itemChild->setText(0, strName);
    itemChild->setText(1, strLon);
    itemChild->setText(2, strLat);
    curItem->addChild(itemChild);
    //自动展开显示新加的子节点
    ui->treeWidget->expandItem(curItem);
    ui->treeWidget->setFocus();
}

void Widget::on_pushButtonDelLeaf_clicked()
{
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem();
    if( NULL == curItem ){
        QMessageBox::warning(this, tr("无选中节点"), tr("无选中节点，没东西删除。"));
        return;
    }
    if(curItem->childCount() > 0){
        QMessageBox::warning(this, tr("不是叶子节点"), tr("不是叶子节点，不能删除！"));
        return;
    }
    //是叶子节点可以删除
    //凡是知道指针的叶子节点，可以直接 delete
    //QTreeWidgetItem 析构函数会自动将条目从树形控件卸载掉
    delete curItem; curItem = NULL;
}

void Widget::on_pushButtonDelSubtree_clicked()
{
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem();
    if( NULL == curItem ){
        QMessageBox::warning(this, tr("无选中节点"), tr("无选中节点，没东西删除。"));
        return;
    }
    RemoveSubtree(curItem);
}

void Widget::RemoveSubtree(QTreeWidgetItem *curLevelItem){
    if( NULL == curLevelItem ){
        return;
    }
    int nCount = curLevelItem->childCount();
    if(nCount < 1){
        delete curLevelItem;    curLevelItem = NULL;
        return;
    }
    for(int i=0; i<nCount; i++){
        QTreeWidgetItem *curChild = curLevelItem->takeChild(i);
        RemoveSubtree(curChild);
    }
    delete curLevelItem;    curLevelItem = NULL;
    return;
}
