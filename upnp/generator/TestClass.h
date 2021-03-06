#ifndef TESTCLASS_H
#define TESTCLASS_H

/*!
 * \file
 *
 * \brief Header file for TestClass methods.
 *
 * Do not edit this file, it is automatically generated. Please look at generator.c.
 *
 * \author Marcelo Roberto Jimenez
 */
#include <stdlib.h> /* for size_t */

#include "UpnpGlobal.h" /* for EXPORT_SPEC */

#include "list.h"
#include "TheStruct.h"
#include "UpnpActionComplete.h"
#include "UpnpString.h"
#include "ixml.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * TestClass
 */
typedef struct s_TestClass TestClass;

/*! Constructor */
EXPORT_SPEC TestClass *TestClass_new();
/*! Destructor */
EXPORT_SPEC void TestClass_delete(TestClass *p);
/*! Copy Constructor */
EXPORT_SPEC TestClass *TestClass_dup(const TestClass *p);
/*! Assignment operator */
EXPORT_SPEC int TestClass_assign(TestClass *p, const TestClass *q);

/*! TestClass_get_TheList */
EXPORT_SPEC const UpnpListHead *TestClass_get_TheList(const TestClass *p);
/*! TestClass_set_TheList */
EXPORT_SPEC int TestClass_set_TheList(TestClass *p, const UpnpListHead *q);
/*! TestClass_add_to_list_TheList */
EXPORT_SPEC void TestClass_add_to_list_TheList(TestClass *p, UpnpListHead *head);

/*! TestClass_get_TheInteger */
EXPORT_SPEC int TestClass_get_TheInteger(const TestClass *p);
/*! TestClass_set_TheInteger */
EXPORT_SPEC int TestClass_set_TheInteger(TestClass *p, int n);

/*! TestClass_get_TheUnsignedLong */
EXPORT_SPEC unsigned long TestClass_get_TheUnsignedLong(const TestClass *p);
/*! TestClass_set_TheUnsignedLong */
EXPORT_SPEC int TestClass_set_TheUnsignedLong(TestClass *p, unsigned long n);

/*! TestClass_get_TheCharPointer */
EXPORT_SPEC char * TestClass_get_TheCharPointer(const TestClass *p);
/*! TestClass_set_TheCharPointer */
EXPORT_SPEC int TestClass_set_TheCharPointer(TestClass *p, char * n);

/*! TestClass_get_TheBuffer */
EXPORT_SPEC const struct TheStruct *TestClass_get_TheBuffer(const TestClass *p);
/*! TestClass_get_TheBuffer */
EXPORT_SPEC int TestClass_set_TheBuffer(TestClass *p, const struct TheStruct *buf); 
/*! TestClass_get_TheBuffer */
EXPORT_SPEC void TestClass_clear_TheBuffer(TestClass *p); 

/*! TestClass_get_TheActionComplete */
EXPORT_SPEC const UpnpActionComplete *TestClass_get_TheActionComplete(const TestClass *p);
/*! TestClass_set_TheActionComplete */
EXPORT_SPEC int TestClass_set_TheActionComplete(TestClass *p, const UpnpActionComplete *n);

/*! TestClass_get_TheString */
EXPORT_SPEC const UpnpString *TestClass_get_TheString(const TestClass *p);
/*! TestClass_set_TheString */
EXPORT_SPEC int TestClass_set_TheString(TestClass *p, const UpnpString *s);
/*! TestClass_get_TheString_Length */
EXPORT_SPEC size_t TestClass_get_TheString_Length(const TestClass *p);
/*! TestClass_get_TheString_cstr */
EXPORT_SPEC const char *TestClass_get_TheString_cstr(const TestClass *p);
/*! TestClass_strcpy_TheString */
EXPORT_SPEC int TestClass_strcpy_TheString(TestClass *p, const char *s);
/*! TestClass_strncpy_TheString */
EXPORT_SPEC int TestClass_strncpy_TheString(TestClass *p, const char *s, size_t n); 
/*! TestClass_clear_TheString */
EXPORT_SPEC void TestClass_clear_TheString(TestClass *p); 

/*! TestClass_get_TheDomString */
EXPORT_SPEC const DOMString TestClass_get_TheDomString(const TestClass *p); 
/*! TestClass_set_TheDomString */
EXPORT_SPEC int TestClass_set_TheDomString(TestClass *p, const DOMString s); 
/*! TestClass_get_TheDomString_cstr */
EXPORT_SPEC const char *TestClass_get_TheDomString_cstr(const TestClass *p); 

#endif /* TESTCLASS_H */

