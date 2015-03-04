/****************************************************************************
** Meta object code from reading C++ file 'SelectPage.h'
**
** Created: Sat Jan 26 19:36:01 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Code/SelectPage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SelectPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SelectPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      28,   11,   11,   11, 0x0a,
      51,   46,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SelectPage[] = {
    "SelectPage\0\0saveRecursion()\0"
    "removeRecursion()\0item\0"
    "updateLineEdit(QListWidgetItem*)\0"
};

void SelectPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SelectPage *_t = static_cast<SelectPage *>(_o);
        switch (_id) {
        case 0: _t->saveRecursion(); break;
        case 1: _t->removeRecursion(); break;
        case 2: _t->updateLineEdit((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SelectPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SelectPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_SelectPage,
      qt_meta_data_SelectPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SelectPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SelectPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SelectPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SelectPage))
        return static_cast<void*>(const_cast< SelectPage*>(this));
    return QWizardPage::qt_metacast(_clname);
}

int SelectPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
