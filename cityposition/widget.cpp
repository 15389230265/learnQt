#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEditLatitude->setReadOnly(true);
    ui->lineEditLongitude->setReadOnly(true);
    loadPositions();
    connect(ui->comboBoxProvince, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onProvinceIndexChange(int)));
    connect(ui->comboBoxCity, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onCityIndexChange(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadPositions(){
    //打开资源里的文件
    QFile fileIn(":/position.txt");
    //资源文件打开一般不需要判断，只要文件名对就可以打开
    fileIn.open(QIODevice::ReadOnly);
    QTextStream tsIn(&fileIn);
    tsIn.setCodec("UTF-8");
    m_vCities.resize(40);
    m_vLongitudes.resize(40);
    m_vLatitudes.resize(40);
    QString strProBefore;
    QString strProCur;
    QString strCity;
    int nLonD;
    int nLonM;
    int nLatD;
    int nLatM;
    int nProvIndex = -1;
    while (!tsIn.atEnd()) {
        tsIn>>strProCur>>strCity
                >>nLatD>>nLatM
                >>nLonD>>nLonM;
        if(strProBefore != strProCur){
            nProvIndex++;
            strProBefore = strProCur;
            m_vProvinces<<strProCur;
        }
        m_vCities[nProvIndex] << strCity;
        m_vLatitudes[nProvIndex] << nLatD + double(nLatM/60.0);
        m_vLongitudes[nProvIndex] << nLonD + double(nLonM/60.0);
    }
    for (int i=0; i<m_vProvinces.count(); i++){
        ui->comboBoxProvince->addItem(m_vProvinces[i]);
    }
    ui->comboBoxProvince->setCurrentIndex(0);
    onProvinceIndexChange(0);
    onCityIndexChange(0);
    qDebug()<<tr("加载完毕，省份计数：%1").arg(m_vProvinces.count());
}

void Widget::onProvinceIndexChange(int index){
    if(index < 0){
        return;
    }
    ui->comboBoxCity->clear();
    int nCount = m_vCities[index].count();
    for(int i=0; i<nCount; i++){
        ui->comboBoxCity->addItem(m_vCities[index][i]);
    }
    ui->comboBoxCity->setCurrentIndex(0);
}

void Widget::onCityIndexChange(int index){
    if(index < 0){
        return;
    }
    int nProvIndex = ui->comboBoxProvince->currentIndex();
    ui->lineEditLongitude->setText(
                tr("%1").arg(m_vLongitudes[nProvIndex][index]));
    ui->lineEditLatitude->setText(
                tr("%1").arg(m_vLatitudes[nProvIndex][index]));
}
