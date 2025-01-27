from array_creator import BT_ARRAY

node_root = 'Root'
node_sequence = 'Sequence'
node_fallback = 'Fallback'
node_reactive_sequence = 'ReactiveSequence'
node_reactive_fallback = 'ReactiveFallback'
node_action = 'Script'
node_condition = 'ScriptCondition'
node_subtree = 'SubTree'
node_decorator_attempts = 'RetryUntilSuccessful'
node_decorator_repeat = 'Repeat'
node_decorator_keep_running_until_failure = 'KeepRunningUntilFailure'
node_decorator_force_failure = 'ForceFailure'
node_decorator_force_success = 'ForceSuccess'
node_decorator_inverter = 'Inverter'
node_decorator_timeout = 'Timeout'
node_delay = 'Sleep'

folder = 'tree-examples'
main_tree = 'subtree'
project_id = ''
name = "Renilson Almeida"
email = "joserenilson.silva@edge.ufal.br"
version = "1.0"
copyrights = ""
project = "test"

x = BT_ARRAY()
x.set_archive_data(project_id, name, email, version, copyrights, project)
x.set_nodes_name(node_root, node_fallback, node_reactive_fallback, node_sequence, node_reactive_sequence,
                 node_action, node_condition, node_decorator_attempts, node_decorator_repeat,
                 node_decorator_keep_running_until_failure, node_decorator_force_failure,
                 node_decorator_force_success, node_decorator_inverter, node_decorator_timeout, node_delay, node_subtree)
x.create_trees(folder, main_tree)