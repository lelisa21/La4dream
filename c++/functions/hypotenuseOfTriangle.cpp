#include <iostream>
#include <cmath> 

using namespace std;


double hypotenuse(double side1, double side2);

int main() {
    double side1, side2;
    
            
    cout << "Enter the length of the first side: ";
    cin >> side1;
    cout << "Enter the length of the second side: ";
    cin >> side2;

    
    double hypotenuseLength = hypotenuse(side1, side2);

    
    cout << "The length of the hypotenuse is: " << hypotenuseLength << endl;

    return 0;
}


double hypotenuse(double side1, double side2) {
    
    return sqrt(pow(side1, 2) + pow(side2, 2));
}

