import java.util.*;
import java.util.function.BiConsumer;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class Test {
    public static void main(String[] args) {
        //String[] info = {"Иванов Иван Иваныч, 1999", "Петров Пётр Петрович, 2000",
        //                 "Михайлов Михаил Михайлович, 8888"};
        HashSet<String> set = new HashSet<>();
        set.add("Иванов Иван Иваныч, 1999");
        set.add("Петров Пётр Петрович, 2000");
        set.stream()
                .peek(s -> s.substring(0, s.indexOf(' ')));

    }
}

