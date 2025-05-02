package aoc.day3;

public class Instruction implements Comparable<Instruction> {
    public enum Type {
        MUL, DO, DONT
    }

    int position;
    Type type;
    int x, y;  // Only used for MUL type

    public Instruction(int position, Type type, int x, int y) {
        this.position = position;
        this.type = type;
        this.x = x;
        this.y = y;
    }

    @Override
    public int compareTo(Instruction other) {
        return Integer.compare(this.position, other.position);
    }

    @Override
    public String toString() {
        if (type == Type.MUL) {
            return "Instruction{position=" + position + ", type=" + type + ", x=" + x + ", y=" + y + "}";
        } else {
            return "Instruction{position=" + position + ", type=" + type + "}";
        }
    }
}