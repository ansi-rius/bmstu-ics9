import java.util.*;


class RHS {
    public Set<String> first(Map<Nonterminal, RHS> rules) {
        return new HashSet<>();
    }
}

class Terminal extends RHS {
    String name;

    Terminal(String name) {
        this.name = name;
    }

    public Set<String> first(Map<Nonterminal, RHS> rules) {
        return new HashSet<>(Arrays.asList(this.name));
    }
}

class Nonterminal extends RHS {
    String name;

    Nonterminal(String name) {
        this.name = name;
    }

    public Set<String> first(Map<Nonterminal, RHS> rules) {
        return rules.get(this).first(rules);
    }
}

class Empty extends RHS {
    static String name = "eps";

    public Set<String> first(Map<Nonterminal, RHS> rules) {
        return new HashSet<>(Arrays.asList("eps"));
    }
}

class Concat extends RHS {
    RHS left, right;

    Concat(RHS left, RHS right) {
        this.left = left;
        this.right = right;
    }

    public Set<String> first(Map<Nonterminal, RHS> rules) {
        if (left.getClass() != Empty.class) {
            return left.first(rules);
        } else {
            Set<String> leftFirst = left.first(rules);
            leftFirst.remove(Empty.name);
            return new HashSet<String>() {{
                addAll(leftFirst);
                addAll(right.first(rules));
            }};
        }
    }
}

class Alt extends RHS {
    RHS left, right;

    Alt(RHS left, RHS right) {
        this.left = left;
        this.right = right;
    }

    public Set<String> first(Map<Nonterminal, RHS> rules) {
        return new HashSet<String>() {{
            addAll(left.first(rules));
            addAll(right.first(rules));
        }};
    }
}

public class Grammar {
    private ArrayList<Nonterminal> nonterminals = new ArrayList<>();
    private ArrayList<Terminal> terminals = new ArrayList<>();
    private Map<Nonterminal, RHS> rules = new HashMap<>();

    public void addNonterminal(Nonterminal n) {
        nonterminals.add(n);
    }

    public Nonterminal getNonterminal(String name) throws Exception {
        for (Nonterminal n : nonterminals) {
            if (n.name.equals(name)) {
                return n;
            }
        }
        throw new Exception("unknown nonterminal");
    }

    public void addTerminal(Terminal t) {
        terminals.add(t);
    }

    public Terminal getTerminal(String name) throws Exception {
        for (Terminal n : terminals) {
            if (n.name.equals(name)) {
                return n;
            }
        }
        throw new Exception("unknown terminal");
    }

    public void addRule(Nonterminal n, RHS rhs) {
        rules.put(n, rhs);
    }

    public void findFirst() {
        System.out.println("\n\nFIRST:");
        for (Nonterminal n : nonterminals) {
            Set<String> first = rules.get(n).first(rules);
            System.out.print(n.name + ": ");
            for (String s : first) {
                System.out.print(s + " ");
            }
            System.out.println();
        }
    }
}
