// ============================================================================
//     Name: Fahad Tariq
//     File:  HashMap.h
//     Description: HashMap Implimentation
// ============================================================================
#ifndef TEMPLATE_HASH_MAP
#define TEMPLATE_HASH_MAP
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>


// default hash map size
const int HASH_SIZE = 1000;

template <class Key, class Value>
class HashMap
{
public:
	HashMap(int hashSze = HASH_SIZE);
	// Constructor initializes for hash map 

	bool IsEmpty(int keyIndex);
	// Determines whether hash map is empty at the given hash

	bool  IsFull();
	//Determines whether hash map is full

	int Hash(Key m_key);
	//Computes and returns a hash map key index for a given item

	void Insert(Key m_key, Value m_value);
	// Adds new item to the back of the list at a given key in the hash map

	bool Remove(Key m_key, Value deleteItem);
	// Removes the first instance from the map whose value is "deleteItem"

	void Sort(int keyIndex);
	// Sort the items in the map at the given hashmap key index

	int TableSize();
	// Return the size of the hash map

	int TotalElems();
	// Return the total number of elements contained in the hash map

	int BucketSize(int keyIndex);
	//   Return the number of items contained in the hash map

	int Count(Key m_key, Value searchItem);
	// Return the number of times searchItem appears in the map

	int ContainsKey(Key m_key);
	// Return the number of times the given key appears in the hashmap

	void MakeEmpty();
	// Initializes hash map to an empty state 

	~HashMap();
	// Removes the hash map 


	//  Class for Iterator

	class Iterator;
	// Class declaration to the iterator 


	Iterator begin(int keyIndex) { return(!IsEmpty(keyIndex)) ? head[keyIndex] : NULL; }
	// Returns the beginning of the current hashmap key index


	Iterator end(int keyIndex = 0) { return NULL; }
	//  Returns the end of the current hashmap key index


private:
	struct KeyValue  // struct to hold key and value pairs
	{
		Key key;
		Value value;
	};
	struct node
	{
		KeyValue currentItem;
		node* next;
	};
	node** head; // array of linked list declaration - front of each hash map cell
	int hashSize; // the size of the hash map (how many cells it has)
	int totElems; // holds the total number of elements in the entire table
	int* bucketSize; // holds the total number of elems in each specific hash map cell
};

// Implementation 

template <class Key, class Value>
HashMap<Key, Value>::HashMap(int hashSze)
{
	hashSize = hashSze;
	head = new node*[hashSize];
	bucketSize = new int[hashSize];
	for (int x = 0; x < hashSize; ++x)
	{
		head[x] = NULL;
		bucketSize[x] = 0;
	}
	totElems = 0;
} // End of HashMap

template <class Key, class Value>
bool HashMap<Key, Value>::IsEmpty(int keyIndex)
{
	if (keyIndex >= 0 && keyIndex < hashSize)
	{
		return head[keyIndex] == NULL;
	}
	return true;
}//  End of IsEmpty 

template <class Key, class Value>
bool HashMap<Key, Value>::IsFull()
{
	try
	{
		node* location = new node;
		delete location;
		return false;
	}
	catch (std::bad_alloc&)
	{
		return true;
	}
} // End of IsFull

template <class Key, class Value>
int HashMap<Key, Value>::Hash(Key m_key)
{
	long h = 19937;
	std::stringstream convert;

	convert << m_key;
	std::string temp = convert.str();

	for (unsigned x = 0; x < temp.length(); ++x)
	{
		h = (h << 6) ^ (h >> 26) ^ temp[x];
	}
	return abs(h % hashSize);
} //  End of Hash

template <class Key, class Value>
void HashMap<Key, Value>::Insert(Key m_key, Value m_value)
{
	if (IsFull())
	{
		//std::cout<<"\nINSERT ERROR - HASH MAP FULL\n";
	}
	else
	{
		int keyIndex = Hash(m_key);
		node* newNode = new node;   // add new node
		newNode->currentItem.key = m_key;
		newNode->currentItem.value = m_value;
		newNode->next = NULL;

		if (IsEmpty(keyIndex))
		{
			head[keyIndex] = newNode;
		}
		else
		{
			node* temp = head[keyIndex];
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = newNode;
		}
		++bucketSize[keyIndex];
		++totElems;
	}
}/* End of Insert */

template <class Key, class Value>
bool HashMap<Key, Value>::Remove(Key m_key, Value deleteItem)
{
	bool isFound = false;
	node* temp;
	int keyIndex = Hash(m_key);

	if (IsEmpty(keyIndex))
	{
		//std::cout<<"\nREMOVE ERROR - HASH MAP EMPTY\n";
	}
	else if (head[keyIndex]->currentItem.key == m_key
		&& head[keyIndex]->currentItem.value == deleteItem)
	{
		temp = head[keyIndex];
		head[keyIndex] = head[keyIndex]->next;
		delete temp;
		--totElems;
		--bucketSize[keyIndex];
		isFound = true;
	}
	else
	{
		for (temp = head[keyIndex]; temp->next != NULL; temp = temp->next)
		{
			if (temp->next->currentItem.key == m_key
				&& temp->next->currentItem.value == deleteItem)
			{
				node* deleteNode = temp->next;
				temp->next = temp->next->next;
				delete deleteNode;
				isFound = true;
				--totElems;
				--bucketSize[keyIndex];
				break;
			}
		}
	}
	return isFound;
}/* End of Remove */

