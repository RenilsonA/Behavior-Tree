/**
 * @file btree_main_array.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header of interface of array tree.
 * @version 1.0
 * @date 18/05/2025
 *
 */

#ifndef BTREE_MAIN_ARRAY_H_
#define BTREE_MAIN_ARRAY_H_

#include "btree_main_blackboard.h"

/**
 * @brief main tree size.
 *
 */
#define BTREE_MAIN_ARRAY_SIZE 240

/**
 * @brief Array containing the nodes of the main tree.
 *
 */
extern const btree_definition_node_t btree_main_array[BTREE_MAIN_ARRAY_SIZE];

/**
 * @brief Externalizes main tree control structure.
 *
 */
extern btree_definition_tree_data_t btree_main_control;

#endif /* BTREE_MAIN_ARRAY_H_ */
