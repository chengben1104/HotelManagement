#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QDataStream>

class Data : public QObject
{
    Q_OBJECT
public:
    enum RoomType
    {
        Single, //单人间
        Dual,   // 双人间
        Deluxe, // 豪华间
        President,   // 总统套房
        Invalid
    };

    enum Gender{
        Male,
        Female
    };

    static constexpr int ROOM_TYPE_COUNT = 4;

    static constexpr int PRICE[4] = {100, 200, 300, 500};
    static constexpr int AMOUNT[4] = {150, 100, 45, 5};
    static const QString PicturePath[4];
    static constexpr int ROOM_ID_OFFSET = 8100;  //起始编号
    static constexpr int ROOM_AMOUNT = 300;

    struct RoomInfo
    {
        RoomType type;
        int price;
        int remain;  //可用数量
        int amount;
    };

    //汇总所有客房类型的信息
    struct RoomSummary
    {
        RoomInfo info[4];
        int totalAmount;
    };

    struct Person {
        QString name{""};
        QString phoneNumber;
        QString idNumber;
        Gender gender;
    };

    //一次客人的入住和退房记录，包括了入住和退房时间、客房类型、入住人和退房人等属性
    struct RoomRecord {
    public:
        Person p;
        Person p2;
        QDate checkIn;
        QDate checkOut;
        RoomType type{Invalid};
        int roomNum{0};
        bool isCheckIn{false};

        inline Data::RoomRecord& operator=(const Data::RoomRecord& other)
        {
            if (this == &other) {
                return *this;
            } else {
                this->p = other.p;
                this->p2 = other.p2;
                this->checkIn = other.checkIn;
                this->checkOut = other.checkOut;
                this->isCheckIn = other.isCheckIn;
                this->roomNum = other.roomNum;
                this->type = other.type;
            }
            return *this;
        }
    };

    Data(QObject* parent);

    static QString GetRoomTypeStr(const RoomInfo& info);
    static QString GetRoomTypeStr(const RoomType& type);
    static QString GetRoomTypePicturePath(const RoomInfo& info);
    static void Initialize();
    static RoomSummary gRoomSummary;
};

QDataStream& operator<<(QDataStream& output, const Data::Person& record);
QDataStream& operator>>(QDataStream& in, Data::Person& record);
QDataStream& operator<<(QDataStream& output, const Data::RoomRecord& record);
QDataStream& operator>>(QDataStream& in, Data::RoomRecord& record);

inline bool operator==(const Data::Person& lhs, const Data::Person& rhs)
{
    return lhs.gender == rhs.gender && lhs.idNumber == rhs.idNumber
            && lhs.phoneNumber == rhs.phoneNumber && lhs.name == rhs.name;
}

inline bool operator==(const Data::RoomRecord& lhs, const Data::RoomRecord& rhs)
{
    return lhs.p == rhs.p && lhs.p2 == lhs.p2 && lhs.checkIn == rhs.checkIn
            && lhs.checkOut == rhs.checkOut && lhs.isCheckIn == rhs.isCheckIn
            && lhs.roomNum == rhs.roomNum && lhs.type == rhs.type;
}



#endif // DATA_H
