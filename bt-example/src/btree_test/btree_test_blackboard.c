/**
 * @file btree_test_blackboard.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Blackboard interface.
 * @version 1.0
 * @date 27/04/2025
 *
 *
 */

#include "string.h"
#include "btree_test_blackboard.h"

/**
 * @brief Tree structure with relevant blackboard data test.
 * 
 */
struct btree_test_blackboard {

} btree_test_data = {

};

btree_definition_status_t btree_test_set_blackboard_value(btree_test_blackboard_value_id_t id, void *value)
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

btree_definition_status_t btree_test_get_blackboard_value(btree_test_blackboard_value_id_t id, void *target)
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

btree_definition_status_t btree_test_set_blackboard_buffer(btree_test_blackboard_buffer_id_t id, uint8_t *buffer, size_t buffer_size)
{
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

btree_definition_status_t btree_test_get_blackboard_buffer(btree_test_blackboard_buffer_id_t id, uint8_t *buffer, size_t *buffer_len)
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

void btree_test_reset_blackboard(void)
{
     memset(&btree_test_data, 0, sizeof(btree_test_data));
}
