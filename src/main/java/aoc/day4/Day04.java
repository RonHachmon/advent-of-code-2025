package aoc.day4;

import aoc.template.DaySolution;
import aoc.utils.Point;
import aoc.utils.Direction;

import java.util.List;

public class Day04 extends DaySolution {
    private char[][] grid;
    private int rows;
    private int cols;
    private static final String XMAS_PATTERN = "XMAS";

    public Day04() {
        super(4);
    }

    @Override
    public String solvePart1(List<String> input) {
        initializeGrid(input);
        int totalPatterns = countAllXmasPatterns();
        return Integer.toString(totalPatterns);
    }

    @Override
    public String solvePart2(List<String> input) {
        initializeGrid(input);
        int totalXShapes = countAllXShapedPatterns();
        return Integer.toString(totalXShapes);
    }

    /**
     * Initializes the grid from input data.
     */
    private void initializeGrid(List<String> input) {
        if (input == null || input.isEmpty()) {
            return;
        }

        rows = input.size();
        cols = input.get(0).length();
        grid = new char[rows][cols];

        for (int i = 0; i < rows; i++) {
            String line = input.get(i);
            for (int j = 0; j < line.length(); j++) {
                grid[i][j] = line.charAt(j);
            }
        }
    }

    /**
     * Counts all XMAS patterns in the grid.
     */
    private int countAllXmasPatterns() {
        int count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                count += countXmasPatterns(new Point(i, j));
            }
        }
        return count;
    }

    /**
     * Counts XMAS patterns starting from a specific point.
     */
    private int countXmasPatterns(Point start) {
        int count = 0;
        for (Direction direction : Direction.ALL_DIRECTIONS) {
            if (isXmasPattern(start, direction)) {
                count++;
            }
        }
        return count;
    }

    /**
     * Checks if an XMAS pattern exists starting from a point in a specific direction.
     */
    private boolean isXmasPattern(Point start, Direction direction) {
        return isPatternMatch(start, direction, XMAS_PATTERN, 0);
    }

    /**
     * Recursively checks if a pattern matches starting from a point.
     */
    private boolean isPatternMatch(Point point, Direction direction, String pattern, int index) {
        // Base case: pattern complete
        if (index == pattern.length()) {
            return true;
        }

        // Check if point is within bounds
        if (!point.isInBounds(rows, cols)) {
            return false;
        }

        // Check if current character matches
        if (grid[point.x][point.y] != pattern.charAt(index)) {
            return false;
        }

        // Continue checking the pattern in the given direction
        return isPatternMatch(point.move(direction), direction, pattern, index + 1);
    }

    /**
     * Counts all X-shaped patterns in the grid.
     */
    private int countAllXShapedPatterns() {
        int count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 'A') {
                    if (isXShapedPattern(new Point(i, j))) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    /**
     * Checks if an X-shaped pattern exists with 'A' at the center.
     */
    private boolean isXShapedPattern(Point center) {
        // Check if we have enough space around the center
        if (!hasValidSurroundings(center)) {
            return false;
        }

        // Check northwest-southeast diagonal
        char nwChar = grid[center.x - 1][center.y - 1];
        char seChar = grid[center.x + 1][center.y + 1];
        boolean nwseDiagonal = (nwChar == 'M' && seChar == 'S') || (nwChar == 'S' && seChar == 'M');

        // Check northeast-southwest diagonal
        char neChar = grid[center.x - 1][center.y + 1];
        char swChar = grid[center.x + 1][center.y - 1];
        boolean neswDiagonal = (neChar == 'M' && swChar == 'S') || (neChar == 'S' && swChar == 'M');

        // Both diagonals must have M-S pairs
        return isMASShaped(center) ;
    }

    private boolean isMASShaped(Point center){
        Point northWest = center.move(Direction.NORTHWEST);
        Point southEast = center.move(Direction.SOUTHEAST);
        Point northEast = center.move(Direction.NORTHEAST);
        Point southWest = center.move(Direction.SOUTHWEST);

        // Check northwest-southeast diagonal
        char nwChar = grid[northWest.x][northWest.y];
        char seChar = grid[southEast.x][southEast.y];
        boolean nwseDiagonal = (nwChar == 'M' && seChar == 'S') || (nwChar == 'S' && seChar == 'M');

        // Check northeast-southwest diagonal
        char neChar = grid[northEast.x][northEast.y];
        char swChar = grid[southWest.x][southWest.y];
        boolean neswDiagonal = (neChar == 'M' && swChar == 'S') || (neChar == 'S' && swChar == 'M');

        // Both diagonals must have M-S pairs
        return nwseDiagonal && neswDiagonal;
    }

    /**
     * Checks if the center point has valid surrounding positions within grid bounds.
     */
    private boolean hasValidSurroundings(Point center) {
        return center.move(Direction.NORTHWEST).isInBounds(rows, cols) &&
                center.move(Direction.SOUTHEAST).isInBounds(rows, cols);
    }
}