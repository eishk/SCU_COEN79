//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence::sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence::sequence(const sequence& source)
    {
        init();
        *this = source;
    }

    // Destructor
    sequence::~sequence() {
        list_clear(head_ptr);
        many_nodes = 0;
    }

    // Start Function - moves cursor to front of sequence
    void sequence::start() {
        precursor = head_ptr;
        cursor = head_ptr;
        return;
    }

    // End function
    void sequence::end() {
        cursor = tail_ptr;
        // If only one pointer
        if (head_ptr == tail_ptr) {
            precursor = NULL;
        }
        else {
            precursor = head_ptr;
            // While the precursor's next isn't the cursor, keep moving forward
            while (precursor->link() != cursor) {
                precursor = precursor->link();
            }
        }
        return;
    }

    // Advance function
    void sequence::advance() {
        assert(is_item());
        // If we are at the last node in sequence
        if (cursor == tail_ptr) {
            cursor = NULL;
            return;
        }
        // If not, move one forward
        precursor = cursor;
        cursor = cursor->link();
        return;
    }

    // Insert entry into sequence function
    void sequence::insert(const value_type& entry) {
        // If sequence is empty
        if (head_ptr == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        }
        // If sequence is non_empty and cursor at the beginning
        else if (is_item() && cursor == head_ptr) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
        }
        // If sequence is non_empty and cursor not at the beginning
        else if (is_item() && cursor != head_ptr) {
            list_insert(precursor, entry);
            cursor = precursor->link();
        }
        // If cursor is not pointing to anything
        else if (!is_item()) {
            list_head_insert(head_ptr, entry);
            tail_ptr = precursor->link();
            cursor = head_ptr;
            precursor = NULL;
        }
        many_nodes++;
        return;
    }

    // Attach function
    void sequence::attach(const value_type& entry) {
        // If only one node
        if (is_item() && many_nodes == 1) {
            list_insert(head_ptr, entry);
            precursor = head_ptr;
            tail_ptr = precursor->link();
            cursor = tail_ptr;
        }
        // If more than one node and cursor at the head of sequence
        else if (is_item() && many_nodes > 1 && cursor == head_ptr) {
            list_insert(head_ptr, entry);
            precursor = head_ptr;
            cursor = precursor->link();
        }
        // If 1+ node and cursor not at head of sequence
        else if (is_item() && cursor != head_ptr) {
            // If cursor is tail
            if (cursor == tail_ptr) {
                list_insert(tail_ptr, entry);
                tail_ptr = cursor->link();
                precursor = cursor;
                cursor = tail_ptr;
            }
            // If cursor is not at tail nor at head
            else {
                list_insert(cursor, entry);
                advance();
            }
        }
        // Many nodes in sequence but cursor not pointing to anything
        else if (!is_item() && many_nodes > 0) {
            list_insert(tail_ptr, entry);
            precursor = tail_ptr;
            cursor = precursor->link();
            tail_ptr = cursor;
        }
        // Empty sequence
        else if (head_ptr == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        }
        many_nodes++;
        return;
    }

    // Equals operator
    void sequence::operator =(const sequence& source) {
        // If assigning same to same
        if (this == &source) {
            return;
        }
        // Clearing out current sequence
        many_nodes = 0;
        list_clear(head_ptr);
        node* tail_t;
        // Copy
        list_copy(source.head_ptr, head_ptr, tail_t);
        cursor = head_ptr;
        tail_ptr = tail_t;
        precursor = head_ptr;
        node *temp = source.head_ptr;
        // If cursor doesn't point to anything
        if (source.cursor == NULL) {
            precursor = tail_ptr;
            cursor = NULL;
        }
        else {
            // Moves precursor to right place if cursor does point to something
            while (temp != source.precursor) {
                precursor = precursor->link();
                temp = temp->link();
            }
            // Moves cursor accordingly
            if (precursor != NULL) {
                cursor = precursor->link();
            }
        }
        many_nodes = source.many_nodes;
    }

    // Remove current entry in sequence
    void sequence::remove_current() {
        assert(is_item());
        // Checks if more than one node
        if (head_ptr->link() == NULL) {
            delete cursor;
            head_ptr = NULL;
            tail_ptr = NULL;
            precursor = NULL;
            cursor = NULL;
        }
        // When cursor is at head and more nodes
        else if (cursor == head_ptr && head_ptr->link() != NULL) {
            cursor = head_ptr->link();
            precursor = NULL;
            list_head_remove(head_ptr);
        }
        // When cursor is at tail and more nodes
        else if (cursor == tail_ptr && many_nodes > 1) {
            tail_ptr = precursor;
            tail_ptr->set_link(NULL);
            delete cursor;
            cursor = NULL;
        }
        // When cursor isn't head or tail
        else if (cursor != head_ptr && cursor != tail_ptr) {
            precursor->set_link(cursor->link());
            delete cursor;
            cursor = precursor->link();
        }
        many_nodes--;
    }

    // Returns size of sequence
    sequence::size_type sequence::size() const {
        return many_nodes;
    }

    // Checks if cursor is pointing to something
    bool sequence::is_item() const {
        if (cursor == NULL) {
            return false;
        }
        else {
            return true;
        }
    }

    // Returns entry at current cursor in sequence
    sequence::value_type sequence::current() const {
        assert(is_item());
        return cursor->data();
    }
}
