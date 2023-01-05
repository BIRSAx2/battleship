#include "src/Coordinates.cpp"

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main(void){
    cout << "Exception" << endl;
    cout << "Coordinates exc = Coordinates(9,12); --> ";
    try{
        Coordinates exc = Coordinates(9,12);    
    } catch(invalid_argument e){
        cout << e.what() << endl << endl;
    }

    cout << "Cout : ";
    Coordinates coord = Coordinates(2, 2);
    cout << coord << endl << endl;


    cout << "IsInBound()" << endl;
    cout << coord.IsInBound(0,11) << endl << endl;

    
    cout << "GetAdjacentCoordinates()" << endl;
    cout << "VERTICAL"<< endl;
    vector<Coordinates> adj = Coordinates::GetAdjacentCoordinates(coord, VERTICAL, 3);
    for(auto item : adj)
        cout << item << endl;

    cout << "HORIZONTAL" << endl;
    adj = Coordinates::GetAdjacentCoordinates(coord, HORIZONTAL, 3);
    for(auto item : adj)
        cout << item << endl;
    cout << endl;


    cout << "GetAdjacentStarCoordinates()" << endl;
    adj = Coordinates::GetAdjacentStarCoordinates(coord);
    cout << "strting : " << coord << endl;
    for(auto item : adj)
        cout << item << endl;
    cout << endl;


    cout << "ParseCoordinates()" << endl;
    string c = "C4";
    Coordinates coord2 = Coordinates::ParseCoordinates(c);
    cout <<  c << " : " << coord2 << endl;


    cout << "Comparisons" << endl;
    cout << (coord == coord2) << endl;
    cout << (coord != coord2) << endl;




    return 0;
}
