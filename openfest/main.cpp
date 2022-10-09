#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char * argv[]) {

    int numberOfElements;

    cout << "Enter the number of elements: ";
    cin >> numberOfElements;
    cout << endl << "You will have " << numberOfElements << " elements in your queue. Now enter each element!";

    vector<int> elements(numberOfElements);
    for(size_t cur = 1; cur <= numberOfElements; cur++) {
        cout << endl << "Enter element " << cur << ": ";
        cin >> elements[cur];
    }

    cout << endl << "You entered all elements. Here they are: ";
    for(auto cur : elements)
        cout << cur << " ";
    cout << endl;

    return 0;
}
