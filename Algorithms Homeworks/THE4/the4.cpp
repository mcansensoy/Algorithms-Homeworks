#include "the4.h"

// DO NOT CHANGE ABOVE THIS LINE!
// You may implement helper functions below

unsigned int alice_cutting_cake(const unsigned short cake_width,
                                const unsigned short cake_height,
                                bool **perfect_cuts){
    
    std::vector<std::vector<unsigned int>> dp(cake_width + 1, std::vector<unsigned int>(cake_height + 1, INT_MAX));
    
    for(int w=0; w<=cake_width; w++){
        for(int h=0; h<=cake_height; h++){
            if(perfect_cuts[w][h] == true){
                dp[w][h] = 0;
                continue;
            }
            
            int vertical_min = dp[w][h];
            for(int i=0; i<w; i++){
                if(dp[w-i][h] + dp[i][h]< vertical_min){
                    vertical_min = dp[w-i][h] + dp[i][h];
                }
            }
            
            int horizontal_min = dp[w][h];
            for(int j=0; j<h; j++){
                if(dp[w][h-j] + dp[w][j]< horizontal_min){
                    horizontal_min = dp[w][h-j] + dp[w][j];
                }
            }
            
            dp[w][h] = std::min(vertical_min, horizontal_min);
            
            if(dp[w][h] == INT_MAX){
                dp[w][h] = w*h;
            }
        }
    }
    
    return dp[cake_width][cake_height];
}
