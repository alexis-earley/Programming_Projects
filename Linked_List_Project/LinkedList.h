#pragma once
#include<iostream>
#include<vector>
using namespace std;

template <typename T>
class LinkedList
{
public:
	class Node {
	public:
		T data;
		Node* next;
		Node* prev; //prev
		Node();
		Node(Node* next, Node* prev, T data);
	};
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	unsigned int NodeCount() const;
	void PrintForward() const;
	void PrintReverse() const;
	LinkedList();
	~LinkedList();
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;
	Node* GetNode(unsigned int index);
	const Node* GetNode(unsigned int index) const;
	T& operator[](unsigned int index);
	const T& operator[](unsigned int index) const;
	Node* Find(const T& data);
	const Node* Find(const T& data) const;
	void FindAll(vector<Node*>& outdata, const T& value) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	LinkedList(const LinkedList<T>& rhs);
	void InsertBefore(Node* node, const T& data);
	void InsertAfter(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	bool RemoveHead();
	bool RemoveTail();
	bool RemoveAt(unsigned int index);
	void Clear();
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;
	unsigned int Remove(const T& data);


private:
	unsigned int nodeCount;
	Node* headPointer;
	Node* tailPointer;
};

template <typename T>
LinkedList<T>::Node::Node() {
	const T* next = nullptr;
	const T* prev = nullptr;
}

template <typename T>
LinkedList<T>::Node::Node(Node* prev, Node* next, T data) {
	this->prev = prev;
	this->next = next;
	this->data = data;
}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	Node* tempNode = new Node(nullptr, nullptr, data);
	if (nodeCount == 0) {
		headPointer = tailPointer = tempNode;
	}
	else {
		tempNode->next = headPointer;
		headPointer->prev = tempNode;
		headPointer = tempNode;
	}
	nodeCount++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	Node* tempNode = new Node(nullptr, nullptr, data);
	if (nodeCount == 0) {
		tailPointer = headPointer = tempNode;
	}
	else {
		tempNode->prev = tailPointer;
		tailPointer->next = tempNode;
		tailPointer = tempNode;
	}
	nodeCount++;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
	for (const T* p = (data + count - 1); p >= data; --p) {
		AddHead(*p);
	}
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
	const T* end = data + count;
	for (const T* p = data; p != end; ++p) {
		AddTail(*p);
	}
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return nodeCount;
}

