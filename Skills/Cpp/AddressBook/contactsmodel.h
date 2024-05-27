#pragma once
#include <QAbstractListModel>
#include <vector>
#include "contacts.h"
#include "contactsreader.h"
class ContactsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ContactsModel();
    static void registerMe(const std::string& moduleName);
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent={}) const override;
    QVariant data(const QModelIndex& index={}, int role=Qt::DisplayRole) const override;
private:
    contactsreader m_contactsReader;
    std::vector<Contact> m_contacts;
    enum ContactRoles {
        NameRole= Qt::UserRole+1,
        SurnameRole,
        PhoneNumberRole
    };
    bool updateConstacts();
};
