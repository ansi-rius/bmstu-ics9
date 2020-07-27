import java.util.Arrays;
import java.util.Scanner;
import java.util.function.IntPredicate;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Position {
    private String text;
    private int amountRemoved;
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

    public boolean isEmpty() {
        return text.isEmpty();
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
                return new Position(text.substring(1), index/* + 1*/, line + 1, 1);
            default:
                return new Position(text.substring(1), index/* + (c > 0xFFFF ? 2 : 1)*/, line, col + 1);
        }
    }

    public Position skipToken(int range) {
        Position pos = this;
        for (int i = 0; i < range; i++) {
            pos = pos.skip();
        }
        pos.text = text.substring(range);

        return pos;
    }

    public Position skipWhile(IntPredicate p) {
        Position pos = this;
        while (pos.satisfies(p)) pos = pos.skip();
        return pos;
    }

    public String getText() {
        return text;
    }

    public String toString() {
        return String.format("(%d, %d)", line, col);
    }
}

class SyntaxError extends Exception {
    public SyntaxError(Position pos, String msg) {
        super(String.format("Syntax error at %s: %s", pos.toString(), msg));
    }
}


enum Tag {
    IDENT,
    comments,
    sm1,
    sif,
    sfor,
    END_OF_TEXT;

    public String toString() {
        switch (this) {
            case IDENT:
                return "IDENT";
            case comments:
                return "comments";
            case sm1:
                return "sm1";
            case sif:
                return "sif";
            case sfor:
                return "sfor";
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
    private Pattern pattern;

    public Token(String text, Pattern pattern) throws SyntaxError {
        this(new Position(text), pattern);
    }

    private Token(Position cur, Pattern pattern) throws SyntaxError {
        this.pattern = pattern;
        start = cur.skipWhile(Character::isWhitespace);
        follow = start.skip();

        Matcher matcher = pattern.matcher(start.getText());

        if (start.isEmpty()) {
            tag = Tag.END_OF_TEXT;
            value = "EOF";
        } else if (!matcher.find()) {
            throwError("invalid character");
        } else if (matcher.group("ident") != null) {
            tag = Tag.IDENT;
            value = matcher.group("ident");
            follow = follow.skipToken(matcher.end() - 1);
        } else if (matcher.group("sm1") != null) {
            tag = Tag.sm1;
            value = matcher.group("sm1");
            follow = follow.skipToken(matcher.end() - 1);
        } else if (matcher.group("sif") != null) {
            tag = Tag.sif;
            value = matcher.group("sif");
            follow = follow.skipToken(matcher.end() - 1);
        } else if (matcher.group("comments") != null) {
            tag = Tag.comments;
            value = matcher.group("comments");
            follow = follow.skipToken(matcher.end() - 1);
        } else if (matcher.group("sfor") != null) {
            tag = Tag.sfor;
            value = matcher.group("sfor");
            follow = follow.skipToken(matcher.end() - 1);
        } else {
            throwError("invalid character");
        }
    }

    public void throwError(String msg) throws SyntaxError {
        throw new SyntaxError(start, msg);
    }

    public boolean matches(Tag... tags) {
        return Arrays.stream(tags).anyMatch(t -> tag == t);
    }

    public Token next() throws SyntaxError {
        return new Token(follow, pattern);
    }

    public Tag getTag() {
        return tag;
    }

    public Position getPosition() {
        return start;
    }

    public String getValue() {
        return value;
    }
}

public class Lab3 {

    private static Token token;
    private static String ident = "(((^(([A-z])(\\d))+)([A-z])?)|((^((\\d)([A-z]))+)([0-9])?))";
    private static String comments = "(\\\")?(?!\\\")(.*)(\\\\)?(?=\\\")|(?!\\\")(.)";
    private static String sfor = "for";
    private static String sif = "if";
    private static String sm1 = "m1";
    private static String pattern =
            "(?<sfor>^" + sfor + ")|" +
            "(?<sif>^" + sif + ")|" +
            "(?<sm1>^" + sm1 + ")|" +
            "(?<ident>^" + ident + ")|" +
            "(?<comments>^" + comments + ")|";

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        in.useDelimiter("\\Z");
        String text = in.next();
        Pattern p = Pattern.compile(pattern);
        try {
            token = new Token(text, p);
            do {
                printToken(
                        token.getTag().toString(),
                        token.getPosition().toString(),
                        token.getValue()
                );
                token = token.next();

            } while (token.getTag() != Tag.END_OF_TEXT);
        } catch (SyntaxError syntaxError) {
            syntaxError.printStackTrace();
        }
    }

    private static void printToken(String tag, String position, String value) {
        System.out.printf("%s %s: %s\n", tag, position, value);
    }
}

// /* AAAAAAA */ if for m1 a5v6n  /*b*/