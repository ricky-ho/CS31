//
//  main.cpp
//  Project 2
//
//  Created by Ricky Ho on 4/15/17.
//  Copyright © 2017 Ricky Ho. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    const double RATE1 = 0.013;
    const double RATE2 = 0.01;
    const double RATE3 = 0.009;
    const double SPECIALRATE2 = 0.002;
    const double THOUSAND = 1000;
    
    // Collects the name of the asset
    cout << "Asset name: ";
    string assetName;
    getline(cin, assetName);
    
    // Collects the value of the asset in thousands
    cout << "Value (in thousands): ";
    double value;
    cin >> value;
    cin.ignore(10000, '\n');
    
    // Collects the category of the asset
    cout << "Category: ";
    string category;
    getline(cin, category);
    
    // Error message if asset name is empty
    if(assetName == "")
    {
        cout << "---" << endl << "You must enter an asset name." << endl;
        return 1;
    }
    
    // Error message if asset value is negative
    if(value < 0)
    {
        cout << "---" << endl << "The asset value must be nonnegative." << endl;
        return 1;
    }
    
    // Error message if asset category is empty
    if(category == "")
    {
        cout << "---" << endl << "You must enter an asset category." << endl;
        return 1;
    }
    
    double trusteeFee = 0;
    cout.setf(ios::fixed);
    cout.precision(0);
    
    // Calculates trustee fee if asset value is less than or equal to 1 million
    if(value <= 1000)
        trusteeFee = (value * RATE1) * THOUSAND;
    
    // Calculates trustee fee for asset values over 1 million in royalty/mutual fund category
    if(category == "mutual fund" || category == "royalty")
    {
        if(value > 1000 && value <= 10000)
            trusteeFee = ((1000 * RATE1) + (value - 1000) * SPECIALRATE2) * THOUSAND;
        
        if(value > 10000)
            trusteeFee = ((1000 * RATE1) + (9000 * SPECIALRATE2) + (value - 10000) * RATE3) * THOUSAND;
    }
    // Calculates trustee fee for asset values over 1 million (general)
    else
    {
        if(value > 1000 && value <= 10000)
            trusteeFee = ((1000 * RATE1) + (value - 1000) * RATE2) * THOUSAND;

        if(value > 10000)
            trusteeFee = ((1000 * RATE1) + (9000 * RATE2) + (value - 10000) * RATE3) * THOUSAND;
    }
    
    cout << "---" << endl << "The trustee fee for " << assetName << " is $" << trusteeFee << "." << endl;
}
