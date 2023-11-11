#ifndef PERSISTENCEDATA_H
#define PERSISTENCEDATA_H

#include <QObject>
#include <QMap>

//提供持久化数据的功能，并有助于保存、加载数据
class PersistenceData : public QObject
{
    Q_OBJECT
public:
    PersistenceData(QObject* parent=nullptr);

    virtual bool serialize();
    virtual bool deserialize();
};

class UserInfo : public PersistenceData
{
    Q_OBJECT
public:
    UserInfo(QObject* parent=nullptr);

    //注册
    bool registerUser(const QString& username, const QString& password);

    bool login(const QString& username, const QString& password);


    // PersistenceData interface
public:
    virtual bool serialize() override;
    virtual bool deserialize() override;

private:
    QMap<QString, QString> m_info;
};

#endif // PERSISTENCEDATA_H
