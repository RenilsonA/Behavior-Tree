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

/**
 * @brief Minimum quantity of attempts.
 *
 */
#define BT_PROCESS_MIN_ATTEMPTS 0

#define BT_PROCESS_CHECK_RUNNING(_tree_ptr) \
    do {\
        if((_tree_ptr)->last_node_state != BT_DEFINITION_STATUS_RUNNING)\
        {\
            (_tree_ptr)->node_index = 0;\
            return BT_DEFINITION_STATUS_ERROR;\
        }\
    } while(0)

#define BT_PROCESS_CHECK_TARGET(_tree_ptr, _index) \
    do {                                                                              \
        if ((_tree_ptr)->tree[index].decorator_node.target_index == BT_DEFINITION_TREE_UNRELATED) { \
            (_tree_ptr)->node_index = BT_DEFINITON_NODE_FIRST_INDEX;                   \
            return BT_DEFINITION_STATUS_ERROR;                                        \
        }                                                                             \
    } while (0)

bt_definition_status_t bt_process_node(bt_definition_tree_data_t *struct_tree,
                                       bt_index_t index_status_key,
                                       uint32_t index_status_position)
{
    bt_index_t index = struct_tree->node_index;
    bt_definition_status_t status = BT_DEFINITION_STATUS_RUNNING;
    const bt_definition_node_t *node_struct = &(struct_tree->tree[index]);
    bt_definition_node_type_t node_type = node_struct->node_type;
    uint32_t value_status = 0;

    if(struct_tree == NULL)
    {
        return BT_DEFINITION_STATUS_ERROR;
    }

    SEGGER_RTT_printf(0, "[%d]", index);

    switch(node_type)
    {
        case BT_DEFINITION_NODE_ACTION:
        case BT_DEFINITION_NODE_CONDITION:
        case BT_DEFINITION_NODE_REACTIVE_ACTION:
        case BT_DEFINITION_NODE_REACTIVE_CONDITION:
        {
//            BT_PROCESS_CHECK_RUNNING(struct_tree);

            status = node_struct->interaction_node.function();
            break;
        }

        case BT_DEFINITION_NODE_RETRY_UNTIL_SUCCESS:
        case BT_DEFINITION_NODE_REACTIVE_RETRY_UNTIL_SUCCESS:
        {
            BT_PROCESS_CHECK_TARGET(struct_tree, index);

            if (struct_tree->last_node_state == BT_DEFINITION_STATUS_RUNNING)
            {
                if(node_struct->decorator_node.ties_node.times <= 0){
                    status = BT_DEFINITION_STATUS_FAIL;
                    break;
                }

                *node_struct->decorator_node.ties_node.local = node_struct->decorator_node.ties_node.times - 1;

                struct_tree->node_index = node_struct->decorator_node.target_index;

//                struct_tree->nodes_status[index_status_position] = (()) | (0b00 << (index_status_key));
//                struct_tree->last_node_state = BT_DEFINITION_STATUS_RUNNING;
//                return BT_DEFINITION_STATUS_RUNNING;
                break;
            }
            else if((struct_tree->last_node_state == BT_DEFINITION_STATUS_FAIL) &&
                    (*node_struct->decorator_node.ties_node.local > BT_PROCESS_MIN_ATTEMPTS))
            {
                *node_struct->decorator_node.ties_node.local -= 1;
                SEGGER_RTT_printf(0, "%d, ", *node_struct->decorator_node.ties_node.local);
                struct_tree->node_index = node_struct->decorator_node.target_index;
                status = BT_DEFINITION_STATUS_RUNNING;
            }
            else
            {
                status = struct_tree->last_node_state;
                *node_struct->decorator_node.ties_node.local = BT_PROCESS_MIN_ATTEMPTS;
            }

            bt_index_t clear_index = struct_tree->node_index;
            bt_index_t key = 0;
            bt_index_t position = 0;
            uint32_t nodes_status = 0;
            uint32_t mask = 0;
            uint32_t valor = 0;

            do
            {
                key = (clear_index % 16) * 2;
                position = clear_index / 16;
                nodes_status = struct_tree->nodes_status[position];
                mask = (0b11 << (key));
                valor = (nodes_status & (~mask));
                struct_tree->nodes_status[position] = (valor) | (0b00 << (key));
                SEGGER_RTT_printf(0, "%d, ", clear_index);
                SEGGER_RTT_printf(0, "%x, ", struct_tree->nodes_status[position]);
                clear_index += 1;
            } while(clear_index <= node_struct->decorator_node.ties_node.node_limit);

            break;
        }

        case BT_DEFINITION_NODE_REPEAT:
        case BT_DEFINITION_NODE_REACTIVE_REPEAT:
        {
            BT_PROCESS_CHECK_TARGET(struct_tree, index);
            if((struct_tree->last_node_state == BT_DEFINITION_STATUS_RUNNING))
            {
                if(node_struct->decorator_node.ties_node.times <= 0){
                    status = BT_DEFINITION_STATUS_FAIL;
                    break;
                }

                *node_struct->decorator_node.ties_node.local = node_struct->decorator_node.ties_node.times - 1;

                struct_tree->node_index = node_struct->decorator_node.target_index;

//                struct_tree->nodes_status[index_status_position] = (value_status) | (0b00 << (index_status_key));
//                struct_tree->last_node_state = BT_DEFINITION_STATUS_RUNNING;
//                return BT_DEFINITION_STATUS_RUNNING;
                break;
            }
            else if(*node_struct->decorator_node.ties_node.local > BT_PROCESS_MIN_ATTEMPTS)
            {
                *node_struct->decorator_node.ties_node.local -= 1;
                struct_tree->node_index = node_struct->decorator_node.target_index;
                status = BT_DEFINITION_STATUS_RUNNING;
            }
            else
            {
                status = struct_tree->last_node_state;
                *node_struct->decorator_node.ties_node.local = BT_PROCESS_MIN_ATTEMPTS;
            }

            bt_index_t clear_index = struct_tree->node_index;
            bt_index_t key = 0;
            bt_index_t position = 0;
            uint32_t nodes_status = 0;
            uint32_t mask = 0;
            uint32_t valor = 0;

            do
            {
                key = (clear_index % 16) * 2;
                position = clear_index / 16;
                nodes_status = struct_tree->nodes_status[position];
                mask = (0b11 << (key));
                valor = (nodes_status & (~mask));
                struct_tree->nodes_status[position] = (valor) | (0b00 << (key));
                SEGGER_RTT_printf(0, "%d, ", clear_index);
                SEGGER_RTT_printf(0, "%x, ", struct_tree->nodes_status[position]);
                clear_index += 1;
            } while(clear_index <= node_struct->decorator_node.ties_node.node_limit);

            break;
        }

        case BT_DEFINITION_NODE_KEEP_RUNNING_UNTIL_FAILURE:
        case BT_DEFINITION_NODE_REACTIVE_KEEP_RUNNING_UNTIL_FAILURE:
        {
            BT_PROCESS_CHECK_TARGET(struct_tree, index);
            if ((struct_tree->last_node_state == BT_DEFINITION_STATUS_RUNNING) ||
                (struct_tree->last_node_state == BT_DEFINITION_STATUS_FAIL)) {

                struct_tree->node_index = node_struct->decorator_node.target_index;

//                struct_tree->nodes_status[index_status_position] = (value_status) | (0b00 << (index_status_key));
//                struct_tree->last_node_state = BT_DEFINITION_STATUS_RUNNING;

                bt_index_t clear_index = struct_tree->node_index;
                bt_index_t key = 0;
                bt_index_t position = 0;
                uint32_t nodes_status = 0;
                uint32_t mask = 0;
                uint32_t valor = 0;

                do
                {
                    key = (clear_index % 16) * 2;
                    position = clear_index / 16;
                    nodes_status = struct_tree->nodes_status[position];
                    mask = (0b11 << (key));
                    valor = (nodes_status & (~mask));
                    struct_tree->nodes_status[position] = (valor) | (0b00 << (key));
                    clear_index += 1;
                } while(clear_index < node_struct->decorator_node.ties_node.node_limit);

//                return BT_DEFINITION_STATUS_RUNNING;
                break;
            }
            else
            {
                status = struct_tree->last_node_state;
            }

            break;
        }

        case BT_DEFINITION_NODE_INVERTER:
        case BT_DEFINITION_NODE_REACTIVE_INVERTER:
        {
            BT_PROCESS_CHECK_TARGET(struct_tree, index);

            if(struct_tree->last_node_state == BT_DEFINITION_STATUS_SUCCESS)
            {
                status = BT_DEFINITION_STATUS_FAIL;
            }
            else if (struct_tree->last_node_state == BT_DEFINITION_STATUS_FAIL)
            {
                status = BT_DEFINITION_STATUS_SUCCESS;
            }
            else
            {
                struct_tree->node_index = node_struct->decorator_node.target_index;
                status = BT_DEFINITION_STATUS_RUNNING;
            }
            break;
        }

        case BT_DEFINITION_NODE_FORCE_SUCCESS:
        case BT_DEFINITION_NODE_REACTIVE_FORCE_SUCCESS:
        {
            BT_PROCESS_CHECK_TARGET(struct_tree, index);
            if (struct_tree->last_node_state == BT_DEFINITION_STATUS_RUNNING) {
                struct_tree->node_index = node_struct->decorator_node.target_index;
                status = BT_DEFINITION_STATUS_RUNNING;
            }
            else if (struct_tree->last_node_state == BT_DEFINITION_STATUS_RE_EXECUTE) {
                struct_tree->node_index = node_struct->decorator_node.target_index;
                status = BT_DEFINITION_STATUS_RUNNING;
            }
            else
            {
                status = BT_DEFINITION_STATUS_SUCCESS;
            }
            break;
        }

        case BT_DEFINITION_NODE_FORCE_FAIL:
        case BT_DEFINITION_NODE_REACTIVE_FORCE_FAIL:
        {
            BT_PROCESS_CHECK_TARGET(struct_tree, index);
            status = BT_DEFINITION_STATUS_RUNNING;
            if (struct_tree->last_node_state == BT_DEFINITION_STATUS_RUNNING) {
                struct_tree->node_index = node_struct->decorator_node.target_index;
                status = BT_DEFINITION_STATUS_RUNNING;
            }
            else if (struct_tree->last_node_state == BT_DEFINITION_STATUS_RE_EXECUTE) {
                struct_tree->node_index = node_struct->decorator_node.target_index;
                status = BT_DEFINITION_STATUS_RUNNING;
            }
            else
            {
                status = BT_DEFINITION_STATUS_FAIL;
            }
            break;
        }

        case BT_DEFINITION_NODE_ACTION_TIMEOUT:
        case BT_DEFINITION_NODE_REACTIVE_ACTION_TIMEOUT:
        {
            status = bt_common_action_timeout(node_struct->decorator_node.timeout_ms);
            break;
        }

        case BT_DEFINITION_NODE_DECORATOR_TIMEOUT:
        case BT_DEFINITION_NODE_REACTIVE_DECORATOR_TIMEOUT:
        {
            BT_PROCESS_CHECK_TARGET(struct_tree, index);
            if ((struct_tree->last_node_state == BT_DEFINITION_STATUS_RUNNING) ||
                (struct_tree->last_node_state == BT_DEFINITION_STATUS_RE_EXECUTE))
            {
                status = bt_common_action_timeout(node_struct->decorator_node.timeout_ms);
                struct_tree->node_index = node_struct->decorator_node.target_index;

//                uint32_t x = (value_status) | (0b00 << (index_status_key));
//                struct_tree->nodes_status[index_status_position] = x;
//                struct_tree->last_node_state = BT_DEFINITION_STATUS_RUNNING;
//                return BT_DEFINITION_STATUS_RUNNING;
                break;
            }
            else if (struct_tree->last_node_state == BT_DEFINITION_STATUS_RE_EXECUTE) {
                struct_tree->node_index = node_struct->decorator_node.target_index;
                status = BT_DEFINITION_STATUS_RUNNING;
            }
            else
            {
                status = struct_tree->last_node_state;
            }

            break;
        }

        default:
        {
            return BT_DEFINITION_STATUS_ERROR;
        }
    }

    if(status == BT_DEFINITION_STATUS_SUCCESS)
      SEGGER_RTT_printf(0, "S ");
    if(status == BT_DEFINITION_STATUS_FAIL)
      SEGGER_RTT_printf(0, "F ");
    if(status == BT_DEFINITION_STATUS_RUNNING)
      SEGGER_RTT_printf(0, "R ");

    value_status = struct_tree->nodes_status[index_status_position] & (~mask);

    if((status == BT_DEFINITION_STATUS_SUCCESS))
    {
        struct_tree->node_index = node_struct->st_index;
        if((node_type >= BT_DEFINITION_NODE_REACTIVE_DECORATOR_TIMEOUT) && (node_type <= BT_DEFINITION_NODE_REACTIVE_FORCE_FAIL))
          struct_tree->nodes_status[index_status_position] = (value_status) | (0b11 << (index_status_key));
        else
          struct_tree->nodes_status[index_status_position] = (value_status) | (0b01 << (index_status_key));
    }
    else if((status == BT_DEFINITION_STATUS_FAIL))
    {
        struct_tree->node_index = node_struct->ft_index;
        if((node_type >= BT_DEFINITION_NODE_REACTIVE_DECORATOR_TIMEOUT) && (node_type <= BT_DEFINITION_NODE_REACTIVE_FORCE_FAIL))
          struct_tree->nodes_status[index_status_position] = (value_status) | (0b11 << (index_status_key));
        else
          struct_tree->nodes_status[index_status_position] = (value_status) | (0b10 << (index_status_key));
    }
    else
    {
        struct_tree->nodes_status[index_status_position] = (value_status) | (0b00 << (index_status_key));
    }

    struct_tree->last_node_state = BT_DEFINITION_STATUS_RUNNING;
    if(index > struct_tree->node_index){
        struct_tree->last_node_state = status;
        bt_index_t key = (struct_tree->node_index % 16) * 2;
        bt_index_t position = struct_tree->node_index / 16;
        uint32_t nodes_status = struct_tree->nodes_status[position];
        uint32_t mask = (0b11 << (key));
        uint32_t valor = (nodes_status & (~mask));
        if(status == BT_DEFINITION_STATUS_SUCCESS)
        {
            struct_tree->nodes_status[position] = (valor) | (0b01 << (key));
        }
        else if(status == BT_DEFINITION_STATUS_FAIL)
        {
            struct_tree->nodes_status[position] = (valor) | (0b10 << (key));
        }
    }

    return status;
}
