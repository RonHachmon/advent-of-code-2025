package aoc.day2;

import java.util.ArrayList;
import java.util.List;

public class SecondSafeRowPolicy implements SafeRowPolicy {

    @Override
    public boolean isSafe(List<Integer> nums) {
        if (nums.size() < 2) {
            return true;
        }

        boolean descendingRow = isDescending(nums.get(0), nums.get(1));

        for (int i = 1; i < nums.size(); i++) {
            int previous = nums.get(i - 1);
            int current = nums.get(i);

            // Handle equal adjacent numbers
            if (previous == current) {
                List<Integer> modified = new ArrayList<>(nums);
                modified.remove(i - 1);
                return isValidSequence(modified);
            }

            // Handle direction changes
            if (descendingRow != isDescending(previous, current)) {
                List<Integer> option1 = new ArrayList<>(nums);
                List<Integer> option2 = new ArrayList<>(nums);
                List<Integer> option3 = new ArrayList<>(nums);

                option1.remove(i);         // Remove current number
                option2.remove(i - 1);     // Remove previous number

                // Remove element before previous if possible
                if (i >= 2) {
                    option3.remove(i - 2);
                    return isValidSequence(option1) || isValidSequence(option2) || isValidSequence(option3);
                } else {
                    return isValidSequence(option1) || isValidSequence(option2);
                }
            }

            // Handle excessive difference
            if (Math.abs(previous - current) > 3) {
                if (i == 1) {
                    List<Integer> option1 = new ArrayList<>(nums);
                    List<Integer> option2 = new ArrayList<>(nums);

                    option1.remove(i);     // Remove current number
                    option2.remove(i - 1); // Remove previous number
                    return isValidSequence(option1) || isValidSequence(option2);
                } else {
                    List<Integer> modified = new ArrayList<>(nums);
                    modified.remove(i);    // Remove current number
                    return isValidSequence(modified);
                }
            }
        }

        return true; // The sequence is already valid
    }

    /**
     * Checks if the given sequence is valid without modifications
     */
    private boolean isValidSequence(List<Integer> nums) {
        if (nums.size() < 2) {
            return true;
        }

        boolean descendingRow = isDescending(nums.get(0), nums.get(1));

        for (int i = 1; i < nums.size(); i++) {
            int current = nums.get(i);
            int previous = nums.get(i-1);

            // Check for invalid conditions
            if (previous == current ||
                    Math.abs(previous - current) > 3 ||
                    descendingRow != isDescending(previous, current)) {
                return false;
            }
        }

        return true;
    }

    /**
     * Checks if the second number is less than the first (descending order)
     */
    private boolean isDescending(int first, int second) {
        return second < first;
    }
}