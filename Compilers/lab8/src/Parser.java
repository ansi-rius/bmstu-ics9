import java.io.File;
import java.util.Arrays;
import java.util.Scanner;
import java.util.function.IntPredicate;

class Position {
    private String text;
    private int index;

    public Position(String text) {
        this(text, 0);
    }

    private Position(String text, int index) {
        this.text = text;
        this.index = index;
    }

    public int getChar() {
        return index < text.length() ? text.codePointAt(index) : -1;
    }

    public String getWord(Position b) {
        return text.substring(index, b.index);
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
                return new Position(text, index+1);
            default:
                return new Position(text, index + (c > 0xFFFF ? 2 : 1));
        }
    }

    public Position skipWhile(IntPredicate p) {
        Position pos = this;
        while (pos.satisfies(p)) pos = pos.skip();
        return pos;
    }

    public Position skipWhileNot(char p) {
        Position pos = this;
        while (pos.getChar() != p) pos = pos.skip();
        return pos;
    }
}

class SyntaxError extends Exception {
    public SyntaxError(Position pos, String msg) {
        super(msg);
    }
}

enum Tag {
    NONTERMS,
    TERMS,
    NONTERM,
    TERM,
    RULE,
    LPAREN,
    RPAREN,
    LFPAREN,
    RFPAREN,
    ALTER,
    ASSIGN,
    END_OF_TEXT;
}

class Token {
    public Tag tag;
    public Position start, follow;

    public Token(String text) throws SyntaxError {
        this(new Position(text));
    }

    private Token(Position cur) throws SyntaxError {
        start = cur.skipWhile(Character::isWhitespace);
        follow = start.skip();
        //  System.out.println(start.getWord(follow));

        switch (start.getChar()) {
            case -1:
                tag = Tag.END_OF_TEXT;
                break;
            case '(':
                tag = Tag.LPAREN;

                break;
            case ')':
                tag = Tag.RPAREN;

                break;
            case '{':
                tag = Tag.LFPAREN;

                break;
            case '}':
                tag = Tag.RFPAREN;

                break;
            case '|':
                tag = Tag.ALTER;

                break;
            case '=':
                tag = Tag.ASSIGN;

                break;
            case '$':
                start = follow;
                follow = follow.skipWhile(Character::isLetter);
                if (start.getWord(follow).equals("TERM")) {
                    tag = Tag.TERMS;
                } else if (start.getWord(follow).equals("NTERM")) {
                    tag = Tag.NONTERMS;
                } else if (start.getWord(follow).equals("RULE")) {
                    tag = Tag.RULE;
                } else {
                    throwError("error");
                }
                break;

            case '"':
                follow = follow.skipWhileNot('"').skip();
                if (start.getWord(follow).length() == 3) {
                    tag = Tag.TERM;
                } else {
                    throwError("error");
                }
                break;

            default:
                if (start.satisfies(Character::isLetter)) {
                    follow = follow.skipWhile(Character::isLetterOrDigit);

                    if (start.getWord(follow).length() == 1) {
                        if (start.getChar() >= 'A' && start.getChar() <= 'Z') {
                            tag = Tag.NONTERM;
                        }
                    }
                } else {
                    throwError("error");
                }
        }
    }

    public void throwError(String msg) throws SyntaxError {
        throw new SyntaxError(start, msg);
    }

    public boolean matches(Tag...tags) {
        return Arrays.stream(tags).anyMatch(t -> tag == t);
    }

    public Token next() throws SyntaxError {
        return new Token(follow);
    }
}

public class Parser {
    private static Token sym;
    public static Grammar grammar = new Grammar();

    private static void expect(Tag tag) throws SyntaxError {
        if (!sym.matches(tag)) {
            sym.throwError("error");
        }
        sym = sym.next();
    }

