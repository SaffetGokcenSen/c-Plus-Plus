#include "Letter_grades.h"

using std::list;
using std::cin;
using std:: map;
using std::cout;
using std::endl;

int main() {
    // read in the number grades
    list<double> grade_list = read_grades(cin);

    // create the letter grade distribution
    map<char, list<double> > letter_grade_dist = get_letter_grades(grade_list);

    // put a newline for clear output
    cout << endl;

    // report the distribution of the letter grades
    for (map<char, list<double> >::const_iterator it = letter_grade_dist.begin(); 
    it != letter_grade_dist.end(); ++it) {
        // the letter grade
        char letter_grade = it->first;
        // the list of grades
        list<double> the_list = it->second;
        if (the_list.empty()) {
            cout << "There are no students with the letter grade " 
                 << letter_grade << "." << endl;
        }
        else {
            list<double>::size_type i = (it->second).size();
            if (i == 1) {
                cout << "There is a student with the letter grade " 
                     << letter_grade << "." << endl;
            }
            else {
                cout << "There are " << i << " students with the letter grade "
                 << letter_grade << "." << endl;
            }
        }
    }

    return 0;
}