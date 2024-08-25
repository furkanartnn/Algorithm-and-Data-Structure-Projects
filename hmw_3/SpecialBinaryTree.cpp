// SpecialBinaryTree.cpp
#include "SpecialBinaryTree.h"
#include "BinaryTreeNode.h"
#include <climits>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

SpecialBinaryTree::SpecialBinaryTree()
{
    root = nullptr;
}

SpecialBinaryTree::~SpecialBinaryTree()
{
	
}
BinaryTreeNode* SpecialBinaryTree::find_node(BinaryTreeNode* node, int value) {
    if (node == nullptr) {
        return nullptr; 
    }
    if (node->get_value() == value) {
        return node; 
    }
    // Recursively search in the left subtree
    BinaryTreeNode* left_result = find_node(node->get_left(), value);
    if (left_result != nullptr) {
        return left_result; 
    }
    // Recursively search in the right subtree
    BinaryTreeNode* right_result = find_node(node->get_right(), value);
    return right_result; 
}
bool SpecialBinaryTree::add_node(int new_value, int parent_value, bool is_left_child, bool is_right_child, bool is_root){

// create a root if tree is empty
    if (is_root) {
        if (root == nullptr) {
            root = new BinaryTreeNode();
            root->set_value(new_value);
            return true;
        } else {
            // if a root node already exists, operation is not allowed
            return false;
        }
    }

    // if tree is not empty
    if (root != nullptr) {
        if (find_node(root, new_value) != nullptr) {
            return false;
        }

        BinaryTreeNode* parent = find_node(root, parent_value);
        if (parent == nullptr || (is_left_child && is_right_child)) {
            return false;
        }

        if (is_left_child) {
            if (parent->get_left() != nullptr) {
                return false;
            }
            BinaryTreeNode* newNode = new BinaryTreeNode();
            newNode->set_value(new_value);
            parent->set_left(newNode);
            return true;
        } else if (is_right_child) {
            if (parent->get_right() != nullptr) {
                return false;
            }
            BinaryTreeNode* newNode = new BinaryTreeNode();
            newNode->set_value(new_value);
            parent->set_right(newNode);
            return true;
        }
    }

    return false;
}

bool SpecialBinaryTree::update_value(int previous_value, int new_value){	
	// check tree is empty
    if (root == nullptr || find_node(root, new_value) != nullptr) {
        return false;
    }

    stack<BinaryTreeNode*> node_stack;
    node_stack.push(root);

    while (!node_stack.empty()) {
        BinaryTreeNode* current = node_stack.top();
        node_stack.pop();

        if (current->get_value() == previous_value) {
            current->set_value(new_value);
            return true;
        }

        // Push the right child first because we want to traverse left child first
        if (current->get_right() != nullptr) {
            node_stack.push(current->get_right());
        }
        
        if (current->get_left() != nullptr) {
            node_stack.push(current->get_left());
        }
    }

    return false;
}

bool SpecialBinaryTree::remove_node(int value) {
    if (root == nullptr) {
        return false;
    }

    // Special case if root needs to be removed
    if (root->get_value() == value) {
        if (root->get_left() == nullptr && root->get_right() == nullptr) {
            delete root;
            root = nullptr;
        } else {
            // Replace root value with the rightmost child in the left subtree
            BinaryTreeNode* current = root;
            BinaryTreeNode* parent = nullptr;
            if (current->get_left() != nullptr) {
                parent = current;
                current = current->get_left();
                while (current->get_right() != nullptr) {
                    parent = current;
                    current = current->get_right();
                }
                root->set_value(current->get_value());
                if (parent->get_right() == current) {
                    parent->set_right(current->get_left());
                } else {
                    parent->set_left(current->get_left());
                }
                delete current;
            } else {
                // Replace root with right child if left child is absent
                BinaryTreeNode* temp = root;
                root = root->get_right();
                delete temp;
            }
        }
        return true;
    }

    queue<BinaryTreeNode*> node_queue;
    node_queue.push(root);
    BinaryTreeNode* target_parent = nullptr;
    BinaryTreeNode* target_node = nullptr;

    while (!node_queue.empty()) {
        BinaryTreeNode* current = node_queue.front();
        node_queue.pop();

        if (current->get_left() != nullptr) {
            if (current->get_left()->get_value() == value) {
                target_parent = current;
                target_node = current->get_left();
                break;
            }
            node_queue.push(current->get_left());
        }

        if (current->get_right() != nullptr) {
            if (current->get_right()->get_value() == value) {
                target_parent = current;
                target_node = current->get_right();
                break;
            }
            node_queue.push(current->get_right());
        }
    }

    if (target_node == nullptr) {
        return false;
    }

    // Case where target node is a leaf node
    if (target_node->get_left() == nullptr && target_node->get_right() == nullptr) {
        if (target_parent->get_left() == target_node) {
            target_parent->set_left(nullptr);
        } else {
            target_parent->set_right(nullptr);
        }
        delete target_node;
        return true;
    }

    // Case where target node has children
    BinaryTreeNode* replacement = target_node;
    BinaryTreeNode* replacement_parent = target_node;
    if (target_node->get_left() != nullptr) {
        replacement = target_node->get_left();
        while (replacement->get_right() != nullptr) {
            replacement_parent = replacement;
            replacement = replacement->get_right();
        }
        target_node->set_value(replacement->get_value());
        if (replacement_parent->get_right() == replacement) {
            replacement_parent->set_right(replacement->get_left());
        } else {
            replacement_parent->set_left(replacement->get_left());
        }
    } else {
        replacement = target_node->get_right();
        while (replacement->get_left() != nullptr) {
            replacement_parent = replacement;
            replacement = replacement->get_left();
        }
        target_node->set_value(replacement->get_value());
        if (replacement_parent->get_left() == replacement) {
            replacement_parent->set_left(replacement->get_right());
        } else {
            replacement_parent->set_right(replacement->get_right());
        }
    }

    delete replacement;
    return true;
}


