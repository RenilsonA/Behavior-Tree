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

#include <bt_process.h>

/**
 * @brief Standard data structure for behavior tree processing.
 *
 */
static struct
{
    bt_definition_status_t last_node_state;    /**< Stores the state of the last node. */
} self = {
    .last_node_state = BT_DEFINITION_STATUS_RUNNING,
};

bt_definition_status_t bt_process_node(bt_definition_tree_data_t *data_tree)
{
    bt_definition_status_t status = 0;
    bt_definition_node_type_t node_type = data_tree.node_type;

    switch(node_type)
    {
        case BT_DEFINITION_NODE_CONDITION:
        case BT_DEFINITION_NODE_ACTION:
        {
            if(self.last_node_state != BT_DEFINITION_STATUS_RUNNING)
            {
                *bt_index = 0;
                return BT_DEFINITION_STATUS_ERROR;
            }

            status = tree[*bt_index].node.interation_node.interation();
            if(status == BT_DEFINITION_STATUS_RUNNING)
            {
                return BT_DEFINITION_STATUS_RUNNING;
            }
            else if(status == BT_DEFINITION_STATUS_SUCCESS)
            {
                *bt_index = tree[*bt_index].interation_node.st_index;
            }
            else if(status == BT_DEFINITION_STATUS_FAIL)
            {
                *bt_index = tree[*bt_index].interation_node.ft_index;
            }
            if(node_type == BT_DEFINITION_NODE_CONDITION)
            {

            }


            break;
        }

        case BT_DEFINITION_NODE_ACTION_TIMEOUT:
        {
            if(tree[*bt_index].node.interation_node.timeout_ms == 0)
            {
                *bt_index = 0;
                return BT_DEFINITION_STATUS_ERROR;
            }

            status = bt_common_action_timeout(tree[*bt_index].node.interation_node.timeout_ms);

            break;
        }

        default:
        {
            *bt_index = 0;
            return BT_DEFINITION_STATUS_ERROR;
        }
    }

    if((bt_process_check_parent_fallback(tree, *bt_index, status)) ||
       (bt_process_check_parent_sequence(tree, *bt_index, status)) ||
       (bt_process_check_sibling(tree, *bt_index)))
    {
        self.last_node_state = status;
        *bt_index = tree[*bt_index].node.parent_index;
    }
    else
    {
        self.last_node_state = BT_DEFINITION_STATUS_RUNNING;
        *bt_index = tree[*bt_index].node.sibling_index;
    }

    return BT_DEFINITION_STATUS_RUNNING;
}
