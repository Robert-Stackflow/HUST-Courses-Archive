package util;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class MapUtil {
    public static Map<Integer, Double> sortMap(Map<Integer, Double> map) {
        List<Map.Entry<Integer, Double>> entryList = new ArrayList<>(map.entrySet());
        entryList.sort((o1, o2) -> o2.getValue().compareTo(o1.getValue()));
        LinkedHashMap<Integer, Double> linkedHashMap = new LinkedHashMap<>();
        for (Map.Entry<Integer, Double> e : entryList)
            linkedHashMap.put(e.getKey(), e.getValue());
        return linkedHashMap;
    }
}
