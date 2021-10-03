// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    // Constructor with initial capacity input
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    // Constructor when given a database to copy
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
        used_slots = src.used_slots;
        aloc_slots = src.aloc_slots;
        company_array = new company[aloc_slots];
        std::copy(src.company_array, src.company_array + src.used_slots, company_array);
    }
    
    // Constructor when equals operator is used
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
        std::cout << "copying elements of database...";
        if (this == &rhs) {
            return *this;
        }
        company* holder = new company[rhs.aloc_slots];
        delete [] company_array;
        company_array = holder;
        std::copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array);
        used_slots = rhs.used_slots;
        aloc_slots = rhs.aloc_slots;
        return *this;
    }
    
    // Destructor
    database::~database() {
        delete [] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    // Reserves space size of new capacity for the database.
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        company* new_comp = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, new_comp);
        delete [] company_array;
        company_array = new_comp;
        aloc_slots = new_capacity;
        return;
    }
    
    // Inserts company entry into database and returns true if successful,
    // false if not
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
        company *insert_comp = new company(entry);
        if (used_slots >= aloc_slots) {
            reserve(aloc_slots * 2);
        }
        company_array[used_slots] = *insert_comp;
        used_slots++;
        return true;
    }
    
    // Inserts item along with its price in for the given company in the database.
    // If successful, returns true else false.
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);
        
        size_type place;
        if ((place = search_company(company)) < 0) {
            return false;
        }
        else {
            bool ans = company_array[place].insert(product_name, price);
            return ans;
        }
    }
    
    // Erases company from database if company is present. Returns
    // true if successful, else false;
    bool database::erase_company(const std::string &company) {
        size_type company_index = search_company(company);
        if (company_index >= used_slots) {
            return false;
        }
        else {
            for (size_type i = company_index; i < used_slots-1; ++i) {
                company_array[i] = company_array[i+1];
            }
            --used_slots;
            return true;
        }
    }
    
    // Erases item for the given company if possible. If the action is
    // successful, returns true else false;
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        assert(cName.length() > 0 && pName.length() > 0);
        size_type place = search_company(cName);
        if (place == COMPANY_NOT_FOUND) {
            return false;
        }
        else {
            bool ans = company_array[place].erase(pName);
            return ans;
        }
    }
    
    
    // Searches database for whether given company exists in the database.
    // If not, returns false. Else true.
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);
        size_type place = -1;
        for (size_type i = 0; i < used_slots; ++i) {
            if (company_array[i].get_name() == company) {
                place = i;
            }
        }
        if (place == -1)
            return COMPANY_NOT_FOUND;
        return place;
    }
    
    // Prints the items catalogued for the given company. If company is found
    // in the database, returns true. Else false.
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    // Prints companies contained in the database.
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
