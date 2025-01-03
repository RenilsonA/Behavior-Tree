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
#define TEST_BT_COMMON_ATTEMPTS_SIZE 0

/**
 * @brief Referência o array de tentativas.
 *
 */
extern uint8_t test_bt_commom_attempts[TEST_BT_COMMON_ATTEMPTS_SIZE];

#endif /* TEST_BT_COMMON_H_ */