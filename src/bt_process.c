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

/**
 * @brief Performs a node check, whose parent may be a fallback.
 *
 * @param tree Tree to be checked.
 * @param bt_index Tree index.
 * @param status Status of the node.
 * @return int 0 if the check is not false, 1 if the check is true.
 */
static int bt_process_check_parent_fallback(bt_definition_t *tree, uint8_t bt_index, bt_definition_status_t status);

/**
 * @brief Performs a node check, whose parent can be a sequence.
 *
 * @param tree Tree to be checked.
 * @param bt_index Tree index.
 * @param status Status of the node.
 * @return int 0 if the check is not false, 1 if the check is true.
 */
static int bt_process_check_parent_sequence(bt_definition_t *tree, uint8_t bt_index, bt_definition_status_t status);

/**
 * @brief Checks whether the node has a sibling.
 *
 * @param tree Tree to be checked.
 * @param bt_index Tree index.
 * @param status Status of the node.
 * @return int 0 if the check is not false, 1 if the check is true.
 */
static int bt_process_check_sibling(bt_definition_t *tree, uint8_t bt_index);

static int bt_process_check_parent_fallback(bt_definition_t *tree, uint8_t bt_index, bt_definition_status_t status)
{
    return (status == BT_DEFINITION_STATUS_SUCCESS) && (tree[tree[bt_index].node.parent_index].node_type == BT_DEFINITION_NODE_FALLBACK);
}

static int bt_process_check_parent_sequence(bt_definition_t *tree, uint8_t bt_index, bt_definition_status_t status)
{
    return (status == BT_DEFINITION_STATUS_FAIL) && (tree[tree[bt_index].node.parent_index].node_type == BT_DEFINITION_NODE_SEQUENCE);
}

static int bt_process_check_sibling(bt_definition_t *tree, uint8_t bt_index)
{
    return tree[bt_index].node.sibling_index == BT_DEFINITION_TREE_UNRELATED;
}

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

        case BT_DEFINITION_NODE_SEQUENCE:
        case BT_DEFINITION_NODE_FALLBACK:
        {
            if(self.last_node_state == BT_DEFINITION_STATUS_RUNNING)
            {
                if(tree[*bt_index].node.composite_node.children_index == BT_DEFINITION_TREE_UNRELATED)
                {
                    *bt_index = 0;
                    return BT_DEFINITION_STATUS_ERROR;
                }

                *bt_index = tree[*bt_index].node.composite_node.children_index;

                return BT_DEFINITION_STATUS_RUNNING;
            }

            status = self.last_node_state;

            break;
        }

        case BT_DEFINITION_NODE_ACTION:
        case BT_DEFINITION_NODE_CONDITION:
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


        case BT_DEFINITION_NODE_SUBTREE:
        {
            if(self.last_node_state == BT_DEFINITION_STATUS_RUNNING)
            {
                return BT_DEFINITION_STATUS_ENTER_TREE;
            }

            status = self.last_node_state;

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
