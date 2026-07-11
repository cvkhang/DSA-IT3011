int majorityElement(int* nums, int numsSize){
    int sol = nums[0],
    cnt = 0;
    for (int i = 0; i < numsSize; i++) {
        if (cnt == 0) {
            sol = nums[i];
        }
        if (nums[i] == sol) {
            cnt++;
        } else {
            cnt--;
        } 
    }        
    return sol;
}

// Given an array nums of size n, return the majority element.

// The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

// Example 1:

// Input: nums = [3,2,3]
// Output: 3
// Example 2:

// Input: nums = [2,2,1,1,1,2,2]
// Output: 2
