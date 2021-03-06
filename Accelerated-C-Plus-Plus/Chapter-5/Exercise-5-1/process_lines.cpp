#include "Process_lines.h"
#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <vector>

using std::istream;
using std::list;
using std::string;
using std::getline;
using std::isspace;
using std::tolower;
using std::vector;

istream& read_lines(istream& input_stream, list<string>& line_list) {
    if (input_stream) {
        // clear the previous content of the list
        line_list.clear();

        string input_line;
        // read the input lines
        while (getline(input_stream, input_line)) {
            line_list.push_back(input_line);
        }

        // make the stream ready for the next input
        input_stream.clear();
        
    }

    return input_stream;
}

list<string> extract_words(const string& line) {
    list<string> words_list;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != line.size()) {
        while (i != line.size() && isspace(line[i])) {
            ++i;
        }
        
        string_size j = i;
        while (j != line.size() && !isspace(line[j])){
            ++j;
        }

        if (i != j) {
            words_list.push_back(line.substr(i, j - i));
            i = j;          
        }
    }

    return words_list;
}

list<Line_rotations>& rotate_lines(const list<string>& line_list, list<Line_rotations>& rotated_lines) {
    // a line from the input list of lines
    string the_line; 
    // the definition of a type for constant iterators of string lists
    typedef list<string>::const_iterator string_list_it;
    // the list for the extracted words of the line from the input list of lines
    list<string> word_list;
    // each of the line structures to be accumulated in the rotated lines structure 
    Line_rotations line_structure;
    // the iterator for the input list of lines
    string_list_it list_it;
    list<string>::const_reverse_iterator list_r_it;
    // the string containing the rotated line
    string rotated_line;
    for (string_list_it it = line_list.begin(); it != line_list.end(); ++it) {
        the_line = *it;
        // the words of the line are stored in the word list
        word_list = extract_words(the_line);
        // an iterator is pointed to the end of the word list
        list_r_it = word_list.rbegin();
        // the last word of the line is stored in the last word element of the structure
        line_structure.lastWord = *list_r_it;
        // an iterator is pointed to the beginning of the word list
        list_it = word_list.begin();
        // the first word of the line is stored in the first word element of the structure
        line_structure.firstWord = *list_it;
        for (list<string>::size_type i = 0; i < word_list.size(); ++i) {
            // rotated_line = "";
            // send the first word to the end of the line
            word_list.push_back(*list_it);
            // erase the first word of the line
            word_list.erase(list_it);
            // point the iterator to the new beginning of the list
            list_it = word_list.begin();
            // the rotated line is stored in the rotation element of the structure
            line_structure.rotation = word_list;
            // the structure containing the first word and rotated version of the line is stored
            // in the rotated lines structure 
            rotated_lines.push_back(line_structure);
        }
    }

    return rotated_lines;
}

bool string_compare(const Line_rotations struct1, const Line_rotations struct2) {
    string::size_type i = 0;
    list<string>::const_iterator it1, it2;
    it1 = struct1.rotation.begin();
    it2 = struct2.rotation.begin();
    string word1, word2;
    word1 = *it1;
    word2 = *it2;
    while (tolower(word1[i]) == tolower(word2[i])) {
        ++i;
    }
    return tolower(word1[i]) < tolower(word2[i]);
}

list<string::size_type> num_of_unrotation_chars(const list<Line_rotations>& rotation_structs) {
    list<string::size_type> unrotation_char_num;
    string::size_type char_num;
    string first_word, current_word, last_word;
    typedef list<Line_rotations>::const_iterator line_it;
    list<string> rotated_line;
    list<string>::const_reverse_iterator it2;
    for (line_it it = rotation_structs.begin(); it != rotation_structs.end(); ++it) {
        first_word = it->firstWord;
        last_word = it->lastWord;
        rotated_line = it->rotation;
        char_num = 0;
        it2 = rotated_line.rbegin();
        current_word = *it2;
        if (current_word != last_word) {
            while (current_word != first_word) {
                char_num += current_word.size() + 1;
                ++it2;
                current_word = *it2;
            }
            char_num += first_word.size() + 1;
        }
        unrotation_char_num.push_back(char_num);
    }

    return unrotation_char_num;
}

string::size_type find_max(const list<string::size_type>& unrotation_char_nums) {
    string::size_type max_size = 0, current_size;
    for (list<string::size_type>::const_iterator it = unrotation_char_nums.begin(); it != unrotation_char_nums.end(); ++it) {
        current_size = *it;
        if (current_size > max_size) max_size = current_size;
    }

    return max_size;
}

list<string> permuted_index(const list<string::size_type>& unrotation_char_nums, const list<Line_rotations>& rotated_lines_struct) {
    string::size_type max_size = find_max(unrotation_char_nums);
    list<string> the_permuted_index, rotated_line;
    list<string::size_type>::const_iterator it2 = unrotation_char_nums.begin();
    list<string>::iterator str_lst_it;
    string first_word, last_word, formatted_line;
    Line_rotations line_struct;
    list<string>::const_reverse_iterator str_lst_rev_it;
    for (list<Line_rotations>::const_iterator it = rotated_lines_struct.begin(); it != rotated_lines_struct.end(); ++it) {
        line_struct = *it;
        first_word = line_struct.firstWord;
        last_word = line_struct.lastWord;
        rotated_line = line_struct.rotation;
        str_lst_rev_it = rotated_line.rbegin();
        if (*str_lst_rev_it == last_word) {
            string spaces(max_size, ' ');
            formatted_line = "";
            formatted_line += spaces;
            for (str_lst_it = rotated_line.begin(); str_lst_it != rotated_line.end(); ++str_lst_it){
                formatted_line += *str_lst_it + ' ';
            }
            formatted_line.pop_back();
        }
        else {
            str_lst_it = rotated_line.begin();
            while (*str_lst_it != first_word) {
                rotated_line.push_back(*str_lst_it);
                rotated_line.erase(str_lst_it);
                str_lst_it = rotated_line.begin();
            }
            string spaces(max_size-(*it2), ' ');
            formatted_line = "";
            formatted_line += spaces;
            for (str_lst_it = rotated_line.begin(); str_lst_it != rotated_line.end(); ++str_lst_it){
                formatted_line += *str_lst_it + ' ';
            }
            formatted_line.pop_back();
        }
        ++it2;
        the_permuted_index.push_back(formatted_line);
    }

    return the_permuted_index;
}