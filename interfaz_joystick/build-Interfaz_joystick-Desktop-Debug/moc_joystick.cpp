/****************************************************************************
** Meta object code from reading C++ file 'joystick.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Interfaz_joystick/joystick.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'joystick.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Joystick[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Joystick[] = {
    "Joystick\0prueba()\0\0"
};

void Joystick::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Joystick *_t = static_cast<Joystick *>(_o);
        switch (_id) {
        case 0: _t->prueba(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Joystick::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Joystick::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Joystick,
      qt_meta_data_Joystick, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Joystick::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Joystick::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Joystick::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Joystick))
        return static_cast<void*>(const_cast< Joystick*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Joystick::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
