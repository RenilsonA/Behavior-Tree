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

//const bt_definition_node_t test_bt_array[TEST_BT_ARRAY_SIZE] =
//{
//    [0] = BT_DEFINITION_CREATE_NODE_REACTIVE_RETRY_UNTIL_SUCCESS(4, 10, 1, 5, &test_bt_common_attempts[0]), \
//    [1] = BT_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(0, 2, &test_bt_subtree_condition20), \
//    [2] = BT_DEFINITION_CREATE_NODE_REACTIVE_REPEAT(0, 0, 3, 1, &test_bt_common_attempts[1]), \
//    [3] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(2, 2, &test_bt_subtree_action21), \
//    [4] = BT_DEFINITION_CREATE_NODE_REACTIVE_FORCE_FAIL(BT_DEFINITION_TREE_UNRELATED, 10, 5), \
//    [5] = BT_DEFINITION_CREATE_NODE_REACTIVE_INVERTER(4, 4, 6), \
//    [6] = BT_DEFINITION_CREATE_NODE_REACTIVE_FORCE_FAIL(5, 8, 7), \
//    [7] = BT_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(6, 6, &test_bt_subtree_condition21), \
//    [8] = BT_DEFINITION_CREATE_NODE_REACTIVE_FORCE_SUCCESS(5, 5, 9), \
//    [9] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(8, 8, &test_bt_subtree_action23), \
//    [10] = BT_DEFINITION_CREATE_NODE_REACTIVE_KEEP_RUNNING_UNTIL_FAILURE(BT_DEFINITION_TREE_UNRELATED, BT_DEFINITION_TREE_UNRELATED, 11), \
//    [11] = BT_DEFINITION_CREATE_NODE_REACTIVE_DECORATOR_TIMEOUT(10, 10, 12, 500), \
//    [12] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(11, 11, &test_bt_subtree_action24), \
//};

const bt_definition_node_t test_bt_array[TEST_BT_ARRAY_SIZE] =
{
         [0] = BT_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(7, 1, &test_bt_example_condition1), \
         [1] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(2, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action1), \
         [2] = BT_DEFINITION_CREATE_NODE_CONDITION(5, 3, &test_bt_example_condition2), \
         [3] = BT_DEFINITION_CREATE_NODE_ACTION(5, 4, &test_bt_example_action2), \
         [4] = BT_DEFINITION_CREATE_NODE_ACTION(5, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action3), \
         [5] = BT_DEFINITION_CREATE_NODE_CONDITION(7, 6, &test_bt_example_condition4), \
         [6] = BT_DEFINITION_CREATE_NODE_ACTION(7, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action9), \
         [7] = BT_DEFINITION_CREATE_NODE_CONDITION(11, 8, &test_bt_example_condition5), \
         [8] = BT_DEFINITION_CREATE_NODE_CONDITION(11, 9, &test_bt_example_condition9), \
         [9] = BT_DEFINITION_CREATE_NODE_CONDITION(11, 10, &test_bt_example_condition10), \
         [10] = BT_DEFINITION_CREATE_NODE_ACTION(11, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action10), \
         [11] = BT_DEFINITION_CREATE_NODE_CONDITION(16, 12, &test_bt_example_condition6), \
         [12] = BT_DEFINITION_CREATE_NODE_CONDITION(16, 13, &test_bt_example_condition7), \
         [13] = BT_DEFINITION_CREATE_NODE_ACTION(16, 14, &test_bt_example_action11), \
         [14] = BT_DEFINITION_CREATE_NODE_CONDITION(16, 15, &test_bt_example_condition8), \
         [15] = BT_DEFINITION_CREATE_NODE_ACTION(16, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action12), \
         [16] = BT_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(26, 17, &test_bt_example_condition9), \
         [17] = BT_DEFINITION_CREATE_NODE_ACTION(18, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action13), \
         [18] = BT_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(21, 19, &test_bt_example_condition10), \
         [19] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(21, 20, &test_bt_example_action14), \
         [20] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(21, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action15), \
         [21] = BT_DEFINITION_CREATE_NODE_ACTION(22, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action9), \
         [22] = BT_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(24, 23, &test_bt_example_condition11), \
         [23] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(24, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action16), \
         [24] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(25, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action9), \
         [25] = BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(26, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action13), \
         [26] = BT_DEFINITION_CREATE_NODE_CONDITION(BT_DEFINITION_TREE_UNRELATED, 27, &test_bt_example_condition7), \
         [27] = BT_DEFINITION_CREATE_NODE_ACTION(BT_DEFINITION_TREE_UNRELATED, BT_DEFINITION_TREE_UNRELATED, &test_bt_example_action12), \
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

