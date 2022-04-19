// // Pick's theorem provides a formula for the area of a simple polygon with integer vertex coordinates
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int pickTheorem(vector<pair<int, int>> vertices){
    int res = 0;

    for(int i=2; i<vertices.size(); i++){
        res += (vertices[i].first - vertices[0].first)*(vertices[i-1].second - vertices[0].second) - (vertices[i-1].first - vertices[0].first)*(vertices[i].second - vertices[0].second);
    }    

    return abs(res/2);
}

int main(){
    int t;
    cin>>t;
    vector<pair<int, int>> vertices(t);
    for(int i=0; i<t; i++){
        cin>>vertices[i].first>>vertices[i].second;
    }
    cout<<"Polygon Area: "<<pickTheorem(vertices);

    return 0;
}