long long findHours(int* piles, int size, int speed) {
    long long totalHours = 0;
    for (int i = 0; i < size; i++) {
        if (piles[i] % speed == 0)
            totalHours += piles[i] / speed;
        else
            totalHours += (piles[i] / speed) + 1;
    }
    return totalHours;
}

int findMax(int* piles, int size) {
    int maxElement = 0;
    for (int i = 0; i < size; i++) {
        if (piles[i] > maxElement)
            maxElement = piles[i];
    }
    return maxElement;
}

int minEatingSpeed(int* piles, int size, int h) {
    int maxPiles = findMax(piles, size);
    int low = 1, high = maxPiles, minSpeed = maxPiles;

    while (low <= high) {
        int mid = (low + high) / 2;
        long long checkHours = findHours(piles, size, mid);
        if (checkHours <= h) {
            minSpeed = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return minSpeed;
}

// Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

// Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

// Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

// Return the minimum integer k such that she can eat all the bananas within h hours.
