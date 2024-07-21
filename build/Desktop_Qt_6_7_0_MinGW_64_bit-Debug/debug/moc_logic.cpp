/****************************************************************************
** Meta object code from reading C++ file 'logic.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../logic.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
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
struct qt_meta_stringdata_CLASSLogicENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSLogicENDCLASS = QtMocHelpers::stringData(
    "Logic",
    "ChangeMove",
    "",
    "Moved",
    "WhiteMove",
    "BlackMove",
    "DeleteFigureBlackBoard",
    "Figure*",
    "fig",
    "COLOR",
    "clr",
    "DeleteFigureWhiteBoard",
    "CheckForCheck",
    "Notation",
    "HidePossibleMoves",
    "MakeMoveTo",
    "str",
    "ShowPossibleMoves",
    "FieldElement*",
    "element",
    "KillFigure"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLogicENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,
       3,    0,   81,    2, 0x06,    2 /* Public */,
       4,    0,   82,    2, 0x06,    3 /* Public */,
       5,    0,   83,    2, 0x06,    4 /* Public */,
       6,    2,   84,    2, 0x06,    5 /* Public */,
      11,    2,   89,    2, 0x06,    8 /* Public */,
      12,    1,   94,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    0,   97,    2, 0x0a,   13 /* Public */,
      15,    1,   98,    2, 0x0a,   14 /* Public */,
      17,    1,  101,    2, 0x0a,   16 /* Public */,
      20,    1,  104,    2, 0x0a,   18 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

Q_CONSTINIT const QMetaObject Logic::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSLogicENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLogicENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSLogicENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Logic, std::true_type>,
        // method 'ChangeMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Moved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'WhiteMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'BlackMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'DeleteFigureBlackBoard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Figure *, std::false_type>,
        QtPrivate::TypeAndForceComplete<COLOR, std::false_type>,
        // method 'DeleteFigureWhiteBoard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Figure *, std::false_type>,
        QtPrivate::TypeAndForceComplete<COLOR, std::false_type>,
        // method 'CheckForCheck'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'HidePossibleMoves'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'MakeMoveTo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'ShowPossibleMoves'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<FieldElement *, std::false_type>,
        // method 'KillFigure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<FieldElement *, std::false_type>
    >,
    nullptr
} };

void Logic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Logic *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ChangeMove(); break;
        case 1: _t->Moved(); break;
        case 2: _t->WhiteMove(); break;
        case 3: _t->BlackMove(); break;
        case 4: _t->DeleteFigureBlackBoard((*reinterpret_cast< std::add_pointer_t<Figure*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<COLOR>>(_a[2]))); break;
        case 5: _t->DeleteFigureWhiteBoard((*reinterpret_cast< std::add_pointer_t<Figure*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<COLOR>>(_a[2]))); break;
        case 6: _t->CheckForCheck((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->HidePossibleMoves(); break;
        case 8: _t->MakeMoveTo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->ShowPossibleMoves((*reinterpret_cast< std::add_pointer_t<FieldElement*>>(_a[1]))); break;
        case 10: _t->KillFigure((*reinterpret_cast< std::add_pointer_t<FieldElement*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Figure* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Figure* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< FieldElement* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< FieldElement* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Logic::*)();
            if (_t _q_method = &Logic::ChangeMove; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Logic::*)();
            if (_t _q_method = &Logic::Moved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Logic::*)();
            if (_t _q_method = &Logic::WhiteMove; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Logic::*)();
            if (_t _q_method = &Logic::BlackMove; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Logic::*)(Figure * , COLOR );
            if (_t _q_method = &Logic::DeleteFigureBlackBoard; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Logic::*)(Figure * , COLOR );
            if (_t _q_method = &Logic::DeleteFigureWhiteBoard; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Logic::*)(const QString & );
            if (_t _q_method = &Logic::CheckForCheck; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *Logic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Logic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLogicENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Logic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Logic::ChangeMove()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Logic::Moved()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Logic::WhiteMove()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Logic::BlackMove()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Logic::DeleteFigureBlackBoard(Figure * _t1, COLOR _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Logic::DeleteFigureWhiteBoard(Figure * _t1, COLOR _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Logic::CheckForCheck(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
