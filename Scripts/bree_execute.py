#Behavior Tree like Tree.
POSITION_NODE_INDEX = 0
POSITION_NODE_TYPE = 1
POSITION_NODE_CHILDREN = 2
POSITION_NODE_SIBLING = -3
POSITION_NODE_PARENT = -2
POSITION_NODE_REACTIVE = -1
POSITION_NODE_FUNCTION = 2
POSITION_NODE_TARGET = 4
POSITION_NODE_DECORATOR_POINTER = 2
POSITION_NODE_DECORATOR_TARGET = -3
POSITION_NODE_DECORATOR_NUM_ATTEMPTS = 3
POSITION_NODE_DECORATOR_TIMEOUT_TIME = 2
POSITION_NODE_DECORATOR_RETRY_DEPTH = -4

#Tree like DAG
INDEX_OF_POSITION = 0
INDEX_OF_MACRO = 1
INDEX_SUCCESS_CASE = 2
INDEX_FAIL_CASE = 3
INDEX_POINTER_VERIFY = -1
INDEX_CLEAN_UNTIL_NODE = -1

#Node invalid
NODE_UNRELATED = "BTREE_DEFINITION_TREE_UNRELATED"

#Macros of nodes
macro_node_condition = "BTREE_DEFINITION_CREATE_NODE_CONDITION"
macro_node_action = "BTREE_DEFINITION_CREATE_NODE_ACTION"
macro_node_retry_until_success = "BTREE_DEFINITION_CREATE_NODE_RETRY_UNTIL_SUCCESS"
macro_node_repeat = "BTREE_DEFINITION_CREATE_NODE_REPEAT"
macro_node_keep_running_until_failure = "BTREE_DEFINITION_CREATE_NODE_KEEP_RUNNING_UNTIL_FAILURE"
macro_node_force_failure = "BTREE_DEFINITION_CREATE_NODE_FORCE_FAIL"
macro_node_force_success = "BTREE_DEFINITION_CREATE_NODE_FORCE_SUCCESS"
macro_node_inverter = "BTREE_DEFINITION_CREATE_NODE_INVERTER"
macro_node_decorator_timeout = "BTREE_DEFINITION_CREATE_NODE_DECORATOR_TIMEOUT"

macro_node_reactive_condition = "BTREE_DEFINITION_CREATE_NODE_REACTIVE_CONDITION"
macro_node_reactive_action = "BTREE_DEFINITION_CREATE_NODE_REACTIVE_ACTION"
macro_node_reactive_retry_until_success = "BTREE_DEFINITION_CREATE_NODE_REACTIVE_RETRY_UNTIL_SUCCESS"
macro_node_reactive_repeat = "BTREE_DEFINITION_CREATE_NODE_REACTIVE_REPEAT"
macro_node_reactive_keep_running_until_failure = "BTREE_DEFINITION_CREATE_NODE_REACTIVE_KEEP_RUNNING_UNTIL_FAILURE"
macro_node_reactive_force_failure = "BTREE_DEFINITION_CREATE_NODE_REACTIVE_FORCE_FAIL"
macro_node_reactive_force_success = "BTREE_DEFINITION_CREATE_NODE_REACTIVE_FORCE_SUCCESS"
macro_node_reactive_inverter = "BTREE_DEFINITION_CREATE_NODE_REACTIVE_INVERTER"
macro_node_reactive_decorator_timeout = "BTREE_DEFINITION_CREATE_NODE_REACTIVE_DECORATOR_TIMEOUT"

#Status of nodes
status_node = [ 'success', 'fail']
status_fail = 'fail'
status_success = 'success'
status_running = 'Running'

