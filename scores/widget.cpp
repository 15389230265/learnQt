#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTableWidgetSelectionRange>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    InitScoresTable();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitScoresTable(){
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(4);
    QStringList listHeaders;
    listHeaders<<tr("语文")<<tr("数学")<<tr("外语")<<tr("美食");
    ui->tableWidget->setHorizontalHeaderLabels(listHeaders);

    SetTableRow(0, tr("小明"),
                tr("66"), tr("77"),
                tr("88"), tr("99"));
    SetTableRow(1, tr("小萌"),
                tr("99"), tr("88"),
                tr("77"), tr("66"));
}

void Widget::SetTableRow(int nRow, QString strName,
                         QString strChinese, QString strMath,
                         QString strForeignLanguage, QString strFood){
    QTableWidgetItem *itemName = new QTableWidgetItem(strName);
    ui->tableWidget->setVerticalHeaderItem(nRow, itemName);
    QTableWidgetItem *itemChinese = new QTableWidgetItem(strChinese);
    ui->tableWidget->setItem(nRow, 0, itemChinese);
    QTableWidgetItem *itemMath = new QTableWidgetItem(strMath);
    ui->tableWidget->setItem(nRow, 1, itemMath);
    QTableWidgetItem *itemForeignLanguage = new QTableWidgetItem(strForeignLanguage);
    ui->tableWidget->setItem(nRow, 2, itemForeignLanguage);
    QTableWidgetItem *itemFood = new QTableWidgetItem(strFood);
    ui->tableWidget->setItem(nRow, 3, itemFood);
}

void Widget::on_tableWidget_itemSelectionChanged()
{
    QList<QTableWidgetItem*> listItems = ui->tableWidget->selectedItems();
    int nItemCount = listItems.count();
    QList<QTableWidgetSelectionRange> listRanges = ui->tableWidget->selectedRanges();
    int nRangesCount = listRanges.count();
    int nCellsCount = 0;
    for (int i=0; i<nRangesCount; i++){
        nCellsCount += (listRanges[i].rowCount()) * (listRanges[i].columnCount());
    }
    qDebug()<<tr("选中条目数：%1，选中区域数：%2，选中单元格数：%3")
              .arg(nItemCount)
              .arg(nRangesCount)
              .arg(nCellsCount);
}

void Widget::on_pushButtonFind_clicked()
{
    const QString strDstScore = ui->lineEditText->text().trimmed();
    if(strDstScore.isEmpty()){
        return;
    }
    const int nDstScore = strDstScore.toInt();

    int nTheColumn = ui->comboBoxColumns->currentIndex();
    int nCompra = ui->comboBoxCompares->currentIndex();

    int nRowCount = ui->tableWidget->rowCount();
    int nFilteredCount = 0;
    double dblTotal = 0;
    double dblAverage = 0;
    QTableWidgetItem *itemFilteredFirst = NULL;
    ui->tableWidget->setCurrentItem(NULL, QItemSelectionModel::Clear);

    for(int i=0; i<nRowCount; i++){
        QTableWidgetItem *itemCur = ui->tableWidget->item(i, nTheColumn);
        if(NULL == itemCur){
            continue;
        }
        QString strCur = itemCur->text().trimmed();
        int nCurScore = strCur.toInt();
        if(0 == nCompra){
            if(nCurScore != nDstScore){
                continue;
            }
        }
        else if (1 == nCompra) {
            if(! (nCurScore <= nDstScore)){
                continue;
            }
        }
        else {
            if(! (nCurScore >= nDstScore)){
                continue;
            }
        }
        nFilteredCount++;
        dblTotal += nCurScore;
        itemCur->setSelected(true);
        if(NULL == itemFilteredFirst){
            itemFilteredFirst = itemCur;
            ui->tableWidget->setCurrentItem(itemFilteredFirst);
            ui->tableWidget->scrollToItem(itemFilteredFirst);
        }
    }

    if(nFilteredCount > 0){
        dblAverage = dblTotal / nFilteredCount;
    }
    QString strMsg = tr("匹配条目数：%1，匹配条目的总值：%2，均值：%3")
            .arg(nFilteredCount).arg(dblTotal).arg(dblAverage);
    QMessageBox::information(this, tr("查找"), strMsg);
    ui->tableWidget->setFocus();
}

void Widget::on_pushButtonAddLine_clicked()
{
    QString strName = ui->lineEditName->text().trimmed();
    if(strName.isEmpty()){
        return;
    }
    int nOldRowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow( nOldRowCount );
    SetTableRow(nOldRowCount, strName,
                tr("0"), tr("0"),
                tr("0"), tr("0"));
    ui->tableWidget->scrollToBottom();
}

void Widget::on_pushButtonDelLines_clicked()
{
    QList<int> listRowIndex;
    QList<QTableWidgetSelectionRange> listRanges = ui->tableWidget->selectedRanges();
    int nRangeCount = listRanges.count();
    if(nRangeCount < 1){
        return;
    }
    for(int i=0; i<nRangeCount; i++){
        int nCurRangeRowCount = listRanges[i].rowCount();
        for(int j=0; j<nCurRangeRowCount; j++){
            int nRowIndex = listRanges[i].topRow() + j;
            if(! listRowIndex.contains(nRowIndex)){
                listRowIndex.append(nRowIndex);
            }
        }
    }
    qSort(listRowIndex);
    int nRowIndexCount = listRowIndex.count();
    for(int i=nRowIndexCount-1; i>=0; i--){
        ui->tableWidget->removeRow( listRowIndex[i] );
    }
    listRanges.clear();
    listRowIndex.clear();
}

void Widget::on_pushButtonDelSelectedItems_clicked()
{
    QList<QTableWidgetItem*> listItems = ui->tableWidget->selectedItems();
    int nCount = listItems.count();
    if(nCount < 1){
        return;
    }
    for(int i=0; i<nCount; i++){
        int nItemRow = listItems[i]->row();
        int nItemColum = listItems[i]->column();
        delete ui->tableWidget->takeItem(nItemRow, nItemColum);
    }
}
