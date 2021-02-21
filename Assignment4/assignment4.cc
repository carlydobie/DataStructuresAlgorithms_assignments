#include <iostream>
#include <iomanip>
#include "assignment4.h"
using namespace std;

int main() {
    Queue q;
    string op;
    int val = 0;
 
   cout << "operation -- size front end" << endl;
   cin >> op;
   while ( !cin.eof() ) {
        if ( op == "push" ) {
            cin >> val;
            q.push( val );
            cout << op << " " << val << "    -- ";
        }
        else if ( op == "pop" ) {
            q.pop();
            cout << op << "       -- ";
        }
        else {
            cerr << "Error input: " << op << endl;
            return 1;
        }
        if ( q.size() > 0 )
            cout << setw(3) << q.size() << setw(5) << q.front() << setw(5) << q.back() << endl;
        else
            cout << setw(3) << q.size() << endl;

        cin >> op;
    }

    while ( !q.empty() )
        q.pop();

    return 0;
}


