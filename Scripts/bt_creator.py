from array_creator import BT_ARRAY

node_root = 'Root'
node_sequence = 'Sequence'
node_fallback = 'Fallback'
node_action = 'Script'
node_condition = 'ScriptCondition'
node_subtree = 'SubTree'
node_decorator_attempts = 'RetryUntilSuccessful'
node_delay = 'Sleep'

folder = 'tree-examples'
main_tree = 'example'
project_id =''
name = "Renilson Almeida"
email = "joserenilson.silva@edge.ufal.br"
version = "1.0"
copyrights = ""
project = "test"

x = BT_ARRAY()
x.set_archive_data(project_id, name, email, version, copyrights, project)
x.set_nodes_name(node_root, node_fallback, node_sequence, node_action, node_condition, node_decorator_attempts, node_delay, node_subtree)
x.create_trees(folder, main_tree)