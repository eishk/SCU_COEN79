#include "sequence.h"

using namespace std;
using coen79_lab6::sequence;

void printSequence(sequence &s) {
    sequence seq(s);
    seq.start();

    // Loop to print the sequence.
    while(seq.is_item()) {
        cout << seq.current() << " ";
        seq.advance();
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    sequence s1;
    
    s1.attach(50);
    printSequence(s1);
    s1.attach(40);
    printSequence(s1);
    
}
