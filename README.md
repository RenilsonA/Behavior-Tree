# Behavior Tree for Embedded Systems

This project presents an optimized approach for using Behavior Trees (BTs) in embedded systems. The focus is on facilitating the development and organization of repetitive tasks in resource-constrained control environments.

# Minimum Behavior Graph

To optimize the number of processed nodes and memory in embedded systems, this implementation proposes the **Minimum Behavior Graph**. This is a simplified representation of the conventional behavior tree, which converts the tree's structure into a directed graph. The goal is to allow the system to operate more directly, eliminating unnecessary queries and optimizing the execution of complex behaviors, especially when switching between branches.

# Examples and Usage

The developed application examples demonstrate the solution's viability and efficiency in different scenarios. These tests were performed using **MicriumOS** with **SimplicityIDE** for the **DevKit EFR32xG24-DK2601B**, and **FreeRTOS** for the **ESP32 WROOM-32**. Within the examples, there is a folder named "**Trees**", which contains an XML file and some execution images of the same.

* **ble-wifi**: Simple execution of a non-reactive behavior tree, initiating the Bluetooth application and waiting for the network SSID and password credentials to be sent.
* **btree-example-subtree**: Example of two reactive trees executing in parallel.
* **btree-long-tree**: Example of a non-reactive tree with over 200 nodes.
* **btree-msgs**: Example of a Bluetooth application that waits for a message with content "led" or "print \"message content\"" to execute actions. It runs without reactivity, but the images include the reactive approach.

# Comparison Tests

Additionally, comparisons were made with the **BehaviorTree.CPP** library for validation. These tests are located in the "**BehaviorTree.CPP**" folder and correspond to the three examples from the DevKit EFR32xG24-DK2601B, disregarding reactivity.