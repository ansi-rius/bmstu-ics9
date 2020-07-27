

public class AST {
    public RHS node;

    AST() {
        this.node = new RHS();
    }

    public void push(RHS newRhs) {
        if (this.node.getClass() == RHS.class) {
            this.node = newRhs;
        } else {
            this.node = new Concat(this.node, newRhs);
        }
    }
}
