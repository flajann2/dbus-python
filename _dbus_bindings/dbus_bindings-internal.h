/* _dbus_bindings internal API. For use within _dbus_bindings only.
 *
 * Copyright (C) 2006 Collabora Ltd. <http://www.collabora.co.uk/>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef DBUS_BINDINGS_INTERNAL_H
#define DBUS_BINDINGS_INTERNAL_H

#include <Python.h>
#define INSIDE_DBUS_BINDINGS
#include "dbus_bindings.h"

/* no need for extern "C", this is only for internal use */

/* on/off switch for debugging support (see below) */
#undef USING_DBG
/* #define USING_DBG 1 */

#define DEFINE_CHECK(type) \
static inline int type##_Check (PyObject *o) \
{ \
    return (PyObject_TypeCheck (o, &type##_Type)); \
}

/* conn.c */
extern PyTypeObject DBusPyConnection_Type;
DEFINE_CHECK(DBusPyConnection)
extern PyObject *DBusPyConnection_NewConsumingDBusConnection(PyTypeObject *,
                                                             DBusConnection *,
                                                             PyObject *);
extern dbus_bool_t dbus_py_init_conn_types(void);
extern dbus_bool_t dbus_py_insert_conn_types(PyObject *this_module);

/* bus.c */
extern dbus_bool_t dbus_py_init_bus_types(void);
extern dbus_bool_t dbus_py_insert_bus_types(PyObject *this_module);

/* exceptions.c */
extern PyObject *DBusPyException;
extern PyObject *DBusPyException_ConsumeError(DBusError *error);
extern dbus_bool_t dbus_py_init_exception_types(void);
extern dbus_bool_t dbus_py_insert_exception_types(PyObject *this_module);

/* types */
extern PyTypeObject DBusPyBoolean_Type;
DEFINE_CHECK(DBusPyBoolean)
extern PyTypeObject DBusPyObjectPath_Type, DBusPySignature_Type;
DEFINE_CHECK(DBusPyObjectPath)
DEFINE_CHECK(DBusPySignature)
extern PyTypeObject DBusPyArray_Type, DBusPyDict_Type, DBusPyStruct_Type;
DEFINE_CHECK(DBusPyArray)
DEFINE_CHECK(DBusPyDict)
DEFINE_CHECK(DBusPyStruct)
extern PyTypeObject DBusPyByte_Type, DBusPyByteArray_Type;
DEFINE_CHECK(DBusPyByteArray)
DEFINE_CHECK(DBusPyByte)
extern PyTypeObject DBusPyUTF8String_Type, DBusPyString_Type;
DEFINE_CHECK(DBusPyUTF8String)
DEFINE_CHECK(DBusPyString)
extern PyTypeObject DBusPyDouble_Type;
DEFINE_CHECK(DBusPyDouble)
extern PyTypeObject DBusPyInt16_Type, DBusPyUInt16_Type;
DEFINE_CHECK(DBusPyInt16)
DEFINE_CHECK(DBusPyUInt16)
extern PyTypeObject DBusPyInt32_Type, DBusPyUInt32_Type;
DEFINE_CHECK(DBusPyInt32)
DEFINE_CHECK(DBusPyUInt32)
extern PyTypeObject DBusPyInt64_Type, DBusPyUInt64_Type;
DEFINE_CHECK(DBusPyInt64)
DEFINE_CHECK(DBusPyUInt64)
extern dbus_bool_t dbus_py_init_abstract(void);
extern dbus_bool_t dbus_py_init_signature(void);
extern dbus_bool_t dbus_py_init_int_types(void);
extern dbus_bool_t dbus_py_init_string_types(void);
extern dbus_bool_t dbus_py_init_float_types(void);
extern dbus_bool_t dbus_py_init_container_types(void);
extern dbus_bool_t dbus_py_init_byte_types(void);
extern dbus_bool_t dbus_py_insert_abstract_types(PyObject *this_module);
extern dbus_bool_t dbus_py_insert_signature(PyObject *this_module);
extern dbus_bool_t dbus_py_insert_int_types(PyObject *this_module);
extern dbus_bool_t dbus_py_insert_string_types(PyObject *this_module);
extern dbus_bool_t dbus_py_insert_float_types(PyObject *this_module);
extern dbus_bool_t dbus_py_insert_container_types(PyObject *this_module);
extern dbus_bool_t dbus_py_insert_byte_types(PyObject *this_module);

/* generic */
extern void dbus_py_take_gil_and_xdecref(PyObject *);
extern int dbus_py_immutable_setattro(PyObject *, PyObject *, PyObject *);
extern PyObject *dbus_py_tp_richcompare_by_pointer(PyObject *,
                                                   PyObject *,
                                                   int);
extern long dbus_py_tp_hash_by_pointer(PyObject *self);
extern PyObject *dbus_py_empty_tuple;
extern dbus_bool_t dbus_py_init_generic(void);

/* message.c */
extern DBusMessage *DBusPyMessage_BorrowDBusMessage(PyObject *msg);
extern PyObject *DBusPyMessage_ConsumeDBusMessage(DBusMessage *);
extern dbus_bool_t dbus_py_init_message_types(void);
extern dbus_bool_t dbus_py_insert_message_types(PyObject *this_module);

/* pending-call.c */
extern PyObject *DBusPyPendingCall_ConsumeDBusPendingCall(DBusPendingCall *,
                                                          PyObject *);
extern dbus_bool_t dbus_py_init_pending_call(void);
extern dbus_bool_t dbus_py_insert_pending_call(PyObject *this_module);

/* mainloop.c */
extern dbus_bool_t dbus_py_set_up_connection(PyObject *conn,
                                             PyObject *mainloop);
extern PyObject *dbus_py_get_default_main_loop(void);
extern dbus_bool_t dbus_py_check_mainloop_sanity(PyObject *);
extern dbus_bool_t dbus_py_init_mainloop(void);
extern dbus_bool_t dbus_py_insert_mainloop_types(PyObject *);

/* validation.c */
dbus_bool_t dbus_py_validate_bus_name(const char *name,
                                      dbus_bool_t may_be_unique,
                                      dbus_bool_t may_be_not_unique);
dbus_bool_t dbus_py_validate_member_name(const char *name);
dbus_bool_t dbus_py_validate_interface_name(const char *name);
dbus_bool_t dbus_py_validate_object_path(const char *path);
#define dbus_py_validate_error_name dbus_py_validate_interface_name

/* debugging support */
void _dbus_py_assertion_failed(const char *);
#define DBUS_PY_RAISE_VIA_NULL_IF_FAIL(assertion) \
    do { if (!(assertion)) { \
            _dbus_py_assertion_failed(#assertion); \
            return NULL; \
        } \
    } while (0)

#define DBUS_PY_RAISE_VIA_GOTO_IF_FAIL(assertion, label) \
    do { if (!(assertion)) { \
            _dbus_py_assertion_failed(#assertion); \
            goto label; \
        } \
    } while (0)

#define DBUS_PY_RAISE_VIA_RETURN_IF_FAIL(assertion, value) \
    do { if (!(assertion)) { \
            _dbus_py_assertion_failed(#assertion); \
            return value; \
        } \
    } while (0)

/* verbose debugging support */
#ifdef USING_DBG

#   include <sys/types.h>
#   include <unistd.h>

void _dbus_py_dbg_exc(void);
void _dbus_py_whereami(void);
void _dbus_py_dbg_dump_message(DBusMessage *);

#   define DBG(format, ...) fprintf(stderr, "DEBUG: " format "\n",\
                                    __VA_ARGS__)
#   define DBG_EXC(format, ...) do {DBG(format, __VA_ARGS__); \
                                    _dbus_py_dbg_exc();} while (0)
#   define DBG_DUMP_MESSAGE(x) _dbus_py_dbg_dump_message(x)
#   define DBG_WHEREAMI _dbus_py_whereami()

#else /* !defined(USING_DBG) */

#   define DBG(format, ...) do {} while (0)
#   define DBG_EXC(format, ...) do {} while (0)
#   define DBG_DUMP_MESSAGE(x) do {} while (0)
#   define DBG_WHEREAMI do {} while (0)

#endif /* !defined(USING_DBG) */

/* General-purpose Python glue */

#define DEFERRED_ADDRESS(ADDR) 0

#if defined(__GNUC__)
#   if __GNUC__ >= 3
#       define UNUSED __attribute__((__unused__))
#   else
#       define UNUSED /*nothing*/
#   endif
#else
#   define UNUSED /*nothing*/
#endif

#endif