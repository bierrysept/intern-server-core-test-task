#pragma once
#include <exception>

namespace MyFIFO {
	class ListEmpty : std::exception {};

	class ListFull : std::exception {};

	class ListElementDoesNotExist : std::exception {};
}

namespace {
	template <typename T>
	class FIFOListedNode {
		FIFOListedNode<T>* next = NULL;
		T value;
	public:
		FIFOListedNode(T valueOnCreate) {
			value = valueOnCreate;
		}

		void setNext(FIFOListedNode<T>* next) {
			this->next = next;
		}

		FIFOListedNode<T>* getNext(int depth = 1) {
			if (depth == 0) {
				return this;
			}

			if (depth == 1) {
				return this->next;
			}

			if (!this->next) {
				throw MyFIFO::ListElementDoesNotExist();
			}

			return this->next->getNext(depth - 1);
		}

		FIFOListedNode<T>* getLast(unsigned int &depth) {
			FIFOListedNode<T>* element;
			if (next != NULL) {
				element = next->getLast(depth);
			}
			else {
				element = this;
			}
			
			if (depth == 0) {
				return element;
			}
			depth--;
			return this;
		}

		T getValue() {
			return value;
		}
	};

}

namespace MyFIFO {

	template <typename T, unsigned int maxSize>
	class FIFOArrayed {
	T items[maxSize]{};
	unsigned int start = 0;
	unsigned int end = 0;
public:
	bool isEmpty() {
		return start == end;
	}

	void push(T item) {
		unsigned int newEnd = (end + 1) % maxSize;

		if (newEnd == start) {
			throw ListFull();
		}

		items[end] = item;
		end = newEnd;
	}

	void pop() {
		if (this->isEmpty()) {
			throw ListEmpty();
		}

		start = (start + 1) % maxSize;
	}

	T first(unsigned int depth = 0) {
		if (this->isEmpty()) {
			throw ListEmpty();
		}

		unsigned int index = (start + depth) % maxSize;

		return items[index];
	}

	T last(unsigned int depth = 0) {
		if (this->isEmpty()) {
			throw ListEmpty();
		}

		unsigned int index = (end - depth) % maxSize;
		if (index < 0) {
			index += maxSize;
		}

		return items[index];
	}

};


	template <typename T>
	class FIFOListed {
	FIFOListedNode<T>* start = NULL;
	FIFOListedNode<T>* end = NULL;
	unsigned int length = 0;
public:
	bool isEmpty() {
		return !length;
	}

	void push(T item) {
		FIFOListedNode<T>* newNode = new FIFOListedNode<T>(item);

		if (this->isEmpty()) {
			start = newNode;
			end = newNode;
		}
		else {
			start->setNext(newNode);
			start = newNode;
		}
		length++;
	}

	void pop() {
		if (this->isEmpty()) {
			throw ListEmpty();
		}

		if (start == end) {
			FIFOListedNode<T>* node = start;
			delete node;
			start = end = NULL;
		}
		else {
			FIFOListedNode<T>* tmp = end->getNext();
			delete end;
			end = tmp;
		}

		length--;
	}

	T first(unsigned int depth = 0) {
		if (this->isEmpty()) {
			throw ListEmpty();
		}

		return this->end->getNext(depth)->getValue();
	}

	T last(unsigned int depth = 0) {
		if (this->isEmpty()) {
			throw ListEmpty();
		}
		depth++;
		return this->end->getLast(depth)->getValue();
	}
};
}