#include <behaviortree_cpp/bt_factory.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>

using namespace BT;

static std::unordered_map<std::string, int> counters;
static std::unordered_map<std::string, bool> action_executed;

static int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0;
static int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0, a8 = 0, a9 = 0, a10 = 0, a11 = 0;

namespace CustomNodes
{

class ScriptCondition : public BT::ConditionNode
{
public:
    ScriptCondition(const std::string& name, const BT::NodeConfig& config)
        : BT::ConditionNode(name, config) {}

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("code") };
    }

    BT::NodeStatus tick() override
    {
        auto res = getInput<std::string>("code");
        if (!res)
        {
            throw BT::RuntimeError("Missing parameter [code] in ScriptCondition");
        }

        const std::string& code = res.value();
        NodeStatus state;

        if (code == "condition1") {
            c1++;
            state = (c1 >= 20) ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
        } else if (code == "condition2") {
            state = (c2 != 0) ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
        } else if (code == "condition4") {
            state = (c4 != 0) ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
        } else if (code == "condition5") {
            state = NodeStatus::FAILURE;
        } else if (code == "condition6") {
            state = (c6 != 0) ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
        } else if (code == "condition7") {
            state = NodeStatus::SUCCESS;
        } else {
            std::cerr << "                                                           [" << name() << "] " << code << "\n";
            state = NodeStatus::FAILURE;
        }

        std::cout << "                                                           [" << code << "] " << state << "\n";
        return state;
    }
};

class ScriptAction : public BT::SyncActionNode
{
public:
    ScriptAction(const std::string& name, const BT::NodeConfig& config)
        : BT::SyncActionNode(name, config) {}

    static BT::PortsList providedPorts()
    {
        return { BT::InputPort<std::string>("code") };
    }

    BT::NodeStatus tick() override
    {
        auto res = getInput<std::string>("code");
        if (!res)
        {
            throw BT::RuntimeError("Missing parameter [code] in ScriptAction");
        }

        const std::string& code = res.value();
        NodeStatus state;
        state = NodeStatus::SUCCESS;

        if (code == "action1") {
        } else if (code == "action2") {
            state = NodeStatus::FAILURE;
        } else if (code == "action3") {
            c2 = 1;
        } else if (code == "action4") {
            c4 = 1;
        } else if (code == "action5") {
        } else if (code == "action6") {
            c6 = 1;
            state = NodeStatus::FAILURE;
        } else if (code == "action7") {
        } else if (code == "actio8") {
        } else if (code == "action9") {
        } else if (code == "action10") {
        } else if (code == "action11") {
        } else {
            std::cerr << "                                                           [" << name() << "] " << code << "\n";
            state = NodeStatus::FAILURE;
        }

        std::cout << "                                                           [" << code << "] " << state << "\n";
        return state;
    }
};
}

int main()
{
    BehaviorTreeFactory factory;
    factory.registerNodeType<CustomNodes::ScriptCondition>("MyScriptCondition");
    factory.registerNodeType<CustomNodes::ScriptAction>("MyScript");

    std::ifstream xml_file("simple.xml");
    if (!xml_file.is_open()) {
        std::cerr << "Erro ao abrir simple.xml\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << xml_file.rdbuf();
    std::string xml_content = buffer.str();

    Tree tree;
    try {
        tree = factory.createTreeFromText(xml_content);
    } catch (const std::exception& e) {
        std::cerr << "Erro ao criar árvore: " << e.what() << "\n";
        return 1;
    }

    // BT::StdCoutLogger logger(tree);

    std::cout << "Executando árvore...\n";

    while (tree.tickOnce() == NodeStatus::RUNNING) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Execução finalizada.\n";
    return 0;
}
