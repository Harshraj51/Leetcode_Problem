
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);
        vector<int> ans(n, 1);
        vector<int> newParent = parent;
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }
        vector<int> last(26, -1);

        auto dfs = [&](auto&& self, int node) -> void {
            int ch = s[node] - 'a';
            if (last[ch] != -1) {
                newParent[node] = last[ch];
            }

            int prev = last[ch];
            last[ch] = node;

            for (int child : adj[node]) {
                self(self, child);
            }
            last[ch] = prev;
        };

        dfs(dfs, 0);
        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }
        auto calc = [&](auto&& self, int node) -> void {
            for (int child : tree[node]) {
                self(self, child);
                ans[node] += ans[child];
            }
        };

        calc(calc, 0);

        return ans;
    }
};
