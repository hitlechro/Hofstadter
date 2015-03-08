/****************************************************************************
** Meta object code from reading C++ file 'ConfigPage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Code/ConfigPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfigPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ConfigPage_t {
    QByteArrayData data[10];
    char stringdata[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigPage_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigPage_t qt_meta_stringdata_ConfigPage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ConfigPage"
QT_MOC_LITERAL(1, 11, 18), // "addExtraConstraint"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 21), // "removeExtraConstraint"
QT_MOC_LITERAL(4, 53, 8), // "updateIC"
QT_MOC_LITERAL(5, 62, 4), // "noIC"
QT_MOC_LITERAL(6, 67, 18), // "updateParaLineEdit"
QT_MOC_LITERAL(7, 86, 16), // "updateICLineEdit"
QT_MOC_LITERAL(8, 103, 1), // "r"
QT_MOC_LITERAL(9, 105, 1) // "c"

    },
    "ConfigPage\0addExtraConstraint\0\0"
    "removeExtraConstraint\0updateIC\0noIC\0"
    "updateParaLineEdit\0updateICLineEdit\0"
    "r\0c"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    1,   51,    2, 0x0a /* Public */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    2,   55,    2, 0x0a /* Public */,
       7,    1,   60,    2, 0x2a /* Public | MethodCloned */,
       7,    0,   63,    2, 0x2a /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,

       0        // eod
};

void ConfigPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConfigPage *_t = static_cast<ConfigPage *>(_o);
        switch (_id) {
        case 0: _t->addExtraConstraint(); break;
        case 1: _t->removeExtraConstraint(); break;
        case 2: _t->updateIC((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateParaLineEdit(); break;
        case 4: _t->updateICLineEdit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->updateICLineEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateICLineEdit(); break;
        default: ;
        }
    }
}

const QMetaObject ConfigPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_ConfigPage.data,
      qt_meta_data_ConfigPage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConfigPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigPage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigPage.stringdata))
        return static_cast<void*>(const_cast< ConfigPage*>(this));
    return QWizardPage::qt_metacast(_clname);
}

int ConfigPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
