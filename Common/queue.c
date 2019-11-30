/**
 * @file queue.c
 * @author jozochen (jozocyz@hotmail.com)
 * @brief 
 * @date 2019-11-30
 * @copyright Apache License 2.0
 *            jozochen (jozocyz@hotmail.com) Copyright (c) 2019
 */
#include "queue.h"

static unsigned char Queue_IsFull(Queue_HandleType* handle);
static unsigned char Queue_IsEmpty(Queue_HandleType* handle);

int Queue_Creat(Queue_HandleType* handle, unsigned char* buf, 
                        unsigned short element_size, unsigned short element_num)
{
    int ret = E_QUEUE_FAIL;

    if( (handle != NULL) && (buf != NULL) && (element_size != 0u) && (element_num != 0u))
    {
        handle->pbuf = buf;
        handle->element_size = element_size;
        handle->element_ind_max = (element_num - 1) * element_size;
        handle->head_ind = 0u;
        handle->tail_ind = 0u;
        handle->empty_flg = TRUE;
        handle->full_flg = FALSE;

        ret = E_QUEUE_OK;
    }
    else
    {
        /*nothing*/
    }

    return ret;
}

static unsigned char Queue_IsFull(Queue_HandleType* handle)
{
    return handle->full_flg;
}

static unsigned char Queue_IsEmpty(Queue_HandleType* handle)
{
    return handle->empty_flg;   
}

int Queue_Push(Queue_HandleType* handle, unsigned char* data)
{
    int ret = E_QUEUE_FAIL;
    unsigned long i = 0u;

    if( (handle != NULL) && (data != NULL) )
    {
        if(Queue_IsFull(handle) == TRUE)
        {
            ret = E_QUEUE_FAIL;
        }
        else
        {
            for(i = 0u; i < handle->element_size; i++)
            {
                handle->pbuf[handle->head_ind + i] = data[i];
            }
            handle->empty_flg = FALSE;

            handle->head_ind += handle->element_size;
            if(handle->head_ind > handle->element_ind_max)
            {
                handle->head_ind = 0u;
            }
            else
            {
                /*nothing*/
            }

            if(handle->head_ind == handle->tail_ind)
            {
                handle->full_flg = TRUE;
            }
            else
            {
                /*nothing*/
            }
            ret = E_QUEUE_OK;
        }      
    }
    else
    {
        /*nothing*/
    }

    return ret;
}

int Queue_Pop(Queue_HandleType* handle, unsigned char* data)
{
    int ret = E_QUEUE_FAIL;
    unsigned long i = 0u;

    if( (handle != NULL) && (data != NULL) )
    {
        if(Queue_IsEmpty(handle) == TRUE)
        {
            ret = E_QUEUE_FAIL;
        }
        else
        {
            for(i = 0u; i < handle->element_size; i++)
            {
                data[i] = handle->pbuf[handle->tail_ind + i];
            }
            handle->full_flg = FALSE;

            handle->tail_ind += handle->element_size;
            if(handle->tail_ind > handle->element_ind_max)
            {
                handle->tail_ind = 0u;
            }
            else
            {
                /*nothing*/
            }

            if(handle->head_ind == handle->tail_ind)
            {
                handle->empty_flg = TRUE;
            }
            else
            {
                /*nothing*/
            }
            ret = E_QUEUE_OK;
        }      
    }
    else
    {
        /*nothing*/
    }

    return ret;
}

#if 0
void Queue__test(void)
{
    Queue_HandleType test_queue_handle;
    Queue_HandleType test_buf[5];
    Queue_HandleType test_data;
    unsigned i = 0u;

    queueCreat(&test_queue_handle, (unsigned char *)test_buf, sizeof(Queue_HandleType), 5);

    for(i = 0u; i < 6u; i++)
    {
        test_data.element_ind_max = i;
        queuePush(&test_queue_handle, (unsigned char *)&test_data);
    }

    for(i = 0u; i < 6u; i++)
    {
        queuePop(&test_queue_handle, (unsigned char *)&test_data);
        if(test_data.element_ind_max == i)
        {
            test_data.element_ind_max = i;
        }
    }

    for(i = 0u; i < 6u; i++)
    {
        test_data.element_ind_max = i;
        queuePush(&test_queue_handle, (unsigned char *)&test_data);
        queuePop(&test_queue_handle, (unsigned char *)&test_data);
        if(test_data.element_ind_max == i)
        {
            test_data.element_ind_max = i;
        }
    }
}
#endif
