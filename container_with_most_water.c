/*
 * Solution to LeetCode problem 'Container with most water'. 
 *
 * Approach:
 *
 * 1. Maintain two poinaters 'i' and 'j' - one starting at index 0  end and moving right, 
 *    the other starting at the end (index 'len -1') and moving to the left.
 *
 * 2. Compute the size of the container that would be formed using height[i] & height[j].
 *    The formula for container size (i.e. the area) is (j - i) * min(height[i], height[j])
 *    If this is larger than the maximum area that has been computed so far, updated the maximum area.
 *
 * 3. If height[i] > height [j], we would have to advance 'j' if we want to find a bigger container. 
 *    This is because any subsequent container made by advancing 'i' will have a lower width (j - i) 
 *    and the effective height of the containre will be height[j] at most. So in this case, we have to move
 *    'j' to the left to find a bigger container.
 *
 * 4. If height[j] > height[i], we would have to advance 'i' to find a bigger container. Same rationale
 *    as explained above.
 *
 * 5. Else both pointers can advance
 *
 * Keep looping while i < j
 *
 */
int maxArea(int* height, int heightSize){

    int i = 0, j = heightSize - 1;
    int maxAmount = 0, currentAmount = 0;

    while(i < j)
    {
        
        /* Compute Amount within these two edges and update maxAmount
           if the current Amount is larger. Advance the index on the 
           smaller side in order to find a containre with a potentially
           larger amount  */
        if(height[i] > height[j])
        {
            currentAmount = height[j] * (j - i);
            j--;
        }
        else if(height[j] > height[i])
        {
            currentAmount = height[i] * (j - i);
            i++;
        }
        else
        {
            currentAmount = height[i] * (j - i);
            i++;
            j--;
        }
        if(currentAmount > maxAmount)
        {
            maxAmount = currentAmount;
        }
    }

    return maxAmount;
}
