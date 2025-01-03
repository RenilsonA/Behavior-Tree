/**
 * @file test_bt_example.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface da behavior tree example.
 * @version 1.0
 * @date 03/01/2025
 *
 */

#include "test_bt_example.h"

int x = 0;

bt_definition_status_t test_bt_example_condition1(void)
{
  x += 1;
  SEGGER_RTT_printf(0, "Condition1 ");
  if(x < 2)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action1(void)
{
  SEGGER_RTT_printf(0, "Action1 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition2(void)
{
  x += 1;
  SEGGER_RTT_printf(0, "Condition2 ");
  if(x < 3)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action2(void)
{
  x += 1;
  SEGGER_RTT_printf(0, "Action2 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_action3(void)
{
  SEGGER_RTT_printf(0, "Action3 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition4(void)
{
  x += 1;
  SEGGER_RTT_printf(0, "Condition4 ");
  if(x < 4)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action9(void)
{
  SEGGER_RTT_printf(0, "Action9 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition5(void)
{
  x += 1;
  SEGGER_RTT_printf(0, "Condition5 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_action10(void)
{
  SEGGER_RTT_printf(0, "Action10 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition6(void)
{
  x += 1;
  SEGGER_RTT_printf(0, "Condition6 ");
  if(x < 6)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_condition7(void)
{
  x += 1;
  SEGGER_RTT_printf(0, "Condition7 ");
  if(x < 7)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action11(void)
{
  SEGGER_RTT_printf(0, "Action11 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition8(void)
{
  x += 1;
  SEGGER_RTT_printf(0, "Condition8 ");
  if(x < 8)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action12(void)
{
  SEGGER_RTT_printf(0, "Action12 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

