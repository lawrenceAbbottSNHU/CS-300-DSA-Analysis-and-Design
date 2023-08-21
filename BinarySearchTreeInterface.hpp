#include "CSVparser.hpp"
#include "CSVparser.cpp"

#include <iostream>
#include <locale>

using namespace std;

class BinarySearchTreeInterface {

public:
    const int exitOption = 9;
    bool coursesLoaded = false;

    BinarySearchTreeInterface();
    virtual ~BinarySearchTreeInterface();
    static void OutputWelcomeMessage();
    static void OutputExitMessage();
    static void OutputCoursesNotLoadedMessage();
    static void OutputInvalidEntryMessage(const string&);
    void OutputMainMenu() const;
    void LoadCoursesRoutine();
    void PrintCourseList();
    void PrintCourseRoutine();

private:
    BinarySearchTree* courses;
    vector<string> yeas = {"yes", "Yes", "YES", "y"};

    bool loadCourses(const string&);
    bool printCourse(const string&);
    static void outputFilePathPrompt();
    static void outputCourseNumberPrompt();
    static void outputAdditionalCoursePrompt();
    static void outputTryAgainPrompt();
    static string strToUpper(const string&);
};

/**
 * Constructor
 */
BinarySearchTreeInterface::BinarySearchTreeInterface() {
    courses = new BinarySearchTree();
}

/**
 * Destructor
 */
BinarySearchTreeInterface::~BinarySearchTreeInterface() {
    delete courses;
}

/**
 * Load courses from csv file
 *
 * @param string& filePath
 * @return bool
 */
bool BinarySearchTreeInterface::loadCourses(const string& filePath) {
    cout << "Loading courses from " << filePath << endl;
    try {
        // load data from the csv into memory
        csv::Parser file = csv::Parser(filePath, ',');
        // iterate over each line
        for (unsigned int lineIndex = 0; lineIndex < file.getContent().size(); ++lineIndex) {
            // initialize course
            Course course;
            // iterate over each item of each line
            for (unsigned int itemIndex = 0; itemIndex < file.getContent().at(lineIndex).size(); ++itemIndex) {
                switch(itemIndex) {
                    case 0:
                        if (file.getContent().at(lineIndex).at(itemIndex).empty()) {
                            throw runtime_error(string("Course number not found"));
                        } else {
                            course.number = file.getContent().at(lineIndex).at(itemIndex);
                        }
                        break;
                    case 1:
                        if (file.getContent().at(lineIndex).at(itemIndex).empty()) {
                            throw runtime_error(string("Course name not found"));
                        } else {
                            course.name = file.getContent().at(lineIndex).at(itemIndex);
                        }
                        break;
                    default:
                        course.prerequisites.push_back(file.getContent().at(lineIndex).at(itemIndex));
                        break;
                }
            }
            // insert course into the binary search tree
            courses->Insert(course);
        }
        // now that all the courses have been inserted into the binary search tree, validate the courses
        courses->ValidateCourses();
    } catch (runtime_error &e) {
        // output the error and return false
        cout << "runtime error: " << e.what() << endl;
        return false;
    }
    return true;
}

/**
 * Begin a routine for printing metadata of a course found in the binary search tree, including prompting
 * the user for a course number to search upon. The routine allows the user repeat the process multiple
 * times. Errors are handled gracefully, allowing the user a chance to repeat the process, should they
 * choose to do so.
 */
void BinarySearchTreeInterface::PrintCourseRoutine() {
    string userInput;
    string userInputToUpper;
    bool repeat = true;

    outputCourseNumberPrompt(); // prompt user for course number
    cin >> userInput; // get response from user
    while (repeat) { // repeat the process as many times as the user permits
        if (printCourse(strToUpper(userInput))) {
            outputAdditionalCoursePrompt(); // prompt user to repeat process
            cin >> userInput; // get response from user
            if (find(yeas.begin(), yeas.end(), userInput) != yeas.end()) {
                outputCourseNumberPrompt(); // prompt user for course number
                cin >> userInput; // get response from user
            } else {
                repeat = false;
            }
        } else {
            outputCourseNumberPrompt(); // prompt user for course number
            cin >> userInput; // get response from user
        }
    }
}

