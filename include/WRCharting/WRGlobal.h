#pragma once
#ifndef WRCHARTING_GLOBAL
#define WRCHARTING_GLOBAL

#include <qglobal.h>

#if defined(WRCHARTING_LIBRARY)
#   define WRCHARTING_API     Q_DECL_EXPORT
#   define WRCHARTING_CLASS   Q_DECL_EXPORT
#elif defined(WRCHARTING_PROGRAM)
#   define WRCHARTING_API
#   define WRCHARTING_CLASS
#elif defined(WRCHARTING_STATICLIB)
#   define WRCHARTING_API
#   define WRCHARTING_CLASS
#else
#   define WRCHARTING_API     Q_DECL_IMPORT
#   define WRCHARTING_CLASS   Q_DECL_IMPORT
#endif

#endif //WRCHARTING_GLOBAL
