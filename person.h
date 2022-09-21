#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QDate>

class person : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber)
    Q_PROPERTY(GENDER gender READ gender WRITE setGender)
    Q_PROPERTY(QDate dob READ dob WRITE setDob)
    Q_ENUMS(GENDER)
public:
    explicit person(QObject *parent = nullptr);
    ~person() {}

    QString name() const {return _name;}
    void setName(const QString &name) {_name = name;}

    QString phoneNumber() const {return _phoneNumber;}
    void setPhoneNumber(const QString phoneNumber) {_phoneNumber = phoneNumber;}

    enum GENDER {MALE, FEMALE};
    void setGender(GENDER gender) {_gender = gender;}
    GENDER gender() const {return _gender;}

    QDate dob() const {return _dob;}
    void setDob(const QDate &dob) {_dob = dob;}
signals:


private:
    QString _name;
    QString _phoneNumber;
    GENDER _gender;
    QDate _dob;
};

#endif // PERSON_H