class BTREE_EXECUTE:
    def __init__(self):
        self.node_root = 'Root'
        self.node_sequence = 'Sequence'
        self.node_fallback = 'Fallback'
        self.node_reactive_sequence = 'ReactiveSequence'
        self.node_reactive_fallback = 'ReactiveFallback'
        self.node_action = 'Script'
        self.node_condition = 'ScriptCondition'
        self.node_subtree = 'SubTree'
        self.tree_status = status_running
        self.node_decorator_retry_until_successful = 'RetryUntilSuccessful'
        self.node_decorator_repeat = 'Repeat'
        self.node_decorator_keep_running_until_failure = 'KeepRunningUntilFailure'
        self.node_decorator_force_failure = 'ForceFailure'
        self.node_decorator_force_success = 'ForceSuccess'
        self.node_decorator_inverter = 'Inverter'
        self.node_decorator_timeout = 'Timeout'
        self.next_node = 0
        self.nodes_path = []
        self.decorator_retry_depth = []

    def is_decorator_node(self, node_type):
        return ((node_type == self.node_decorator_retry_until_successful) or
                (node_type == self.node_decorator_repeat) or
                (node_type == self.node_decorator_keep_running_until_failure) or
                (node_type == self.node_decorator_force_failure) or 
                (node_type == self.node_decorator_force_success) or 
                (node_type == self.node_decorator_inverter) or
                (node_type == self.node_decorator_timeout))
    
    def is_decorator_retry_node(self, node_type):
        return ((node_type == self.node_decorator_retry_until_successful) or
                (node_type == self.node_decorator_repeat) or
                (node_type == self.node_decorator_keep_running_until_failure))

    def is_valid_node(self, node_type):
        return ((node_type == self.node_condition) or
                (node_type == self.node_action) or
                (node_type == self.node_delay) or
                (node_type == self.node_decorator_retry_until_successful) or
                (node_type == self.node_decorator_retry_until_successful) or
                (node_type == self.node_decorator_repeat) or
                (node_type == self.node_decorator_keep_running_until_failure) or
                (node_type == self.node_decorator_force_failure) or 
                (node_type == self.node_decorator_force_success) or 
                (node_type == self.node_decorator_inverter) or
                (node_type == self.node_decorator_timeout))

    def is_decorator_macro_node(self, node_type):
        return ((node_type == macro_node_retry_until_success) or (node_type == macro_node_reactive_retry_until_success) or
                (node_type == macro_node_repeat) or (node_type == macro_node_reactive_repeat) or
                (node_type == macro_node_keep_running_until_failure) or (node_type == macro_node_reactive_keep_running_until_failure) or
                (node_type == macro_node_force_failure) or (node_type == macro_node_reactive_force_failure) or
                (node_type == macro_node_force_success) or (node_type == macro_node_reactive_force_success) or
                (node_type == macro_node_inverter) or (node_type == macro_node_reactive_inverter) or
                (node_type == macro_node_decorator_timeout) or (node_type == macro_node_reactive_decorator_timeout))

    def is_decorator_macro_retry_node(self, node_type):
        return ((node_type == macro_node_retry_until_success) or (node_type == macro_node_reactive_retry_until_success) or
                (node_type == macro_node_repeat) or (node_type == macro_node_reactive_repeat) or
                (node_type == macro_node_keep_running_until_failure) or (node_type == macro_node_reactive_keep_running_until_failure))

    def get_nodes_name(self, node_root = None, node_fallback = None, node_reactive_fallback = None, 
                       node_sequence = None, node_reactive_sequence = None, 
                       node_action = None, node_condition = None, node_retry_until_successful = None, 
                       node_decorator_repeat = None, node_keep_running_until_failure = None, 
                       node_decorator_force_failure = None, node_decorator_force_success = None, 
                       node_decorator_inverter = None, node_decorator_timeout = None, 
                       node_delay = None, node_subtree = None):
        self.node_root = node_root
        self.node_fallback = node_fallback
        self.node_reactive_fallback = node_reactive_fallback
        self.node_sequence = node_sequence
        self.node_reactive_sequence = node_reactive_sequence
        self.node_action = node_action
        self.node_condition = node_condition
        self.node_retry_until_successful = node_retry_until_successful
        self.node_decorator_repeat = node_decorator_repeat
        self.node_keep_running_until_failure = node_keep_running_until_failure
        self.node_decorator_force_failure = node_decorator_force_failure
        self.node_decorator_force_success = node_decorator_force_success
        self.node_decorator_inverter = node_decorator_inverter
        self.node_decorator_timeout = node_decorator_timeout
        self.node_delay = node_delay
        self.node_subtree = node_subtree

    def process_node(self, node, node_status):
        if node[POSITION_NODE_TYPE] == self.node_root:
            if((self.tree_status == status_success) or (self.tree_status == status_fail)):
                return self.tree_status
            self.next_node = node[POSITION_NODE_SIBLING]
        elif ((node[POSITION_NODE_TYPE] == self.node_sequence) or (node[POSITION_NODE_TYPE] == self.node_fallback)):
            if self.tree_status == status_running:
                self.next_node = node[POSITION_NODE_CHILDREN]
                return status_running
            node_status = self.tree_status
        elif ((node[POSITION_NODE_TYPE] == self.node_reactive_sequence) or (node[POSITION_NODE_TYPE] == self.node_reactive_fallback)):
            if self.tree_status == status_running:
                self.next_node = node[POSITION_NODE_CHILDREN]
                return status_running
            node_status = self.tree_status
        if (((self.tree[node[POSITION_NODE_PARENT]][POSITION_NODE_TYPE] == self.node_fallback) and (node_status == status_success)) or 
            ((self.tree[node[POSITION_NODE_PARENT]][POSITION_NODE_TYPE] == self.node_sequence) and (node_status == status_fail)) or 
            ((self.tree[node[POSITION_NODE_PARENT]][POSITION_NODE_TYPE] == self.node_reactive_fallback) and (node_status == status_success)) or 
            ((self.tree[node[POSITION_NODE_PARENT]][POSITION_NODE_TYPE] == self.node_reactive_sequence) and (node_status == status_fail)) or 
            ((self.is_decorator_node(self.tree[node[POSITION_NODE_PARENT]][POSITION_NODE_TYPE]) and (node_status != status_running))) or
            ((node[POSITION_NODE_SIBLING] == NODE_UNRELATED))):
            self.next_node = node[POSITION_NODE_PARENT]
            self.tree_status = node_status
        elif ((self.is_decorator_node(self.tree[node[POSITION_NODE_PARENT]][POSITION_NODE_TYPE]) and (node_status == status_running))):
            self.next_node = node[POSITION_NODE_DECORATOR_TARGET]
            self.tree_status = node_status
            print(node[POSITION_NODE_TYPE])
            if self.is_decorator_retry_node(node[POSITION_NODE_TYPE]):
                put = True
                for i in self.decorator_retry_depth:
                    if i[0] == node[POSITION_NODE_INDEX]:
                        put = False 
                if put:
                    self.decorator_retry_depth.append([node[POSITION_NODE_INDEX], 0])
                print(self.decorator_retry_depth)
        else:
            self.tree_status = status_running
            self.next_node = node[POSITION_NODE_SIBLING]
        if((len(self.decorator_retry_depth) > 0)):
            for i in self.decorator_retry_depth:
                if i[0] == node[POSITION_NODE_INDEX]:
                    i[1] += 1
        return status_running        
        
    def init_process(self, tree):
        self.tree = tree
        index = 0
        for i in range(len(tree)):
            if((tree[i][POSITION_NODE_TYPE] == self.node_condition) or
               (tree[i][POSITION_NODE_TYPE] == self.node_action) or
               (tree[i][POSITION_NODE_TYPE] == self.node_decorator_retry_until_successful) or
               (tree[i][POSITION_NODE_TYPE] == self.node_decorator_repeat) or
               (tree[i][POSITION_NODE_TYPE] == self.node_decorator_keep_running_until_failure) or
               (tree[i][POSITION_NODE_TYPE] == self.node_decorator_force_failure) or
               (tree[i][POSITION_NODE_TYPE] == self.node_decorator_force_success) or
               (tree[i][POSITION_NODE_TYPE] == self.node_decorator_inverter) or
               (tree[i][POSITION_NODE_TYPE] == self.node_decorator_timeout)):
                value = []
                for status in status_node:
                    status_tree = self.process_node(tree[i], status)
                    while((tree[self.next_node][POSITION_NODE_TYPE] != self.node_root) and
                          (tree[self.next_node][POSITION_NODE_TYPE] != self.node_condition) and
                          (tree[self.next_node][POSITION_NODE_TYPE] != self.node_action) and
                          (tree[self.next_node][POSITION_NODE_TYPE] != self.node_decorator_retry_until_successful) and
                          (tree[self.next_node][POSITION_NODE_TYPE] != self.node_decorator_repeat) and
                          (tree[self.next_node][POSITION_NODE_TYPE] != self.node_decorator_keep_running_until_failure) and
                          (tree[self.next_node][POSITION_NODE_TYPE] != self.node_decorator_force_failure) and 
                          (tree[self.next_node][POSITION_NODE_TYPE] != self.node_decorator_force_success) and 
                          (tree[self.next_node][POSITION_NODE_TYPE] != self.node_decorator_inverter) and 
                          (tree[self.next_node][POSITION_NODE_TYPE] != self.node_decorator_timeout) and 
                          (status_tree == status_running)):
                        self.process_node(tree[self.next_node], self.tree_status)
                    value.append(tree[self.next_node])
                    if (tree[self.next_node][POSITION_NODE_TYPE] == self.node_root):
                        value[-1] = NODE_UNRELATED
                if (tree[tree[i][POSITION_NODE_PARENT]][POSITION_NODE_REACTIVE]):
                    is_reactive = True
                else:
                    is_reactive = False
                if tree[i][POSITION_NODE_TYPE] == self.node_condition:
                    node_type = macro_node_reactive_condition if is_reactive else macro_node_condition
                    self.nodes_path.append([index, node_type, value[0], value[1], 
                                            tree[i][POSITION_NODE_FUNCTION], tree[i]])
                elif tree[i][POSITION_NODE_TYPE] == self.node_action:
                    node_type = macro_node_reactive_action if is_reactive else macro_node_action
                    self.nodes_path.append([index, node_type, value[0], value[1], 
                                            tree[i][POSITION_NODE_FUNCTION], tree[i]])
                elif tree[i][POSITION_NODE_TYPE] == self.node_decorator_retry_until_successful:
                    node_type = macro_node_reactive_retry_until_success if is_reactive else macro_node_retry_until_success
                    self.nodes_path.append([index, node_type, value[0], value[1], index + 1, 
                                            tree[i][POSITION_NODE_DECORATOR_NUM_ATTEMPTS], 
                                            tree[i][POSITION_NODE_DECORATOR_POINTER],
                                            tree[i][POSITION_NODE_DECORATOR_RETRY_DEPTH] + index, tree[i]])
                elif tree[i][POSITION_NODE_TYPE] == self.node_decorator_repeat:
                    node_type = macro_node_reactive_repeat if is_reactive else macro_node_repeat
                    self.nodes_path.append([index, node_type, value[0], value[1], index + 1, 
                                            tree[i][POSITION_NODE_DECORATOR_NUM_ATTEMPTS], 
                                            tree[i][POSITION_NODE_DECORATOR_POINTER], 
                                            tree[i][POSITION_NODE_DECORATOR_RETRY_DEPTH] + index, tree[i]])
                elif tree[i][POSITION_NODE_TYPE] == self.node_decorator_keep_running_until_failure:
                    node_type = macro_node_reactive_keep_running_until_failure if is_reactive else macro_node_keep_running_until_failure
                    self.nodes_path.append([index, node_type, value[0], value[1], 
                                            index + 1, tree[i][POSITION_NODE_DECORATOR_RETRY_DEPTH] + index, tree[i]])
                elif tree[i][POSITION_NODE_TYPE] == self.node_decorator_force_failure:
                    node_type = macro_node_reactive_force_failure if is_reactive else macro_node_force_failure
                    self.nodes_path.append([index, node_type, value[0], value[1], 
                                            index + 1, tree[i]])
                elif tree[i][POSITION_NODE_TYPE] == self.node_decorator_force_success:
                    node_type = macro_node_reactive_force_success if is_reactive else macro_node_force_success
                    self.nodes_path.append([index, node_type, value[0], value[1], 
                                            index + 1, tree[i]])
                elif tree[i][POSITION_NODE_TYPE] == self.node_decorator_inverter:
                    node_type = macro_node_reactive_inverter if is_reactive else macro_node_inverter
                    self.nodes_path.append([index, node_type, value[0], value[1], 
                                            index + 1, tree[i]])
                elif tree[i][POSITION_NODE_TYPE] == self.node_decorator_timeout:
                    node_type = macro_node_reactive_decorator_timeout if is_reactive else macro_node_decorator_timeout
                    self.nodes_path.append([index, node_type, value[0], value[1], 
                                            index + 1, tree[i][POSITION_NODE_DECORATOR_TIMEOUT_TIME], tree[i]])
                index += 1

        for i in range(len(self.nodes_path)):
            succes_case = False
            fail_case = False
            for j in range(len(self.nodes_path)):
                if((self.nodes_path[i][INDEX_SUCCESS_CASE] == self.nodes_path[j][INDEX_POINTER_VERIFY])):
                    self.nodes_path[i][INDEX_SUCCESS_CASE] = self.nodes_path[j][0]
                    succes_case = True
                if((self.nodes_path[i][INDEX_FAIL_CASE] == self.nodes_path[j][INDEX_POINTER_VERIFY])):
                    self.nodes_path[i][INDEX_FAIL_CASE] = self.nodes_path[j][0]
                    fail_case = True
                if((succes_case) and (fail_case)):
                    break

        for i in self.nodes_path:
            i.pop()

        return self.nodes_path