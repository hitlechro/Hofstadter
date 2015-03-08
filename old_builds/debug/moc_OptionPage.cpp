/****************************************************************************
** Meta object code from reading C++ file 'OptionPage.h'
**
** Created: Sat Jan 26 19:36:09 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Code/OptionPage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OptionPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OptionPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x0a,
      35,   31,   11,   11, 0x0a,
      63,   61,   11,   11, 0x2a,
      85,   11,   11,   11, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_OptionPage[] = {
    "OptionPage\0\0noIC\0updateGS(int)\0r,c\0"
    "updateGSLineEdit(int,int)\0r\0"
    "updateGSLineEdit(int)\0updateGSLineEdit()\0"
};

void OptionPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
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

const QMetaObjectExtraData OptionPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OptionPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_OptionPage,
      qt_meta_data_OptionPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OptionPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OptionPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OptionPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OptionPage))
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
    }
    return _id;
}
QT_END_MOC_NAMESPACE
