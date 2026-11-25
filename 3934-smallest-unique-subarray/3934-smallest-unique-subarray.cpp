class Solution {
public:
    using ull = unsigned long long;
    const ull base = 100003;

    bool check(vector<int>& nums, int k) {
        int n = nums.size();

        unordered_map<ull, int> freq;

        ull hash = 0;
        ull power = 1;

        for (int i = 0; i < k - 1; i++) {
            power *= base;
        }

        // First window
        for (int i = 0; i < k; i++) {
            hash = hash * base + nums[i];
        }

        freq[hash]++;

        // Sliding window
        for (int i = k; i < n; i++) {
            hash -= nums[i - k] * power;
            hash = hash * base + nums[i];

            freq[hash]++;
        }

        // Check if any subarray appears exactly once
        for (auto& p : freq) {
            if (p.second == 1) {
                return true;
            }
        }

        return false;
    }

    int smallestUniqueSubarray(vector<int>& nums) {
        int left = 1;
        int right = nums.size();
        int ans = right;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (check(nums, mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return ans;
    }
};