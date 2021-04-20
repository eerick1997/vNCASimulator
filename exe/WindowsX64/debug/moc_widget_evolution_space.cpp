/****************************************************************************
** Meta object code from reading C++ file 'widget_evolution_space.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/widget_evolution_space.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_evolution_space.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_evolution_space_t {
    QByteArrayData data[18];
    char stringdata0[279];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_evolution_space_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_evolution_space_t qt_meta_stringdata_widget_evolution_space = {
    {
QT_MOC_LITERAL(0, 0, 22), // "widget_evolution_space"
QT_MOC_LITERAL(1, 23, 15), // "set_alive_color"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 15), // "set_death_color"
QT_MOC_LITERAL(4, 56, 20), // "set_projection_color"
QT_MOC_LITERAL(5, 77, 14), // "set_grid_color"
QT_MOC_LITERAL(6, 92, 20), // "draw_evolution_space"
QT_MOC_LITERAL(7, 113, 9), // "QPainter&"
QT_MOC_LITERAL(8, 123, 22), // "next_generation_update"
QT_MOC_LITERAL(9, 146, 11), // "set_project"
QT_MOC_LITERAL(10, 158, 13), // "set_show_grid"
QT_MOC_LITERAL(11, 172, 17), // "set_show_gradient"
QT_MOC_LITERAL(12, 190, 11), // "set_3d_mode"
QT_MOC_LITERAL(13, 202, 20), // "draw_with_projection"
QT_MOC_LITERAL(14, 223, 9), // "draw_cube"
QT_MOC_LITERAL(15, 233, 7), // "QColor&"
QT_MOC_LITERAL(16, 241, 14), // "draw_dead_cell"
QT_MOC_LITERAL(17, 256, 22) // "render_evolution_space"

    },
    "widget_evolution_space\0set_alive_color\0"
    "\0set_death_color\0set_projection_color\0"
    "set_grid_color\0draw_evolution_space\0"
    "QPainter&\0next_generation_update\0"
    "set_project\0set_show_grid\0set_show_gradient\0"
    "set_3d_mode\0draw_with_projection\0"
    "draw_cube\0QColor&\0draw_dead_cell\0"
    "render_evolution_space"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget_evolution_space[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       3,    1,   87,    2, 0x0a /* Public */,
       4,    1,   90,    2, 0x0a /* Public */,
       5,    1,   93,    2, 0x0a /* Public */,
       6,    1,   96,    2, 0x0a /* Public */,
       8,    0,   99,    2, 0x0a /* Public */,
       9,    1,  100,    2, 0x0a /* Public */,
      10,    1,  103,    2, 0x0a /* Public */,
      11,    1,  106,    2, 0x0a /* Public */,
      12,    1,  109,    2, 0x0a /* Public */,
      13,    1,  112,    2, 0x0a /* Public */,
      14,    6,  115,    2, 0x0a /* Public */,
      16,    1,  128,    2, 0x0a /* Public */,
      17,    1,  131,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal, 0x80000000 | 15, 0x80000000 | 15,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

void widget_evolution_space::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget_evolution_space *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_alive_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 1: _t->set_death_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 2: _t->set_projection_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 3: _t->set_grid_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 4: _t->draw_evolution_space((*reinterpret_cast< QPainter(*)>(_a[1]))); break;
        case 5: _t->next_generation_update(); break;
        case 6: _t->set_project((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->set_show_grid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->set_show_gradient((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->set_3d_mode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->draw_with_projection((*reinterpret_cast< QPainter(*)>(_a[1]))); break;
        case 11: _t->draw_cube((*reinterpret_cast< QPainter(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< QColor(*)>(_a[5])),(*reinterpret_cast< QColor(*)>(_a[6]))); break;
        case 12: _t->draw_dead_cell((*reinterpret_cast< QPainter(*)>(_a[1]))); break;
        case 13: _t->render_evolution_space((*reinterpret_cast< QPainter(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget_evolution_space::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_widget_evolution_space.data,
    qt_meta_data_widget_evolution_space,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget_evolution_space::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget_evolution_space::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget_evolution_space.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget_evolution_space::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
