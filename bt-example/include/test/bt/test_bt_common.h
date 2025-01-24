/**
 * @file test_bt_common.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header da interface das variáveis comuns do test_.
 * @version 1.0
 * @date 03/01/2025
 *
 */

#ifndef TEST_BT_COMMON_H_
#define TEST_BT_COMMON_H_

#include "bt_definition.h"

/**
 * @brief Número máximo de nós de tentativas em uma ramificação.
 *
 */
#define TEST_BT_COMMON_ATTEMPTS_SIZE 2

/**
 * @brief Número máximo de itens para o array de nós.
 *
 */
#define TEST_BT_COMMON_STATUS_NODES_SIZE 1

/**
 * @brief Referência o array de tentativas.
 *
 */
extern uint32_t test_bt_common_attempts[TEST_BT_COMMON_ATTEMPTS_SIZE];

/**
 * @brief Guarda os status dos nós executados.
 *
 */
extern uint32_t test_bt_status_nodes[TEST_BT_COMMON_STATUS_NODES_SIZE];

#endif /* TEST_BT_COMMON_H_ */
