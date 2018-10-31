#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QFileDialog>
#include <QFileInfo>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->checkBoxAutoSort->setCheckState(Qt::Checked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAdd_clicked()
{
    QStringList slist = QFileDialog::getOpenFileNames(
                this,
                tr("添加多个音乐文件"),
                tr("."),
                tr("Music files(*.mp3 *.wma *.wav)::All files(*)")
                );
    int nCount = slist.count();
    if(nCount < 1){
        return;
    }
    for(int i=0; i<nCount; i++){
        QListWidgetItem *theItem = new QListWidgetItem(ui->listWidget);
        QFileInfo fi(slist[i]);
        theItem->setText(fi.completeBaseName());
        theItem->setToolTip(fi.absoluteFilePath());
    }
}

void Widget::on_pushButtonDel_clicked()
{
    QList<QListWidgetItem *> itemList = ui->listWidget->selectedItems();
    int nCount = itemList.count();
    if(nCount < 1){
        return;
    }
    //有选中的条目需要删除
    //一般删除多个条目时，从尾部开始删除，这样删除过程中前面的条目行号不会变
    for(int i=nCount-1; i>=0; i--){
        //根据条目求出行号
        int theRow = ui->listWidget->row(itemList[i]);
        ui->listWidget->takeItem(theRow);
        delete itemList[i];
        itemList[i] = NULL;
    }
    itemList.clear();
}

void Widget::on_pushButtonOutput_clicked()
{
    int nCount = ui->listWidget->count();
    if(nCount < 1){
        return;
    }
    QString strName = QFileDialog::getSaveFileName(
                this,
                tr("保存为 M3U 文件"),
                tr("."),
                tr("M3U files(*,m3u)")
                );
    if(strName.isEmpty()){
        return;
    }
    QFile fileOut(strName);
    if(!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("打开文件"),
                             tr("无法打开文件,请检查是否有写入权限!"));
        return;
    }
    QTextStream tsOut(&fileOut);
    tsOut<<tr("#EXTM3U")<<endl;
    for (int i=0; i<nCount; i++){
        QString strCurName = ui->listWidget->item(i)->toolTip();
        tsOut<<strCurName<<endl;
    }
}

void Widget::on_pushButtonSerch_clicked()
{
    QString strTemplate = ui->lineEdit->text();
    if(strTemplate.isEmpty()){
        return;
    }
    ui->listWidget->setCurrentItem(NULL, QItemSelectionModel::Clear);
    QList<QListWidgetItem *> list = ui->listWidget->findItems(strTemplate, Qt::MatchContains);
    int nCount = list.count();
    if(nCount < 1){
        QMessageBox::information(this, tr("查找条目"),
                                 tr("没有找到匹配的条目文本."));
        return;
    }
    ui->listWidget->setCurrentItem(list[0]);
    ui->listWidget->scrollToItem(list[0], QAbstractItemView::PositionAtTop);

    for (int i=0; i<nCount; i++){
        list[i]->setSelected(true);
    }

    ui->listWidget->setFocus();
}

void Widget::on_checkBoxAutoSort_clicked(bool checked)
{
    if(checked){
        ui->listWidget->setSortingEnabled(true);
        ui->checkBoxReverse->setEnabled(true);
        if (ui->checkBoxReverse->checkState() != Qt::Checked){
            ui->listWidget->sortItems(Qt::AscendingOrder);
        }
        else{
            ui->listWidget->sortItems(Qt::DescendingOrder);
        }
    }
    else{
        ui->listWidget->setSortingEnabled(false);
        ui->checkBoxReverse->setEnabled(false);
    }
}

void Widget::on_checkBoxReverse_clicked(bool checked)
{
    if(! checked){
        ui->listWidget->sortItems(Qt::AscendingOrder);
    }
    else{
        ui->listWidget->sortItems(Qt::DescendingOrder);
    }
}
