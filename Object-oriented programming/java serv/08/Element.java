public class Element<T> {
    private T x;
    private Element<T> parent;
    private Element<T> root;
    private int depth = 0;

    // Создаёт новый элемент со значением x
    public Element(T x) {
        this.x = x;
        parent = this;
    }

    // Возвращает значение элемента
    public T x() {
        return x;
    }

    // Определяет, принадлежит ли текущий элемент
    // тому же множеству, что и элемент elem
    public boolean equivalent(Element<T> elem) {
        return (find(this) == find(elem));
    }

    // Объединяет множество, которому принадлежит текущий
    // элемент, с множеством, которому принадлежит
    // элемент elem
    public void union(Element<T> elem) { //Не наивный Union 1 сем 3 модуль стр 112
        Element<T> root_x = find(this);
        Element<T> root_y = find(elem);
        if (root_x.depth < root_y.depth) {
            root_x.parent = root_y;
        }
        else {
            root_y.parent = root_x;
            if ((root_x.depth == root_y.depth) && (root_y != root_y)) {
                root_x.depth = root_x.depth + 1;
            }
        }
    }

    //Реализация не наивного Find 1 сем. 3 модуль, стр 113
    public Element<T> find(Element<T> elem) {
        if (elem.parent == elem)
            root = elem;
        else {
            elem.parent = find(elem.parent);
            root = elem.parent;
        }
        return root;
    }
}
