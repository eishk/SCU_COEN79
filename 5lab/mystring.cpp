#include "mystring.h"
#include <cctype>
#include <cassert>
#include <string.h>
#include <iostream>

using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5 {
    string::string(const char str[ ]) {
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, str, allocated);
    }

    string::string(char c) {
        current_length = 1;
        allocated = current_length + 1;
        characters = new char[allocated];
        characters[0] = c;
        characters[1] = '\0';
    }

    string::string(const string& source) {
        current_length = source.current_length;
        allocated = source.allocated;
        characters = new char[source.current_length];
        strncpy(characters, source.characters, source.current_length);
    }

    string::~string( ) {
        current_length = 0;
        allocated = 0;
        delete [] characters;
    }

    void string::operator +=(const string& addend) {
        size_t addL = addend.current_length;
        size_t finalL = current_length + addL;
        allocated = finalL + 1;
        reserve(allocated);
        strncat(characters, addend.characters, addL);
        current_length = finalL;
        return;
    }

    void string::operator +=(const char addend[ ]) {
        size_t addL = strlen(addend);
        size_t finalL = current_length + addL;
        allocated = finalL + 1;
        reserve(allocated);
        strncat(characters, addend, addL);
        current_length = finalL;
        return;
    }
                
    void string::operator +=(char addend) {
        size_t finalL = current_length + 1;
        allocated = finalL + 1;
        reserve(allocated);
        characters[current_length] = addend;
        current_length = finalL;
        return;
     }

    void string::reserve(size_t n) {
        char* new_characters = new char[n];
        if (characters != NULL){
          strncpy(new_characters, characters, current_length);
          delete []characters;
        }
        characters = new_characters;
        return;
    }

    string& string::operator =(const string& source) {
        this->dlt(0, current_length);
        if (current_length != source.current_length) {
            allocated = source.allocated;
            reserve(allocated);
        }
        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;
        return *this;
    }

    void string::insert(const string& source, unsigned int position) {
        assert(position <= length());
        char* tempA = new char[current_length + source.current_length + 1];
        if (position > 0) {
            strncpy(tempA, characters, position);
        }
        char* tempB = new char[allocated - position];
        int i, j;
        for (i = position, j = 0; i <= current_length; i++, j++) {
            tempB[j] = characters[i];
        }
        delete[] characters;
        strncat(tempA, source.characters, source.current_length);
        strncat(tempA, tempB, strlen(tempB));
        characters = tempA;
        current_length += source.current_length;
        allocated = current_length + 1;
        return;
      }

    void string::dlt(unsigned int position, unsigned int num) {
        assert((position + num) <= length());
        int i;
        for (i = position; i < length(); i++){
          characters[i] = characters[i + num];
        }
        current_length -= num;
        return;
    }

    void string::replace(char c, unsigned int position) {
        assert(position < length());
        characters[position] = c;
        return;
      }

    void string::replace(const string& source, unsigned int position) {
        assert((position + source.current_length) <= current_length);
        int i, j = 0;
        for(i = position; i < (position + source.length()); i++){
            *(characters + i) = source[j++];
        }
        return;
    }

    char string::operator [ ](size_t position) const {
        assert(position < length());
        return characters[position];
    }

    int string::search(char c) const {
        int index = -1;
        int i;
        for (i = 0; i < length(); i++) {
            if (c == characters[i]) {
                index = i;
                break;
            }
        }
        return index;
    }

    int string::search(const string& substring) const {
        int index = -1;
        char* tmp = strstr(characters, substring.characters);
        if (tmp != NULL) {
          index = *tmp - *characters;
        }
        return index;
      }

    unsigned int string::count(char c) const {
        unsigned int counter = 0;
        int i;
        for (i = 0; i < length(); i++) {
            if(c == characters[i]){
                counter++;
            }
        }
        return counter;
    }

    std::ostream& operator <<(std::ostream& outs, const string& source) {
        outs << source.characters;
        return outs;
    }

    bool operator ==(const string& s1, const string& s2) {
        return (strcmp(s1.characters, s2.characters) == 0);
    }

    bool operator !=(const string& s1, const string& s2) {
        return (strcmp(s1.characters, s2.characters) != 0);
    }

    bool operator > (const string& s1, const string& s2) {
        return (strcmp(s1.characters, s2.characters) > 0);
    }

    bool operator < (const string& s1, const string& s2) {
        return (strcmp(s1.characters, s2.characters) < 0);
    }

    bool operator >=(const string& s1, const string& s2) {
        return ((s1 > s2) || (s1 == s2));
    }

    bool operator <=(const string& s1, const string& s2) {
        return ((s1 < s2) || (s1 == s2));
    }

    string operator +(const string& s1, const string& s2) {
        string temp;
        temp.reserve(s1.length() + s2.length() + 1);
        temp += s1;
        temp += s2;
        return temp;
    }

    string operator +(const string& s1, const char addend[ ]) {
        string temp;
        temp.reserve(s1.length() + strlen(addend) + 1);
        temp += s1;
        temp += addend;
        return temp;
    }

    std::istream& operator >> (std::istream& ins, string& target) {
        while(ins && isspace(ins.peek())){
            ins.ignore();
        }
        char* input = new char[500];
        ins >> input;
        target = string(input);
        return ins;
    }    
}
