#ifndef COMMON_H__
#define COMMON_H__


#include "logprint.h"
#include "alloc.h"

typedef void          VOID;
typedef int           BOOL;
typedef int           INT32;
typedef unsigned int  UINT32;
typedef float         FLOAT32;
typedef double        FLOAT64;
typedef int           int32_t;
typedef unsigned int  uint32_t;
typedef float         float32_t;
typedef double        float64_t;
typedef char          int8_t;
typedef unsigned char uint8_t;

#ifndef _BOOLEAN_DEFINED
typedef  unsigned char      boolean;     /* Boolean value type. */
#define _BOOLEAN_DEFINED
#endif

#ifndef TRUE
#define TRUE  (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef NULL
#define NULL (0)
#endif


/* ERROR CODE */
#define RET_NORMAL           (0)   /* Normal end */
#define RET_ERR_VARIOUS      (-1)  /* Undefined error */
#define RET_ERR_INITIALIZE   (-2)  /* Initialization error */
#define RET_ERR_INVALIDPARAM (-3)  /* Parameter error */
#define RET_ERR_ALLOCMEMORY  (-4)  /* Memory allocation error */

#ifndef MAX
#define	MAX(a, b) (((a) > (b)) ? (a) : (b))	/* Maximum value */
#endif

#ifndef MIN
#define	MIN(a, b) (((a) < (b)) ? (a) : (b))	/* Minimum value */
#endif

#ifndef CLAMP
#define	CLAMP(_min,x,_max)   MIN( MAX((_min),(x)), (_max) )
#endif


//使用pthread.h需要此宏定义
#define HAVE_STRUCT_TIMESPEC

#define NO_ERR  0
#define ERROR     1
#define NO_MEMORY 2
#define ERR_QUEUE_FULL 3

#endif
