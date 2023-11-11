#include "PersistenceData.h"
#include <QFile>
#include <QDebug>

PersistenceData::PersistenceData(QObject *parent) : QObject(parent)
{
}

bool PersistenceData::serialize()
{
    return true;
}

bool PersistenceData::deserialize()
{
    return true;
}


UserInfo::UserInfo(QObject *parent) : PersistenceData(parent)
{
    deserialize();
}

bool UserInfo::registerUser(const QString &username, const QString &password)
{
    if (m_info.contains(username)) {
        return false;
    } else {
        m_info.insert(username, password);
    }
    serialize();

    return true;
}

bool UserInfo::login(const QString &username, const QString &password)
{
    if (m_info.contains(username)) {
        return m_info.value(username) == password;
    } else {
        return false;
    }
}

bool UserInfo::serialize()
{

    QFile file("user.bin");
    if (file.open(QFile::Text|QFile::Truncate|QFile::WriteOnly)) {
        //遍历 m_info 变量中的每个键，并将其格式化为一行字符串，使用 toLocal8Bit() 函数将其转换为本地字符编码，并使用 write() 函数写入到文件中
        for (auto& key : m_info.keys()) {
            const QString line = QString("%1\t%2\n").arg(key).arg(m_info.value(key));
            file.write(line.toLocal8Bit());
        }
        file.close();

        return true;
    } else {
        return false;
    }
}

bool UserInfo::deserialize()
{
    m_info.clear();
    m_info.insert("111", "111");
    QFile file("user.bin");

    //以 ASCII 模式打开文件并只读文件数据。如果文件成功打开，则开始循环读取每一行字符串
    //在循环内，读取一行数据，使用 trimmed() 函数将该行末尾的空白字符删除，然后将其按照键值对格式（使用 ‘\t’ 分隔）分割成字符串列表 strs
    //如果字符串列表中的元素数量不等于2，则忽略该行数据，并继续读取下一行数据。否则，将键值对插入到 m_info 变量中
    if (file.open(QFile::Text|QFile::ReadOnly)) {
        while(!file.atEnd()) {
            auto line = file.readLine();
            const QString str = line.trimmed();
            QStringList strs = str.split("\t");
            if (strs.count() != 2) {
                continue;
            }
            m_info.insert(strs[0], strs[1]);
        }
        file.close();
        return true;
    } else {
        return false;
    }
    return true;
}
