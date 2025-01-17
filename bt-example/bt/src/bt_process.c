/**
 * @file bt_process.c
 * @author Renilson Almeida (renilson.123@hotmail.com)
 * @brief Behavior tree process.
 * @version 1.0
 * @date 26/06/24
 * 
 * @copyright Copyright (c) 2024 Renilson Almeida
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "bt_process.h"

bt_definition_status_t bt_process_node(bt_definition_tree_data_t *struct_tree)
{
    bt_index_t index = struct_tree->node_index;
    bt_definition_status_t status = 0;
    const bt_definition_node_t *node_struct = &(struct_tree->tree[index]);
    bt_definition_node_type_t node_type = node_struct->node_type;

    if(struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    switch(node_type)
    {
        case BT_DEFINITION_NODE_ACTION:
        case BT_DEFINITION_NODE_CONDITION:
        {
            if(struct_tree->last_node_state != BT_DEFINITION_STATUS_RUNNING)
            {
                struct_tree->node_index = 0;
                return BT_DEFINITION_STATUS_ERROR;
            }

            status = node_struct->interaction_node.function();
            break;
        }

        case BT_DEFINITION_NODE_ACTION_TIMEOUT:
        {

            break;
        }

        default:
        {
            return BT_DEFINITION_STATUS_ERROR;
        }
    }

    if(status == BT_DEFINITION_STATUS_SUCCESS)
    {
        struct_tree->node_index = node_struct->st_index;
    }
    else if(status == BT_DEFINITION_STATUS_FAIL)
    {
        struct_tree->node_index = node_struct->ft_index;
    }

    return BT_DEFINITION_STATUS_RUNNING;
}

bt_definition_status_t bt_process_node_with_memory(bt_definition_tree_data_t *struct_tree,
                                                   bt_index_t index_status_key,
                                                   uint32_t index_status_position,
                                                   uint32_t value_status)
{
    bt_index_t index = struct_tree->node_index;
    bt_definition_status_t status = 0;
    const bt_definition_node_t *node_struct = &(struct_tree->tree[index]);
    bt_definition_node_type_t node_type = node_struct->node_type;

    if(struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    switch(node_type)
    {
        case BT_DEFINITION_NODE_REACTIVE_ACTION:
        case BT_DEFINITION_NODE_REACTIVE_CONDITION:
        {
            if(struct_tree->last_node_state != BT_DEFINITION_STATUS_RUNNING)
            {
                struct_tree->node_index = 0;
                return BT_DEFINITION_STATUS_ERROR;
            }

            status = node_struct->interaction_node.function();
            break;
        }

        case BT_DEFINITION_NODE_ACTION:
        case BT_DEFINITION_NODE_CONDITION:
        {
            if(struct_tree->last_node_state != BT_DEFINITION_STATUS_RUNNING)
            {
                struct_tree->node_index = 0;
                return BT_DEFINITION_STATUS_ERROR;
            }

            status = node_struct->interaction_node.function();
            break;
        }

        case BT_DEFINITION_NODE_ACTION_TIMEOUT:
        {

            break;
        }

        default:
        {
            return BT_DEFINITION_STATUS_ERROR;
        }
    }

    if(status == BT_DEFINITION_STATUS_SUCCESS)
    {
        struct_tree->node_index = node_struct->st_index;
        SEGGER_RTT_printf(0, "%d, ", struct_tree->node_index);
        uint32_t x = (value_status) | (0b1 << (index_status_key));
        struct_tree->nodes_status[index_status_position] = x;
        SEGGER_RTT_printf(0, "Success ");
    }
    else if(status == BT_DEFINITION_STATUS_FAIL)
    {
        struct_tree->node_index = node_struct->ft_index;
        SEGGER_RTT_printf(0, "%d, ", struct_tree->node_index);
        uint32_t x = (value_status) | (0b0 << (index_status_key));
        struct_tree->nodes_status[index_status_position] = x;
        SEGGER_RTT_printf(0, "Fail ");
    }

    return status;
}
