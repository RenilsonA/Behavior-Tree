/**
 * @file bt_manager.c
 * @author Renilson Almeida (renilson.123@hotmail.com)
 * @brief Behavior tree manager.
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

#include <bt_manager.h>

static struct
{
    uint8_t bt_index;             /**< Stores the index of the next node to be executed in the tree. */
    bt_definition_t *tree;        /**< General tree pointer. */
} self = {
    .bt_index = 0,
    .tree = NULL,
};

/**
 * @brief Exit the current subtree and enter in a parent tree.
 *
 */
static void bt_manager_leave_subtree();

static void bt_manager_leave_subtree()
{
    uint8_t index = self.tree[self.bt_index].root_node.parent_tree_index;

    self.tree = self.tree[self.bt_index].root_node.tree_index;
    self.bt_index = index;
}

bt_definition_status_t bt_manager_tick_tree()
{
    bt_definition_status_t tree_status;

    tree_status = bt_process_node(self.tree, &self.bt_index);

    if(tree_status == BT_DEFINITION_STATUS_SUCCESS)
    {
        
    }
    else if(tree_status == BT_DEFINITION_STATUS_FAIL)
    {
        
    }
    else if(tree_status == BT_DEFINITION_STATUS_ERROR)
    {
        
    }
    else if(tree_status == BT_DEFINITION_STATUS_LEAVE_TREE)
    {
        bt_manager_leave_subtree();
    }

    return tree_status;
}

int bt_manager_init()
{
    /**
     * Init here first tree on self.tree
     * 
     */

    return 0;
}
