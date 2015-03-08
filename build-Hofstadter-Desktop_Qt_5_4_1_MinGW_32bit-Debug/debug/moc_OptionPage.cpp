/****************************************************************************
** Meta object code from reading C++ file 'OptionPage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Code/OptionPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OptionPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OptionPage_t {
    QByteArrayData data[7];
    char stringdata[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OptionPage_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OptionPage_t qt_meta_stringdata_OptionPage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "OptionPage"
QT_MOC_LITERAL(1, 11, 8), // "updateGS"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "noIC"
QT_MOC_LITERAL(4, 26, 16), // "updateGSLineEdit"
QT_MOC_LITERAL(5, 43, 1), // "r"
QT_MOC_LITERAL(6, 45, 1) // "c"

    },
    "OptionPage\0updateGS\0\0noIC\0updateGSLineEdit\0"
    "r\0c"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OptionPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    2,   37,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x2a /* Public | MethodCloned */,
       4,    0,   45,    2, 0x2a /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void OptionPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OptionPage *_t = static_cast<OptionPage *>(_o);
        switch (_id) {
        case 0: _t->updateGS((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateGSLineEdit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->updateGSLineEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateGSLineEdit(); break;
        default: ;
        }
    }
}

const QMetaObject OptionPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_OptionPage.data,
      qt_meta_data_OptionPage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OptionPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OptionPage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OptionPage.stringdata))
        return static_cast<void*>(const_cast< OptionPage*>(this));
    return QWizardPage::qt_metacast(_clname);
}

int OptionPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
