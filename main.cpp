#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
  struct Node
  {
    T data;
    Node * next;
    Node * prev;

    Node(const T & value) : data(value), next(nullptr), prev(nullptr) {}
  };

  Node * head;
  Node * tail;
  size_t size;

public:
  class iterator;
  class const_iterator;
  class reverse_iterator;
  class const_reverse_iterator;

  LinkedList() : head(nullptr), tail(nullptr), size(0) {}

  ~LinkedList()
  {
    Node * current = head;
    while (current) {
      Node * next = current->next;
      delete current;
      current = next;
    }
  }

  void push_back(const T & value)
  {
    Node * newNode = new Node(value);
    if (empty()) {
      head = tail = newNode;
    } else {
      newNode->prev = tail;
      tail->next = newNode;
      tail = newNode;
    }
    ++size;
  }

  void push_front(const T & value)
  {
    Node * newNode = new Node(value);
    if (empty()) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
    ++size;
  }

  void pop_back()
  {
    if (empty()) {
      throw out_of_range("Cannot pop from empty list");
    }
    Node * temp = tail;
    if (head == tail) {
      head = tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
    }
    delete temp;
    --size;
  }

  void pop_front()
  {
    if (empty()) {
      throw out_of_range("Cannot pop from empty list");
    }
    Node * temp = head;
    if (head == tail) {
      head = tail = nullptr;
    } else {
      head = head->next;
      head->prev = nullptr;
    }
    delete temp;
    --size;
  }

  bool empty() const noexcept { return size == 0; }
  size_t getSize() const noexcept { return size; }

  iterator begin() { return iterator(head); }
  iterator end() { return iterator(nullptr); }
  const_iterator cbegin() const { return const_iterator(head); }
  const_iterator cend() const { return const_iterator(nullptr); }

  reverse_iterator rbegin() { return reverse_iterator(tail); }
  reverse_iterator rend() { return reverse_iterator(nullptr); }
  const_reverse_iterator crbegin() const { return const_reverse_iterator(tail); }
  const_reverse_iterator crend() const { return const_reverse_iterator(nullptr); }

  class iterator
  {
  private:
    Node * current;
    explicit iterator(Node * node) : current(node) {}
    friend class LinkedList;

  public:
    T & operator*() { return current->data; }
    iterator & operator++()
    {
      current = current->next;
      return *this;
    }
    iterator operator++(int)
    {
      iterator temp = *this;
      current = current->next;
      return temp;
    }
    iterator & operator--()
    {
      current = current->prev;
      return *this;
    }
    iterator operator--(int)
    {
      iterator temp = *this;
      current = current->prev;
      return temp;
    }
    bool operator==(const iterator & other) const { return current == other.current; }
    bool operator!=(const iterator & other) const { return current != other.current; }
  };

  class const_iterator
  {
  private:
    const Node * current;
    explicit const_iterator(const Node * node) : current(node) {}
    friend class LinkedList;

  public:
    const T & operator*() const { return current->data; }
    const_iterator & operator++()
    {
      current = current->next;
      return *this;
    }
    const_iterator operator++(int)
    {
      const_iterator temp = *this;
      current = current->next;
      return temp;
    }
    const_iterator & operator--()
    {
      current = current->prev;
      return *this;
    }
    const_iterator operator--(int)
    {
      const_iterator temp = *this;
      current = current->prev;
      return temp;
    }
    bool operator==(const const_iterator & other) const { return current == other.current; }
    bool operator!=(const const_iterator & other) const { return current != other.current; }
  };

  class reverse_iterator
  {
  private:
    Node * current;
    explicit reverse_iterator(Node * node) : current(node) {}
    friend class LinkedList;

  public:
    T & operator*() { return current->data; }
    reverse_iterator & operator++()
    {
      current = current->prev;
      return *this;
    }
    reverse_iterator operator++(int)
    {
      reverse_iterator temp = *this;
      current = current->prev;
      return temp;
    }
    reverse_iterator & operator--()
    {
      current = current->next;
      return *this;
    }
    reverse_iterator operator--(int)
    {
      reverse_iterator temp = *this;
      current = current->next;
      return temp;
    }
    bool operator==(const reverse_iterator & other) const { return current == other.current; }
    bool operator!=(const reverse_iterator & other) const { return current != other.current; }
  };

  class const_reverse_iterator
  {
  private:
    const Node * current;
    explicit const_reverse_iterator(const Node * node) : current(node) {}
    friend class LinkedList;

  public:
    const T & operator*() const { return current->data; }
    const_reverse_iterator & operator++()
    {
      current = current->prev;
      return *this;
    }
    const_reverse_iterator operator++(int)
    {
      const_reverse_iterator temp = *this;
      current = current->prev;
      return temp;
    }
    const_reverse_iterator & operator--()
    {
      current = current->next;
      return *this;
    }
    const_reverse_iterator operator--(int)
    {
      const_reverse_iterator temp = *this;
      current = current->next;
      return temp;
    }
    bool operator==(const const_reverse_iterator & other) const { return current == other.current; }
    bool operator!=(const const_reverse_iterator & other) const { return current != other.current; }
  };
};

