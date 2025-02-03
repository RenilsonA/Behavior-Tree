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
#include "test_bt_subtree.h"

/**
 * @brief Array contendo os nós da árvore test.
 *
 */
const bt_definition_node_t test_bt_array[TEST_BT_ARRAY_SIZE] =
{
    [0] = BT_DEFINITION_CREATE_NODE_REACTIVE_FORCE_SUCCESS(2, BT_DEFINITION_TREE_UNRELATED, 1), \
    [1] = BT_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(0, 0, &test_bt_subtree_condition21), \
    [2] = BT_DEFINITION_CREATE_NODE_REACTIVE_INVERTER(5, BT_DEFINITION_TREE_UNRELATED, 3), \
    [3] = BT_DEFINITION_CREATE_NODE_REACTIVE_DECORATOR_TIMEOUT(2, 2, 4, 500), \
    [4] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(3, 3, &test_bt_subtree_action24), \
    [5] = BT_DEFINITION_CREATE_NODE_REACTIVE_FORCE_SUCCESS(10, BT_DEFINITION_TREE_UNRELATED, 6), \
    [6] = BT_DEFINITION_CREATE_NODE_FORCE_FAIL(5, 8, 7), \
    [7] = BT_DEFINITION_CREATE_NODE_CONDITION(6, 6, &test_bt_subtree_condition21), \
    [8] = BT_DEFINITION_CREATE_NODE_FORCE_SUCCESS(5, 5, 9), \
    [9] = BT_DEFINITION_CREATE_NODE_ACTION(8, 8, &test_bt_subtree_action23), \
    [10] = BT_DEFINITION_CREATE_NODE_REACTIVE_RETRY_UNTIL_SUCCESS(14, BT_DEFINITION_TREE_UNRELATED, 11, 5, &test_bt_common_attempts[0], 13), \
    [11] = BT_DEFINITION_CREATE_NODE_CONDITION(10, 12, &test_bt_subtree_condition20), \
    [12] = BT_DEFINITION_CREATE_NODE_REPEAT(10, 10, 13, 2, &test_bt_common_attempts[1], 13), \
    [13] = BT_DEFINITION_CREATE_NODE_ACTION(12, 12, &test_bt_subtree_action21), \
    [14] = BT_DEFINITION_CREATE_NODE_KEEP_RUNNING_UNTIL_FAILURE(17, BT_DEFINITION_TREE_UNRELATED, 15, 16), \
    [15] = BT_DEFINITION_CREATE_NODE_DECORATOR_TIMEOUT(14, 14, 16, 500), \
    [16] = BT_DEFINITION_CREATE_NODE_ACTION(15, 15, &test_bt_subtree_action25), \
    [17] = BT_DEFINITION_CREATE_NODE_RETRY_UNTIL_SUCCESS(BT_DEFINITION_TREE_UNRELATED, BT_DEFINITION_TREE_UNRELATED, 18, 9, &test_bt_common_attempts[0], 19), \
    [18] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(19, 17, &test_bt_subtree_action25), \
    [19] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(17, 17, &test_bt_subtree_action25), \
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

