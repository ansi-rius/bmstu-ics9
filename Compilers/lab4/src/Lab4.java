import java.util.Arrays;
import java.util.Scanner;
import java.util.function.IntPredicate;

class Position {
    private String text;
    private int index, line, col;

    public Position(String text) {
        this(text, 0, 1, 1);
    }

    private Position(String text, int index, int line, int col) {
        this.text = text;
        this.index = index;
        this.line = line;
        this.col = col;
    }

    public int getChar() {
        return index < text.length() ? text.codePointAt(index) : -1;
    }

    public boolean satisfies(IntPredicate p) {
        return p.test(getChar());
    }

    public Position skip() {
        int c = getChar();
        switch (c) {
            case -1:
                return this;
            case '\n':
                return new Position(text, index + 1, line + 1, 1);
            default:
                return new Position(text, index + (c > 0xFFFF ? 2 : 1), line, col + 1);
        }
    }

    public Position skipWhile(IntPredicate p) {
        Position pos = this;
        while (pos.satisfies(p)) pos = pos.skip();
        return pos;
    }

    public String getSubText(Position end) {
        return text.substring(index, end.index);
    }

    public String toString() {
        return String.format("(%d, %d)", line, col);
    }

    public Position getCopy() {
        return new Position(text, index, line, col);
    }
}

class SyntaxError extends Exception {
    public SyntaxError(Position pos, String msg) {
        super(String.format("Syntax error at %s: %s", pos.toString(), msg));
    }
}

enum Tag {
    IDENT,
    KEYWORD,
    OPERATION,
    UNKNOWN,
    END_OF_TEXT;

    public String toString() {
        switch (this) {
            case IDENT:
                return "IDENT";
            case KEYWORD:
                return "KEYWORD";
            case OPERATION:
                return "OPERATION";
            case UNKNOWN:
                return "UNKNOWN";
            case END_OF_TEXT:
                return "END OF TEXT";
        }
        throw new RuntimeException("unreachable code");
    }
}

class Token {
    private Tag tag;
    private String value;
    private Position start, follow;

    public Token(String text) throws SyntaxError {
        this(new Position(text));
    }

    private Token(Position cur) throws SyntaxError {
        value = "";
        start = cur.skipWhile(Character::isWhitespace);
        follow = start.skip();
        int c = start.getChar();
        if (c == -1) {
            tag = Tag.END_OF_TEXT;
        }

        else if (((c == '-' || c == '=' ) && follow.getChar() == '>')) {
            follow = follow.skip();
            assignTagKEYWORDAndValue();
        }
        else if (isCharacterPart(c)) {
            follow = follow.skipWhile(isSymbol());
            assignTagOPERATIONAndValue();
        }
        else if (c == '`' && follow.satisfies(Character::isLetter)) {
            Position tmp = follow.skipWhile(isIdent());
            if (tmp.getChar() != '`') {
                follow = follow.skipWhile(isQuote());
                skipUnknown();
            } else {
                follow = follow.skipWhile(isQuote());
                follow = follow.skip();
                assignTagOPERATIONAndValue();
            }

        }
        else if (start.satisfies(Character::isLetter)) {
            Position p = start.getCopy();
            if (!follow.satisfies(Character::isWhitespace)) {
                if (follow.satisfies(Character::isDigit) || follow.satisfies(Character::isLetter)) {
                    follow = follow.skipWhile(Character::isLetterOrDigit);
                    String word = (p.getSubText(follow));
                    if (word.equals("where")) {
                        if (!follow.satisfies(Character::isWhitespace)) {
                            skipUnknown();
                            return;
                        }
                        assignTagKEYWORDAndValue();
                    } else
                    if (!follow.satisfies(Character::isWhitespace)) {
                        skipUnknown();
                        return;
                    }
                    else {
                        assignTagIDENTAndValue();
                    }
                } else {
                    assignTagIDENTAndValue();
                }
            } else {
                assignTagIDENTAndValue();
            }
        }

        else {
            skipUnknown();
            return;
        }
    }

    private boolean isCharacterPart(int c) {
        if (!(c == '!' || c == '#' || c == '$' || c == '%' || c == '&'
                || c == '*' || c == '+' || c == '.' || c == '/' || c == '<'
                || c == '=' || c == '>' || c == '?' || c == '@' || c == '^'
                || c == '|' || c == '-' || c == '~' || c == '\\')) {
            return false;
        }
        return true;
    }

    private IntPredicate isSymbol() {
        IntPredicate predicate = c -> c == '!' || c == '#' || c == '$' || c == '%' || c == '&'
                || c == '*' || c == '+' || c == '.' || c == '/' || c == '<'
                || c == '=' || c == '>' || c == '?' || c == '@' || c == '^'
                || c == '|' || c == '-' || c == '~' || c == '\\';
        return predicate;
    }

    private IntPredicate isQuote() {
        IntPredicate predicate = c -> (c != '`');
        return predicate;
    }

    private IntPredicate isIdent() {
        IntPredicate predicate = c -> (c != '`' && !isCharacterPart(c) && c != ' ');
        return predicate;
    }

    private void assignTagOPERATIONAndValue() {
        tag = Tag.OPERATION;
        value = start.getSubText(follow);
    }

    private void assignTagKEYWORDAndValue() {
        tag = Tag.KEYWORD;
        value = start.getSubText(follow);
    }

    private void assignTagIDENTAndValue() {
        tag = Tag.IDENT;
        value = start.getSubText(follow);
    }

    private void skipUnknown() {
        tag = Tag.UNKNOWN;
        skipBeforeWhitespace();
        value = start.getSubText(follow);
    }

    private void skipBeforeWhitespace() {
        while (!follow.satisfies(Character::isWhitespace) && follow.getChar() != -1) {
            follow = follow.skip();
        }
    }

    public Token next() throws SyntaxError {
        return new Token(follow);
    }

    public String getValue() {
        return value;
    }

    public Tag getTag() {
        return tag;
    }

    public Position getStart() {
        return start;
    }

    public Position getFollow() {
        return follow;
    }
}

public class Lab4 {
    private static Token token;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        in.useDelimiter("\\Z");
        String text = in.next();

        try {
            token = new Token(text);
            do {
                printToken(
                        token.getTag().toString(),
                        token.getStart().toString(),
                        token.getFollow().toString(),
                        token.getValue()
                );
                token = token.next();

            } while (token.getTag() != Tag.END_OF_TEXT);
        } catch (SyntaxError e) {
            System.out.println(e.getMessage());
        }
    }

    private static void printToken(String tag, String start, String end, String value) {
        System.out.printf("%s %s-%s: %s\n", tag, start, end, value);
    }
}