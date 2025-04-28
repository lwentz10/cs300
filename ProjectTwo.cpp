// ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>


using namespace std;

//struct for a course
struct Course {
	string courseNumber;
	string courseTitle;
	vector<string> prerequisites;
};

//Map that holds the courses
map<string, Course> courseMap;

vector<string> split(const string& line, char delimiter) {
	vector<string> tokens;
	stringstream ss(line);
	string token;

	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

//function for loading course data from files
void loadCoursesFromFile(const string& fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Error:This file could not open " << fileName << endl;
		return;
	}
	courseMap.clear();
	string line;

	while (std::getline(file, line)) {
		vector<string> parts = split(line, ',');

		if (parts.size() < 2) continue;

		Course course;
		course.courseNumber = parts[0];
		course.courseTitle = parts[1];

		for (size_t i = 2; i < parts.size(); ++i) {
			if (!parts[i].empty()) {
				course.prerequisites.push_back(parts[i]);
			}
		}
		courseMap[course.courseNumber] = course;
	}
	file.close();
	cout << "Courses have been loaded successfully from file.\n";
}
//Print the course list
void printCourseList() {
	vector<string> keys;
	for (const auto& pair : courseMap) {
		if (pair.first.find("CSCI") == 0 || pair.first.find("MATH") == 0) {
			keys.push_back(pair.first);
		}
	}
	sort(keys.begin(), keys.end());

	cout << "\nCourse List:\n";
	for (const string& key : keys) {
		cout << key << ": " << courseMap[key].courseTitle << endl;
	}
	void printCourseDetails(const string & courseNumber) {
		auto it = courseMap.find(courseNumber);
		if (it == courseMap.end()) {
			cout << "Error: Course was not found.\n";
			return;
		}
		const Course& course = it->second;
		cout << "\n" << course.courseNumber << ": " << course.courseTitle << endl;

		if (!course.prerequisites.empty()) {
			cout << "Prerequisites: ";
			for (size_t i = 0; i < course.prerequisites.size(); ++i) {
				string prereq = course.prerequisites[1];
				cout << prereq;
				if (i != course.prerequisites.size() - 1) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		else {
			cout << "No Prerequisites\n";
		}
	}
	//Display the menu
	void displayMenu() {
		cout << "\nMenu Options:\n"
			<< "1. Load Data Structure\n"
			<< "2. Print Course List\n"
			<< "3. Print Course\n"
			<< "9. Exit\n";
	}
	int main() {
		int choice = 0;
		string fileName;
		string courseNumber;

		while (choice != 9) {
			displayMenu();
			cout << "Enter your choice: ";
			cin >> choice;
			cin.ignore();

			switch (choice)[
				case 1:
					cout << "Enter the file name: ";
					getline(cin, fileName);
					loadCoursesFromFile(fileName);
					break;

				case 2:
					printCourseList();
					break;

				case 3:
					cout << "enter the course number: ";
					cin >> courseNumber;
					printCourseDetails(courseNumber);
					break;

				case 9:
					cout << "Exit program.\n";
					break;

				defaul:
					cout << "Invalid please try again.\n";
		}
	}
	return 0;
}
