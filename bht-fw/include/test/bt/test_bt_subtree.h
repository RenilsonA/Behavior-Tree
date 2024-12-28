/**
 * @file test_bt_subtree.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header da interface da behavior tree subtree.
 * @version 1.0
 * @date 27/12/2024
 *
 */

#ifndef TEST_BT_SUBTREE_H_
#define TEST_BT_SUBTREE_H_

#include "test_bt_blackboard.h"

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_subtree_condition3(void);

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_subtree_action7(void);

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_subtree_action8(void);

#endif /* TEST_BT_SUBTREE_H_ */