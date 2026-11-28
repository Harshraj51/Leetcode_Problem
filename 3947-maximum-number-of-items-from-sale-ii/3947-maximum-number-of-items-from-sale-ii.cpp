class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);
        vector<int> freeCount(n + 1, 0);

        long long minPrice = INT_MAX;
        long long money = budget;
        long long ans = 0;

        for (auto &item : items) {
            freq[item[0]]++;
            minPrice = min(minPrice, (long long)item[1]);
        }

        for (int i = 1; i <= n; i++) {
            if (freq[i] == 0)
                continue;

            for (int j = i; j <= n; j += i) {
                freeCount[i] += freq[j];
            }

            freeCount[i]--;
        }

        sort(items.begin(), items.end(),
             [](const auto &a, const auto &b) {
                 return a[1] < b[1];
             });

        for (auto &item : items) {
            int factor = item[0];
            long long price = item[1];

            if (price >= 2 * minPrice)
                break;

            long long count = min(
                (long long)freeCount[factor],
                money / price
            );

            ans += 2 * count;
            money -= count * price;
        }

        ans += money / minPrice;

        return ans;
    }
};