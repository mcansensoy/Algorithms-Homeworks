#include "the6.h"

// do not add extra libraries here
// I used (INT_MAX/2) as infinity, but I am not sure about that

std::vector< std::vector<int>> Floyd_Warshall(std::vector<std::vector<int>> matrix){
    int i,j,k;
    int n = matrix.size();
    std::vector< std::vector<int>> SP2 = matrix;
    
    for(k=0; k<n; k++){
        for(i=0; i<n; i++){
            for(j=0; j<n; j++){
                if (SP2[i][k] != INT_MAX/2 && SP2[k][j] != INT_MAX/2) {
                    if(SP2[i][k] + SP2[k][j] < SP2[i][j]){
                        SP2[i][j] = SP2[i][k] + SP2[k][j];
                    }
                }
            }
        }
    }
    
    return SP2;
}

std::vector< std::vector<float> > get_friendship_scores(const std::vector< std::vector< std::pair<int, int> > >& network){
    int i, j, temp;
    int n = network.size();
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, (INT_MAX/2)));
    
    for(i=0; i<n; i++){
        int n2 = network[i].size();
        for(j=0; j<n2; j++){
            matrix[i][network[i][j].first] = network[i][j].second;
        }
    }
    
    std::vector<int> SP1(n, INT_MAX);
    
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            temp = matrix[i][j];
            if(temp < SP1[i]){
                SP1[i] = temp;
            }
        }
    }
    
    std::vector< std::vector<int>> SP2 = Floyd_Warshall(matrix);
    
    std::vector< std::vector<float>> FS(n, std::vector<float>(n, -1));
    
    for(i=0; i<n; i++){
        for(j=0; j<=i; j++){
            if(SP2[i][j] == INT_MAX/2 && SP2[j][i] == INT_MAX/2) {
                FS[i][j] = -1;
            }
            else if(SP2[i][j] == INT_MAX/2 || SP2[j][i] == INT_MAX/2) {
                FS[i][j] = 0;
            }
            else{
                FS[i][j] = (((float)SP1[i])/((float)SP2[i][j]))*(((float)SP1[j])/((float)SP2[j][i]));
            }
        }
    }
    
    return FS;
}
