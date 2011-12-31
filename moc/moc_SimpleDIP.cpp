/****************************************************************************
** Meta object code from reading C++ file 'SimpleDIP.h'
**
** Created: Sat Dec 31 19:57:35 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SimpleDIP.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimpleDIP.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimpleDIP[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   10,   10,   10, 0x08,
      39,   10,   34,   10, 0x08,
      46,   10,   34,   10, 0x08,
      55,   10,   10,   10, 0x08,
      66,   10,   10,   10, 0x08,
      80,   10,   10,   10, 0x08,
      99,   10,   10,   10, 0x08,
     115,   10,   10,   10, 0x08,
     133,   10,   10,   10, 0x08,
     150,   10,   10,   10, 0x08,
     170,  165,   10,   10, 0x08,
     185,  165,   10,   10, 0x08,
     202,  165,   10,   10, 0x08,
     218,   10,   10,   10, 0x08,
     233,  165,   10,   10, 0x08,
     253,  165,   10,   10, 0x08,
     275,   10,   10,   10, 0x08,
     293,   10,   10,   10, 0x08,
     314,   10,   10,   10, 0x08,
     332,   10,   10,   10, 0x08,
     351,   10,   10,   10, 0x08,
     370,   10,   10,   10, 0x08,
     377,   10,   10,   10, 0x08,
     392,   10,   10,   10, 0x08,
     409,   10,   10,   10, 0x08,
     430,   10,   10,   10, 0x08,
     449,   10,   10,   10, 0x08,
     475,  468,   10,   10, 0x08,
     504,   10,   10,   10, 0x08,
     516,   10,   10,   10, 0x08,
     540,  532,   10,   10, 0x08,
     566,   10,   10,   10, 0x08,
     587,  581,   10,   10, 0x08,
     618,   10,   10,   10, 0x08,
     648,  636,   10,   10, 0x08,
     686,   10,   10,   10, 0x08,
     704,   10,   10,   10, 0x08,
     723,   10,   10,   10, 0x08,
     742,   10,   10,   10, 0x08,
     758,   10,   10,   10, 0x08,
     764,   10,   10,   10, 0x08,
     771,   10,   10,   10, 0x08,
     778,   10,   10,   10, 0x08,
     785,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SimpleDIP[] = {
    "SimpleDIP\0\0imageModified()\0open()\0"
    "bool\0save()\0saveAs()\0tempSave()\0"
    "tempRestore()\0setImageModified()\0"
    "getRedChannel()\0getGreenChannel()\0"
    "getBlueChannel()\0getGreyScale()\0rate\0"
    "redChange(int)\0greenChange(int)\0"
    "blueChange(int)\0colorsChange()\0"
    "contrastChange(int)\0brightnessChange(int)\0"
    "hisEqualization()\0hisEqualizationAVG()\0"
    "fixedHalftoning()\0expandHalftoning()\0"
    "laplaceTransform()\0blur()\0weightedBlur()\0"
    "laplaceEnhance()\0unsharpMaskEnhance()\0"
    "highBoostEnhance()\0spatialFiltering()\0"
    "filter\0applySpatialFiltering(int**)\0"
    "resizeImg()\0gaussianNoise()\0mean,sd\0"
    "addGaussianNoise(int,int)\0impulseNoise()\0"
    "pa,pb\0addImpulseNoise(double,double)\0"
    "colorExtracting()\0r,g,b,range\0"
    "applyColorExtracting(int,int,int,int)\0"
    "medianFiltering()\0maximumFiltering()\0"
    "minimumFiltering()\0originalImage()\0"
    "fft()\0ifft()\0LPGF()\0HPGF()\0imgMatching()\0"
};

const QMetaObject SimpleDIP::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SimpleDIP,
      qt_meta_data_SimpleDIP, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimpleDIP::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimpleDIP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimpleDIP::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleDIP))
        return static_cast<void*>(const_cast< SimpleDIP*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SimpleDIP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: imageModified(); break;
        case 1: open(); break;
        case 2: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: tempSave(); break;
        case 5: tempRestore(); break;
        case 6: setImageModified(); break;
        case 7: getRedChannel(); break;
        case 8: getGreenChannel(); break;
        case 9: getBlueChannel(); break;
        case 10: getGreyScale(); break;
        case 11: redChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: greenChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: blueChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: colorsChange(); break;
        case 15: contrastChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: brightnessChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: hisEqualization(); break;
        case 18: hisEqualizationAVG(); break;
        case 19: fixedHalftoning(); break;
        case 20: expandHalftoning(); break;
        case 21: laplaceTransform(); break;
        case 22: blur(); break;
        case 23: weightedBlur(); break;
        case 24: laplaceEnhance(); break;
        case 25: unsharpMaskEnhance(); break;
        case 26: highBoostEnhance(); break;
        case 27: spatialFiltering(); break;
        case 28: applySpatialFiltering((*reinterpret_cast< int**(*)>(_a[1]))); break;
        case 29: resizeImg(); break;
        case 30: gaussianNoise(); break;
        case 31: addGaussianNoise((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 32: impulseNoise(); break;
        case 33: addImpulseNoise((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 34: colorExtracting(); break;
        case 35: applyColorExtracting((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 36: medianFiltering(); break;
        case 37: maximumFiltering(); break;
        case 38: minimumFiltering(); break;
        case 39: originalImage(); break;
        case 40: fft(); break;
        case 41: ifft(); break;
        case 42: LPGF(); break;
        case 43: HPGF(); break;
        case 44: imgMatching(); break;
        default: ;
        }
        _id -= 45;
    }
    return _id;
}

// SIGNAL 0
void SimpleDIP::imageModified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
