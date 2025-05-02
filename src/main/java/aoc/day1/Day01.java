package aoc.day1;

import aoc.template.DaySolution;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;

public class Day01 extends DaySolution {
    // Part 1 fields
    private PriorityQueue<Integer> leftSide;
    private PriorityQueue<Integer> rightSide;

    // Part 2 fields
    private List<Integer> leftSideNumbers;
    private Map<Integer, Integer> numberToOccurrence;

    public Day01() {
        super(1);
    }

    @Override
    public String solvePart1(List<String> input) {
        // Initialize data structures for part 1
        initializePartOneStructures();

        // Parse input and populate data structures
        parseInputForPartOne(input);

        // Calculate total distance
        long totalDistance = calculateTotalDistance();

        return Long.toString(totalDistance);
    }

    private void initializePartOneStructures() {
        leftSide = new PriorityQueue<>();
        rightSide = new PriorityQueue<>();
    }

    private void parseInputForPartOne(List<String> input) {
        for (String line : input) {
            String[] nums = line.split("\\s+");

            if (nums.length >= 2) {
                leftSide.add(Integer.parseInt(nums[0]));
                rightSide.add(Integer.parseInt(nums[1]));
            }
        }
    }

    private long calculateTotalDistance() {
        long totalDistance = 0;

        while (!leftSide.isEmpty() && !rightSide.isEmpty()) {
            int leftValue = leftSide.poll();
            int rightValue = rightSide.poll();
            int distance = Math.abs(rightValue - leftValue);

            totalDistance += distance;
        }

        return totalDistance;
    }

    @Override
    public String solvePart2(List<String> input) {
        // Initialize data structures for part 2
        initializePartTwoStructures();

        // Parse input and populate data structures
        parseInputForPartTwo(input);

        // Calculate the result based on occurrences
        long result = calculateOccurrenceBasedResult();

        return Long.toString(result);
    }

    private void initializePartTwoStructures() {
        leftSideNumbers = new ArrayList<>();
        numberToOccurrence = new HashMap<>();
    }

    private void parseInputForPartTwo(List<String> input) {
        for (String line : input) {
            String[] nums = line.split("\\s+");

            if (nums.length >= 2) {
                int leftValue = Integer.parseInt(nums[0]);
                int rightValue = Integer.parseInt(nums[1]);

                leftSideNumbers.add(leftValue);
                numberToOccurrence.compute(rightValue, (key, count) -> count == null ? 1 : count + 1);
            }
        }
    }

    private long calculateOccurrenceBasedResult() {
        long result = 0;
        for (Integer leftValue : leftSideNumbers) {
            Integer occurrences = numberToOccurrence.getOrDefault(leftValue, 0);
            result += (long) leftValue * occurrences;
        }
        return result;
    }
}