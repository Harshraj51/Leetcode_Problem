class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n=items.size();
        vector<int>gain(n,1);
        for(int i=0;i<n;i++){
            int count=0;
            for(int j =0;j<n;j++){
                if(i==j){
                    continue;
                }
                if(items[j][0]%items[i][0]==0){
                    count++;
                }
            }
                gain[i]+=count;
        }
        vector<int>dp(budget + 1,0);
        for(int i=0;i<n;i++){
            int cost=items[i][1];
            vector<int>ndp = dp;
            for(int b=budget; b>=cost; b--){
                ndp[b] = max(ndp[b],dp[b-cost] + gain[i]);
            }
            for(int b=cost; b<= budget; b++){
                ndp[b] = max(ndp[b],ndp[b-cost] + 1);
            }
            dp=ndp;
        }
        return *max_element(dp.begin(),dp.end());
    }
};