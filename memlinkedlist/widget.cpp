#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

#define MEM_MAX 10

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置SpinBox上下限，至少分配1块，最多10块内存
    ui->spinBoxMemCount->setRange(1, MEM_MAX);
    for(int i=0; i<MEM_MAX; i++){
        m_memFree.append(tr("空闲内存"));
    }
    updateListWidgets();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateListWidgets(){
    ui->listWidgetFree->clear();
    ui->listWidgetUsed->clear();
    //根据空闲内存块链表显示
    //空链表的 begin() 和 end() 是等同的
    QLinkedList<QString>::iterator itFree = m_memFree.begin();
    while (itFree != m_memFree.end()) {
        ui->listWidgetFree->addItem(*itFree);
        itFree++;
    }
    QLinkedList<QString>::iterator itUsed = m_memUsed.begin();
    while (itUsed != m_memUsed.end()) {
        ui->listWidgetUsed->addItem(*itUsed);
        itUsed++;
    }
}

void Widget::on_pushButtonAllocate_clicked()
{
    const QString strName = ui->lineEditName->text().trimmed();
    if(strName.isEmpty()){
        QMessageBox::warning(this, tr("分配"), tr("进程名为空，无法分配。"));
        return;
    }
    if(tr("空闲内存") == strName){
        QMessageBox::warning(this, tr("分配"), tr("进程名不能等同 空闲内存 。"));
        return;
    }
    int nNeededCount = ui->spinBoxMemCount->value();
    int nCurFree = m_memFree.count();
    if(nNeededCount > nCurFree){
        QMessageBox::warning(this, tr("分配"), tr("请求数量大于现有空闲数量，请减少请求量或释放其他进程内存。"));
        return;
    }
    for (int i=0; i<nNeededCount; i++){
        QString strCurMem = m_memFree.takeFirst();
        strCurMem = strName;
        m_memUsed.append(strCurMem);
    }
    updateListWidgets();
}

void Widget::on_pushButtonFind_clicked()
{
    //获取进程名
    const QString strName = ui->lineEditName->text().trimmed();
    //判断是否为空
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("查询"), tr("进程名为空，无法查询。"));
        return;
    }
    //判断是否为 空闲内存查询
    if( tr("空闲内存") == strName )
    {
        QMessageBox::information(this, tr("查询"),
                                 tr("空闲内存数量为：%1").arg( m_memFree.count() ) );
        return;
    }
    int nMemCount = m_memUsed.count();
    if(nMemCount < 1){
        QMessageBox::warning(this, tr("查询"), tr("没有找到该进程名。"));
        return;
    }else {
        QMessageBox::information(this, tr("查询"),
                                 tr("该进程拥有的内存块数量为：%1").arg(nMemCount) );
    }
}

void Widget::on_pushButtonFree_clicked()
{
    const QString strName = ui->lineEditName->text().trimmed();
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("释放"), tr("进程名为空，无法查询。"));
        return;
    }
    int nNeedFree = ui->spinBoxMemCount->value();
    int nCurOwn = m_memUsed.count(strName);
    if( nCurOwn < 1 )//判断是否存在
    {
        QMessageBox::warning(this, tr("释放"),tr("没有找到该进程名。"));
        return;
    }
    //判断释放数量是否超过了拥有数量
    if( nNeedFree > nCurOwn )
    {
        QMessageBox::warning(this, tr("释放"),
                             tr("该进程只拥有 %1 块内存，不能释放 %2 块。").arg(nCurOwn).arg(nNeedFree) );
        return;
    }
    int nCurFreed = 0;
    QLinkedList<QString>::iterator itUsed = m_memUsed.begin();
    while (itUsed != m_memUsed.end()) {
        if(strName == (*itUsed)){
            QString strMem = (*itUsed);
            itUsed = m_memUsed.erase(itUsed);
            //erase() 返回值就是指向下一个，不需要++，并且不能再用erase()参数里的数值迭代
            strMem = tr("空闲内存");
            m_memFree.append(strMem);
            nCurFreed += 1;
            if( nCurFreed >= nNeedFree){
                break;
            }
        }else{
            itUsed++;
        }
    }
    updateListWidgets();
}