    public static void main(String[] args) throws Exception {
        try {
            File file = new File("/Users/anemone/Documents/3curs/6sem/compilers/lab8/src/test.txt");
            Scanner in = new Scanner(file);
            in.useDelimiter("\\Z");
            String text = in.next();
            sym = new Token(text);
            parse();
            grammar.findFirst();
        }
        catch (SyntaxError e) {
            System.out.println(e.getMessage());
        }
    }
    //Grammar ::= ('$NTERM' Nterms | '$TERM' Terms | '$RULE' Rule)+
    //Nterms ::= N+
    //Terms ::= T+
    //Rule ::= ((N | T | '{' Rule '}' | '(' Rule ')' ) ('|' Rule)?)+

    //Grammar ::= ('$NTERM' Nterms | '$TERM' Terms | '$RULE' Rule)+
    private static void parse() throws Exception {
        while (!sym.matches(Tag.END_OF_TEXT)) {
            if (sym.matches(Tag.NONTERMS)) {
                System.out.println("\nNONTERMS");
                sym = sym.next();
                do {
                    parseNonterms();
                    sym = sym.next();

                } while (sym.matches(Tag.NONTERM));

            } else if (sym.matches(Tag.TERMS)) {
                System.out.println("\nTERMS");
                sym = sym.next();

                do {
                    parseTerms();
                    sym = sym.next();
                } while (sym.matches(Tag.TERM));
            } else if (sym.matches(Tag.RULE)) {
                sym = sym.next();
                parseRule();
            }
            else {
                sym.throwError("error");
            }
        }
    }

    //Nterms ::= N+
    private static void parseNonterms() {
        System.out.println(sym.start.getWord(sym.follow));
        grammar.addNonterminal(new Nonterminal(sym.start.getWord(sym.follow)));
    }

    //Terms ::= T+
    private static void parseTerms() {
        System.out.println(sym.start.getWord(sym.follow));
        grammar.addTerminal(new Terminal(sym.start.getWord(sym.follow)));
    }

    //Rule ::= ( ( N | T | '{' Rule '}' | '(' Rule ')' ) ('|' Rule)?)+
    private static void parseRule() throws Exception {
        if (!sym.matches(Tag.NONTERM)) {
            sym.throwError("error");
        } else {
            Nonterminal rule = grammar.getNonterminal(sym.start.getWord(sym.follow));
            sym = sym.next();
            expect(Tag.ASSIGN);
            AST tree = new AST();
            do {
                tree = parseRule1(tree);
            }
            while (!sym.matches(Tag.NONTERMS, Tag.TERMS, Tag.END_OF_TEXT, Tag.RULE));
            grammar.addRule(rule, tree.node);
        }
    }

    private static AST parseRule1(AST ast) throws Exception {
        if (sym.matches(Tag.TERM)) {
            ast.push(grammar.getTerminal(sym.start.getWord(sym.follow)));
            sym = sym.next();
        } else if (sym.matches(Tag.NONTERM)) {
            ast.push(grammar.getNonterminal(sym.start.getWord(sym.follow)));
            sym = sym.next();
        } else if (sym.matches(Tag.LFPAREN)) {
            sym = sym.next();
            AST current = new AST();
            do {
                current = parseRule1(current);
            } while (!sym.matches(Tag.RFPAREN));
            ast.push(new Alt(current.node, new Empty()));
            expect(Tag.RFPAREN);
        } else if (sym.matches(Tag.LPAREN)) {
            sym = sym.next();
            AST current = new AST();
            do {
                current = parseRule1(current);
            } while (!sym.matches(Tag.RPAREN));
            ast.push(current.node);
            expect(Tag.RPAREN);
        } else if (sym.matches(Tag.RPAREN, Tag.RFPAREN)) {
            return ast;
        } else if (!sym.matches(Tag.ALTER)){
            sym.throwError("error");
        }
        if (sym.matches(Tag.ALTER)) {
            sym = sym.next();
            AST current = parseRule1(new AST());
            ast.node = new Alt(ast.node, current.node);
        }
        return ast;
    }
}