int SpecialBinaryTree::is_leaf_node(int value){
	// if tree is empty
	if (root == nullptr) {
        return -1;
    }
    
    // Queue for BFS
    queue<BinaryTreeNode*> node_queue;
    node_queue.push(root);
    
    // BFS
    while (!node_queue.empty()) {
        BinaryTreeNode* current = node_queue.front();
        node_queue.pop();
        
        if (current->get_value() == value) {
            // Check if it is a leaf node or not
            if (current->get_left() == nullptr && current->get_right() == nullptr) {
                return 1; // Leaf node
            } else {
                return 0; // Not a leaf node
            }
        }
        
        // Add left child
        if (current->get_left() != nullptr) {
            node_queue.push(current->get_left());
        }
        
        // Add right child
        if (current->get_right() != nullptr) {
            node_queue.push(current->get_right());
        }
    }
    
    return -1; // Value not found in the tree
}

bool SpecialBinaryTree::does_exist_in_subtree(int subtree_root_value, int value_to_search){
    if (root == nullptr) {
        return false;
    }
    
    // Queue for BFS
    queue<BinaryTreeNode*> node_queue;
    node_queue.push(root);
    
    BinaryTreeNode* subtree_root = nullptr;
    
    // Find the subtree root node
    while (!node_queue.empty()) {
        BinaryTreeNode* current = node_queue.front();
        node_queue.pop();
        
        if (current->get_value() == subtree_root_value) {
            subtree_root = current;
            break;
        }
        
        if (current->get_left() != nullptr) {
            node_queue.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            node_queue.push(current->get_right());
        }
    }
    
    // Subtree root is not found
    if (subtree_root == nullptr) {
        return false;
    }
        
    // Search in the subtree
    node_queue.push(subtree_root);
    
    // Search for the value in the subtree
    while (!node_queue.empty()) {
        BinaryTreeNode* current = node_queue.front();
        node_queue.pop();
        
        if (current->get_value() == value_to_search) {
            return true;
        }
        
        if (current->get_left() != nullptr) {
            node_queue.push(current->get_left());
        }
        
        if (current->get_right() != nullptr) {
            node_queue.push(current->get_right());
        }
    }
    
    return false;
}

int SpecialBinaryTree::find_depth(int value){
	
    if (root == nullptr) {
        return -1;
    }

    queue<pair<BinaryTreeNode*, int>> node_queue;
    node_queue.push({root, 0});

    while (!node_queue.empty()) {
        auto [current, depth] = node_queue.front(); 
        node_queue.pop();

        if (current->get_value() == value) {
            return depth;
        }

        if (current->get_left() != nullptr) {
            node_queue.push({current->get_left(), depth + 1});
        }

        if (current->get_right() != nullptr) {
            node_queue.push({current->get_right(), depth + 1});
        }
    }

    return -1; 
}

int SpecialBinaryTree::find_height(int value) {
    if (root == nullptr) {
        return -1;
    }
    
    // Find the node
    BinaryTreeNode* node = find_node(root, value);
    
    if (node == nullptr) {
        return -1;
    }
    
    return calculate_height(node);
}

// Define recursive function
int SpecialBinaryTree::calculate_height(BinaryTreeNode* node) {
    if (node == nullptr) {
        return -1;
    }
    
    int left_height = calculate_height(node->get_left());
    int right_height = calculate_height(node->get_right());
    
    return max(left_height, right_height) + 1;
}

