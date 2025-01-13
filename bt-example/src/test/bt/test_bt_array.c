/**
 * @file test_bt_array.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface da behavior tree array.
 * @version 1.0
 * @date 07/01/2025
 *
 */

#include "test_bt_array.h"
#include "test_bt_example.h"

/**
 * @brief Array contendo os nós da árvore test.
 *
 */
const bt_definition_node_t test_bt_array[TEST_BT_ARRAY_SIZE] = 
{
    [0] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition1, 7, 1, 0), \
    [1] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action1, 2, BT_DEFINITION_TREE_UNRELATED, 0), \
    [2] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition2, 5, 3, 0), \
    [3] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action2, 5, 4, 0), \
    [4] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action3, 5, BT_DEFINITION_TREE_UNRELATED, 0), \
    [5] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition4, 7, 6, 0), \
    [6] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action9, 7, BT_DEFINITION_TREE_UNRELATED, 0), \
    [7] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition5, 11, 8, 0), \
    [8] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition9, 11, 9, 0), \
    [9] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition10, 11, 10, 0), \
    [10] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action10, 11, BT_DEFINITION_TREE_UNRELATED, 0), \
    [11] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition6, BT_DEFINITION_TREE_UNRELATED, 12, 0), \
    [12] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition7, BT_DEFINITION_TREE_UNRELATED, 13, 0), \
    [13] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action11, BT_DEFINITION_TREE_UNRELATED, 14, 0), \
    [14] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition8, BT_DEFINITION_TREE_UNRELATED, 15, 0), \
    [15] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action12, BT_DEFINITION_TREE_UNRELATED, BT_DEFINITION_TREE_UNRELATED, 0), \
};

/**
 * @brief Estrutura de controle da árvore test.
 *
 */
bt_definition_tree_data_t test_bt_control = {
    .last_node_state      = BT_DEFINITION_STATUS_RUNNING,
    .node_index           = BT_DEFINITON_NODE_FIRST_INDEX,
    .tree_size            = TEST_BT_ARRAY_SIZE,
    .nodes_status         = test_bt_status_nodes,
    .tree                 = test_bt_array,
};

