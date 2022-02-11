#include<iostream>
#include<vector>

class numbers{
    public:
        numbers(std::vector<int> _nums): nums(_nums) {};

        void printEl(){
            std::cout<<"Numbers: ";
            for(int n : nums){
                std::cout<<n<<" ";
            }
            std::cout<<std::endl;
        }

        void insertion_sort(){
            for(size_t i = 1; i < nums.size(); ++i){
                auto j = i;
                while(j > 0 && nums[j-1] > nums[j]){
                    std::swap(nums[j], nums[j-1]);
                    j--;
                }
            }
        }

    private:
        std::vector<int> nums;
};

int main(){
    std::vector<int> vec = {14, 68, 41, 10, 55, 48, 43, 31, 4};
    numbers n (vec);
    n.insertion_sort();
    n.printEl();

    return 0;
}