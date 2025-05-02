package aoc.day03;

import aoc.template.DaySolution;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day03 extends DaySolution {

    public Day03() {
        super(3);
    }

    @Override
    public String solvePart1(List<String> input) {
        int sum = 0;

        String combinedInput = String.join("", input);

        // Regex to match valid mul(X,Y) instructions where X and Y are 1-3 digit numbers
        Pattern pattern = Pattern.compile("mul\\((\\d{1,3}),(\\d{1,3})\\)");
        Matcher matcher = pattern.matcher(combinedInput);

        // Find all matches and process them
        while (matcher.find()) {
            int x = Integer.parseInt(matcher.group(1));
            int y = Integer.parseInt(matcher.group(2));
            int result = x * y;
            sum += result;
        }

        return Integer.toString(sum);
    }

    @Override
    public String solvePart2(List<String> input) {
        String combinedInput = String.join("", input);

        // Find all instructions in the input
        List<Instruction> allInstructions = findAllInstructions(combinedInput);

        // Sort all instructions by position to process them in the correct order
        Collections.sort(allInstructions);

        // Process instructions and calculate the sum
        int sum = processInstructions(allInstructions);

        return Integer.toString(sum);
    }

    /**
     * Find all instructions in the input string
     */
    private List<Instruction> findAllInstructions(String input) {
        List<Instruction> instructions = new ArrayList<>();

        // Add multiplication instructions
        findMulInstructions(input, instructions);

        // Add do() instructions
        findDoInstructions(input, instructions);

        // Add don't() instructions
        findDontInstructions(input, instructions);

        // Add undo() instructions (treated as do())
        findUndoInstructions(input, instructions);

        return instructions;
    }

    /**
     * Find all mul(X,Y) instructions
     */
    private void findMulInstructions(String input, List<Instruction> instructions) {
        Pattern pattern = Pattern.compile("mul\\((\\d{1,3}),(\\d{1,3})\\)");
        Matcher matcher = pattern.matcher(input);

        while (matcher.find()) {
            int x = Integer.parseInt(matcher.group(1));
            int y = Integer.parseInt(matcher.group(2));
            instructions.add(new Instruction(matcher.start(), Instruction.Type.MUL, x, y));
        }
    }

    /**
     * Find all do() instructions
     */
    private void findDoInstructions(String input, List<Instruction> instructions) {
        Pattern pattern = Pattern.compile("do\\(\\)");
        Matcher matcher = pattern.matcher(input);

        while (matcher.find()) {
            instructions.add(new Instruction(matcher.start(), Instruction.Type.DO, 0, 0));
        }
    }

    /**
     * Find all don't() instructions
     */
    private void findDontInstructions(String input, List<Instruction> instructions) {
        Pattern pattern = Pattern.compile("don't\\(\\)");
        Matcher matcher = pattern.matcher(input);

        while (matcher.find()) {
            instructions.add(new Instruction(matcher.start(), Instruction.Type.DONT, 0, 0));
        }
    }

    /**
     * Find all undo() instructions (treated as do())
     */
    private void findUndoInstructions(String input, List<Instruction> instructions) {
        Pattern pattern = Pattern.compile("undo\\(\\)");
        Matcher matcher = pattern.matcher(input);

        while (matcher.find()) {
            instructions.add(new Instruction(matcher.start(), Instruction.Type.DO, 0, 0));
        }
    }

    /**
     * Process all instructions in order and calculate the sum
     */
    private int processInstructions(List<Instruction> instructions) {
        boolean mulEnabled = true; // Initially enabled
        int sum = 0;

        for (Instruction inst : instructions) {
            if (inst.type == Instruction.Type.DO) {
                mulEnabled = true;
            } else if (inst.type == Instruction.Type.DONT) {
                mulEnabled = false;
            } else if (inst.type == Instruction.Type.MUL && mulEnabled) {
                sum += inst.x * inst.y;
            }
        }

        return sum;
    }
}