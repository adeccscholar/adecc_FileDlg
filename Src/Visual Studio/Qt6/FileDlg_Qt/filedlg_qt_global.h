#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FILEDLG_QT_LIB)
#  define FILEDLG_QT_EXPORT Q_DECL_EXPORT
# else
#  define FILEDLG_QT_EXPORT Q_DECL_IMPORT
# endif
#else
# define FILEDLG_QT_EXPORT
#endif
