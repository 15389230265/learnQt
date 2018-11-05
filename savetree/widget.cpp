#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->headerItem()->setText(0, "TreeHeader");
    QTreeWidgetItem *itemA = new QTreeWidgetItem();
    itemA->setText(0, "A");
    //设置条目可以双击编辑
    itemA->setFlags(itemA->flags() | Qt::ItemIsEditable);
    ui->treeWidget->addTopLevelItem(itemA);
    QTreeWidgetItem *itemB = new QTreeWidgetItem(itemA);
    itemB->setText(0, "B");
    itemB->setFlags(itemB->flags() | Qt::ItemIsEditable);
    QTreeWidgetItem *itemC = new QTreeWidgetItem(itemA);
    itemC->setText(0, "C");
    itemC->setFlags(itemC->flags() | Qt::ItemIsEditable);
    ui->treeWidget->expandAll();
    ui->lineEditFileName->setText("s.tree");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAddTop_clicked()
{
    QString strText = ui->lineEditText->text();
    if(strText.isEmpty()){
        QMessageBox::warning(this, tr("添加"), tr("条目文本不能为空。"));
        return;
    }
    QTreeWidgetItem *itemNew = new QTreeWidgetItem();
    itemNew->setText(0, strText);
    itemNew->setFlags( itemNew->flags() | Qt::ItemIsEditable);
    ui->treeWidget->addTopLevelItem(itemNew);
    ui->treeWidget->setFocus();
}

void Widget::on_pushButtonAddChild_clicked()
{
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem();
    if(NULL == curItem){
        QMessageBox::warning(this, tr("添加子节点"), tr("未选中节点，无法添加子节点。"));
        return;
    }
    QString strText = ui->lineEditText->text();
    if(strText.isEmpty()){
        QMessageBox::warning(this, tr("添加"), tr("条目文本不能为空。"));
        return;
    }
    QTreeWidgetItem *itemChild = new QTreeWidgetItem(curItem);
    itemChild->setText(0, strText);
    itemChild->setFlags( itemChild->flags() | Qt::ItemIsEditable);
    ui->treeWidget->expandItem(curItem);
    ui->treeWidget->setFocus();
}

void Widget::on_pushButtonEditHeader_clicked()
{
    QString strText = ui->lineEditText->text();
    if(strText.isEmpty()){
        QMessageBox::warning(this, tr("修改树头"), tr("条目文本不能为空。"));
        return;
    }
    ui->treeWidget->headerItem()->setText(0, strText);
}

void Widget::on_pushButtonSaveFile_clicked()
{
    QString strFileName = ui->lineEditFileName->text().trimmed();
    if(strFileName.isEmpty()){
        QMessageBox::warning(this, tr("保存"), tr("文件名不能为空。"));
        return;
    }
    m_file.setFileName(strFileName);
    if( ! m_file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, tr("打开"), tr("要写入的文件无法打开，请检查文件名或权限。"));
        return;
    }
    m_ds.setDevice( &m_file );
    QTreeWidgetItem *iHeader = ui->treeWidget->headerItem();
    m_ds<< (*iHeader);
    //获取隐形根条目，虽然顶级条目 parent 指针是 NULL，但是隐形根条目的子节点是顶级条目
    //隐形根条目可以像普通条目递归使用，为隐形根条目添加或删除子条目，就是添加或删除顶级条目
    QTreeWidgetItem *iRoot = ui->treeWidget->invisibleRootItem();
    SaveTree(iRoot);
    QMessageBox::information(this, tr("保存完毕"), tr("保存节点到文件完毕。"));
    m_file.close();
    m_ds.setDevice(NULL);
    return;
}

void Widget::SaveTree(QTreeWidgetItem *curItem){
    if(NULL == curItem){
        return;
    }
    int nChildCount = curItem->childCount();
    if (nChildCount < 1){
        m_ds<< (*curItem) << nChildCount;
        return;
    }
    m_ds<< (*curItem) << nChildCount;
    for(int i=0; i<nChildCount; i++){
        QTreeWidgetItem *curChild = curItem->child(i);
        SaveTree(curChild);
    }
    return;
}

void Widget::on_pushButtonClearTree_clicked()
{
    ui->treeWidget->clear();
    ui->treeWidget->headerItem()->setText(0, "");
}

void Widget::on_pushButtonLoadFile_clicked()
{
    QString strFileName = ui->lineEditFileName->text().trimmed();
    if(strFileName.isEmpty()){
        QMessageBox::warning(this, tr("文件名"), tr("文件名不能为空。"));
        return;
    }
    m_file.setFileName(strFileName);
    if( ! m_file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, tr("打开"), tr("要写入的文件无法打开，请检查文件名或权限。"));
        return;
    }
    m_ds.setDevice( &m_file );
    QTreeWidgetItem *iHeader = ui->treeWidget->headerItem();
    //读取数据到树头，树头数据里自带了树的列计数 columnCount()
    m_ds >> (*iHeader);
    int nColCount = iHeader->columnCount();
    qDebug()<<"Header columns: "<<nColCount;
    if((nColCount < 0) || (nColCount > MAX_COLS)){
        QMessageBox::critical(this, tr("树头加载异常"),
                              tr("树头条目加载异常，列计数小于0或大于1000。"));
        ui->treeWidget->setColumnCount(1);
        m_file.close();
        m_ds.setDevice(NULL);
        return;
    }
    QTreeWidgetItem *iRoot = ui->treeWidget->invisibleRootItem();
    LoadTree(iRoot);
    QString strMsg = tr("加载文件中树形节点结束。");
    if(m_ds.status() != QDataStream::Ok){
        strMsg += tr("\r\n文件读取异常，只加载了部分数据。");
    }
    if(!m_ds.atEnd()){
        int nres = m_file.size() - m_file.pos();
        strMsg += tr("\r\n文件内容未全部加载，后面数据不合格或与树无关。\r\n剩余未读数据：%1 B").arg(nres);
    }
    QMessageBox::information(this, tr("加载文件结束"), strMsg);
    ui->treeWidget->expandAll();
    m_file.close();
    m_ds.setDevice(NULL);
    return;
}

void Widget::LoadTree(QTreeWidgetItem *curItem){
    if(NULL == curItem){
        return;
    }
    if( m_ds.atEnd() ){
        qDebug()<<"File end. This is an empty node.";
        return;
    }
    int nChildCount = 0;
    m_ds>> (*curItem) >> nChildCount;
    int nColCount = curItem->columnCount();
    qDebug()<<"curItem text: "<<curItem->text(0)
           <<" , colCount: "<<nColCount
          <<" , childCount: "<<nChildCount;
    if((nChildCount < 0) || (nColCount < 0) || (nColCount > MAX_COLS)){
        qDebug()<<"This is an erro node.";
        return;
    }
    for(int i=0; i<nChildCount; i++){
        QTreeWidgetItem *curChild = new QTreeWidgetItem(curItem);
        curChild->setFlags(curChild->flags() | Qt::ItemIsEditable);
        LoadTree(curChild);
    }
    return;
}
