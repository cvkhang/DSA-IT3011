int cmp(const void *a, const void *b) {
    int *p1 = *(int **)a;
    int *p2 = *(int **)b;

    if (p1[0] == p2[0])
        return p2[1] - p1[1];

    return p1[0] - p2[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes) {
    qsort(intervals, intervalsSize, sizeof(int *), cmp);

    int **ans = (int **)malloc(sizeof(int *) * intervalsSize);
    *returnColumnSizes = (int *)malloc(sizeof(int) * intervalsSize);

    int p1 = intervals[0][0], p2 = intervals[0][1];
    int k = 0;

    for (int i = 1; i <= intervalsSize; i++) {
        if (i == intervalsSize || intervals[i][0] > p2) {
            ans[k] = (int *)malloc(sizeof(int) * 2);
            ans[k][0] = p1;
            ans[k][1] = p2;
            (*returnColumnSizes)[k++] = 2;

            if (i < intervalsSize) {
                p1 = intervals[i][0];
                p2 = intervals[i][1];
            }
        } else {
            if (intervals[i][1] > p2)
                p2 = intervals[i][1];
        }
    }
    *returnSize = k;
    return ans;
}

// Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

 

// Example 1:

// Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
// Output: [[1,6],[8,10],[15,18]]
// Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
// Example 2:

// Input: intervals = [[1,4],[4,5]]
// Output: [[1,5]]
// Explanation: Intervals [1,4] and [4,5] are considered overlapping.
// Example 3:

// Input: intervals = [[4,7],[1,4]]
// Output: [[1,7]]
// Explanation: Intervals [1,4] and [4,7] are considered overlapping.
