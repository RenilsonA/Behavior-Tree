/**
 * @file btree_subtree_common.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface of the common variables of the subtree.
 * @version 1.0
 * @date 12/05/2025
 *
 */

#include "btree_subtree_common.h"

/**
 * @brief Nodes states. Each value, carry 16 nodes status. Each node status is 2 bits.
 *
 */
uint32_t btree_subtree_status_nodes[BTREE_SUBTREE_COMMON_STATUS_NODES_SIZE] = {0};

/**
 * @brief Fields to input tries or attempts.
 *
 */
uint32_t btree_subtree_common_attempts[BTREE_SUBTREE_COMMON_ATTEMPTS_SIZE] = {0};

