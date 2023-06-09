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

	int rollNo;
	string nm;
	cout << "\nEnter the roll number of the student: ";
	cin >> rollNo;
	cout << "Enter the name of the student: ";
	cin >> nm;

	Node* newnode = new Node();
	newnode->rollNumber = rollNo;
	newnode->name = nm;

	if (LAST == NULL) {
		newnode->next = LAST;
		LAST = newnode;
		LAST->next = LAST;
		return;
	}
	else if (rollNo <= LAST->next->rollNumber) {
		if (rollNo == LAST->next->rollNumber) {
			cout << "\nDuplicate roll numbers not allowed\n";
			return;
		}
		newnode->next = LAST->next;
		LAST->next = newnode;
		return;
	}

	Node* previous = LAST->next;
	Node* current = LAST->next;

	while (rollNo >= current->rollNumber && current != LAST) {
		if (rollNo == current->rollNumber) {
			cout << "\nDuplicate roll numbers not allowed\n";
			return;
		}
		previous = current;
		current = current->next;
	}

	if (previous == LAST) {
		newnode->next = LAST->next;
		LAST->next = newnode;
		LAST = newnode;
	}
	else {
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