template <class Key, class Value>
void HashMap<Key, Value>::Sort(int keyIndex)
{
	if (IsEmpty(keyIndex))
	{
		//std::cout<<"\nSORT ERROR - HASH MAP EMPTY\n";
	}
	else
	{
		int listSize = BucketSize(keyIndex);
		bool sorted = false;

		do {
			sorted = true;
			int x = 0;
			for (node* temp = head[keyIndex];
				temp->next != NULL && x < listSize - 1;
				temp = temp->next, ++x)
			{
				if (temp->currentItem.value > temp->next->currentItem.value)
				{
					std::swap(temp->currentItem, temp->next->currentItem);
					sorted = false;
				}
			}
			--listSize;
		} while (!sorted);
	}
}/* End of Sort */

template <class Key, class Value>
int HashMap<Key, Value>::TableSize()
{
	return hashSize;
}/* End of TableSize */

template <class Key, class Value>
int HashMap<Key, Value>::TotalElems()
{
	return totElems;
}/* End of TotalElems */

template <class Key, class Value>
int HashMap<Key, Value>::BucketSize(int keyIndex)
{
	return(!IsEmpty(keyIndex)) ? bucketSize[keyIndex] : 0;
}/* End of BucketSize */

template <class Key, class Value>
int HashMap<Key, Value>::Count(Key m_key, Value searchItem)
{
	int keyIndex = Hash(m_key);
	int search = 0;

	if (IsEmpty(keyIndex))
	{
		//std::cout<<"\nCOUNT ERROR - HASH MAP EMPTY\n";
	}
	else
	{
		for (node* temp = head[keyIndex]; temp != NULL; temp = temp->next)
		{
			if (temp->currentItem.key == m_key
				&& temp->currentItem.value == searchItem)
			{
				++search;
			}
		}
	}
	return search;
}/* End of Count */

template <class Key, class Value>
int HashMap<Key, Value>::ContainsKey(Key m_key)
{
	int keyIndex = Hash(m_key);
	int search = 0;

	if (IsEmpty(keyIndex))
	{
		//std::cout<<"\nCONTAINS KEY ERROR - HASH MAP EMPTY\n";
	}
	else
	{
		for (node* temp = head[keyIndex]; temp != NULL; temp = temp->next)
		{
			if (temp->currentItem.key == m_key)
			{
				++search;
			}
		}
	}
	return search;
}/* End of ContainsKey */

template <class Key, class Value>
void HashMap<Key, Value>::MakeEmpty()
{
	totElems = 0;
	for (int x = 0; x < hashSize; ++x)
	{
		if (!IsEmpty(x))
		{
			//std::cout << "Destroying nodes ...\n";
			while (!IsEmpty(x))
			{
				node* temp = head[x];
				//std::cout << temp-> currentItem.value <<std::endl;
				head[x] = head[x]->next;
				delete temp;
			}
		}
		bucketSize[x] = 0;
	}
}/* End of MakeEmpty */

template <class Key, class Value>
HashMap<Key, Value>::~HashMap()
{
	MakeEmpty();
	delete[] head;
	delete[] bucketSize;
}/* End of ~HashMap */

 //   END OF THE HASH MAP CLASS
 // -----------------------------------------------------------
 //   START OF THE HASH MAP ITERATOR CLASS

template <class Key, class Value>
class HashMap<Key, Value>::Iterator :
	public std::iterator<std::forward_iterator_tag, Value>,
	public HashMap<Key, Value>
{
public:
	// Iterator constructor
	Iterator(node* otherIter = NULL)
	{
		itHead = otherIter;
	}
	~Iterator() {}
	// The assignment and relational operators are straightforward
	Iterator& operator=(const Iterator& other)
	{
		itHead = other.itHead;
		return(*this);
	}
	bool operator==(const Iterator& other)const
	{
		return itHead == other.itHead;
	}
	bool operator!=(const Iterator& other)const
	{
		return itHead != other.itHead;
	}
	bool operator<(const Iterator& other)const
	{
		return itHead < other.itHead;
	}
	bool operator>(const Iterator& other)const
	{
		return other.itHead < itHead;
	}
	bool operator<=(const Iterator& other)const
	{
		return (!(other.itHead < itHead));
	}
	bool operator>=(const Iterator& other)const
	{
		return (!(itHead < other.itHead));
	}
	// Update my state such that I refer to the next element in the HashMap.
	Iterator operator+(int incr)
	{
		node* temp = itHead;
		for (int x = 0; x < incr && temp != NULL; ++x)
		{
			temp = temp->next;
		}
		return temp;
	}
	Iterator operator+=(int incr)
	{
		for (int x = 0; x < incr && itHead != NULL; ++x)
		{
			itHead = itHead->next;
		}
		return itHead;
	}
	Iterator& operator++() // pre increment
	{
		if (itHead != NULL)
		{
			itHead = itHead->next;
		}
		return(*this);
	}
	Iterator operator++(int) // post increment
	{
		node* temp = itHead;
		this->operator++();
		return temp;
	}
	KeyValue& operator[](int incr)
	{
		// Return "junk" data to prevent the program from crashing
		if (itHead == NULL || (*this + incr) == NULL)
		{
			return junk;
		}
		return(*(*this + incr));
	}
	// Return a reference to the value in the node. 

	KeyValue& operator*()
	{


		if (itHead == NULL)
		{
			return junk;
		}
		return itHead->currentItem;
	}
	KeyValue* operator->()
	{
		return(&**this);
	}
private:
	node * itHead;
	KeyValue junk;
};
#endif 
