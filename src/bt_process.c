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

bt_definition_status_t bt_process_node(bt_definition_t *tree, uint8_t *bt_index)
{
    bt_definition_status_t status = 0;

    switch(tree[*bt_index].node_type)
    {
        case BT_DEFINITION_NODE_ROOT:
        {
            if(tree[*bt_index].root_node.tree_index == BT_DEFINITION_TREE_UNRELATED && 
              (self.last_node_state == BT_DEFINITION_STATUS_SUCCESS || 
               self.last_node_state == BT_DEFINITION_STATUS_FAIL))
            {
                *bt_index = 0;
                return self.last_node_state;
            }

            if(self.last_node_state == BT_DEFINITION_STATUS_SUCCESS || 
               self.last_node_state == BT_DEFINITION_STATUS_FAIL)
            {
                return BT_DEFINITION_STATUS_LEAVE_TREE;
            }

            *bt_index = tree[*bt_index].root_node.children_index;

            return BT_DEFINITION_STATUS_RUNNING;
        }

        default:
        {
            *bt_index = 0;
            return BT_DEFINITION_STATUS_ERROR;
        }
    }

    return BT_DEFINITION_STATUS_RUNNING;
}
