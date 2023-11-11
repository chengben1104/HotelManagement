#ifndef ROOMRECORDMANAGER_H
#define ROOMRECORDMANAGER_H

#include "Core/PersistenceData.h"
#include "Core/Data.h"

//提供了多种处理房间预订、入住、退房等操作的函数，并维护了一个房间记录数据列表、一个房间概要数据和一组空闲房间列表
class RoomRecordManager : public PersistenceData
{
public:
    static RoomRecordManager* GetInstance();  //单例设计模式

    //预订房间操作，并将预订记录添加到房间记录数据列表（m_records）中
    bool booking(Data::RoomRecord& record);

    //办理入住手续，并更新房间状态为 “入住中”
    bool checkIn(const Data::Person& p2, const Data::RoomRecord& record);
    //办理退房手续，并更新房间状态为空闲
    bool checkOut(const Data::RoomRecord& record);
    bool searchRecordByPerson(const Data::Person& person, Data::RoomRecord& record);
    bool searchBookingRecordByPerson(const Data::Person& person, Data::RoomRecord& record);

    bool searchRecordByRoom(const QDate& start, const QDate& end, Data::RoomRecord& record);

    //获取指定日期范围内的房间概要数据
    Data::RoomSummary getRoomSummary(const QDate& start, const QDate& end);

    //获取指定类型房间在指定日期范围内的第一个可用房间编号
    int getFirstFreeRoomNumber(Data::RoomType type, const QDate& start, const QDate& end);

    QList<int> getFreeRoomList(Data::RoomType type, const QDate& start, const QDate& end);
private:
    RoomRecordManager(QObject* parent);
    void initialize();
    static RoomRecordManager* gInstance;
    QList<Data::RoomRecord> m_records;
    Data::RoomSummary m_summary;
    QList<int> m_rooms[Data::ROOM_TYPE_COUNT];
    // PersistenceData interface
public:
    virtual bool serialize() override;
    virtual bool deserialize() override;
};

#endif // ROOMRECORDMANAGER_H
