/**
 * @file btree_main_blackboard.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Blackboard interface.
 * @version 1.0
 * @date 18/05/2025
 *
 *
 */

#include "string.h"
#include "btree_main_blackboard.h"

/**
 * @brief Tree structure with relevant blackboard data main.
 * 
 */
struct btree_main_blackboard {
    
} btree_main_data = {
    
};

btree_definition_status_t btree_main_blackboard_set_value(btree_main_blackboard_value_id_t id, void *value)
{
    if(value == NULL)
    {
        return BTREE_DEFINITION_STATUS_FAIL;
    }

    switch(id)
    {
        default: {

            break;
        }
    }
    
    return BTREE_DEFINITION_STATUS_SUCCESS;
}

btree_definition_status_t btree_main_blackboard_get_value(btree_main_blackboard_value_id_t id, void *target)
{
    if(target == NULL)
    {
        return BTREE_DEFINITION_STATUS_FAIL;
    }

    switch(id)
    {
        default: {

            break;
        }
    }
    
    return BTREE_DEFINITION_STATUS_SUCCESS;
}

btree_definition_status_t btree_main_blackboard_set_buffer(btree_main_blackboard_buffer_id_t id, uint8_t *buffer, size_t buffer_size)
{
    size_t buffer_len = buffer_size;

    if((buffer == NULL) || (buffer_size == 0))
    {
        return BTREE_DEFINITION_STATUS_FAIL;
    }

    switch(id)
    {
        default: {

            break;
        }
    }
    
    return BTREE_DEFINITION_STATUS_SUCCESS;
}

btree_definition_status_t btree_main_blackboard_get_buffer(btree_main_blackboard_buffer_id_t id, uint8_t *buffer, size_t *buffer_len)
{
    if((buffer == NULL) || (buffer_len == NULL))
    {
        return BTREE_DEFINITION_STATUS_FAIL;
    }

    switch(id)
    {
        default: {

            break;
        }
    }
    
    return BTREE_DEFINITION_STATUS_SUCCESS;
}

void btree_main_reset_blackboard(void)
{
     memset(&btree_main_data, 0, sizeof(btree_main_data));
}
