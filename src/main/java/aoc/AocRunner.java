package aoc;


import aoc.day03.Day03;
import aoc.day1.Day01;
import aoc.day2.Day02;
import aoc.template.DaySolution;
import aoc.template.PartSolver;


/**
 * Enhanced runner for Advent of Code solutions
 * Uses PartSolver enum to determine which parts to run
 */
public class AocRunner {

    public static void main(String[] args) {

        simpleRun(1);
        //menuRun(args);

    }

    private static void simpleRun(int day) {
        DaySolution daySolution = new Day03();
        daySolution.runTest(1,PartSolver.BOTH_PARTS);
        //daySolution.run(PartSolver.PART_TWO);

    }

    private static void menuRun(String[] args) {
        // Default parameters
        int day = 0;                          // 0 means run latest
        PartSolver part = PartSolver.BOTH_PARTS;
        boolean useTest = false;
        int testNumber = 1;

        // Parse command line arguments
        for (int i = 0; i < args.length; i++) {
            String arg = args[i].toLowerCase();

            if (arg.equals("-day") && i + 1 < args.length) {
                try {
                    day = Integer.parseInt(args[++i]);
                } catch (NumberFormatException e) {
                    System.err.println("Invalid day number: " + args[i]);
                    return;
                }
            } else if (arg.equals("-part") && i + 1 < args.length) {
                try {
                    int partNum = Integer.parseInt(args[++i]);
                    if (partNum == 1) {
                        part = PartSolver.PART_ONE;
                    } else if (partNum == 2) {
                        part = PartSolver.PART_TWO;
                    } else {
                        System.err.println("Part must be 1 or 2");
                        return;
                    }
                } catch (NumberFormatException e) {
                    System.err.println("Invalid part number: " + args[i]);
                    return;
                }
            } else if (arg.equals("-test")) {
                useTest = true;
                // Check if test number is provided
                if (i + 1 < args.length && args[i + 1].matches("\\d+")) {
                    try {
                        testNumber = Integer.parseInt(args[++i]);
                    } catch (NumberFormatException e) {
                        // Use default test number 1
                    }
                }
            } else if (arg.equals("-help") || arg.equals("--help") || arg.equals("-h")) {
                printUsage();
                return;
            }
        }

        // Run the appropriate day
        if (day == 0) {
            runLatestDay(part, useTest, testNumber);
        } else {
            runDay(day, part, useTest, testNumber);
        }
    }

    private static void printUsage() {
        System.out.println("Usage: AocRunner [options]");
        System.out.println("Options:");
        System.out.println("  -day N     Run solution for day N (default: latest day)");
        System.out.println("  -part N    Run only part N (1 or 2) (default: both parts)");
        System.out.println("  -test [N]  Use test input file (optional test number N, default: 1)");
        System.out.println("  -help      Show this help message");
        System.out.println("\nExamples:");
        System.out.println("  AocRunner                  Run latest day, both parts, regular input");
        System.out.println("  AocRunner -day 3           Run day 3, both parts, regular input");
        System.out.println("  AocRunner -day 3 -part 1   Run day 3, part 1 only, regular input");
        System.out.println("  AocRunner -day 3 -test     Run day 3, both parts, test input #1");
        System.out.println("  AocRunner -day 3 -test 2   Run day 3, both parts, test input #2");
    }

    private static void runLatestDay(PartSolver part, boolean useTest, int testNumber) {
        // Change this to the latest day you've implemented
        runDay(1, part, useTest, testNumber);
    }

    private static void runDay(int day, PartSolver part, boolean useTest, int testNumber) {
        DaySolution solution = getSolution(day);
        if (solution == null) {
            System.err.println("Day " + day + " not implemented yet");
            return;
        }

        if (useTest) {
            System.out.println("Using test input #" + testNumber + " for day " + day);
            solution.runTest(testNumber, part);
        } else {
            solution.run(part);
        }
    }

    private static DaySolution getSolution(int day) {
        switch (day) {
            case 1:
                return new Day01();
            // Add more days as you implement them
            default:
                return null;
        }
    }
}