#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

using namespace std;


// ----------------------------------------------


/**
 * @class Bst
 * @brief Binary Search Tree
 *
 * @author Li Weihao
 * @version 01
 * @date 05/07/2026 Weihao Started
 */

template <class T>
class Bst
{
public:
    typedef void (*VisitFunction)(T& data);

    /**
     * @brief   Constructor
     */
    Bst();

    /**
     * @brief   Creates a deep copy of another BST
     * @param   other - the other BST to copy
     */
    Bst(const Bst<T>& other);

    /**
     * @brief   Destructor
     */
    ~Bst();

    /**
     * @brief   Assignment operator
     * @param   other - the other BST to copy
     */
    Bst<T>& operator=(const Bst<T>& other);

    /**
     * @brief   Inserts data into the BST. Returns false for duplicates
     * @param   data - data to be inserted
     */
    bool Insert(const T& data);

    /**
     * @brief   Searches for data in the BST
     * @param   data - data to be searched
     */
    bool Search(const T& data) const;

    /**
     * @brief   Prints the BST using in-order traversal
     * @param   visit - for printing the traversal result
     */
    void InOrder(VisitFunction visit) const;

    /**
     * @brief   Prints the BST using pre-order traversal
     * @param   visit - for printing the traversal result
     */
    void PreOrder(VisitFunction visit) const;

    /**
     * @brief   Prints the BST using post-order traversal
     * @param   visit - for printing the traversal result
     */
    void PostOrder(VisitFunction visit) const;

    /**
     * @brief   Copies the BST data into a Vector using in-order traversal
     * @param   data - Vector used to store copied tree data
     */
    void ToVector(Vector<T>& data) const;

    /**
     * @brief   Debug check for the BST representation invariant
     */
    bool IsValidBST() const;

private:

    /**
     * @brief   Struct containing the Node data
     */
    struct Node
    {
        T data;
        Node* lLink;
        Node* rLink;

        Node(const T& value);
    };

    /// Single node represented through a struct
    Node* m_root;

    /**
     * @brief   Delete the tree recursively and free up the memory
     * @param   node - Tree/Subtree Root node
     */
    void Delete(Node*& node);

    /**
     * @brief   Deep Copy recursive helper method
     * @param   node - Root node
     */
    Node* Copy(Node* node) const;


    /**
     * @brief   Adds a new node to the tree
     * @param   node - a single node data
     * @param   data - data to be stored
     */
    bool Insert(Node*& node, const T& data);

    /**
     * @brief   Search a node in the tree
     * @param   node - a single node data
     * @param   data - data to be stored
     */
    bool Search(Node* node, const T& data) const;


    /**
     * @brief   Print nodes recursively in order of Smallest to Largest
     * @param   out - for printing the traversal result
     */
    void InOrder(Node* node, VisitFunction visit) const;

    /**
     * @brief   Print nodes recursively, this-left-right
     * @param   out - for printing the traversal result
     */
    void PreOrder(Node* node, VisitFunction visit) const;

    /**
     * @brief   Print nodes recursively, left-right-this
     * @param   out - for printing the traversal result
     */
    void PostOrder(Node* node, VisitFunction visit) const;

    /**
     * @brief   Copies a subtree into a Vector using in-order traversal
     * @param   node - root of the subtree to copy
     * @param   data - Vector used to store copied tree data
     */
    void ToVector(Node* node, Vector<T>& data) const;

    /**
     * @brief   Checks that the BST is ordered correctly
     * @param   node - a single node data
     * @param   minValue - smallest value in the tree
     * @param   maxValue - largest value in the tree
     */
    bool IsValidBST(Node* node, const T* minValue, const T* maxValue) const;

};


// ----------------------------------------------


// Struct construction
template <class T>
Bst<T>::Node::Node(const T& value) : data(value), lLink(nullptr), rLink(nullptr)
{
}

// Constructor
template <class T>
Bst<T>::Bst() : m_root(nullptr)
{
}

// Copy constructor
template <class T>
Bst<T>::Bst(const Bst<T>& other) : m_root(nullptr)
{
    m_root = Copy(other.m_root);
}

// Destructor
template <class T>
Bst<T>::~Bst()
{
    Delete(m_root);
}

// Assignment operator override
template <class T>
Bst<T>& Bst<T>::operator=(const Bst<T>& other)
{
    if (this != &other)
    {
        Delete(m_root);
        m_root = Copy(other.m_root);
    }

    return *this;
}


