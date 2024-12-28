/**
 * @file test_bt_example.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header da interface da behavior tree example.
 * @version 1.0
 * @date 27/12/2024
 *
 */

#ifndef TEST_BT_EXAMPLE_H_
#define TEST_BT_EXAMPLE_H_

#include "test_bt_blackboard.h"

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_example_condition1(void);

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_example_action1(void);

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_example_action2(void);

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_example_action3(void);

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_example_action4(void);

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_example_action5(void);

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_example_condition2(void);

/**
* @brief 
*
* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;
* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;
* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;
*/
bt_definition_status_t test_bt_example_action6(void);

#endif /* TEST_BT_EXAMPLE_H_ */