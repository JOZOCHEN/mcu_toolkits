/**
 * @file common_types.h
 * @author jozochen (jozocyz@hotmail.com)
 * @brief 
 * @date 2019-11-30
 * @copyright Apache License 2.0
 *            jozochen (jozocyz@hotmail.com) Copyright (c) 2019
 */
#ifndef __COMMON_TYPES_H
#define __COMMON_TYPES_H

#ifndef TRUE
    #define TRUE (1u)
#endif

#ifndef FALSE
    #define FALSE (0u)
#endif

#ifndef STD_ON
    #define STD_ON (1u)
#endif

#ifndef STD_OFF
    #define STD_OFF (0u)
#endif  

#ifndef uint8
    typedef unsigned char uint8;
#endif

#ifndef uint16
    typedef unsigned short uint16;
#endif

#ifndef uint32
    typedef unsigned int uint32;
#endif

#ifndef int32
    typedef int int32;
#endif

#ifndef NULL
    #define NULL ((void*)0)
#endif

#endif
