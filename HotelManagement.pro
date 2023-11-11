QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Core/Data.cc \
    Core/PersistenceData.cc \
    Core/RoomRecordManager.cc \
    Dialogs/LoginDialog.cpp \
    Dialogs/Mydialog.cpp \
    Pages/BookingPage.cc \
    Pages/CheckInPage.cc \
    Pages/CheckOutPage.cc \
    Pages/SearchPage.cc \
    Pages/SearchPersonPage.cc \
    Pages/SearchRoomPage.cc \
    Pages/SystemPage.cc \
    Utils/IconHelper.cpp \
    Widgets/DateTimeEdit/button_day.cpp \
    Widgets/DateTimeEdit/date_time_edit.cpp \
    Widgets/DateTimeEdit/date_time_widget.cpp \
    Widgets/IDNumberLineEdit.cc \
    Widgets/MobilePhoneLineEdit.cc \
    Widgets/RoomSummaryTable.cc \
    main.cpp \
    MainWindow.cc

HEADERS += \
    Core/Data.h \
    Core/PersistenceData.h \
    Core/RoomRecordManager.h \
    Dialogs/LoginDialog.h \
    Dialogs/Mydialog.h \
    MainWindow.h \
    Pages/BookingPage.h \
    Pages/CheckInPage.h \
    Pages/CheckOutPage.h \
    Pages/SearchPage.h \
    Pages/SearchPersonPage.h \
    Pages/SearchRoomPage.h \
    Pages/SystemPage.h \
    Utils/IconHelper.h \
    Widgets/DateTimeEdit/button_day.h \
    Widgets/DateTimeEdit/date_time_defines.h \
    Widgets/DateTimeEdit/date_time_edit.h \
    Widgets/DateTimeEdit/date_time_widget.h \
    Widgets/IDNumberLineEdit.h \
    Widgets/MobilePhoneLineEdit.h \
    Widgets/RoomSummaryTable.h

FORMS += \
    Dialogs/LoginDialog.ui \
    Dialogs/Mydialog.ui \
    MainWindow.ui \
    Pages/BookingPage.ui \
    Pages/CheckInPage.ui \
    Pages/CheckOutPage.ui \
    Pages/SearchPage.ui \
    Pages/SearchPersonPage.ui \
    Pages/SearchRoomPage.ui \
    Pages/SystemPage.ui \
    Widgets/DateTimeEdit/date_time_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

RC_ICONS = images/double.ico

INCLUDEPATH += Widgets/DateTimeEdit
