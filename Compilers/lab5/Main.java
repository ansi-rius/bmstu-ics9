import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {

    public static void main(String[] args) throws IOException {
        String program = new String(Files.readAllBytes(Paths.get(args[0])));
        Automata auto = new Automata(program);
        auto.run();
        while (auto.hasNextToken()) {
            System.out.println(auto.nextToken());
        }
        auto.output_messages();
    }

}
