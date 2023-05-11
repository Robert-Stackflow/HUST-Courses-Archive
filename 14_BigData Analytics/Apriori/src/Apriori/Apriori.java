package Apriori;

import java.util.List;
import java.util.Map;

public class Apriori {
    private static List<List<String>> data;
    private static Map<String, Double> L1;
    private static Map<String, Double> L2;
    private static Map<String, Double> L3;
    private static Map<String, Double> L4;
    private static Map<String, Double> Rules;

    public static void main(String[] args) {
        PreProcesser.init();
        data = PreProcesser.getData();
        L1 = Filter.filter(data);
        System.out.println("L1频繁项集数:" + L1.keySet().size());
        Util.output("L1.csv", L1);
        L2 = Filter.filter(2, data, L1);
        System.out.println("L2频繁项集数:" + L2.keySet().size());
        Util.output("L2.csv", L2);
        L3 = Filter.filter(3, data, L2);
        System.out.println("L3频繁项集数:" + L3.keySet().size());
        Util.output("L3.csv", L3);
        L4 = Filter.filter(4, data, L3);
        System.out.println("L4频繁项集数:" + L4.keySet().size());
        Util.output("L4.csv", L4);
        Rules = Filter.getRules(data, L1, L2);
        Rules.putAll(Filter.getRules(data, L2, L3));
        Rules.putAll(Filter.getRules(data, L3, L4));
        System.out.println("规则数:" + Rules.keySet().size());
        Util.output("Rules.csv", Rules);
    }
}
