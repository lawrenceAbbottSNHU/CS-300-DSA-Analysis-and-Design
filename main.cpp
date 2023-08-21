#include <iostream>
#include "BinarySearchTree.hpp"
#include "BinarySearchTreeInterface.hpp"

using namespace std;

int main() {

    int userInput = 0;
    BinarySearchTreeInterface bstInterface;

    bstInterface.OutputWelcomeMessage();
    while (true) { // loop until user chooses to exit, using the exit option
        bstInterface.OutputMainMenu();
        cin >> userInput;
        if (userInput == bstInterface.exitOption) {
            bstInterface.OutputExitMessage();
            return 0; // exit
        }
        switch (userInput) {
            case 1:
                bstInterface.LoadCoursesRoutine();
                break;
            case 2:
                bstInterface.coursesLoaded ? bstInterface.PrintCourseList()
                                           : bstInterface.OutputCoursesNotLoadedMessage();
                break;
            case 3:
                bstInterface.coursesLoaded ? bstInterface.PrintCourseRoutine()
                                           : bstInterface.OutputCoursesNotLoadedMessage();
                break;
            default:
                bstInterface.OutputInvalidEntryMessage(to_string(userInput));
                break;
        }
    }
}
