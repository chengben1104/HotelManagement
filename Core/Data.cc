#include "Data.h"

const QString Data::PicturePath[4] = {
    QStringLiteral(":/images/room/single.jpg"),
    QStringLiteral(":/images/room/dual.jpg"),
    QStringLiteral(":/images/room/deluxe.jpg"),
    QStringLiteral(":/images/room/president.jpg")
};

Data::RoomSummary Data::gRoomSummary;

Data::Data(QObject *parent) : QObject(parent)
{

}

QString Data::GetRoomTypeStr(const RoomInfo &info)
{
    switch(info.type) {
    case Single:
        return QStringLiteral("单人间");
    case Dual:
        return QStringLiteral("双人间");
    case Deluxe:
        return QStringLiteral("豪华间");
    case President:
        return QStringLiteral("总统套房");
    case Invalid:
        return QStringLiteral("错误");
    }
}

QString Data::GetRoomTypeStr(const RoomType &type)
{
    switch(type) {
    case Single:
        return QStringLiteral("单人间");
    case Dual:
        return QStringLiteral("双人间");
    case Deluxe:
        return QStringLiteral("豪华间");
    case President:
        return QStringLiteral("总统套房");
    case Invalid:
        return QStringLiteral("错误");
    }
}

QString Data::GetRoomTypePicturePath(const RoomInfo &info)
{
    return PicturePath[info.type];
}

void Data::Initialize()
{
    gRoomSummary.totalAmount = 300;
    for (int i = 0; i < 4; ++i) {
        gRoomSummary.info[i].amount = AMOUNT[i];
        gRoomSummary.info[i].type = static_cast<RoomType>(i);
        gRoomSummary.info[i].price = PRICE[i];
        gRoomSummary.info[i].remain = AMOUNT[i];
    }
}


QDataStream& operator<<(QDataStream& output, const Data::Person& record)
{
    output << record.name << record.gender << record.idNumber << record.phoneNumber;
    return output;
}

QDataStream& operator>>(QDataStream& in, Data::Person& record)
{
    in >> record.name >> record.gender >> record.idNumber >> record.phoneNumber;
    return in;
}

QDataStream& operator<<(QDataStream& output, const Data::RoomRecord& record)
{
    output << record.roomNum << record.checkIn << record.checkOut
           << record.isCheckIn << record.roomNum
           << record.p << record.p2 << record.type;
    return output;
}

QDataStream& operator>>(QDataStream& in, Data::RoomRecord& record)
{
    in >> record.roomNum >> record.checkIn >> record.checkOut
           >> record.isCheckIn >> record.roomNum
           >> record.p >> record.p2 >> record.type;
    return in;
}