template <typename T>
class BST
{
private:
  struct Node
  {
    T data;
    Node * parent;
    Node * left;
    Node * right;

    Node(const T & value) : data(value), parent(nullptr), left(nullptr), right(nullptr) {}
  };

  Node * root;
  size_t size;

  Node * getMinimumPtr(Node * x)
  {
    while (x->left) x = x->left;
    return x;
  }

  Node * getMaximumPtr(Node * x)
  {
    while (x->right) x = x->right;
    return x;
  }

  void transplant(Node * u, Node * v)
  {
    if (!(u->parent))
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;
    if (v) v->parent = u->parent;
  }

  Node * search_ptr(const T & data)
  {
    Node * x = root;
    while (x && x->data != data) {
      if (data < x->data)
        x = x->left;
      else
        x = x->right;
    }
    return x;
  }

  void destroyRecursive(Node * node_ptr)
  {
    if (node_ptr->left) destroyRecursive(node_ptr->left);
    if (node_ptr->right) destroyRecursive(node_ptr->right);
    delete node_ptr;
  }

  void left_rotate(Node * x)
  {
    if (!x || !x->right) return;  // Cannot rotate if x or its right child is null

    Node * y = x->right;  // Set y as the right child of x

    // Turn y's left subtree into x's right subtree
    x->right = y->left;
    if (y->left) y->left->parent = x;

    // Link x's parent to y
    y->parent = x->parent;
    if (!x->parent)  // x was root
      root = y;
    else if (x == x->parent->left)  // x was left child
      x->parent->left = y;
    else  // x was right child
      x->parent->right = y;

    // Put x on y's left
    y->left = x;
    x->parent = y;
  }

  void right_rotate(Node * y)
  {
    if (!y || !y->left) return;  // Cannot rotate if y or its left child is null

    Node * x = y->left;  // Set x as the left child of y

    // Turn x's right subtree into y's left subtree
    y->left = x->right;
    if (x->right) x->right->parent = y;

    // Link y's parent to x
    x->parent = y->parent;
    if (!y->parent)  // y was root
      root = x;
    else if (y == y->parent->left)  // y was left child
      y->parent->left = x;
    else  // y was right child
      y->parent->right = x;

    // Put y on x's right
    x->right = y;
    y->parent = x;
  }

public:
  class iterator;
  class const_iterator;

  BST() : root(nullptr), size(0) {}
  ~BST()
  {
    if (root) destroyRecursive(root);
  }

  size_t getSize() { return size; }
  bool empty() { return !size; }