template <typename T>
void LinkedList<T>::PrintForward() const {
	Node* currentPointer = headPointer;
	for (unsigned int i = 0; i < nodeCount; i++) {
		cout << currentPointer->data << endl;
		currentPointer = currentPointer->next;
	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	Node* currentPointer = tailPointer;
	for (unsigned int i = 0; i < nodeCount; i++) {
		cout << currentPointer->data << endl;
		currentPointer = currentPointer->prev;
	}
}

template <typename T>
LinkedList<T>::LinkedList() {
	nodeCount = 0;
	headPointer = nullptr;
	tailPointer = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() { //
	for (unsigned int i = 0; i < nodeCount; i++) {
		Node* tempNode = headPointer->next;
		delete headPointer;
		headPointer = tempNode;
	}
	nodeCount = 0;
	headPointer = nullptr;
	tailPointer = nullptr;
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return headPointer;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return headPointer;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tailPointer;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tailPointer;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	if ((index >= 0) && (index < nodeCount)) {
		Node* currentPointer = headPointer;
		for (unsigned int i = 0; i < index; i++) {
			currentPointer = currentPointer->next;
		}
		return currentPointer;
	}
	else {
		throw out_of_range("Please select a valid index.");
	}
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	if ((index >= 0) && (index < nodeCount)) {
		const Node* currentPointer = headPointer;
		for (unsigned int i = 0; i < index; i++) {
			currentPointer = currentPointer->next;
		}
		return currentPointer;
	}
	else {
		throw out_of_range("Please select a valid index.");
	}
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	return GetNode(index)->data;
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	return GetNode(index)->data;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	Node* currentPointer = headPointer;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentPointer->data == data) {
			return currentPointer;
		}
		currentPointer = currentPointer->next;
	}
	return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	const Node* currentPointer = headPointer;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentPointer->data == data) {
			return currentPointer;
		}
		currentPointer = currentPointer->next;
	}
	return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outdata, const T& value) const {
	Node* currentPointer = headPointer;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentPointer->data == value) {
			outdata.push_back(currentPointer);
		}
		currentPointer = currentPointer->next;
	}
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	for (unsigned int i = 0; i < nodeCount; i++) {
		Node* tempNode = headPointer->next;
		delete headPointer;
		headPointer = tempNode;
	}
	headPointer = tailPointer = new Node(nullptr, nullptr, rhs[0]);
	nodeCount = 1;

	for (unsigned int i = 1; i < rhs.NodeCount(); i++) {
		AddTail(rhs[i]);
	}

	return *this;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs) {
	headPointer = tailPointer = new Node(nullptr, nullptr, rhs[0]);
	nodeCount = 1;

	for (unsigned int i = 1; i < rhs.NodeCount(); i++) {
		AddTail(rhs[i]);
	}
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	if (node == headPointer) {
		AddHead(data);
	}
	else {
		Node* prevNode = node->prev;
		Node* newNode = new Node(prevNode, node, data);
		prevNode->next = newNode;
		node->prev = newNode;
		nodeCount++;
	}
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	if (node == tailPointer) {
		AddTail(data);
	}
	else {
		Node* nextNode = node->next;
		Node* newNode = new Node(node, nextNode, data);
		node->next = newNode;
		nextNode->prev = newNode;
		nodeCount++;
	}
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	if (nodeCount == 0) {
		AddHead(data);
	}
	else {
		if (index == nodeCount) {
			InsertAfter(tailPointer, data);
		}
		else {
			InsertBefore(GetNode(index), data);
		}
	}
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	if (nodeCount != rhs.NodeCount()) {
		return false;
	}

	for (unsigned int i = 0; i < nodeCount; i++) {
		if (GetNode(i)->data != rhs[i]) {
			return false;
		}
	}

	return true;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
	if (nodeCount == 0) {
		return false;
	}
	else if (nodeCount == 1) {
		delete headPointer;
		headPointer = nullptr;
		tailPointer = nullptr;
		nodeCount = 0;
		return true;
	}
	else {
		Node* nextNode = headPointer->next;
		nextNode->prev = nullptr;
		delete headPointer;
		headPointer = nextNode;
		nodeCount--;
		return true;
	}
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
	if (nodeCount == 0) {
		return false;
	}
	else if (nodeCount == 1) {
		delete headPointer;
		headPointer = nullptr;
		tailPointer = nullptr;
		nodeCount = 0;
		return true;
	}
	else {
		Node* prevNode = tailPointer->prev;
		prevNode->next = nullptr;
		delete tailPointer;
		tailPointer = prevNode;
		nodeCount--;
		return true;
	}
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
	if (index >= nodeCount) {
		return false;
	}
	else if (index == 0) {
		RemoveHead();
		return true;
	}
	else if (index == (nodeCount - 1)) {
		RemoveTail();
		return true;
	}
	else {
		Node* nodeToRemove = GetNode(index);
		Node* prevNode = nodeToRemove->prev;
		Node* nextNode = nodeToRemove->next;
		delete nodeToRemove;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		nodeCount--;
		return true;
	}
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
	vector<unsigned int> indexesToRemove;
	Node* currentPointer = headPointer;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentPointer->data == data) {
			cout << i << endl;
			indexesToRemove.push_back(i);
		}
		currentPointer = currentPointer->next;
	}
	unsigned int numRemoved = indexesToRemove.size();
	for (int j = indexesToRemove.size() - 1; j >= 0; j--) {
		RemoveAt(indexesToRemove[j]);
	}
	return numRemoved;
}

template <typename T>
void LinkedList<T>::Clear() {
	for (unsigned int i = 0; i < nodeCount; i++) {
		Node* tempNode = headPointer->next;
		delete headPointer;
		headPointer = tempNode;
	}
	headPointer = nullptr;
	tailPointer = nullptr;
	nodeCount = 0;
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
	if (node == tailPointer)
	{
		cout << node->data << endl;
	}
	else {
		cout << node->data << endl;
		PrintForwardRecursive(node->next);
	}
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
	if (node == headPointer)
	{
		cout << node->data << endl;
	}
	else {
		cout << node->data << endl;
		PrintReverseRecursive(node->prev);
	}
}