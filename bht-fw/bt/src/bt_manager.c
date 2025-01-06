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

#include "bt_manager.h"

bt_definition_status_t bt_manager_tick_tree(bt_definition_tree_data_t *struct_tree)
{
    if (struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    return bt_process_node(struct_tree);
}

bt_definition_status_t bt_manager_reactivity_tick_tree(bt_definition_tree_data_t *struct_tree)
{
    bt_definition_status_t tree_status = BT_DEFINITION_STATUS_SUCCESS;
    bt_index_t node_index = struct_tree->node_index;

    if (struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    struct_tree->node_index = BT_DEFINITON_NODE_FIRST_INDEX;

    while (struct_tree->node_index < node_index)
    {
        tree_status = bt_manager_tick_tree(struct_tree);
        if (tree_status != BT_DEFINITION_STATUS_RUNNING)
        {
            return tree_status;
        }

        // TODO: Refazer a partir do ponto.
    }

    tree_status = bt_manager_tick_tree(struct_tree);

    return tree_status;
}

bt_definition_status_t bt_manager_reset_tree(bt_definition_tree_data_t *struct_tree)
{
    if (struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    struct_tree->last_node_state = BT_DEFINITION_STATUS_RUNNING;
    struct_tree->node_index = BT_DEFINITON_NODE_FIRST_INDEX;

    return BT_DEFINITION_STATUS_SUCCESS;
}
