/****************************************************************************
** Meta object code from reading C++ file 'ConfigPage.h'
**
** Created: Sat Jan 26 19:35:59 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Code/ConfigPage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfigPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConfigPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      33,   11,   11,   11, 0x0a,
      62,   57,   11,   11, 0x0a,
      76,   11,   11,   11, 0x0a,
     101,   97,   11,   11, 0x0a,
     129,  127,   11,   11, 0x2a,
     151,   11,   11,   11, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_ConfigPage[] = {
    "ConfigPage\0\0addExtraConstraint()\0"
    "removeExtraConstraint()\0noIC\0updateIC(int)\0"
    "updateParaLineEdit()\0r,c\0"
    "updateICLineEdit(int,int)\0r\0"
    "updateICLineEdit(int)\0updateICLineEdit()\0"
};

void ConfigPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
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

const QMetaObjectExtraData ConfigPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConfigPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_ConfigPage,
      qt_meta_data_ConfigPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConfigPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConfigPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConfigPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigPage))
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
    }
    return _id;
}
QT_END_MOC_NAMESPACE
