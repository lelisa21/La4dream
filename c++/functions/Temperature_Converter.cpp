#include <iostream>
#include <string>
#include <algorithm> 
using namespace std;

float tempConversion(float temperature, string fromUnit, string toUnit) {
    float result;


    transform(fromUnit.begin(), fromUnit.end(), fromUnit.begin(), ::tolower);
    transform(toUnit.begin(), toUnit.end(), toUnit.begin(), ::tolower);

   
    if (fromUnit == "c" || fromUnit == "celsius") {
        fromUnit = "celsius";
    } else if (fromUnit == "f" || fromUnit == "fahrenheit") {
        fromUnit = "fahrenheit";
    } else if (fromUnit == "k" || fromUnit == "kelvin") {
        fromUnit = "kelvin";
    }

    if (toUnit == "c" || toUnit == "celsius") {
        toUnit = "celsius";
    } else if (toUnit == "f" || toUnit == "fahrenheit") {
        toUnit = "fahrenheit";
    } else if (toUnit == "k" || toUnit == "kelvin") {
        toUnit = "kelvin";
    }

    // Perform conversions based on the units
    if (fromUnit.compare("celsius") == 0) {
        if (toUnit.compare("fahrenheit") == 0) {
            result = (9.0 / 5.0) * temperature + 32;
        } else if (toUnit.compare("kelvin") == 0) {
            result = temperature + 273.15; 
        } else {
            result = temperature; 
        }
    } else if (fromUnit.compare("fahrenheit") == 0) {
        if (toUnit.compare("celsius") == 0) {
            result = (5.0 / 9.0) * (temperature - 32);
        } else if (toUnit.compare("kelvin") == 0) {
            result = (5.0 / 9.0) * (temperature - 32) + 273.15; 
        } else {
            result = temperature; 
        }
    } else if (fromUnit.compare("kelvin") == 0) {
        if (toUnit.compare("fahrenheit") == 0) {
            result = (temperature - 273.15) * 9.0 / 5.0 + 32;
        } else if (toUnit.compare("celsius") == 0) {
            result = temperature - 273.15;
        } else {
            result = temperature; 
        }
    } else {
        cout << "Invalid unit provided!" << endl;
        return -9999; 
    }

    return result;
}

int main() {
    float temp;
    string fromUnit, toUnit;

    cout << "Enter the temperature: ";
    cin >> temp;

    cout << "Enter from which you want to change (i.e., c for Celsius, f for Fahrenheit, or k for Kelvin): ";
    cin >> fromUnit;

    cout << "Enter to which unit you want to change (i.e., c for Celsius, f for Fahrenheit, or k for Kelvin): ";
    cin >> toUnit;

    float convertedTemp = tempConversion(temp, fromUnit, toUnit);
    
    // Check for error in conversion
    if (convertedTemp != -9999) {
        cout << "The temperature converted from " << fromUnit << " to " << toUnit << " is " << convertedTemp << endl;
    }

    return 0;
}
