#Behavior Tree like Tree.
INDEX_NODE_TYPE = 1
INDEX_NODE_CHILDREN = 2
INDEX_NODE_SIBLING = 3
INDEX_NODE_PARENT = 4
INDEX_NODE_FUNCTION = 2

#Tree like DAG
INDEX_SUCCESS_CASE = 3
INDEX_FAIL_CASE = 4
INDEX_NEXT_CONDITION = 5

#Node invalid
NODE_UNRELATED = "BT_DEFINITION_TREE_UNRELATED"

#Macros of nodes
macro_node_condition = "BT_DEFINITION_CREATE_NODE_CONDITION"
macro_node_action = "BT_DEFINITION_CREATE_NODE_ACTION"

#Status of nodes
status_node = [ 'success', 'fail']
status_fail = 'fail'
status_success = 'success'
status_running = 'Running'

class BT_EXECUTE:
    def __init__(self):
        self.node_root = 'Root'
        self.node_sequence = 'Sequence'
        self.node_fallback = 'Fallback'
        self.node_action = 'Script'
        self.node_condition = 'ScriptCondition'
        self.node_subtree = 'SubTree'
        self.tree_status = status_running
        self.next_node = 0
        self.nodes_path = []

    def get_nodes_name(self, node_root, node_fallback = None, node_sequence = None, node_action = None, node_condition = None, node_decorator_attempts = None, node_delay = None, node_subtree = None):
        self.node_root = node_root
        self.node_fallback = node_fallback
        self.node_sequence = node_sequence
        self.node_action = node_action
        self.node_condition = node_condition
        self.node_decorator_attempts = node_decorator_attempts
        self.node_delay = node_delay
        self.node_subtree = node_subtree

    def process_node(self, node, node_status):
        if node[INDEX_NODE_TYPE] == self.node_root:
            if((self.tree_status == status_success) or (self.tree_status == status_fail)):
                return self.tree_status
            self.next_node = node[INDEX_NODE_SIBLING]
        elif ((node[INDEX_NODE_TYPE] == self.node_sequence) or (node[INDEX_NODE_TYPE] == self.node_fallback)):
            if self.tree_status == status_running:
                self.next_node = node[INDEX_NODE_CHILDREN]
                return status_running
            node_status = self.tree_status
        if (((self.tree[node[INDEX_NODE_PARENT]][INDEX_NODE_TYPE] == self.node_fallback) and (node_status == status_success)) or 
            ((self.tree[node[INDEX_NODE_PARENT]][INDEX_NODE_TYPE] == self.node_sequence) and (node_status == status_fail)) or 
            ((node[INDEX_NODE_SIBLING] == NODE_UNRELATED))) :
            self.next_node = node[INDEX_NODE_PARENT]
            self.tree_status = node_status
        else:            
            self.tree_status = status_running
            self.next_node = node[INDEX_NODE_SIBLING]
        return status_running        
        
    def init_process(self, tree):
        self.tree = tree
        index = 0
        for i in range(len(tree)):
            if((tree[i][INDEX_NODE_TYPE] == self.node_condition) or
               (tree[i][INDEX_NODE_TYPE] == self.node_action)):
                is_condition = True if tree[i][INDEX_NODE_TYPE] == self.node_condition else False
                next_condition = NODE_UNRELATED
                value = []
                for status in status_node:
                    status_tree = self.process_node(tree[i], status)
                    while((tree[self.next_node][INDEX_NODE_TYPE] != self.node_root) and
                          (tree[self.next_node][INDEX_NODE_TYPE] != self.node_condition) and
                          (tree[self.next_node][INDEX_NODE_TYPE] != self.node_action) and
                          (status_tree == status_running)):
                        self.process_node(tree[self.next_node], self.tree_status)
                    if ((is_condition) and (tree[self.next_node][INDEX_NODE_TYPE] == self.node_condition)):
                        next_condition = tree[self.next_node][INDEX_NODE_FUNCTION]
                    value.append(self.next_node)
                if tree[i][INDEX_NODE_TYPE] == self.node_condition:
                    node_type = macro_node_condition
                    self.nodes_path.append([index, node_type, tree[i][INDEX_NODE_FUNCTION], tree[value[0]][INDEX_NODE_FUNCTION], 
                                            tree[value[1]][INDEX_NODE_FUNCTION], next_condition])
                elif tree[i][INDEX_NODE_TYPE] == self.node_action:
                    node_type = macro_node_action
                    self.nodes_path.append([index, node_type, tree[i][INDEX_NODE_FUNCTION], tree[value[0]][INDEX_NODE_FUNCTION], 
                                            tree[value[1]][INDEX_NODE_FUNCTION]])
                index += 1
        
        for i in range(len(self.nodes_path)):
            succes_case = False
            fail_case = False
            condition_whitout_next_condition = True
            if ((self.nodes_path[i][INDEX_NODE_TYPE] == macro_node_condition) and
                (self.nodes_path[i][INDEX_NEXT_CONDITION] != NODE_UNRELATED)):
                condition_whitout_next_condition =  False
            for j in range(len(self.nodes_path)):
                if(self.nodes_path[i][INDEX_SUCCESS_CASE] == self.nodes_path[j][INDEX_NODE_FUNCTION]):
                    self.nodes_path[i][INDEX_SUCCESS_CASE] = self.nodes_path[j][0]
                    succes_case = True
                if(self.nodes_path[i][INDEX_FAIL_CASE] == self.nodes_path[j][INDEX_NODE_FUNCTION]):
                    self.nodes_path[i][INDEX_FAIL_CASE] = self.nodes_path[j][0]
                    fail_case = True
                if((not condition_whitout_next_condition) and (self.nodes_path[i][INDEX_NEXT_CONDITION] == self.nodes_path[j][INDEX_NODE_FUNCTION])):
                    self.nodes_path[i][INDEX_NEXT_CONDITION] = self.nodes_path[j][0]
                    condition_whitout_next_condition = True
                if((succes_case) and (fail_case) and (condition_whitout_next_condition)):
                    break

        return self.nodes_path