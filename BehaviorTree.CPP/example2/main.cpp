#include <behaviortree_cpp/bt_factory.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include <cstdlib>
#include <ctime>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>

using namespace BT;

int buffer_index = 0;
NodeStatus buffer[16] = {NodeStatus::SUCCESS, NodeStatus::FAILURE, NodeStatus::SUCCESS, NodeStatus::SUCCESS, NodeStatus::FAILURE,
                        NodeStatus::SUCCESS, NodeStatus::FAILURE, NodeStatus::FAILURE, NodeStatus::FAILURE, NodeStatus::SUCCESS,
                        NodeStatus::FAILURE, NodeStatus::SUCCESS, NodeStatus::FAILURE, NodeStatus::SUCCESS, NodeStatus::FAILURE,
                        NodeStatus::FAILURE};

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
        NodeStatus state = buffer[buffer_index];
        buffer_index += 1;

        if(buffer_index >= 16)
        {
            buffer_index = 0;
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

        std::cout << "                                                           [" << code << "] " << state << "\n";
        return state;
    }
};
}

int main()
{
    BehaviorTreeFactory factory;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    factory.registerNodeType<CustomNodes::ScriptCondition>("MyScriptCondition");
    factory.registerNodeType<CustomNodes::ScriptAction>("MyScript");

    std::ifstream xml_file("msgs.xml");
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



    BT::StdCoutLogger logger(tree);

    std::cout << "Executando árvore...\n";

    while (tree.tickOnce() == NodeStatus::RUNNING) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Execução finalizada.\n";
    return 0;
}
