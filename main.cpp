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
}
