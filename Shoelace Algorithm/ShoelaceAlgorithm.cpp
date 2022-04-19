// The Shoelace Algorithm is a mathematical algorithm to determine the area of a simple polygon whose vertices are described by their Cartesian coordinates in the plane
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int ShoelaceAlgorithm(vector<pair<int, int>> vertices){
    int res = 0;

    for(int i=0; i<vertices.size()-1; i++){
        res += vertices[i].first*vertices[i+1].second;
        res -= vertices[i+1].first*vertices[i].second;
    }    
    res += vertices[vertices.size()-1].first*vertices[0].second;
    res -= vertices[0].first*vertices[vertices.size()-1].second;

    return abs(res/2);
}

int main(){
    int t;
    cin>>t;
    vector<pair<int, int>> vv;
    for(int i=0; i<t; i++){
        int tmp1, tmp2;
        cin>>tmp1>>tmp2;

        vv.push_back(make_pair(tmp1, tmp2));
    }
    cout<<"Polygon Area: "<<ShoelaceAlgorithm(vv);

    return 0;
}