/**
 * Begin a routine for loading courses into the binary search tree, including prompting the user for
 * a csv file path. Errors are handled gracefully, allowing the user a chance to repeat the process,
 * should they choose to do so.
 */
void BinarySearchTreeInterface::LoadCoursesRoutine() {
    string userInput;
    bool repeat = true;

    outputFilePathPrompt(); // prompt user for file path
    cin >> userInput; // get response from user
    while (repeat) { // repeat the process until the courses are loaded or the user declines to retry
        if (loadCourses(userInput)) {
            cout << "Courses successfully loaded." << endl;
            coursesLoaded = true;
            repeat = false;
        } else {
            courses->Empty(); // empty the binary search tree, as the user may want to try again
            cout << "Courses have not been successfully loaded." << endl;
            outputTryAgainPrompt(); // prompt user to try again
            cin >> userInput; // get response from user
            if (find(yeas.begin(), yeas.end(), userInput) != yeas.end()) {
                outputFilePathPrompt(); // prompt user for file path
                cin >> userInput; // get response from user
            } else {
                repeat = false;
            }
        }
    }
}

/**
 * Output all courses in the binary search tree
 */
void BinarySearchTreeInterface::PrintCourseList() {
    cout << "Here is a sample schedule:" << endl << endl;
    courses->PrintCourseInformationInOrder();
}

/**
 * Output one course's metadata, given he course's number for lookup
 *
 * @param string& courseNum
 * @return bool
 */
bool BinarySearchTreeInterface::printCourse(const string& courseNum) {
    Node* node = courses->Search(courseNum);
    if (node->course.number.empty()) {
        cout << "Sorry, that course was not found." << endl;
        return false;
    }
    courses->PrintCourseLongVersion(node->course);
    return true;
}

/**
 * Output a prompt for user to enter a course number for information about a course
 */
void BinarySearchTreeInterface::outputCourseNumberPrompt() {
    cout << endl << "What course would you like to know about? ";
}

/**
 * Output a prompt asking the user if they would like additional course information
 */
void BinarySearchTreeInterface::outputAdditionalCoursePrompt() {
    cout << endl << "Would you like to know about another course? (yes/no) ";
}

/**
 * Output a prompt asking the user if they would like to try the last procedure again
 */
void BinarySearchTreeInterface::outputTryAgainPrompt() {
    cout << endl << "Would you like to try again? (yes/no) ";
}

/**
 * Output a welcome message to the user
 */
void BinarySearchTreeInterface::OutputWelcomeMessage() {
    cout << endl << "Welcome to the course planner." << endl;
}

/**
 * Output a farewell message to the user
 */
void BinarySearchTreeInterface::OutputExitMessage() {
    cout << endl << "Thank you for using the course planner!";
}

/**
 * Output a message to the user indicating the user's entry was invalid
 */
void BinarySearchTreeInterface::OutputInvalidEntryMessage(const string& userInput) {
    cout << userInput << " is not a valid option." << endl;
}

/**
 * Output a message to the user indicating the courses were not properly loaded
 */
void BinarySearchTreeInterface::OutputCoursesNotLoadedMessage() {
    cout << endl << "You will need to load the courses into the data structure first.";
}

/**
 * Output the main menu for the user
 */
void BinarySearchTreeInterface::OutputMainMenu() const {
    cout << endl;
    cout << "\t1. Load Data Structure." << endl;
    if (coursesLoaded) {
        cout << "\t2. Print Course List." << endl;
        cout << "\t3. Print Course." << endl;
    }
    cout << "\t9. Exit" << endl;
    cout << endl << "What would you like to do? ";
}

/**
 * Output a prompt for the user to enter a csv
 */
void BinarySearchTreeInterface::outputFilePathPrompt() {
    cout << endl << "Enter a csv path ";
}

/**
 * Transform the original string to an all upper case string
 *
 * @return string
 */
string BinarySearchTreeInterface::strToUpper(const string& original) {
    locale loc;
    string upperCase;
    for (char i : original) {
        upperCase.push_back(toupper(i, loc));
    }
    return upperCase;
}

