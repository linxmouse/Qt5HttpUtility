#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>
#include <QFile>

#include <qjson/include/QJson/Parser>
#include <qjson/include/QJson/QObjectHelper>
#include <qjson/include/QJson/Serializer>

#include <person.h>

using namespace QJson;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    person p;
    p.setName("SimpleJsonEx");
    p.setPhoneNumber("13388888888");
    p.setGender(person::MALE);
    p.setDob(QDate(1970,1,1));

    // 对象序列化到字符串
    QVariantMap map = QObjectHelper::qobject2qvariant(&p);
    Serializer serializer;
    serializer.setIndentMode(IndentMode::IndentFull);
    QByteArray json = serializer.serialize(map);
    qDebug() << json;

    // 修改对象值
    map["name"] = "NameChanged";
    map["phoneNumber"] = "18866666666";
    json = serializer.serialize(map);
    qDebug() << json;

    // 保存Json
    QFile fw("person.json");
    fw.open(QIODevice::WriteOnly | QIODevice::Text);
    fw.write(json);
    fw.close();

    // 读取Json
    QFile fr;
    fr.setFileName("person.json");
    fr.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray raw = fr.readAll();
    fr.close();

    // 字符串(解析)反序列化到对象
    Parser parser;
    QVariant variant = parser.parse(raw);
    person dp;
    QObjectHelper::qvariant2qobject(variant.toMap(), &dp);
    qDebug() << dp.name() << dp.phoneNumber() << dp.gender() << dp.dob();

    MainWindow w;
    w.show();
    return a.exec();
}
