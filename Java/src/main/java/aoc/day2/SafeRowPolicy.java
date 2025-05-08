package aoc.day2;

import java.util.List;

public interface SafeRowPolicy {
    /**
     * Determines if an array of number strings is considered safe according to the policy
     *
     * @param nums Array of number strings to check
     * @return true if the row is safe, false otherwise
     */
    boolean isSafe(List<Integer> nums);
}