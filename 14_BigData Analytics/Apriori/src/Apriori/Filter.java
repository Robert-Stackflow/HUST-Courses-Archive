package Apriori;

import java.util.*;

import static Apriori.Util.*;

public class Filter {
    private static final double SUPPORT_THRESHOLD = 0.005;
    private static final double CONFIDENCE_THRESHOLD = 0.5;
    private static final int BUCKET_SIZE = 1000;
    static BitSet bitSet = new BitSet(BUCKET_SIZE);

    public static Map<String, Double> filter(List<List<String>> data) {
        int basketCount = data.size();
        Map<String, Integer> map = new TreeMap<>();
        Map<String, Integer> bucket1 = new TreeMap<>();
        for (List<String> basket : data) {
            for (String item : basket)
                map.put((item = arrayToString(item)), map.getOrDefault(item, 0) + 1);
            //PCY
            for (String item1 : basket) {
                int index = basket.indexOf(item1);
                for (String item2 : basket.subList(index + 1, basket.size())) {
                    if (item1.equals(item2)) continue;
                    String str = arrayToString(merge(true, item1, item2));
                    bucket1.put(str, bucket1.getOrDefault(str, 0) + 1);
                }
            }
        }
        bucket1.forEach((k, v) -> {
            if ((v * 1.0) / basketCount >= SUPPORT_THRESHOLD) bitSet.set(hash(k));
        });
        for (int i = 0; i < bitSet.size(); i++)
            System.out.print((bitSet.get(i) ? 1 : 0) + (i < bitSet.size() - 1 ? "," : "\n"));
//        System.out.println(bitSet);
        return getSupportedItemSets(data, map);
    }

    public static Map<String, Double> filter(int pass, List<List<String>> data, Map<String, Double> L1) {
        int basketCount = data.size();
        Map<String, Integer> map = new TreeMap<>();
        String[] frequentItems = L1.keySet().toArray(new String[0]);
        for (int i = 0; i < frequentItems.length; i++) {
            for (int j = i + 1; j < frequentItems.length; j++) {
                String[] mergedItems = merge(false, frequentItems[i], frequentItems[j]);
                if (mergedItems.length > pass) continue;
                String str = arrayToString(mergedItems);
                if (!bitSet.get(hash(str)) && pass == 2) continue;
                int count = count(data, mergedItems);
                if (count != 0) map.put(str, count);
            }
        }
        System.out.println("C" + pass + "候选项集数:" + map.keySet().size());
        return getSupportedItemSets(data, map);
    }

    public static Map<String, Double> getRules(List<List<String>> data, Map<String, Double> L1, Map<String, Double> L2) {
        Map<String, Double> supportedRules = new TreeMap<>();
        for (Map.Entry<String, Double> entry : L2.entrySet())
            supportedRules.putAll(getSupportedRules(L1, entry.getKey(), entry.getValue()));
        return supportedRules;
    }

    public static Map<String, Double> getSupportedItemSets(List<List<String>> data, Map<String, Integer> map) {
        Map<String, Double> supportedItemSets = new TreeMap<>();
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            double rate = (entry.getValue() * 1.0) / data.size();
            if (rate >= SUPPORT_THRESHOLD) supportedItemSets.put(entry.getKey(), rate);
        }
        return supportedItemSets;
    }

    public static Map<String, Double> getSupportedRules(Map<String, Double> data, String str, double support) {
        String[] items = stringToArray(str);
        Map<String, Double> supportedRules = new TreeMap<>();
        for (String item : items) {
            String[] leftItems = new String[items.length - 1];
            for (int i = 0, j = 0; i < items.length; i++)
                if (!Objects.equals(items[i], item)) leftItems[j++] = items[i];
            double rate = support / data.get(arrayToString(leftItems));
            if (rate >= CONFIDENCE_THRESHOLD) supportedRules.put(arrayToString(leftItems) + "->" + item, rate);
        }
        return supportedRules;
    }

    public static int hash(String key) {
        return Math.abs(key.hashCode() % BUCKET_SIZE);
    }

    public static int count(List<List<String>> data, String[] set) {
        int count = 0;
        String setString = arrayToString(set);
        for (List<String> line : data)
            if (contains(line, set))
                count++;
        return count;
    }

}
