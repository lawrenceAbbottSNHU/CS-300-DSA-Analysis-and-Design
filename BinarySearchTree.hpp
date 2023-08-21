#include <iostream>

using namespace std;

struct Course {
    string name;
    string number;
    vector<string> prerequisites;

    /**
     * Default constructor
     */
    Course() {
        name = "";
        number = "";
    }

    /**
     * Copy constructor
     *
     * @param Course aCourse
     */
    Course(Course &aCourse): Course() {
        name = aCourse.name;
        number = aCourse.number;
        prerequisites = aCourse.prerequisites;
    }
};

struct Node {
    Course course;
    Node *left;
    Node *right;

    /**
     * Default constructor
     */
    Node() {
        left = nullptr;
        right  = nullptr;
    }

    /**
     * Initialize with a course
     *
     * @param Course aCourse
     */
    explicit Node(const Course& aCourse) : Node() {
        course = aCourse;
    }
};

class BinarySearchTree {

private:
    Node *root;

    void destroyRecursive(Node*);
    void insertRecursive(Node*, Course);
    void validateCoursesRecursive(Node*);
    void validateCoursePrerequisites(Course);
    Node* searchRecursive(Node*, const string&);
    void printCourseInformationInOrderRecursive(Node*);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Empty();
    void Insert(Course);
    Node* Search(const string&);
    void ValidateCourses();
    void PrintCourseInformationInOrder();
    static void PrintCourseShortVersion(const Course&);
    static void PrintCourseLongVersion(Course);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    destroyRecursive(root);
}

/**
 * Destroy subtree nodes (recursive)
 *
 * @param Node* subTreeRoot
 */
void BinarySearchTree::destroyRecursive(Node* subTreeRoot) {
    if (subTreeRoot != nullptr) {
        destroyRecursive(subTreeRoot->left);
        destroyRecursive(subTreeRoot->right);
        delete subTreeRoot;
    }
}

/**
 * Destroy all nodes from the tree and reinitialize root to null
 */
void BinarySearchTree::Empty() {
    destroyRecursive(root);
    root = nullptr;
}

/**
 * Insert course into tree
 *
 * @param Course course
 */
void BinarySearchTree::Insert(Course course) {
    insertRecursive(root, course);
}

/**
 * Insert course into subtree (recursive)
 *
 * @param Node* subTreeRoot
 * @param Course course
 */
void BinarySearchTree::insertRecursive(Node* subTreeRoot, Course course) {
    if (subTreeRoot == root && subTreeRoot == nullptr) {
        // insert at root and return
        root = new Node(course);
        return;
    }
    if (course.number < subTreeRoot->course.number) {
        if (subTreeRoot->left == nullptr) {
            // insert on the left
            subTreeRoot->left = new Node(course);
        } else {
            // insert somewhere within the subtree to the left
            insertRecursive(subTreeRoot->left, course);
        }
    } else {
        if (subTreeRoot->right == nullptr) {
            // insert on the right
            subTreeRoot->right = new Node(course);
        } else {
            // insert somewhere within the subtree to the right
            insertRecursive(subTreeRoot->right, course);
        }
    }
}

/**
 * Validate that the courses in the tree are up to code
 */
void BinarySearchTree::ValidateCourses() {
    validateCoursesRecursive(root);
}

/**
 * Validate that the courses in the subtree are up to code (recursive)
 * @param node
 */
void BinarySearchTree::validateCoursesRecursive(Node* node) {
    if (node != nullptr) {
        validateCoursesRecursive(node->left);
        validateCoursePrerequisites(node->course);
        validateCoursesRecursive(node->right);
    }
}

/**
 * Validate that a course's prerequisites are found somewhere in the tree
 *
 * @param Course course
 */
void BinarySearchTree::validateCoursePrerequisites(Course course) {
    // for each of the prerequisites, validate they exist in the tree
    for (int p = 0; p < course.prerequisites.size(); ++p) {
        Node* preReq = Search(course.prerequisites.at(p));
        if (preReq->course.number.empty()) {
            throw runtime_error(string("Course " + course.name
            + "'s prerequisite " + course.prerequisites.at(p) + " cannot be found"));
        }
    }
}

/**
 * Search for a course in the tree by the course number
 *
 * @param string courseNum
 * @return Node*
 */
Node* BinarySearchTree::Search(const string& courseNum) {
    return searchRecursive(root, courseNum);
}

/**
 * Search for a course in the subtree by the course number (recursive)
 *
 * @param Node* node
 * @param string courseNum
 * @return Node*
 */
Node* BinarySearchTree::searchRecursive(Node* node, const string& courseNum) {
    if (node == nullptr) {
        // return empty node
        return new Node();
    }
    if (node->course.number == courseNum) {
        // return this node
        return node;
    }
    if (courseNum < node->course.number) {
        // search nodes to the left
        return searchRecursive(node->left, courseNum);
    } else {
        // search nodes to the right
        return searchRecursive(node->right, courseNum);
    }
}

/**
 * Print all courses in the tree in alphanumeric order
 */
void BinarySearchTree::PrintCourseInformationInOrder() {
    printCourseInformationInOrderRecursive(root);
}

/**
 * Print all courses in the subtree in alphanumeric order (recursive)
 *
 * @param Node* node
 */
void BinarySearchTree::printCourseInformationInOrderRecursive(Node* node) {
    if (node != nullptr) {
        printCourseInformationInOrderRecursive(node->left);
        PrintCourseShortVersion(node->course);
        printCourseInformationInOrderRecursive(node->right);
    }
}

/**
 * Print course metadata (short version)
 *
 * @param Course course
 */
void BinarySearchTree::PrintCourseShortVersion(const Course& course) {
    // print course metadata
    cout << course.number << ", " << course.name << endl;
}

/**
 * Print course metadata (long version)
 *
 * @param Course course
 */
void BinarySearchTree::PrintCourseLongVersion(Course course) {
    // print course metadata
    cout << course.number << ", " << course.name << endl;
    unsigned long prerequisiteCount = course.prerequisites.size();
    // if there are prerequisites, list each separated by a comma
    if (prerequisiteCount > 0) {
        cout << "Prerequisites: ";
        for (int p = 0; p < prerequisiteCount; ++p) {
            cout << course.prerequisites.at(p);
            if (p == prerequisiteCount - 1) {
                cout << endl;
            } else {
                cout << ", ";
            }
        }
    }
}