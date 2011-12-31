/****************************************************************************
** Meta object code from reading C++ file 'CentralArea.h'
**
** Created: Sat Dec 31 19:57:33 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CentralArea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CentralArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CentralArea[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_CentralArea[] = {
    "CentralArea\0"
};

const QMetaObject CentralArea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CentralArea,
      qt_meta_data_CentralArea, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CentralArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CentralArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CentralArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CentralArea))
        return static_cast<void*>(const_cast< CentralArea*>(this));
    return QWidget::qt_metacast(_clname);
}

int CentralArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_DoubleCentralArea[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_DoubleCentralArea[] = {
    "DoubleCentralArea\0"
};

const QMetaObject DoubleCentralArea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DoubleCentralArea,
      qt_meta_data_DoubleCentralArea, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DoubleCentralArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DoubleCentralArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DoubleCentralArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DoubleCentralArea))
        return static_cast<void*>(const_cast< DoubleCentralArea*>(this));
    return QWidget::qt_metacast(_clname);
}

int DoubleCentralArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
