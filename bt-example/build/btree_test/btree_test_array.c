/**
 * @file btree_test_array.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface of array tree.
 * @version 1.0
 * @date 27/04/2025
 *
 */

#include "btree_test_array.h"
#include "btree_test_example.h"
#include "btree_test_subtree.h"

/**
 * @brief Array containing the nodes of the test tree.
 *
 */
const btree_definition_node_t btree_test_array[BTREE_TEST_ARRAY_SIZE] = 
{
         [0] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(7, 1, &btree_test_example_condition1), \
         [1] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(2, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action1), \
         [2] = BTREE_DEFINITION_CREATE_NODE_CONDITION(5, 3, &btree_test_example_condition2), \
         [3] = BTREE_DEFINITION_CREATE_NODE_ACTION(5, 4, &btree_test_example_action2), \
         [4] = BTREE_DEFINITION_CREATE_NODE_ACTION(5, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action3), \
         [5] = BTREE_DEFINITION_CREATE_NODE_CONDITION(7, 6, &btree_test_example_condition4), \
         [6] = BTREE_DEFINITION_CREATE_NODE_ACTION(7, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action9), \
         [7] = BTREE_DEFINITION_CREATE_NODE_CONDITION(10, 8, &btree_test_example_condition9), \
         [8] = BTREE_DEFINITION_CREATE_NODE_CONDITION(10, 9, &btree_test_example_condition10), \
         [9] = BTREE_DEFINITION_CREATE_NODE_ACTION(10, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action10), \
         [10] = BTREE_DEFINITION_CREATE_NODE_CONDITION(15, 11, &btree_test_example_condition6), \
         [11] = BTREE_DEFINITION_CREATE_NODE_CONDITION(15, 12, &btree_test_example_condition7), \
         [12] = BTREE_DEFINITION_CREATE_NODE_ACTION(15, 13, &btree_test_example_action11), \
         [13] = BTREE_DEFINITION_CREATE_NODE_CONDITION(15, 14, &btree_test_example_condition8), \
         [14] = BTREE_DEFINITION_CREATE_NODE_ACTION(15, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action12), \
         [15] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(25, 16, &btree_test_example_condition9), \
         [16] = BTREE_DEFINITION_CREATE_NODE_ACTION(17, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action13), \
         [17] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(20, 18, &btree_test_example_condition10), \
         [18] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(20, 19, &btree_test_example_action14), \
         [19] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(20, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action15), \
         [20] = BTREE_DEFINITION_CREATE_NODE_ACTION(21, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action9), \
         [21] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(23, 22, &btree_test_example_condition11), \
         [22] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(23, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action16), \
         [23] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(24, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action9), \
         [24] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(25, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action13), \
         [25] = BTREE_DEFINITION_CREATE_NODE_CONDITION(27, 26, &btree_test_example_condition7), \
         [26] = BTREE_DEFINITION_CREATE_NODE_ACTION(27, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_example_action12), \
         [27] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_FORCE_SUCCESS(29, BTREE_DEFINITION_TREE_UNRELATED, 28), \
         [28] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(27, 27, &btree_test_subtree_condition21), \
         [29] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_INVERTER(31, BTREE_DEFINITION_TREE_UNRELATED, 30), \
         [30] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(29, 29, &btree_test_subtree_action24), \
         [31] = BTREE_DEFINITION_CREATE_NODE_FORCE_FAIL(34, 33, 32), \
         [32] = BTREE_DEFINITION_CREATE_NODE_CONDITION(31, 31, &btree_test_subtree_condition21), \
         [33] = BTREE_DEFINITION_CREATE_NODE_ACTION(34, BTREE_DEFINITION_TREE_UNRELATED, &btree_test_subtree_action23), \
         [34] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_RETRY_UNTIL_SUCCESS(38, BTREE_DEFINITION_TREE_UNRELATED, 35, 5, &btree_test_common_attempts[0], 37), \
         [35] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(34, 36, &btree_test_subtree_condition20), \
         [36] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_REPEAT(34, 34, 37, 1, &btree_test_common_attempts[1], 37), \
         [37] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(36, 36, &btree_test_subtree_action21), \
         [38] = BTREE_DEFINITION_CREATE_NODE_KEEP_RUNNING_UNTIL_FAILURE(40, BTREE_DEFINITION_TREE_UNRELATED, 39, 39), \
         [39] = BTREE_DEFINITION_CREATE_NODE_ACTION(38, 38, &btree_test_subtree_action25), \
         [40] = BTREE_DEFINITION_CREATE_NODE_RETRY_UNTIL_SUCCESS(BTREE_DEFINITION_TREE_UNRELATED, BTREE_DEFINITION_TREE_UNRELATED, 41, 9, &btree_test_common_attempts[0], 42), \
         [41] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(42, 40, &btree_test_subtree_action25), \
         [42] = BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION(40, 40, &btree_test_subtree_action25), \
};

/**
 * @brief test tree Control Structure.
 *
 */
btree_definition_tree_data_t btree_test_control = {
    .last_node_state = BTREE_DEFINITION_STATUS_RUNNING,
    .node_index      = BTREE_DEFINITON_NODE_FIRST_INDEX,
    .tree_size       = BTREE_TEST_ARRAY_SIZE,
    .tree            = btree_test_array,
};

