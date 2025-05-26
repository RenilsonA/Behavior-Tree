/**
 * @file btree_subtree_array.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header of interface of array tree.
 * @version 1.0
 * @date 12/05/2025
 *
 */

#ifndef BTREE_SUBTREE_ARRAY_H_
#define BTREE_SUBTREE_ARRAY_H_

#include "btree_subtree_blackboard.h"

/**
 * @brief subtree tree size.
 *
 */
#define BTREE_SUBTREE_ARRAY_SIZE 16

/**
 * @brief Array containing the nodes of the subtree tree.
 *
 */
extern const btree_definition_node_t btree_subtree_array[BTREE_SUBTREE_ARRAY_SIZE];

/**
 * @brief Externalizes subtree tree control structure.
 *
 */
extern btree_definition_tree_data_t btree_subtree_control;

#endif /* BTREE_SUBTREE_ARRAY_H_ */