import java.util.ArrayList;
import java.util.Map;
import java.util.SortedMap;
import java.util.TreeMap;

public class Automata {
    public final static int[][] table = {
                        /*  d   o   w   h   i   l   e    <    >   '   num  ws a-zA-z EOL  */
            /*  START   */{ 1,  3,  4,  3,  3,  3,  3,   8,   9,  10,  13,  14,  3,  14,  -1},
            /*  ID_1    */{ 3,  2,  3,  3,  3,  3,  3,  -1,  -1,  -1,   3,  -1,  3,  -1,  -1},
            /*  KEY_2   */{ 3,  3,  3,  3,  3,  3,  3,  -1,  -1,  -1,   3,  -1,  3,  -1,  -1},
            /*  ID_3    */{ 3,  3,  3,  3,  3,  3,  3,  -1,  -1,  -1,   3,  -1,  3,  -1,  -1},
            /*  ID_4    */{ 3,  3,  3,  5,  3,  3,  3,  -1,  -1,  -1,   3,  -1,  3,  -1,  -1},
            /*  ID_5    */{ 3,  3,  3,  3,  6,  3,  3,  -1,  -1,  -1,   3,  -1,  3,  -1,  -1},
            /*  ID_6    */{ 3,  3,  3,  3,  3,  7,  3,  -1,  -1,  -1,   3,  -1,  3,  -1,  -1},
            /*  ID_7    */{ 3,  3,  3,  3,  3,  3,  2,  -1,  -1,  -1,   3,  -1,  3,  -1,  -1},
            /*  OP_8    */{-1, -1, -1, -1, -1, -1, -1,  -1,   9,  -1,  -1,  -1, -1,  -1,  -1},
            /*  OP_9    */{-1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1, -1,  -1,  -1},
            /*  LIT_10  */{11, 11, 11, 11, 11, 11, 11,  11,  11,  12,  11,  11, 11,  -1,  11},
            /*  LIT_11  */{11, 11, 11, 11, 11, 11, 11,  11,  11,  12,  11,  11, 11,  -1,  11},
            /*  LIT_12  */{-1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1, -1,  -1,  -1},
            /*  NUM_13  */{-1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  13,  -1, -1,  -1,  -1},
            /*  WS_14   */{-1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  14, -1,  -1,  -1},

    };

    private SortedMap<Position, String> messages;
    private ArrayList<Token> tokens;
    private String program;
    private Position pos;
    private int state;

    public Automata(String program) {
        this.program = program;
        this.pos = new Position(program);
        this.state = 0;
        this.messages = new TreeMap<>();
        this.tokens = new ArrayList<>();
    }

    private int getCode(char c) {
        if (c >= '0' && c <= '9')
            return 10;
        if ('<' == c )
            return 7;
        if ('>' == c )
            return 8;
        if (' ' == c  || '\r' == c || '\t' == c)
            return 11;
        if ('\'' == c)
            return 9;

        switch (c) {
            case 'd':
                return 0;
            case 'o':
                return 1;
            case 'w':
                return 2;
            case 'h':
                return 3;
            case 'i':
                return 4;
            case 'l':
                return 5;
            case 'e':
                return 6;
            case '\n':
                return 13;
        }

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            return 12;

        return 14;
    }

    private String getStateName(int state) {
        if (state == 1 || state == 3 || (state <= 7 && state>=4))
            return "IDENT";

        if (state == 12)
            return "STRING LITERAL";

        switch (state) {
            case 13:
                return "NUMBER";
            case 8:
                return "OPERATION";
            case 9:
                return "OPERATION";
            case 14:
                return "WHITESPACE";
            case 2:
                return "KEYWORD";
            default:
                return "ERROR";
        }
    }

    public void run() {
        while (!pos.isEOF()) {
            StringBuilder word = new StringBuilder();
            state = 0;
            boolean finalState = false;
            boolean errorState = false;
            Position start = new Position(pos);

            while (!pos.isEOF()) {

                char currChar = program.charAt(pos.getIndex());
                int jumpCode = getCode(currChar);

                int next_state = table[state][jumpCode];

                if (-1 == next_state) {
                    if (state == 0) {
                        errorState = true;
                    } else {
                        finalState = true;
                    }
                    break;
                }

                word.append(currChar);
                state = next_state;
                pos = pos.next();

                if (pos.isEOF()) {
                    finalState = true;
                    break;
                }

            }
            if (finalState) {
                Fragment frag = new Fragment(start, pos);
                tokens.add(new Token(getStateName(state), word.toString().replaceAll("\n", " "),  frag));
                continue;
            }

            if (errorState) {
                messages.put(new Position(pos), "Unexpected characters");
            }

            pos = pos.next();
        }

        Fragment frag = new Fragment(pos, pos);
        tokens.add(new Token("END_OF_PROGRAM" , " " , frag));
    }

    public boolean hasNextToken() {
        return !tokens.isEmpty();
    }

    public Token nextToken() {
        return tokens.remove(0);
    }

    public void output_messages() {
        System.out.println("\nMessages:");
        for (Map.Entry<Position, String> entry : messages.entrySet()) {
            System.out.print("ERROR ");
            System.out.print("(" + entry.getKey().getLine() + ", " +
                    entry.getKey().getPos() + "): ");
            System.out.println(entry.getValue());
        }
    }
}
