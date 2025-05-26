/**
 * @file btree_example_array.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header of interface of array tree.
 * @version 1.0
 * @date 12/05/2025
 *
 */

#ifndef BTREE_EXAMPLE_ARRAY_H_
#define BTREE_EXAMPLE_ARRAY_H_

#include "btree_example_blackboard.h"

/**
 * @brief example tree size.
 *
 */
#define BTREE_EXAMPLE_ARRAY_SIZE 17

/**
 * @brief Array containing the nodes of the example tree.
 *
 */
extern const btree_definition_node_t btree_example_array[BTREE_EXAMPLE_ARRAY_SIZE];

/**
 * @brief Externalizes example tree control structure.
 *
 */
extern btree_definition_tree_data_t btree_example_control;

#endif /* BTREE_EXAMPLE_ARRAY_H_ */