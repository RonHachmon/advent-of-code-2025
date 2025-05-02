package aoc.day2;

import java.util.List;

public class FirstSafeRowPolicy implements SafeRowPolicy{
    @Override
    public boolean isSafe(List<Integer> nums) {
        boolean res = true;
        boolean descendingRow = isDescending(nums.get(0), nums.get(1));

        for (int i = 1; i < nums.size(); ++i) {
            int first = nums.get(i-1);
            int second =  nums.get(i);

            if (first == second) {
                res = false;
                break;
            }

            if (Math.abs(first - second) > 3) {
                res = false;
                break;
            }

            if (descendingRow != isDescending(first, second)) {
                res = false;
                break;
            }
        }

        return res;
    }

    /**
     * Checks if the second number is less than the first (descending order)
     *
     * @param first First number to compare
     * @param second Second number to compare
     * @return true if second is less than first (descending), false otherwise
     */
    private boolean isDescending(int first, int second) {
        return second < first;
    }
}

