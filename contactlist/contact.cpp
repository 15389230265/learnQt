#include "contact.h"

Contact::Contact()
{
    m_strName = "None";
    m_strPhone = "000000";
    m_strAddress = "None";
}

Contact::~Contact(){

}

Contact::Contact(QString strName, QString strPhone, QString strAddress){
    m_strName = strName;
    m_strPhone = strPhone;
    m_strAddress = strAddress;
}

Contact::Contact(const Contact &c){
    m_strName = c.m_strName;
    m_strPhone = c.m_strPhone;
    m_strAddress = c.m_strAddress;
}

Contact & Contact::operator=(const Contact &c){
    m_strName = c.m_strName;
    m_strPhone = c.m_strPhone;
    m_strAddress = c.m_strAddress;
    return *this;
}

bool Contact::operator==(const Contact &c){
    return (c.m_strName == this->m_strName);
}

bool operator<(const Contact &c1, const Contact &c2){
    return (c1.m_strName < c2.m_strName);
}

bool caseInsensitiveLessThan (const Contact &c1, const Contact &c2){
    return (c1.m_strName.toLower() < c2.m_strName.toLower());
}

QString Contact::toString(){
    QString strRet = QString("%1\t%2\t%3").arg(this->m_strName)
            .arg(this->m_strPhone).arg(this->m_strAddress);
    return strRet;
}

QDataStream & operator<<(QDataStream & out, const Contact &c){
    out<<c.m_strName<<c.m_strPhone<<c.m_strAddress;
    return out;
}

//数据流操作，流提取运算符
QDataStream & operator>>(QDataStream & in, Contact &c)
{
    in>>c.m_strName>>c.m_strPhone>>c.m_strAddress;
    return in;
}
