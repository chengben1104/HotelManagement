#include "RoomRecordManager.h"
#include <QCoreApplication>
#include <QFile>
#include <QDataStream>

RoomRecordManager* RoomRecordManager::gInstance = nullptr;

RoomRecordManager *RoomRecordManager::GetInstance()
{
    if (gInstance == nullptr) {
        gInstance = new RoomRecordManager(qApp->instance());
        gInstance->deserialize();
        gInstance->initialize();
    }
    return gInstance;
}

bool RoomRecordManager::booking(Data::RoomRecord &record)
{
    QDate start = record.checkIn;
    QDate end = record.checkOut;
    int roomId = getFirstFreeRoomNumber(record.type, start, end);
    record.roomNum = roomId;
    m_records.append(record);
    serialize();
    return true;
}

bool RoomRecordManager::checkIn(const Data::Person& p2, const Data::RoomRecord &record)
{
    if (!m_records.contains(record)) {
        return false;
    } else {
        int idx = m_records.indexOf(record);
        m_records[idx].isCheckIn = true;
        m_records[idx].p2 = p2;
        serialize();
        return true;
    }
}

bool RoomRecordManager::checkOut(const Data::RoomRecord &record)
{
    if (!m_records.contains(record)) {
        return false;
    } else {
        int idx = m_records.indexOf(record);
        m_records.removeAt(idx);
        serialize();
        return true;
    }
}

bool RoomRecordManager::searchRecordByPerson(const Data::Person &person, Data::RoomRecord &record)
{
    bool hasRecord = false;
    for (auto& _record : m_records) {
        if (_record.p.idNumber == person.idNumber) {
           record = _record;
           hasRecord = true;
        }

    }
    return hasRecord;
}

bool RoomRecordManager::searchBookingRecordByPerson(const Data::Person &person, Data::RoomRecord &record)
{
    bool hasRecord = false;
    for (auto& _record : m_records) {
        if (_record.p.idNumber == person.idNumber && !_record.isCheckIn) {
           record = _record;
           hasRecord = true;
        }
    }
    return hasRecord;
}

/**
 * @brief RoomRecordManager::searchRecordByRoom
 * @param start
 * @param end
 * @param [In, Out]record 输入只需要保证有房间号即可，输出具体房间信息
 * @return 房间空闲返回false，查找到信息返回true
 */
bool RoomRecordManager::searchRecordByRoom(const QDate &start, const QDate &end, Data::RoomRecord &record)
{
    bool hasRecord = false;
    for (auto& _record : m_records) {
        if (record.roomNum == _record.roomNum) {
            bool isFree = (_record.checkIn > end || _record.checkOut < start);
            if (!isFree) {
                record = _record;
                hasRecord = true;
                break;
            }
        }

    }
    return hasRecord;
}

Data::RoomSummary RoomRecordManager::getRoomSummary(const QDate& start, const QDate& end)
{
    Data::RoomSummary summary = Data::gRoomSummary;
    for (int i = 0; i < Data::ROOM_TYPE_COUNT; ++i) {
        Data::RoomType type = static_cast<Data::RoomType>(i);
        QList<int> freeRooms = getFreeRoomList(type, start, end);
        summary.info[i].remain = freeRooms.count();
    }
    return summary;
}

int RoomRecordManager::getFirstFreeRoomNumber(Data::RoomType type, const QDate& start, const QDate& end)
{
    QList<int> rooms = getFreeRoomList(type, start, end);
    if (rooms.isEmpty()) {
        return -1;
    } else {
        return rooms.first();
    }
}

QList<int> RoomRecordManager::getFreeRoomList(Data::RoomType type, const QDate& start, const QDate& end)
{
    auto rooms = m_rooms[type];
    for (auto& record : qAsConst(m_records)) {
        if (type != record.type) {
            continue;
        }
        bool isFree = (record.checkIn > end || record.checkOut < start);
        if (!isFree) {
            rooms.removeOne(record.roomNum);
        }

    }
    return rooms;
}

RoomRecordManager::RoomRecordManager(QObject *parent) : PersistenceData(parent)
{

}

void RoomRecordManager::initialize()
{
    // 生成所有的房间号
    int count = 0;
    for (int i = 0; i < Data::ROOM_TYPE_COUNT; ++i) {
        m_rooms[i].clear();
        for (int j = 0; j < Data::AMOUNT[i]; ++j) {
            m_rooms[i].append(Data::ROOM_ID_OFFSET + count + 1);
            ++count;
        }
    }
}

#include <QDebug>

bool RoomRecordManager::serialize()
{
    QFile file("record.bin");
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    } else {
        QDataStream out(&file);
        out << m_records;
        return true;
    }
}

bool RoomRecordManager::deserialize()
{
    QFile file("record.bin");
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    } else {
        QDataStream in(&file);
        in >> m_records;
        return true;
    }
}
