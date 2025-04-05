/****************************************************************************
** Meta object code from reading C++ file 'faceconfirm.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../faceconfirm.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'faceconfirm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFaceConfirmENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFaceConfirmENDCLASS = QtMocHelpers::stringData(
    "FaceConfirm",
    "send_id",
    "",
    "int64_t",
    "id",
    "regFace",
    "cv::Mat&",
    "image",
    "selectFace",
    "cv::Mat"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFaceConfirmENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[12];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[3];
    char stringdata5[8];
    char stringdata6[9];
    char stringdata7[6];
    char stringdata8[11];
    char stringdata9[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFaceConfirmENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFaceConfirmENDCLASS_t qt_meta_stringdata_CLASSFaceConfirmENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "FaceConfirm"
        QT_MOC_LITERAL(12, 7),  // "send_id"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 7),  // "int64_t"
        QT_MOC_LITERAL(29, 2),  // "id"
        QT_MOC_LITERAL(32, 7),  // "regFace"
        QT_MOC_LITERAL(40, 8),  // "cv::Mat&"
        QT_MOC_LITERAL(49, 5),  // "image"
        QT_MOC_LITERAL(55, 10),  // "selectFace"
        QT_MOC_LITERAL(66, 7)   // "cv::Mat"
    },
    "FaceConfirm",
    "send_id",
    "",
    "int64_t",
    "id",
    "regFace",
    "cv::Mat&",
    "image",
    "selectFace",
    "cv::Mat"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFaceConfirmENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   35,    2, 0x0a,    3 /* Public */,
       8,    1,   38,    2, 0x0a,    5 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    0x80000000 | 3, 0x80000000 | 6,    7,
    QMetaType::Int, 0x80000000 | 9,    7,

       0        // eod
};

Q_CONSTINIT const QMetaObject FaceConfirm::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSFaceConfirmENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFaceConfirmENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFaceConfirmENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FaceConfirm, std::true_type>,
        // method 'send_id'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int64_t, std::false_type>,
        // method 'regFace'
        QtPrivate::TypeAndForceComplete<int64_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<cv::Mat &, std::false_type>,
        // method 'selectFace'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<cv::Mat, std::false_type>
    >,
    nullptr
} };

void FaceConfirm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FaceConfirm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->send_id((*reinterpret_cast< std::add_pointer_t<int64_t>>(_a[1]))); break;
        case 1: { int64_t _r = _t->regFace((*reinterpret_cast< std::add_pointer_t<cv::Mat&>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int64_t*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->selectFace((*reinterpret_cast< std::add_pointer_t<cv::Mat>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FaceConfirm::*)(int64_t );
            if (_t _q_method = &FaceConfirm::send_id; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *FaceConfirm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FaceConfirm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFaceConfirmENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FaceConfirm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FaceConfirm::send_id(int64_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
