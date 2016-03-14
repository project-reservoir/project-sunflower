#ifndef _SUNFLOWER_APP_VERSION_NUM
#define _SUNFLOWER_APP_VERSION_NUM

// App Version format:  0xAABBCCDD
//      AA = OS Major Revision
//      BB = OS Minor Revision
//      CC = HW ID (01 = DEVKIT, 02 = EVT1, 03 = EVT2)
//      DD = Build type (01 = DEBUG, 02 = PRODUCTION)

#define OS_MAJOR        4
#define OS_MINOR        0
#define HW_ID           2
#define BUILD_TYPE      1
#define SUNFLOWER_APP_VERSION       ((OS_MAJOR << 24) | (OS_MINOR << 16) | (HW_ID << 8) | (BUILD_TYPE))

#endif // _SUNFLOWER_APP_VERSION_NUM
