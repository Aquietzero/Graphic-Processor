/****************************************************************************
** Meta object code from reading C++ file 'Dialogs.h'
**
** Created: Sat Dec 31 11:45:37 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Dialogs.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Dialogs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GaussianNoiseDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   21,   20,   20, 0x05,
      52,   20,   20,   20, 0x05,
      76,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     100,   20,   20,   20, 0x0a,
     116,   20,   20,   20, 0x0a,
     132,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GaussianNoiseDialog[] = {
    "GaussianNoiseDialog\0\0mean,sd\0"
    "applySettings(int,int)\0closeAndApplySettings()\0"
    "closeNotApplySettings()\0applyNotClose()\0"
    "closeAndApply()\0closeNotApply()\0"
};

const QMetaObject GaussianNoiseDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GaussianNoiseDialog,
      qt_meta_data_GaussianNoiseDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GaussianNoiseDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GaussianNoiseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GaussianNoiseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GaussianNoiseDialog))
        return static_cast<void*>(const_cast< GaussianNoiseDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int GaussianNoiseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: applySettings((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: closeAndApplySettings(); break;
        case 2: closeNotApplySettings(); break;
        case 3: applyNotClose(); break;
        case 4: closeAndApply(); break;
        case 5: closeNotApply(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void GaussianNoiseDialog::applySettings(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GaussianNoiseDialog::closeAndApplySettings()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GaussianNoiseDialog::closeNotApplySettings()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
static const uint qt_meta_data_ImpulseNoiseDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   20,   19,   19, 0x05,
      55,   19,   19,   19, 0x05,
      79,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     103,   19,   19,   19, 0x0a,
     119,   19,   19,   19, 0x0a,
     135,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImpulseNoiseDialog[] = {
    "ImpulseNoiseDialog\0\0pa,pb\0"
    "applySettings(double,double)\0"
    "closeAndApplySettings()\0closeNotApplySettings()\0"
    "applyNotClose()\0closeAndApply()\0"
    "closeNotApply()\0"
};

const QMetaObject ImpulseNoiseDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ImpulseNoiseDialog,
      qt_meta_data_ImpulseNoiseDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImpulseNoiseDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImpulseNoiseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImpulseNoiseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImpulseNoiseDialog))
        return static_cast<void*>(const_cast< ImpulseNoiseDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ImpulseNoiseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: applySettings((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: closeAndApplySettings(); break;
        case 2: closeNotApplySettings(); break;
        case 3: applyNotClose(); break;
        case 4: closeAndApply(); break;
        case 5: closeNotApply(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ImpulseNoiseDialog::applySettings(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImpulseNoiseDialog::closeAndApplySettings()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ImpulseNoiseDialog::closeNotApplySettings()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
static const uint qt_meta_data_SpatialFilteringDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   24,   23,   23, 0x05,
      52,   23,   23,   23, 0x05,
      76,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
     100,   23,   23,   23, 0x0a,
     116,   23,   23,   23, 0x0a,
     132,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SpatialFilteringDialog[] = {
    "SpatialFilteringDialog\0\0filter\0"
    "applySettings(int**)\0closeAndApplySettings()\0"
    "closeNotApplySettings()\0applyNotClose()\0"
    "closeAndApply()\0closeNotApply()\0"
};

const QMetaObject SpatialFilteringDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SpatialFilteringDialog,
      qt_meta_data_SpatialFilteringDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpatialFilteringDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpatialFilteringDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpatialFilteringDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpatialFilteringDialog))
        return static_cast<void*>(const_cast< SpatialFilteringDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SpatialFilteringDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: applySettings((*reinterpret_cast< int**(*)>(_a[1]))); break;
        case 1: closeAndApplySettings(); break;
        case 2: closeNotApplySettings(); break;
        case 3: applyNotClose(); break;
        case 4: closeAndApply(); break;
        case 5: closeNotApply(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SpatialFilteringDialog::applySettings(int * * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SpatialFilteringDialog::closeAndApplySettings()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SpatialFilteringDialog::closeNotApplySettings()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
static const uint qt_meta_data_ColorExtractDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   20,   19,   19, 0x05,
      63,   19,   19,   19, 0x05,
      87,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     111,   19,   19,   19, 0x0a,
     127,   19,   19,   19, 0x0a,
     143,   19,   19,   19, 0x0a,
     159,   19,   19,   19, 0x08,
     176,   19,   19,   19, 0x08,
     195,   19,   19,   19, 0x08,
     213,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ColorExtractDialog[] = {
    "ColorExtractDialog\0\0r,g,b,range\0"
    "applySettings(int,int,int,int)\0"
    "closeAndApplySettings()\0closeNotApplySettings()\0"
    "applyNotClose()\0closeAndApply()\0"
    "closeNotApply()\0setRedValue(int)\0"
    "setGreenValue(int)\0setBlueValue(int)\0"
    "setRangeValue(int)\0"
};

const QMetaObject ColorExtractDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ColorExtractDialog,
      qt_meta_data_ColorExtractDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColorExtractDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColorExtractDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColorExtractDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColorExtractDialog))
        return static_cast<void*>(const_cast< ColorExtractDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ColorExtractDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: applySettings((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: closeAndApplySettings(); break;
        case 2: closeNotApplySettings(); break;
        case 3: applyNotClose(); break;
        case 4: closeAndApply(); break;
        case 5: closeNotApply(); break;
        case 6: setRedValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: setGreenValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setBlueValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setRangeValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ColorExtractDialog::applySettings(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ColorExtractDialog::closeAndApplySettings()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ColorExtractDialog::closeNotApplySettings()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
