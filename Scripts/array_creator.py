import os
import bt_execute
import xml.etree.ElementTree as ET
from library_creator import ARCHIVE_CREATOR

class BT_ARRAY:
    def __init__(self):
        self.node_root = 'Root'
        self.node_fallback = 'Fallback'
        self.node_sequence = 'Sequence'
        self.node_action = 'Script'
        self.node_condition = 'ScriptCondition'
        self.node_decorator_attempts = 'RetryUntilSuccessful'
        self.node_delay = 'Sleep'
        self.node_subtree = 'SubTree'
        self.is_node_root_main = False
        self.node_number = 0
        self.subtree_root_data = ["BT_DEFINITION_TREE_UNRELATED", "BT_DEFINITION_TREE_UNRELATED"]
        self.tree_id = 0
        self.tree_index = 0
        self.main_tree = ""
        self.tree_archive = None
        self.archives = []
        self.texts = []
        self.tree = []
        self.functions = []
        self.tree_function_index = 0
        self.node_index_invalid = 'TC_BHT_DEFINITION_TREE_UNRELATED'
        self.attempts = 0
        self.attempts_max = 0
        self.tree_remodeled_size = 0
        self.folder = ""        
        self.library = ARCHIVE_CREATOR()

    def get_max_attempts(self):
        return self.max_attempts_nodes

    def set_archive_data(self, project_id = None, name = None, email = None, version = None, copyrights = None, project = None):
        self.library.set_text(project_id=project_id, name=name, email=email, version=version, copyrights=copyrights, project=project)

    def set_nodes_name(self, node_root = None, node_fallback = None, node_sequence = None, node_action = None, node_condition = None, 
                       node_decorator_attempts = None, node_delay = None, node_subtree = None):
        self.node_root = node_root
        self.node_fallback = node_fallback
        self.node_sequence = node_sequence
        self.node_action = node_action
        self.node_condition = node_condition
        self.node_decorator_attempts = node_decorator_attempts
        self.node_delay = node_delay
        self.node_subtree = node_subtree

    def set_sibling(self):
        for i in range(1, len(self.tree)):
            sibling_index = "BT_DEFINITION_TREE_UNRELATED"
            parent_index = self.tree[i][0]
            for j in range(len(self.tree) - 1, i, -1):
                if parent_index == self.tree[j][-1]:
                    self.tree[j][-2] = sibling_index
                    sibling_index = self.tree[j][0]

    def mount_nodes(self, element, node_parent_number):
        global attempts
        global attempts_max
        self.node_number += 1

        is_decoration_attempts = False

        if self.node_fallback == element.tag:
            self.tree.append([self.node_number, self.node_fallback, self.node_number + 1, "BT_DEFINITION_TREE_UNRELATED", node_parent_number])
            node_parent_number = self.node_number

        elif self.node_sequence == element.tag:
            self.tree.append([self.node_number, self.node_sequence, self.node_number + 1, "BT_DEFINITION_TREE_UNRELATED", node_parent_number])
            node_parent_number = self.node_number

        elif self.node_action == element.tag:
            self.tree.append([self.node_number, self.node_action, f"bt_{self.archives[self.tree_function_index].lower()}_" + element.get('code'), 
                              "BT_DEFINITION_TREE_UNRELATED", node_parent_number])
            node_parent_number -= 1
            if not element.get('code') in self.functions:
                self.functions[self.tree_function_index].append(element.get('code'))

        elif self.node_condition == element.tag:
            self.tree.append([self.node_number, self.node_condition, f"bt_{self.archives[self.tree_function_index].lower()}_" + element.get('code'), 
                              "BT_DEFINITION_TREE_UNRELATED", node_parent_number])
            node_parent_number -= 1
            if not element.get('code') in self.functions:
                self.functions[self.tree_function_index].append(element.get('code'))

        elif self.node_decorator_attempts == element.tag:
            self.tree.append([self.node_number, self.node_decorator_attempts, "BT_DEFINITION_TREE_UNRELATED", element.get('num_attempts'), 
                              f'&tc_{self.library.project.lower()}_bht_commom_attempts[{attempts}]', "BT_DEFINITION_TREE_UNRELATED",  node_parent_number])
            node_parent_number = self.node_number
            self.attempts += 1
            is_decoration_attempts = True
            if self.attempts > attempts_max:
                attempts_max = self.attempts

        elif self.node_delay == element.tag:
            self.tree.append([self.node_number, self.node_delay, element.get('msec'), "BT_DEFINITION_TREE_UNRELATED",  node_parent_number])
            node_parent_number = self.node_number

        elif self.node_subtree == element.tag:
            self.node_number -= 1
            root = self.tree_archive.getroot()
            for behavior_tree in root.findall('BehaviorTree'):
                tree_id = behavior_tree.get('ID')
                if tree_id == element.get('ID'):
                    self.tree_function_index += 1
                    self.archives.append(tree_id)
                    self.functions.append([])
                    self.mount_nodes(behavior_tree, node_parent_number)
                    self.tree_function_index -= 1
        
        elif self.is_node_root_main == False:
            self.node_number = 0
            self.is_node_root_main = True
            self.tree.append([self.node_number, self.node_root, self.subtree_root_data[0], 1, self.subtree_root_data[1]])

        else:
            self.node_number -= 1

        for child in element:
            self.mount_nodes(child, node_parent_number)

        if is_decoration_attempts:
            self.attempts -= 1

    def open_xml(self, archive):
        self.tree_archive = ET.parse(archive)
        root = self.tree_archive.getroot()
        for behavior_tree in root.findall('BehaviorTree'):
            self.tree_id = behavior_tree.get('ID')
            if self.tree_id == self.main_tree:
                self.functions.clear()
                if self.tree_id in self.archives:
                    elements = [element for element in self.archives]
                    elements_count = len(elements)
                    self.tree_id += str(elements_count)
                    self.archives.append(self.tree_id)
                else:
                    self.archives.append(self.tree_id)
                self.functions.append([])
                self.mount_nodes(behavior_tree, 0)
                self.set_sibling()
                x = bt_execute.BT_EXECUTE()
                tree_remodeled = x.init_process(self.tree)
                text = self.library.tree_vector(self.tree_id, tree_remodeled)
                self.tree_remodeled_size = len(tree_remodeled)
                self.tree.clear()
                self.texts.append(text)

    def load_archives(self):
        trees = os.listdir(self.folder)
        for archive in trees:
            self.open_xml(f"{self.folder}/{archive}")

    def process_tree(self, folder, id, parent_tree, local_parent_tree):
        self.folder = folder
        self.main_tree = id
        self.subtree_root_data[0] = parent_tree
        self.subtree_root_data[1] = local_parent_tree
        self.load_archives()

    def create_trees(self, folder = None, main_tree = None):
        self.folder = folder if folder != None else input("Put archive folder:")
        self.main_tree = main_tree if main_tree != None else input("Put your main tree:")
        self.load_archives()
        self.library.generate_archives(self.archives, self.texts, self.functions, self.attempts_max, self.tree_remodeled_size)
        self.max_attempts_nodes = 0