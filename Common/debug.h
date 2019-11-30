/**
 * @file debug.h
 * @author jozochen (jozocyz@hotmail.com)
 * @brief 
 * @date 2019-11-30
 * @copyright Apache License 2.0
 *            jozochen (jozocyz@hotmail.com) Copyright (c) 2019
 */
#ifndef __DEBUG_H
#define __DEBUG_H
#include "stdio.h"

#define DBG_ERR(args,...) do{\
                            printf("[ERR][%s][%s]",__FILE__,__func__);\
                            printf(args, ##__VA_ARGS__);\
                            }while(0)

#define DBG_MSG(args,...) do{\
                            printf("[MSG][%s][%s]",__FILE__,__func__);\
                            printf(args, ##__VA_ARGS__);\
                            }while(0)
#endif