  void deleteNode(const T & data)
  {
    Node * z = search_ptr(data);
    if (!z) return;
    if (!(z->left))
      transplant(z, z->right);
    else if (!(z->right))
      transplant(z, z->left);
    else {
      Node * y = getMinimumPtr(z->right);
      if (y->parent != z) {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
    }
    delete z;
    --size;
  }

  void insert(const T & data)
  {
    Node * z = new Node(data);
    Node * x = root;
    Node * y = nullptr;
    while (x) {
      y = x;
      if (data < x->data)
        x = x->left;
      else
        x = x->right;
    }
    z->parent = y;
    if (!y)
      root = z;
    else if (data < y->data)
      y->left = z;
    else
      y->right = z;
    ++size;
  }

  bool search(const T & data) { return search_ptr(data); }

  T getMinimum()
  {
    if (empty()) throw out_of_range("Can't find minimum when empty.");
    return getMinimumPtr(root)->data;
  }

  T getMaximum()
  {
    if (empty()) throw out_of_range("Can't find maximum when empty.");
    return getMaximumPtr(root)->data;
  }

  bool left_rotate(const T & data)
  {
    Node * node = search_ptr(data);
    if (!node || !node->right) return false;  // Node must exist and have a right child

    left_rotate(node);
    return true;
  }

  bool right_rotate(const T & data)
  {
    Node * node = search_ptr(data);
    if (!node || !node->left) return false;  // Node must exist and have a left child

    right_rotate(node);
    return true;
  }

  iterator begin() { return iterator(getMinimumPtr(root)); }
  iterator end() { return iterator(nullptr); }
  const_iterator cbegin() const { return const_iterator(getMinimumPtr(root)); }
  const_iterator cend() const { return const_iterator(nullptr); }

  class iterator
  {
  private:
    Node * current;
    explicit iterator(Node * node) : current(node) {}
    friend class BST;

    Node * getSuccessor(Node * x)
    {
      if (x->right) {
        Node * temp = x->right;
        while (temp->left) temp = temp->left;
        return temp;
      }
      Node * y = x->parent;
      while (y && x == y->right) {
        x = y;
        y = y->parent;
      }
      return y;
    }

    Node * getPredecessor(Node * x)
    {
      if (x->left) {
        Node * temp = x->left;
        while (temp->right) temp = temp->right;
        return temp;
      }
      Node * y = x->parent;
      while (y && x == y->left) {
        x = y;
        y = y->parent;
      }
      return y;
    }

  public:
    T & operator*() { return current->data; }
    iterator & operator++()
    {
      current = getSuccessor(current);
      return *this;
    }
    iterator operator++(int)
    {
      iterator temp = *this;
      current = getSuccessor(current);
      return temp;
    }
    iterator & operator--()
    {
      current = getPredecessor(current);
      return *this;
    }
    iterator operator--(int)
    {
      iterator temp = *this;
      current = getPredecessor(current);
      return temp;
    }
    bool operator==(const iterator & other) const { return current == other.current; }
    bool operator!=(const iterator & other) const { return current != other.current; }
  };

  class const_iterator
  {
  private:
    const Node * current;
    explicit const_iterator(const Node * node) : current(node) {}
    friend class BST;

    Node * getSuccessor(Node * x) const
    {
      if (x->right) {
        Node * temp = x->right;
        while (temp->left) temp = temp->left;
        return temp;
      }
      Node * y = x->parent;
      while (y && x == y->right) {
        x = y;
        y = y->parent;
      }
      return y;
    }

    Node * getPredecessor(Node * x) const
    {
      if (x->left) {
        Node * temp = x->left;
        while (temp->right) temp = temp->right;
        return temp;
      }
      Node * y = x->parent;
      while (y && x == y->left) {
        x = y;
        y = y->parent;
      }
      return y;
    }

  public:
    const T & operator*() const { return current->data; }
    const_iterator & operator++()
    {
      current = getSuccessor(const_cast<Node *>(current));
      return *this;
    }
    const_iterator operator++(int)
    {
      const_iterator temp = *this;
      current = getSuccessor(const_cast<Node *>(current));
      return temp;
    }
    const_iterator & operator--()
    {
      current = getPredecessor(const_cast<Node *>(current));
      return *this;
    }
    const_iterator operator--(int)
    {
      const_iterator temp = *this;
      current = getPredecessor(const_cast<Node *>(current));
      return temp;
    }
    bool operator==(const const_iterator & other) const { return current == other.current; }
    bool operator!=(const const_iterator & other) const { return current != other.current; }
  };
};

int main()
{
  // testing LinkedList
  LinkedList<int> list;
  list.push_back(10);
  list.pop_back();
  list.push_back(20);
  list.push_back(30);
  for (auto i : list) cout << i << " ";
  cout << endl;
  list.pop_back();
  for (auto i : list) cout << i << " ";
  cout << endl;
  list.push_front(2);
  list.push_front(3);
  for (auto i : list) cout << i << " ";
  cout << endl;
  list.pop_front();
  for (auto i : list) cout << i << " ";
  cout << endl;

  // testing BST
  BST<int> bst;
  bst.insert(10);
  bst.insert(5);
  bst.insert(15);
  bst.insert(3);
  bst.insert(7);
  cout << "BST in-order traversal: ";
  for (auto i : bst) cout << i << " ";
  cout << endl;
  cout << "Performing left rotation on 5: ";
  bst.left_rotate(5);
  for (auto i : bst) cout << i << " ";
  cout << endl;
  cout << "Performing right rotation on 7: ";
  bst.right_rotate(7);
  for (auto i : bst) cout << i << " ";
  cout << endl;

  return 0;
}
