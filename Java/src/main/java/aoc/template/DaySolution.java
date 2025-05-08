package aoc.template;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

/**
 * Enhanced base template for Advent of Code solutions.
 */
public abstract class DaySolution {

    private final int day;

    protected DaySolution(int day) {
        this.day = day;
    }

    /**
     * Get the day number
     */
    public int getDay() {
        return day;
    }

    /**
     * Solve part one of the day's challenge.
     */
    public abstract String solvePart1(List<String> input);

    /**
     * Solve part two of the day's challenge.
     */
    public abstract String solvePart2(List<String> input);

    /**
     * Read the main input file for the day.
     */
    public List<String> readInput() throws IOException {
        String filename = String.format("day%02d.txt", day);
        Path inputPath = Paths.get("src/main/resources", filename);

        if (!Files.exists(inputPath)) {
            throw new IOException("Input file not found: " + inputPath);
        }

        return Files.readAllLines(inputPath);
    }

    /**
     * Read a test input file for the day.
     *
     * @param testNum The test number (for multiple test files)
     */
    public List<String> readTestInput(int testNum) throws IOException {
        String filename = String.format("day%02d_test%d.txt", day, testNum);
        Path testPath = Paths.get("src/test/resources", filename);

        if (!Files.exists(testPath)) {
            throw new IOException("Test input file not found: " + testPath +
                    "\nMake sure you've created this file with the example input from the puzzle.");
        }

        return Files.readAllLines(testPath);
    }

    /**
     * Run the solution with main input file.
     */
    public void run(PartSolver part) {
        try {
            List<String> input = readInput();
            runWithInput(input, part);
        } catch (IOException e) {
            System.err.println("Error reading input file: " + e.getMessage());
        }
    }

    /**
     * Run the solution with test input file.
     */
    public void runTest(int testNum, PartSolver part) {
        try {
            List<String> input = readTestInput(testNum);
            runWithInput(input, part);
        } catch (IOException e) {
            System.err.println("Error reading test input file: " + e.getMessage());
        }
    }

    /**
     * Run the appropriate part(s) with the given input.
     */
    private void runWithInput(List<String> input, PartSolver part) {
        if (part == PartSolver.PART_ONE || part == PartSolver.BOTH_PARTS) {
            String result1 = solvePart1(input);
            System.out.println("Day " + day + " - Part 1: " + result1);
        }

        if (part == PartSolver.PART_TWO || part == PartSolver.BOTH_PARTS) {
            String result2 = solvePart2(input);
            System.out.println("Day " + day + " - Part 2: " + result2);
        }
    }

    /**
     * Run both parts with main input (convenience method).
     */
    public void run() {
        run(PartSolver.BOTH_PARTS);
    }
}