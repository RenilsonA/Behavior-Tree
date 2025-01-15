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
#include "test_bt_common.h"
#include "SEGGER_RTT.h"

bt_definition_status_t bt_manager_tick_tree(bt_definition_tree_data_t *struct_tree)
{
    if(struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    return bt_process_node(struct_tree);
}

bt_definition_status_t bt_manager_reactivity_tick_tree(bt_definition_tree_data_t *struct_tree)
{
    bt_definition_status_t tree_status = BT_DEFINITION_STATUS_SUCCESS;
    bt_index_t node_index = struct_tree->node_index;
    bt_index_t index_status_key = node_index % 32;
    uint32_t index_status_position = node_index / 32;
    uint32_t value_status = struct_tree->nodes_status[index_status_position];
    uint32_t mask = (0b1 << (value_status));
    bool check_node = (value_status & mask) >> index_status_key;
    uint32_t valor = (value_status & (~mask));

    if(struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    struct_tree->node_index = 0;

    while(struct_tree->node_index < node_index)
    {
        if((!check_node))
        {
            tree_status = bt_process_node_with_memory(struct_tree, index_status_key, index_status_position, valor);
            if(tree_status != BT_DEFINITION_STATUS_RUNNING)
            {
                return tree_status;
            }
            SEGGER_RTT_printf(0, "\n");
        }

        index_status_key = struct_tree->node_index % 32;
        index_status_position = struct_tree->node_index / 32;
        value_status = struct_tree->nodes_status[index_status_position];
        mask = (0b1 << (index_status_key));
        check_node = (value_status & mask) >> index_status_key;
        valor = (value_status & (~mask));

        if((check_node) && (struct_tree->node_index < node_index))
        {
            struct_tree->node_index = struct_tree->tree[struct_tree->node_index].st_index;
        }
        else if((struct_tree->tree[struct_tree->node_index].node_type == BT_DEFINITION_NODE_ACTION) &&
                (struct_tree->tree[struct_tree->node_index].ft_index == (struct_tree->node_index + 1) &&
                (struct_tree->node_index < node_index)))
        {
            struct_tree->node_index = struct_tree->tree[struct_tree->node_index].ft_index;
        }

        sl_sleeptimer_delay_millisecond(50);
    }

    index_status_key = struct_tree->node_index % 32;
    index_status_position = struct_tree->node_index / 32;
    value_status = struct_tree->nodes_status[index_status_position];
    mask = (0b1 << (index_status_key));
    check_node = (value_status & mask) >> index_status_key;
    valor = (value_status & (~mask));

    tree_status = bt_process_node_with_memory(struct_tree, index_status_key, index_status_position, valor);

    SEGGER_RTT_printf(0, "\n");

    return tree_status;
}

bt_definition_status_t bt_manager_tick_reactive_tree(bt_definition_tree_data_t *struct_tree)
{
    bool check_node = 0;
    bt_definition_status_t tree_status = BT_DEFINITION_STATUS_SUCCESS;
    bt_definition_node_type_t node_type = BT_DEFINITION_NODE_CONDITION;
    bt_index_t node_index = struct_tree->node_index;
    bt_index_t index_status_key = 0;
    uint32_t index_status_position = 0;
    uint32_t mask = 0;
    uint32_t valor = 0;
    uint32_t value_status = struct_tree->nodes_status[BT_DEFINITON_NODE_FIRST_INDEX];

    if(struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    struct_tree->node_index = 0;

    while(struct_tree->node_index < node_index)
    {
        node_type = struct_tree->tree[struct_tree->node_index].node_type;

        index_status_key = struct_tree->node_index % 32;
        index_status_position = struct_tree->node_index / 32;
        value_status = struct_tree->nodes_status[index_status_position];
        mask = (0b1 << (index_status_key));
        check_node = (value_status & mask) >> index_status_key;
        valor = (value_status & (~mask));

        if((node_type == BT_DEFINITION_NODE_REACTIVE_CONDITION) ||
           (node_type == BT_DEFINITION_NODE_REACTIVE_ACTION))
        {
            tree_status = bt_process_node_with_memory(struct_tree, index_status_key, index_status_position, valor);
            if(tree_status == BT_DEFINITION_STATUS_RUNNING)
            {
                return tree_status;
            }
            SEGGER_RTT_printf(0, "\n");
        }

        index_status_key = struct_tree->node_index % 32;
        index_status_position = struct_tree->node_index / 32;
        value_status = struct_tree->nodes_status[index_status_position];
        mask = (0b1 << (index_status_key));
        check_node = (value_status & mask) >> index_status_key;
        valor = (value_status & (~mask));

        if((check_node) && (struct_tree->node_index < node_index))
        {
            struct_tree->node_index = struct_tree->tree[struct_tree->node_index].st_index;
        }
        else if((struct_tree->node_index < node_index))
        {
            struct_tree->node_index = struct_tree->tree[struct_tree->node_index].ft_index;
        }

        sl_sleeptimer_delay_millisecond(50);

    }

    index_status_key = struct_tree->node_index % 32;
    index_status_position = struct_tree->node_index / 32;
    value_status = struct_tree->nodes_status[index_status_position];
    mask = (0b1 << (index_status_key));
    check_node = (value_status & mask) >> index_status_key;
    valor = (value_status & (~mask));

    tree_status = bt_process_node_with_memory(struct_tree, index_status_key, index_status_position, valor);

    SEGGER_RTT_printf(0, "\n");

    return tree_status;
}

bt_definition_status_t bt_manager_reset_tree(bt_definition_tree_data_t *struct_tree)
{
    if(struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    struct_tree->last_node_state = BT_DEFINITION_STATUS_RUNNING;
    struct_tree->node_index = BT_DEFINITON_NODE_FIRST_INDEX;

    return BT_DEFINITION_STATUS_SUCCESS;
}
