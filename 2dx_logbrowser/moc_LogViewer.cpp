/****************************************************************************
** Meta object code from reading C++ file 'LogViewer.h'
**
** Created: Wed Jan 20 16:56:02 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "LogViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LogViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LogViewer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LogViewer[] = {
    "LogViewer\0\0updateViewer()\0"
};

const QMetaObject LogViewer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LogViewer,
      qt_meta_data_LogViewer, 0 }
};

const QMetaObject *LogViewer::metaObject() const
{
    return &staticMetaObject;
}

void *LogViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LogViewer))
        return static_cast<void*>(const_cast< LogViewer*>(this));
    return QWidget::qt_metacast(_clname);
}

int LogViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateViewer(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
