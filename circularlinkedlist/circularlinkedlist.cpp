#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int rollNumber;
	string name;
	Node* next;
};

class CircularLinkedList {
private:
	Node* LAST;

public:
	CircularLinkedList() {
		LAST = NULL;
	}

	void addNode();

	bool search(int rollno, Node** previous, Node** current);

	bool listEmpty();

	bool delNode();

	void traverse();


};

void CircularLinkedList::addNode() {
	// Function to add a node to the circular linked list

	int rollNo;
	string nm;
	cout << "\nEnter the roll number of the student: ";
	cin >> rollNo;
	cout << "Enter the name of the student: ";
	cin >> nm;

	// Create a new node and assign the input values
	Node* newnode = new Node();
	newnode->rollNumber = rollNo;
	newnode->name = nm;

	// Check if the list is empty
	if (LAST == NULL) {
		// If the list is empty, make the new node the last node
		newnode->next = LAST;
		LAST = newnode;
		LAST->next = LAST;  // Point the last node back to itself
		return;
	}
	// Check if the roll number of the new node is less than or equal to the roll number of the first node
	else if (rollNo <= LAST->next->rollNumber) {
		// If it is, check if the roll numbers match
		if (rollNo == LAST->next->rollNumber) {
			cout << "\nDuplicate roll numbers not allowed\n";
			return;
		}
		// Insert the new node at the beginning of the list
		newnode->next = LAST->next;
		LAST->next = newnode;
		return;
	}

	// Traverse the list to find the appropriate position to insert the new node
	Node* previous = LAST->next;
	Node* current = LAST->next;

	while (rollNo >= current->rollNumber && current != LAST) {
		// Check if the roll numbers match
		if (rollNo == current->rollNumber) {
			cout << "\nDuplicate roll numbers not allowed\n";
			return;
		}
		previous = current;
		current = current->next;
	}

	// Check if the new node should be inserted at the end of the list
	if (previous == LAST) {
		newnode->next = LAST->next;
		LAST->next = newnode;
		LAST = newnode;
	}
	else {
		// Insert the new node between the previous and current node
		newnode->next = current;
		previous->next = newnode;
	}
}

bool CircularLinkedList::search(int rollno, Node** previous, Node** current) {
	*previous = LAST->next;
	*current = LAST->next;

	while (*current != LAST) {
		if (rollno == (*current)->rollNumber) {
			return true;
		}
		*previous = *current;
		*current = (*current)->next;
	}

	if (rollno == LAST->rollNumber) {
		return true;
	}
	else {
		return false;
	}
}

bool CircularLinkedList::listEmpty() {
	return LAST == NULL;
}

bool CircularLinkedList::delNode() {
	if (listEmpty()) {
		cout << "\nList is empty" << endl;
		return false;
	}

	cout << "\nEnter the roll number of the student whose record is to be deleted: ";
	int rollNo;
	cin >> rollNo;
	cout << endl;

	Node* current = LAST->next;
	Node* previous = NULL;

	do {
		if (current->rollNumber == rollNo) {
			if (current == LAST->next && current == LAST) { // Only one node in the list
				current = NULL;
				LAST = NULL;
			}
			else if (current == LAST->next) { // Deleting the first node
				LAST->next = current->next;
				current = NULL;
			}
			else if (current == LAST) { // Deleting the last node
				previous->next = current->next;
				LAST = previous;
				delete current;
			}
			else { // Deleting a node in between
				previous->next = current->next;
				current = NULL;
			}

			cout << "Record deleted successfully" << endl;
			return true;
		}

		previous = current;
		current = current->next;
	} while (current != LAST->next);

	cout << "Record not found" << endl;
	return false;
}


void CircularLinkedList::traverse() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
	}
	else {
		cout << "\nRecords in the list are:\n";
		Node* currentNode = LAST->next;
		while (currentNode != LAST) {
			cout << currentNode->rollNumber << "   " << currentNode->name << endl;
			currentNode = currentNode->next;
		}
		cout << LAST->rollNumber << "   " << LAST->name << endl;
	}
}


int main() {
	CircularLinkedList obj;
	while (true) {
		try {
			cout << "\nMenu" << endl;
			cout << "1. Add a record to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all the records in the list" << endl;
			cout << "4. Exit" << endl;
			cout << "\nEnter your choice (1-5): ";

			char ch;
			cin >> ch;

			switch (ch) {
			case '1': {
				obj.addNode();
				break;
			}
			case '2': {
				obj.delNode();
				break;
			}
			case '3': {
				obj.traverse();
				break;
			}

			case '4': {
				return 0;
			}
			default: {
				cout << "Invalid option" << endl;
				break;
			}
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}