// Insert (Public)
template <class T>
bool Bst<T>::Insert(const T& data)
{
    return Insert(m_root, data);
}

// Insert (Private recursive)
template <class T>
bool Bst<T>::Insert(Node*& node, const T& data)
{
    // if root node is null, insert as root node
    if (node == nullptr)
    {
        node = new Node(data);
        return true;
    }

    // Left subtree
    if (data < node->data)
    {
        return Insert(node->lLink, data);
    }
    // Right subtree
    else if (node->data < data)
    {
        return Insert(node->rLink, data);
    }

    return false; // duplicate value
}


// Search for a node (Public)
template <class T>
bool Bst<T>::Search(const T& data) const
{
    return Search(m_root, data);
}

// Search for a node (Private recursive)
template <class T>
bool Bst<T>::Search(Node* node, const T& data) const
{
    // return false if root node is empty
    if (node == nullptr)
    {
        return false;
    }

    // left subtree
    if (data < node->data)
    {
        return Search(node->lLink, data);
    }
    // right subtree
    else if (node->data < data)
    {
        return Search(node->rLink, data);
    }

    return true;
}


// In-order traversal (Public)
template <class T>
void Bst<T>::InOrder(VisitFunction visit) const
{
    InOrder(m_root, visit);
}

// In-order traversal (Private recursive)
template <class T>
void Bst<T>::InOrder(Node* node, VisitFunction visit) const
{
    if (node != nullptr)
    {
        InOrder(node->lLink, visit);
        visit(node->data);
        InOrder(node->rLink, visit);
    }
}

// Pre-order traversal (Public)
template <class T>
void Bst<T>::PreOrder(VisitFunction visit) const
{
    PreOrder(m_root, visit);
}

// Pre-order traversal (Private recursive)
template <class T>
void Bst<T>::PreOrder(Node* node, VisitFunction visit) const
{
    if (node != nullptr)
    {
        visit(node->data);
        PreOrder(node->lLink, visit);
        PreOrder(node->rLink, visit);
    }
}

// Post-order traversal (Public)
template <class T>
void Bst<T>::PostOrder(VisitFunction visit) const
{
    PostOrder(m_root, visit);
}

// Post-order traversal (Private recursive)
template <class T>
void Bst<T>::PostOrder(Node* node, VisitFunction visit) const
{
    if (node != nullptr)
    {
        PostOrder(node->lLink, visit);
        PostOrder(node->rLink, visit);
        visit(node->data);
    }
}


// Delete the tree/subtree recursively and free up memory
template <class T>
void Bst<T>::Delete(Node*& node)
{
    if (node != nullptr)
    {
        Delete(node->lLink);
        Delete(node->rLink);

        delete node;
        node = nullptr;
    }
}


// Deep copy recursive helper method
template <class T>
typename Bst<T>::Node* Bst<T>::Copy(Node* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    Node* newNode = new Node(node->data);
    newNode->lLink = Copy(node->lLink);
    newNode->rLink = Copy(node->rLink);

    return newNode;
}


// Copy tree data into a Vector in sorted order (Public)
template <class T>
void Bst<T>::ToVector(Vector<T>& data) const
{
    ToVector(m_root, data);
}

// Helper to Copy tree data into a Vector in sorted order (Private recursive)
template <class T>
void Bst<T>::ToVector(Node* node, Vector<T>& data) const
{
    if(node != nullptr)
    {
        ToVector(node->lLink, data);
        data.Insert(data.Size(), node->data);
        ToVector(node->rLink, data);
    }
}


// Check if the BST is correctly structured (Public)
template <class T>
bool Bst<T>::IsValidBST() const
{
    return IsValidBST(m_root, nullptr, nullptr);
}

// Check if the BST is correctly structured (Private recursive)
template <class T>
bool Bst<T>::IsValidBST(Node* node, const T* minValue, const T* maxValue) const
{
    // End of tree/subtree
    if (node == nullptr)
    {
        return true;
    }

    // Check if right node is smaller than parent node
    if (minValue != nullptr && !(*minValue < node->data))
    {
        return false;
    }
    // Check if left node is larger than parent node
    if (maxValue != nullptr && !(node->data < *maxValue))
    {
        return false;
    }

    // Recursively checks both child nodes if they are within bounds
    return IsValidBST(node->lLink, minValue, &(node->data)) &&
           IsValidBST(node->rLink, &(node->data), maxValue);
}

#endif // BST_H_INCLUDED
