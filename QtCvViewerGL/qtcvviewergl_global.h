#ifndef QTCVVIEWERGL_GLOBAL_H
#define QTCVVIEWERGL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTCVVIEWERGL_LIBRARY)
#  define QTCVVIEWERGLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTCVVIEWERGLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTCVVIEWERGL_GLOBAL_H
