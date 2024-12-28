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

bt_definition_status_t bt_process_node(bt_definition_tree_data_t *data_tree)
{
    bt_index_t index = data_tree->node_index;
    bt_definition_status_t status = 0;
    const bt_definition_node_t *node_struct = &(data_tree->tree[index]);
    bt_definition_node_type_t node_type = node_struct->node_type;

    switch(node_type)
    {
        case BT_DEFINITION_NODE_CONDITION:
        case BT_DEFINITION_NODE_ACTION:
        {
            if(data_tree->last_node_state != BT_DEFINITION_STATUS_RUNNING)
            {
                data_tree->node_index = 0;
                return BT_DEFINITION_STATUS_ERROR;
            }

            status = node_struct->interation_node.interation.function();
            if(node_type == BT_DEFINITION_NODE_CONDITION)
            {
                data_tree->condition_index = node_struct->interation_node.condition.st_condition_index;
            }
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
        data_tree->node_index = node_struct->st_index;
    }
    else if(status == BT_DEFINITION_STATUS_FAIL)
    {
        data_tree->node_index = node_struct->ft_index;
    }

    return BT_DEFINITION_STATUS_RUNNING;
}
