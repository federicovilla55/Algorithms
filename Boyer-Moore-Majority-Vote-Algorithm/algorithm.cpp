/*Boyer Moore majority vote algorithm consist of an algorithm for finding the majority of a sequence.
  It uses linear time complexity O(n) and constant time space */

#include<iostream>
#include<vector>

int main(){
    std::vector<int> nums = {2,2,1,1,1,2,2};
    int ris, i = 0;

    for(int n : nums){
        if(i == 0){
            ris = n;
            i++;
        }else{
            if(ris == n){
                i++;
            }else{
                i--;
            }
        }
    }

    std::cout<<ris<<std::endl;

    return 0;
}