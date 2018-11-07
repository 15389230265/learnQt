#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Contact daala("Daala", "44444", "North");
    m_listContacts.append(daala);
    ui->listWidget->addItem(daala.toString());
    Contact bob("Bob", "22222", "South");
    m_listContacts.append(bob);
    ui->listWidget->addItem(bob.toString());
    Contact carl("Carl", "33333", "West");
    m_listContacts.append(carl);
    ui->listWidget->addItem(carl.toString());
    Contact alice("Alice", "11111", "East");
    m_listContacts.append(alice);
    ui->listWidget->addItem(alice.toString());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAdd_clicked()
{
    QString strName = ui->lineEditName->text().trimmed();
    QString strPhone = ui->lineEditPhone->text().trimmed();
    QString strAddress = ui->lineEditAddress->text().trimmed();
    if(strName.isEmpty()){
        QMessageBox::warning(this, tr("检查姓名"), tr("姓名为空，请输入姓名。"));
        return;
    }
    Contact person(strName, strPhone, strAddress);
    m_listContacts.append(person);
    QListWidgetItem *item = new QListWidgetItem(person.toString());
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
    item->setSelected(true);
    ui->listWidget->setFocus();
}

void Widget::on_pushButtonDel_clicked()
{
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    if(NULL == curItem){
        return;
    }
    int ix = ui->listWidget->currentRow();
    m_listContacts.removeAt(ix);
    delete curItem; curItem = NULL;
}

void Widget::on_pushButtonFind_clicked()
{
    QString strName = ui->lineEditName->text().trimmed();
    if(strName.isEmpty()){
        QMessageBox::warning(this, tr("姓名检查"), tr("姓名为空，无法查询。"));
        return;
    }
    //从列表对象查找序号
    int ix = m_listContacts.indexOf(Contact(strName, "", ""));
    if(ix< 0){
        QMessageBox::information(this, tr("查找"), tr("没有找到联系人"));
        return;
    }else {
        QMessageBox::information(this, tr("查找"),
                                 tr("存在姓名匹配的联系人，序号是 %1 ").arg(ix));
        ui->listWidget->setCurrentRow(ix);
        ui->listWidget->currentItem()->setSelected(true);
        ui->listWidget->setFocus();
    }
}

void Widget::on_pushButtonSort_clicked()
{
    int nCount = m_listContacts.count();
    if(nCount <= 1){
        return;
    }
    //使用这个方法需要重构操作符<
    qSort(m_listContacts);
    //新的排序方法
//    qSort(m_listContacts.begin(), m_listContacts.end(), caseInsensitiveLessThan);
    ui->listWidget->clear();
    for(int i=0; i<nCount; i++){
        ui->listWidget->addItem(m_listContacts[i].toString());
    }
}

void Widget::on_pushButtonSave_clicked()
{
    int nCount = m_listContacts.count();
    if(nCount < 1){
        return;
    }
    QString strFile = QFileDialog::getSaveFileName(this, tr("保存文件"), tr("./test.ds"),
                                                   tr("QDataStream Files (*.ds)"));
    if(strFile.isEmpty()){
        return;
    }
    QFile fileOut(strFile);
    if(! fileOut.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, tr("保存文件"), tr("指定文件名无法打开，请检查文件名和写入权限。"));
        return;
    }
    QDataStream ds(&fileOut);
    ds<<m_listContacts;
    QMessageBox::information(this, tr("保存文件"), tr("保存成功！"));
    ds.setDevice(NULL);
    fileOut.close();
}

void Widget::on_pushButtonOpen_clicked()
{
    QString strFile = QFileDialog::getOpenFileName(this, tr("打开文件"), tr("./test.ds"),
                                                   tr("QDataStream Files (*.ds)"));
    if(strFile.isEmpty()){
        return;
    }
    QFile fileIn(strFile);
    if(! fileIn.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, tr("打开文件"), tr("指定文件名无法打开，请检查文件名和写入权限。"));
        return;
    }
    QDataStream ds(&fileIn);
    m_listContacts.clear();
    ui->listWidget->clear();
    ds>>m_listContacts;
    int nCount = m_listContacts.count();
    for(int i=0; i<nCount; i++){
        ui->listWidget->addItem(m_listContacts[i].toString());
    }
    QMessageBox::information(this, tr("打开文件"), tr("打开文件成功，并已加载联系人列表。"));
    ds.setDevice(NULL);
    fileIn.close();
}
