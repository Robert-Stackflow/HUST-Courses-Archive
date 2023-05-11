import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class PreProcesser {
    private static final String fileName = "sent_receive.csv";
    private static List<String> edges;
    private static List<Integer> nodes;

    public static void init() {
        edges = new ArrayList<>();
        nodes = new ArrayList<>();
        try {
            Scanner scanner = new Scanner(new File(fileName));
            scanner.nextLine();
            while (scanner.hasNextLine()) {
                String[] words = scanner.nextLine().split(",");
                int sender = Integer.parseInt(words[2]);
                int receiver = Integer.parseInt(words[1]);
                if (!nodes.contains(sender))
                    nodes.add(sender);
                if (!nodes.contains(receiver))
                    nodes.add(receiver);
                if (!edges.contains(sender + "," + receiver))
                    edges.add(sender + "," + receiver);
            }
        } catch (FileNotFoundException e) {
            System.out.println(fileName + " Not Found!");
        }
    }

    public static List<String> getEdges() {
        return edges;
    }

    public static Matrix getMatrix() {
        Matrix matrix = new Matrix(nodes.size(), nodes.size());
        for (String edge : edges) {
            String[] words = edge.split(",");
            int sender = Integer.parseInt(words[0]);
            int receiver = Integer.parseInt(words[1]);
            matrix.setElement(nodes.indexOf(sender), nodes.indexOf(receiver), 1.0);
        }
        return matrix;
    }

    public static List<Integer> getNodes() {
        return nodes;
    }
}
