#include<iostream>
#include<vector>

class Matrix{
    public:
        Matrix(std::vector<std::vector<float>> _m): m(_m), line(_m.size()), col(_m[0].size()) {}

        void toUpperTriangolar(){
            for(int j=0; j<line-1; j++){
                for(int i=j+1; i<line; i++){
                    int tmp = m[i][j]/m[j][j];

                    for(int h=0; h<col; h++)
                        m[i][h]-= m[j][h] * tmp;
                }
            }

            std::cout<<"Upper Triangolar Matrix:"<<std::endl;
            this->printAll();
            std::cout<<std::endl;

        }

        void MEG(){
            this->toUpperTriangolar();
            
            for(int i=0; i<line; i++){
                int tmp = m[i][i];

                for(int j=0; j<col; j++)
                    if(m[i][j] != float(0))
                        m[i][j] /= tmp;
            }

            for(int i=0; i<line-1; i++){
                for(int j=i+1; j<line; j++){
                    for(int h=line; h>=j; h--){
                        m[i][h] -= (m[i][j] *  m[j][h]);
                    }
                    m[i][j] = 0;
                }
            }

            std::cout<<"Linear Equations Solved:"<<std::endl;
            this->printAll();
            std::cout<<std::endl;


        }

        void printAll(){
            for(int i=0; i<line; i++){
                for(int j=0; j<line; j++)
                    std::cout<<m[i][j]<<"\t";

                std::cout<<"=\t"<<m[i][line]<<std::endl;
            }        
        }

    private:
        int line, col;
        std::vector<std::vector<float>> m;
};



int main(){
    Matrix vec = Matrix({{1, 2, 4, 5}, {9, 8, 5, 12}, {2, 4, 3, 3}});
    
    vec.MEG();

    return 0;
}


/*Linear Equations System Sample:
    x + y + z = 5
    9x + 8y + 5z = 12
    2x + 4y + 3z = 3
*/