int subarraySum(int nums[], int n, int k) {
    int prefix[n];
    prefix[0] = nums[0];

    for (int i = 1; i < n; i++) {
        prefix[i] = nums[i] + prefix[i - 1];
    }

    int mp[100000] = {0}; // Assuming a maximum size, adjust if needed
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        if (prefix[i] == k) {
            cnt++;
        }

        if (mp[prefix[i] - k]) {
            cnt += mp[prefix[i] - k];
        }
        mp[prefix[i]]++;
    }
    return cnt;
}
