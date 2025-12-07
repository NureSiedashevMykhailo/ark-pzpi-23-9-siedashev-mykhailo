
#include <iostream>
#include <vector>
#include <string>
#include <memory>       
#include <mutex>        
#include <stdexcept>    
#include <cmath>        

// Helper definitions for compilation
class User {};
bool error() { return false; }
void func() {}
void do_other() {}
int calculate() { return 10; }
class Base { public: virtual ~Base() = default; };
class Derived : public Base {};
void func_overload(int) { std::cout << "Called func(int)\n"; }
void func_overload(char*) { std::cout << "Called func(char*)\n"; }

// Rule 1: Naming Conventions
namespace Rule1_Naming {

    // Bad Style: Unclear names, mixed case
    /*
    int d; // elapsed days
    class manager { 
        int Val; 
    };
    */

    // Good Style: snake_case for variables, CamelCase for types
    int days_since_creation = 0;

    class AccountManager {
        int balance_amount = 0;
    };
}

// Rule 2: Code Structure
namespace Rule2_Structure {
    void example(bool x) {
        // Bad Style: Hard to read
        /*
        if(x){func();return;}else{do_other();}
        */

        // Good Style: Structured with indentation
        if (x) {
            func();
            return;
        } else {
            do_other();
        }
    }
}

// Rule 3: Memory Management (Smart Pointers)
namespace Rule3_Memory {

    // Raw Pointers (Unsafe): Risk of memory leaks
    void unsafe() {
        User* u = new User();
        
        if (error()) return; // MEMORY LEAK: 'u' is not deleted
        
        delete u;
    }

    // Smart Pointers (Safe): Automatic memory management
    void safe() {
        auto u = std::make_unique<User>();
        
        if (error()) return; 
        // Destructor called automatically here
    }
}

// Rule 4: Const Correctness
namespace Rule4_Const {

    // Mutating (Unsafe): Function might accidentally change the string
    /*
    void print(std::string& str) {
        std::cout << str;
    }
    */

    // Const Correct (Safe): Guarantees string is not modified
    void print(const std::string& str) {
        std::cout << str;
    }
}

// Rule 5: RAII (Resource Acquisition Is Initialization)
namespace Rule5_RAII {
    std::mutex m;
    void process_data() {}

    // Manual Locking (Bad): Risk of deadlock
    void bad_lock() {
        m.lock();
        process_data(); 
        m.unlock(); 
    }

    // RAII Wrapper (Good): Automatic unlocking
    void good_lock() {
        std::lock_guard<std::mutex> lk(m); 
        process_data(); 
    }
}

// Rule 6: Error Handling
namespace Rule6_ErrorHandling {
    
    // Return Codes (Old Style)
    void old_style() {
        /*
        int res = calculate();
        if (res == -1) handle_error();
        */
    }

    // Exceptions (C++ Style)
    void new_style() {
        try {
            int res = calculate();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what();
        }
    }
}

// Rule 7: Performance (Pass by Reference)
namespace Rule7_Performance {

    // Pass by Value (Slow): Copies the vector
    /*
    void process(std::vector<int> data);
    */

    // Pass by Const Reference (Fast): No copy
    void process(const std::vector<int>& data) {
        // Read only access
    }
}

// Rule 8: Casting (Type Safety)
namespace Rule8_Casting {
    void example() {
        Derived derived_obj;
        Base* derived_ptr = &derived_obj;

        // C-Style Cast (Unsafe)
        /*
        Base* b = (Base*)derived_ptr; 
        */

        // C++ Casts (Safe): Checked by compiler
        Base* b = static_cast<Base*>(derived_ptr); 
    }
}

// Rule 9: nullptr vs NULL
namespace Rule9_Nullptr {
    
    void example() {
        // NULL (Bad): Treated as 0 (int)
        /* func_overload(NULL); 
        */

        // nullptr (Good): Treated as pointer type
        func_overload(nullptr); 
    }
}

// Rule 10: Namespaces
// Global Pollution (Bad)
/*
using namespace std; 
int count() { return 0; } 
*/

// Explicit Scoping (Good)
namespace Rule10_Namespaces {
    void print() {
        std::cout << "Hello World"; 
    }
}

int main() {
    std::cout << "C++ Code Examples successfully compiled." << std::endl;
    return 0;
}