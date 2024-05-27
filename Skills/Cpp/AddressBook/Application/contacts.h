#pragma once
#include <QString>
class Contact
{
public:
    Contact()=default;
    Contact(const QString& firstName, QString&& secondName, QString phone);
    QString phone() const;
    QString firstName() const;
    QString surname() const;
private:
    QString m_phone;
    QString m_firstName;
    QString m_surname;
};
