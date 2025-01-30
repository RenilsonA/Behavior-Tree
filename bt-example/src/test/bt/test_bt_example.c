/**
 * @file test_bt_example.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface da behavior tree example.
 * @version 1.0
 * @date 03/01/2025
 *
 */

#include "test_bt_example.h"

int c1 = 0;
int c2 = 0;
int c3 = 0;
int c4 = 0;
int c5 = 0;
int c6 = 0;
int c7 = 0;
int c8 = 0;
int c9 = 0;
int c10 = 0;

bt_definition_status_t test_bt_example_condition1(void)
{
  SEGGER_RTT_printf(0, "C1 ");
  if(c1 != 0)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action1(void)
{
  SEGGER_RTT_printf(0, "A1 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition2(void)
{
  SEGGER_RTT_printf(0, "C2 ");
  if(c2 != 0)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action2(void)
{
  SEGGER_RTT_printf(0, "A2 ");
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action3(void)
{
  SEGGER_RTT_printf(0, "A3 ");
  c1 = 1;
  c2 = 1;
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition4(void)
{
  SEGGER_RTT_printf(0, "C4 ");
  if(c4 != 0)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action9(void)
{
  SEGGER_RTT_printf(0, "A9 ");
  c4 = 1;
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_action14(void)
{
  SEGGER_RTT_printf(0, "A14 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_action15(void)
{
  SEGGER_RTT_printf(0, "A15 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition11(void)
{
  SEGGER_RTT_printf(0, "C11 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_action16(void)
{
  SEGGER_RTT_printf(0, "A16 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition5(void)
{
  SEGGER_RTT_printf(0, "C5 ");
  if(c5 != 0)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action10(void)
{
  SEGGER_RTT_printf(0, "A10 ");
  c5 = 1;
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition9(void)
{
  SEGGER_RTT_printf(0, "C9 ");
  if(c9 >= 2)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_condition10(void)
{
  SEGGER_RTT_printf(0, "C10 ");
  c5 = 1;
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_action13(void)
{
  SEGGER_RTT_printf(0, "A13 ");
  c9 += 1;
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_example_condition6(void)
{
  SEGGER_RTT_printf(0, "C6 ");
  if(c6 != 0)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_condition7(void)
{
  SEGGER_RTT_printf(0, "C7 ");
  if(c7 != 0)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action11(void)
{
  SEGGER_RTT_printf(0, "A11 ");
  c7 = 1;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_condition8(void)
{
  SEGGER_RTT_printf(0, "C8 ");
  if(c8 != 0)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_example_action12(void)
{
  SEGGER_RTT_printf(0, "A12 ");
  c8 = 1;
  return BT_DEFINITION_STATUS_SUCCESS;
}