void SpecialBinaryTree::preorder_traversal(){
	
	if (root == nullptr) {
        cout << "There is no node in the tree." << endl;
        return;
    }
    
    // Create a stack 
    stack<BinaryTreeNode*> node_stack;
    node_stack.push(root);
    
    // Root-Left-Right 
    while (!node_stack.empty()) {
        BinaryTreeNode* current = node_stack.top();
        node_stack.pop(); 
        
        cout << current->get_value() << " ";
        
        // Push right first because of the stack rule
        if (current->get_right() != nullptr) {
            node_stack.push(current->get_right());
        }
        if (current->get_left() != nullptr) {
            node_stack.push(current->get_left());
        }
    }
    cout << endl; 
}


void SpecialBinaryTree::postorder_traversal(){
	
    if (root == nullptr) {
        cout << "There is no node in the tree." << endl;
        return;
    }

    stack<BinaryTreeNode*> node_stack;
    stack<BinaryTreeNode*> result_stack;
    node_stack.push(root);

    // Iterate until the stack is empty
    while (!node_stack.empty()) {
        BinaryTreeNode* current = node_stack.top();
        node_stack.pop();
        result_stack.push(current);

        
        // Push left child to the stack
        if (current->get_left() != nullptr) {
            node_stack.push(current->get_left());
        }
        // Push right child first to process it before the left child
        if (current->get_right() != nullptr) {
            node_stack.push(current->get_right());
        }
    }

    // Print nodes from result_stack which gives postorder traversal
    while (!result_stack.empty()) {
        cout << result_stack.top()->get_value() << " ";
        result_stack.pop();
    }
    cout << endl;
}


void SpecialBinaryTree::inorder_traversal(){
	
	if (root == nullptr) {
        cout << "There is no node in the tree." << endl;
        return;
    }

    stack<BinaryTreeNode*> node_stack;
    BinaryTreeNode* current = root;

    while (current != nullptr || !node_stack.empty()) {

        while (current != nullptr) {
            node_stack.push(current);
            current = current->get_left();
        }

        current = node_stack.top();
        node_stack.pop();
        cout << current->get_value() << " "; 

        current = current->get_right();
    }

    cout << endl; 
}

int SpecialBinaryTree::find_sum_of_values_in_subtree(int subtree_root_val)
{
	if (root == nullptr) {
        return -1; 
    }   
    
    BinaryTreeNode* subtree_root = find_node(root, subtree_root_val);
    
    if (subtree_root == nullptr) {
        return -1; 
    }
    
    stack<BinaryTreeNode*> node_stack;
    node_stack.push(subtree_root);
    int sum = 0;
    
    while (!node_stack.empty()) {
        BinaryTreeNode* current = node_stack.top();
        node_stack.pop();
        sum += current->get_value();
        
        if (current->get_right() != nullptr) {
            node_stack.push(current->get_right());
        }
        if (current->get_left() != nullptr) { 
            node_stack.push(current->get_left());
        }
    }
    return sum;   
}

int SpecialBinaryTree::find_minimum_value_in_subtree(int subtree_root_val)
{
    if (root == nullptr) {
        return -1; 
    }
    
    BinaryTreeNode* subtree_root = find_node(root, subtree_root_val);
    if (subtree_root == nullptr) {
        return -1; 
    }
    
    stack<BinaryTreeNode*> node_stack;
    node_stack.push(subtree_root);
    int min_value = subtree_root->get_value(); 
    
    while (!node_stack.empty()) {
        BinaryTreeNode* current = node_stack.top();
        node_stack.pop();
        

        if (current->get_value() < min_value) {
            min_value = current->get_value();
        }
        

        if (current->get_right() != nullptr) {
            node_stack.push(current->get_right());
        }
        if (current->get_left() != nullptr) {
            node_stack.push(current->get_left());
        }
    }
    
    return min_value;
}

int SpecialBinaryTree::find_maximum_value_in_subtree(int subtree_root_val){
	
    if (root == nullptr) {
        return -1; 
    }
    
    BinaryTreeNode* subtree_root = find_node(root, subtree_root_val);
    
    if (subtree_root == nullptr) {
        return -1; 
    }
    
    stack<BinaryTreeNode*> node_stack;
    node_stack.push(subtree_root);
    int max_value = subtree_root->get_value(); 
    
    while (!node_stack.empty()) {
        BinaryTreeNode* current = node_stack.top();
        node_stack.pop();
        

        if (current->get_value() > max_value) {
            max_value = current->get_value();
        }
        
        
        if (current->get_right() != nullptr) {
            node_stack.push(current->get_right());
        }
        if (current->get_left() != nullptr) {
            node_stack.push(current->get_left());
        }
    }
    
    return max_value;
}



