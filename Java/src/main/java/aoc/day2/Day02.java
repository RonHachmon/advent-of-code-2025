package aoc.day2;

import aoc.template.DaySolution;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Day02 extends DaySolution {
    private SafeRowPolicy policy;
    public Day02() {
        super(2);
    }

    @Override
    public String solvePart1(List<String> input) {
        SafeRowPolicy rowPolicy = new FirstSafeRowPolicy();
        return Integer.toString(totalSafeRows(input,rowPolicy));
    }

    @Override
    public String solvePart2(List<String> input) {
        SafeRowPolicy rowPolicy = new SecondSafeRowPolicy();
        return Integer.toString(totalSafeRows(input,rowPolicy));
    }


    public int totalSafeRows(List<String> input, SafeRowPolicy safeRowPolicy) {
        int res = 0;
        for (String line : input) {
            String[] nums = line.split("\\s+");
            List<Integer> numbers = Arrays.stream(nums)
                    .map(Integer::parseInt)
                    .collect(Collectors.toList());

            if(safeRowPolicy.isSafe(numbers)){
                res++;
            }

        }

        return res;
    }


}
