#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(AETHER_QTEST_PARSER_LIB)
#  define AETHER_QTEST_PARSER_EXPORT Q_DECL_EXPORT
# else
#  define AETHER_QTEST_PARSER_EXPORT Q_DECL_IMPORT
# endif
#else
# define AETHER_QTEST_PARSER_EXPORT
#endif
