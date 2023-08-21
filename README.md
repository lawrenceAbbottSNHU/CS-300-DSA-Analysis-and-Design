# CS-300-DSA-Analysis-and-Design

# Summarize the project and what problem it was solving.
The scenario for this project involves a team of academic advisors in the Computer Science department at ABCU who have asked us to write code to aid academic advisements during their talks with students. The application that we have developed demonstrates how a list of computer science courses may be loaded into a Binary Search Tree structure. The user may perform actions such as load the data into the data structure, print the list of courses, and print information related to a course. Immediately after the courses are loaded into the binary search tree they are validated, ensuring that each course prerequisite exists somewhere within the list of courses provided. Ultimately, this project serves as an example of the importance of choosing the appropriate data structure for a particular application. By choosing the appropriate data structure, the user experience is vasly improved. In this case, the appropriate data structure was a Binary Search Tree, which is quick to be traversed for operations such as printing a list of courses in alphanumeric order.

# What did you do particularly well?
I feel that I have done well to create a user interface that is robust enough to handle less than optimal user input. For instance, if the user happens to mistype the file name, this event is handled gracefully, with appropriate feedback, and provides a chance for the user to correct thier mistake. Additionally, if the user were to choose the option that allows them to print out course information, they are given the opportunity to repeat this process as many times as they please, only returning to the main menu after they choose to do so.

# Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
One place where it would be nice to improve this code would be to including the ability for the user to select the appropriate file from which to load the courses, via a file system interface, thus reducing the propability that the user mistakenly mistypes the file name. 

# Did you find writing any piece of this code challengeing and how did you overcome this? What tools and/or resources are you adding to your support network?
I was challenged in that I had not considered what would happen should the user mistype the filename during the load courses process. It was only after I was testing this process that I realized that in the event of an erroneous user input such as this, the binary search should be re-initialized, or in other words emptied and made ready should the user attempt the load process again.

# What skills from this project will be particularly transferable to other projects or course work?
The skill that I believe is most transferable to other projects is the critical thinking involved in choosing the appropriate data structure for the job. By performing a run time analasis for each potential data structure, one can determine the best data structure.
