// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        *this = src;
    }

    
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
        
        this->company_name = src.get_name();
        list_clear(this->head_ptr);
        list_copy(src.get_head(), this->head_ptr, this->tail_ptr);
        return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }

        // sets tail and head to new node if first node of list, otherwise inserts at tail
        if (head_ptr == NULL) {
            list_init(head_ptr, tail_ptr, product_name, price);
        } else {
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
        
        // removes and returns true if product_name is found, otherwise returns false
        if (list_contains_item(this->head_ptr, product_name)) {
            node* curr = head_ptr;

            // loop through linkedlist to place curr node pointer to previous
            // node that matches product_name to erase
            while (curr->getLink()->getName() != product_name) {
                curr = curr->getLink();
            }

            node* remove = curr->getLink();
            curr->setLink(remove->getLink());
            delete remove;
            return true;
        } else {
            return false;
        }
        
    }
    
    
}
