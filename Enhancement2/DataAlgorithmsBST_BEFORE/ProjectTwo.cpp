// ============================================================================
// Name			: ProjectTwo.cpp
// Author		: Brandon Cook - brandon.cook2@snhu.edu
// Description	: This program will load course data into a binary search tree data structure and sort it alphanumerically.
// ============================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;



// ===========================================
// Define structure to hold course information
// ===========================================
struct Course {
	string courseID;
	string courseName;
	vector<string> coursePrereqs;

	// default constructor
	Course() {};
};



// =======================
// Internal Node Structure
// =======================
struct Node {
	Course course;
	Node* left;
	Node* right;

	// default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// initialize with a course
	Node(Course aCourse) :
		Node() {
		course = aCourse;
	}
};



// ==============================
// Initialize Tree Data Structure
// ==============================
class BinarySearchTree {
private:
	Node* root;

	void addNode(Node* node, Course course);
	void inOrder(Node* node);

public:
	BinarySearchTree();
	void Insert(Course course);
	void InOrder();
	Course Search(string courseID);
};



// ===================
// Default Constructor
// ===================
BinarySearchTree::BinarySearchTree() {
	// set root to nullptr
	root = nullptr;
};



// =========================
// BST Public InOrder Method
// =========================
void BinarySearchTree::InOrder() {
	// traverse tree in order (Alphanumerically)
	// call inOrder function and pass root
	this->inOrder(root);
};



// ==========================
// BST Private inOrder Method
// ==========================
void BinarySearchTree::inOrder(Node* node) {
	//if node is not equal to null ptr
	if (node != nullptr) {
		// recursive inOrder node left
		inOrder(node->left);

		// output courseID, courseName, any coursePrereqs
		cout << node->course.courseID << ", " << node->course.courseName << endl;

		// recursive inOrder node right
		inOrder(node->right);
	}
};



// ========================
// BST Public Insert Method
// ========================
void BinarySearchTree::Insert(Course course) {
	// if root equal to null ptr
	if (root == nullptr) {
		// root is equal to new node bid
		root = new Node(course);
	}
	// else
	else {
		// add Node root and bid
		this->addNode(root, course);
	}
};



Course BinarySearchTree::Search(string courseID) {
	// set current node equal to root
	Node* current = root;

	// keep looping downwards until bottom reached or matching courseID found
	while (current != nullptr) {
		// if match found, return current course
		if (current->course.courseID.compare(courseID) == 0) {
			return current->course;
		}

		// if bid is smaller than current node then traverse left
		if (courseID.compare(current->course.courseID) < 0) {
			current = current->left;
		}
		// else larger so traverse right
		else {
			current = current->right;
		}
	}

	Course course;
	return course;
};



// ==========================
// BST Private addNode Method
// ==========================
void BinarySearchTree::addNode(Node* node, Course course) {
	// if node is larger then add to the left
	if (node->course.courseID.compare(course.courseID) > 0) {
		// if no left node
		if (node->left == nullptr) {
			// this node becomes left
			node->left = new Node(course);
		}
		// else recurse down the left node
		else {
			this->addNode(node->left, course);
		}
	}
	// else
	else {
		// if no right node
		if (node->right == nullptr) {
			// this node becomes right
			node->right = new Node(course);
		}
		//else
		else {
			// recurse down the right node
			this->addNode(node->right, course);
		}
	}
};



// =================================
// Initialize BST as Global Variable
// =================================
BinarySearchTree courseTree;



// ===================
// Display Menu Method
// ===================
static void displayMenu() {
	cout << "Welcome to the course planner." << endl;
	cout << endl;
	cout << "	1. Load Data Structure." << endl;
	cout << "	2. Print Course List." << endl;
	cout << "	3. Print Course." << endl;
	cout << "	9. Exit." << endl;
	cout << endl;
	cout << "What would you like to do? ";
};



// =========
// Load File
// =========
static void fileLoad() {
	// initialize string to hold user input
	string userFile;

	// take filename as user input
	cout << "Input file name: ";
	cin >> userFile;

	// open data file to be read
	ifstream file(userFile);

	// if file cannot be read, print error
	if (!file.is_open()) {
		cerr << "Error: Could not open file." << endl;
	}
	// else parse file
	else {
		string line;

		// while loop to iterate over each line of the file
		while (getline(file, line)) {
			stringstream ss(line);
			string segment;
			vector<string> segments;

			// split line at comma with delimiter
			while (getline(ss, segment, ',')) {
				segments.push_back(segment);
			}

			// if number of segments on each line is greater than or equal to 2
			if (segments.size() >= 2) {
				// initialize new course object
				Course newCourse;

				// extract courseID from first segment
				newCourse.courseID = segments[0];

				// extract courseName from second segment
				newCourse.courseName = segments[1];

				// if there are still more segments
				if (segments.size() > 2) {
					// create vector to store prerequisites
					vector<string> prereqs(segments.begin() + 2, segments.end());

					// add prerequisites to course
					newCourse.coursePrereqs = prereqs;
				}

				// add node to tree
				courseTree.Insert(newCourse);
			}
		}

		// successfully loaded
		cout << "File successfully loaded." << endl;

		// close file
		file.close();
	}
};



void printCourseInfo(Course course) {
	cout << course.courseID << ", " << course.courseName << endl;
	
	// loop over prereqs to print any prerequisite courses, while keeping format consistent
	if (!course.coursePrereqs.empty()) {
		cout << "Prerequisites: ";
		for (size_t i = 0; i < course.coursePrereqs.size(); i++) {
			cout << course.coursePrereqs[i];
			if (i < course.coursePrereqs.size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}
};



// ==========
// Main class
// ==========
int main() {
	// Create variable choice of type integer, set to 0
	int choice = 0;

	while (choice != 9) {
		// clear the screen
		system("CLS");

		// display menu options
		displayMenu();

		// get input from user
		cin >> choice;

		// if choice is 1
		if (choice == 1) {
			// load file and build tree
			fileLoad();
		}
		// else choice is 2
		else if (choice == 2) {
			// print list alphanumerically
			// Implement in order traversal
			courseTree.InOrder();
		}
		// else choice is 3
		else if (choice == 3) {
			// take input ID from user
			string userInput;

			cout << "What course do you want to know about? ";
			cin >> userInput;
			// transform input to uppercase to match format
			transform(userInput.begin(), userInput.end(), userInput.begin(), toupper);

			// search tree for course and print data
			printCourseInfo(courseTree.Search(userInput));
		}
		// else choice is 9
		else if (choice == 9) {
			// end loop
			cout << "Thank you for using the course planner!" << endl;
			break;
		}
		// else any other input
		else {
			// input invalid
			cout << choice << " is not a valid option." << endl;
		}

		// pause the screen
		system("PAUSE");
	}
	
	return 0;
};