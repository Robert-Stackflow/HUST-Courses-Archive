package recommendation;

import util.Matrix;
import util.Movie;
import util.Record;

import java.util.*;

import static util.FileUtil.*;
import static util.MapUtil.sortMap;

public class UserCFRecommendation {
    static private final Map<Integer, Set<String>> userRatingMap = new TreeMap<>();
    static private final Map<Integer, Set<Integer>> userMovieMap = new TreeMap<>();
    static private final Map<Integer, Set<Integer>> movieUserMap = new TreeMap<>();
    static private final int N = 5;
    static private final int K = 10;
    static private List<Integer> userIdList;
    static private List<Integer> movieIdList;
    static private List<Movie> movieInfoList;
    static private List<Record> testSet;
    static private List<Record> trainSet;
    static private Matrix userMovieRatingMatrix;
    static private Matrix userSimilarity;

    static public void run() {
        //获取数据集
        testSet = getTestSet();
        trainSet = getTrainSet();
        movieIdList = getMovieSet().keySet().stream().toList();
        movieInfoList = getMovieSet().values().stream().toList();
        //处理数据
        for (Record record : trainSet) {
            //某一用户参与的评分
            Set<String> userRatingList = userRatingMap.getOrDefault(record.getUserId(), new TreeSet<>());
            userRatingList.add(record.getMovieId() + "_" + record.getRating());
            userRatingMap.put(record.getUserId(), userRatingList);
            //某一用户观看的电影
            Set<Integer> userMovieList = userMovieMap.getOrDefault(record.getUserId(), new TreeSet<>());
            userMovieList.add(record.getMovieId());
            userMovieMap.put(record.getUserId(), userMovieList);
            //观看某一电影的用户
            Set<Integer> movieUserList = movieUserMap.getOrDefault(record.getMovieId(), new TreeSet<>());
            movieUserList.add(record.getUserId());
            movieUserMap.put(record.getMovieId(), movieUserList);
        }
        userIdList = userMovieMap.keySet().stream().toList();
        //构造user-movie矩阵，并计算用户之间的pearson相似度
        userMovieRatingMatrix = new Matrix(userMovieMap.size(), movieIdList.size());
        for (Record record : trainSet)
            userMovieRatingMatrix.setElement(userIdList.indexOf(record.getUserId()), movieIdList.indexOf(record.getMovieId()), record.getRating());
        userSimilarity = calPearsonSimilarity(userMovieRatingMatrix);
        //处理用户输入
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("[UserCF]输入用户ID(输入-1退出程序,输入0运行测试集):");
            int userId = scanner.nextInt();
            if (userId == -1) {
                break;
            } else if (userId == 0) {
                predictTestSet();
            } else {
                recommendation(userId);
            }
        }
    }

    /**
     * 获取某个用户的K个邻居
     * @param userId 用户ID
     * @return 邻居ID-相似度
     */
    static public Map<Integer, Double> getNeighbors(int userId) {
        Map<Integer, Double> neighborDistMap = new TreeMap<>();
        for (String str : userRatingMap.get(userId))
            for (Integer neighborId : movieUserMap.get(Integer.parseInt(str.split("_")[0])))
                if (!neighborDistMap.containsKey(neighborId) && neighborId != userId)
                    neighborDistMap.put(neighborId, userSimilarity.getElement(userIdList.indexOf(userId), userIdList.indexOf(neighborId)));
        neighborDistMap = sortMap(neighborDistMap);
        Map<Integer, Double> kNeighbor = new TreeMap<>();
        int count = 0;
        for (Map.Entry<Integer, Double> entry : neighborDistMap.entrySet()) {
            kNeighbor.put(entry.getKey(), entry.getValue());
            if ((++count) >= K) break;
        }
        return sortMap(kNeighbor);
    }

    /**
     * 计算用户之间的相似度
     * @param userMovie user-movie矩阵
     * @return user-user相似度矩阵
     */
    static public Matrix calPearsonSimilarity(Matrix userMovie) {
        Matrix pearsonSimilarity = new Matrix(userMovie.getRowCount(), userMovie.getRowCount());
        //减去平均值
        for (int i = 0; i < userMovie.getRowCount(); i++) {
            double average = userMovie.sumOfRow(i) / userMovie.getColumnCount();
            for (int j = 0; j < userMovie.getColumnCount(); j++) {
                if (userMovie.getElement(i, j) != 0) userMovie.setElement(i, j, userMovie.getElement(i, j) - average);
            }
        }
        //计算余弦相似度
        for (int i = 0; i < userMovie.getRowCount(); i++) {
            for (int j = 0; j < userMovie.getRowCount(); j++) {
                double cosine = 0.0, iMod = 0.0, jMod = 0.0;
                if (i != j) {
                    for (int k = 0; k < userMovie.getColumnCount(); k++) {
                        cosine += userMovie.getElement(i, k) * userMovie.getElement(j, k);
                        iMod += userMovie.getElement(i, k);
                        jMod += userMovie.getElement(j, k);
                    }
                    cosine /= Math.sqrt(iMod);
                    cosine /= Math.sqrt(jMod);
                } else cosine = 1.0;
                pearsonSimilarity.setElement(i, j, cosine);
            }
        }
        return pearsonSimilarity;
    }

    /**
     * 运行测试集并输出SSE
     */
    static public void predictTestSet() {
        double SSE = 0.0;
        System.out.println("--------------测试集--------------");
        System.out.printf("%s\t%s\t%-6s\t%-6s\n", "用户ID", "电影ID", "预测评分", "实际评分");
        for (Record record : testSet) {
            double prediction = getPrediction(record.getUserId(), record.getMovieId());
            SSE += Math.pow(Math.abs(prediction - record.getRating()), 2);
            System.out.printf("%4d\t%4d\t%.6f\t%.6f\n", record.getUserId(), record.getMovieId(), prediction, record.getRating());
        }
        System.out.printf("SSE为%.6f\n", SSE);
    }

    /**
     * 获取某个用户对某个电影的评分
     * @param userId 用户ID
     * @param movieId 电影ID
     * @return 预期评分
     */
    static public double getPrediction(int userId, int movieId) {
        double prediction, sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
        //计算用户的平均评分
        double sum = 0.0, userAvg, neighborAvg;
        Map<Integer, Double> neighbors = getNeighbors(userId);
        for (String str : userRatingMap.get(userId)) {
            int ratedMovieId = Integer.parseInt(str.split("_")[0]);
            double rating = Double.parseDouble(str.split("_")[1]);
            sum += rating;
        }
        userAvg = sum / userRatingMap.get(userId).size();
        //遍历每个邻居，得到邻居们对电影的加权评分和
        for (Map.Entry<Integer, Double> entry : neighbors.entrySet()) {
            sum = 0.0;
            for (String str : userRatingMap.get(entry.getKey())) {
                int ratedMovieId = Integer.parseInt(str.split("_")[0]);
                double rating = Double.parseDouble(str.split("_")[1]);
                sum += rating;
            }
            neighborAvg = sum / userRatingMap.get(entry.getKey()).size();
            for (String str : userRatingMap.get(entry.getKey())) {
                int ratedMovieId = Integer.parseInt(str.split("_")[0]);
                double rating = Double.parseDouble(str.split("_")[1]);
                if (ratedMovieId == movieId) {
                    sum1 += entry.getValue() * (rating - neighborAvg);
                    sum2 += entry.getValue();
                }
            }
            sum3 += (sum2 == 0.0 ? entry.getValue() : sum2);
        }
        //计算预期评分
        prediction = sum1 / sum3 + userAvg;
        return prediction;
    }

    /**
     * 向某个用户推荐N部电影
     * @param userId 用户ID
     */
    static public void recommendation(int userId) {
        if (!userMovieMap.containsKey(userId)) {
            System.out.println("用户" + userId + "不存在");
        } else {
            Map<Integer, Double> neighbors = getNeighbors(userId);
            Map<Integer, Double> recommendList = new TreeMap<>();
            Map<Integer, Double> recommendMovie = new TreeMap<>();
            Map<Integer, Double> recommendUserSimilarity = new TreeMap<>();
            double sum = 0.0, userAvg;
            for (String str : userRatingMap.get(userId)) {
                int ratedMovieId = Integer.parseInt(str.split("_")[0]);
                double rating = Double.parseDouble(str.split("_")[1]);
                sum += rating;
            }
            userAvg = sum / userRatingMap.get(userId).size();
            //遍历邻居们的电影列表,计算各个电影的预期评分
            for (Map.Entry<Integer, Double> entry : neighbors.entrySet()) {
                sum = 0.0;
                double neighborAvg;
                for (String str : userRatingMap.get(entry.getKey())) {
                    int ratedMovieId = Integer.parseInt(str.split("_")[0]);
                    double rating = Double.parseDouble(str.split("_")[1]);
                    sum += rating;
                }
                neighborAvg = sum / userRatingMap.get(entry.getKey()).size();
                for (String str : userRatingMap.get(entry.getKey())) {
                    int ratedMovieId = Integer.parseInt(str.split("_")[0]);
                    double rating = Double.parseDouble(str.split("_")[1]);
                    if (!userMovieMap.get(userId).contains(ratedMovieId)) {
                        recommendMovie.put(movieIdList.indexOf(ratedMovieId), recommendMovie.getOrDefault(movieIdList.indexOf(ratedMovieId), 0.0) + entry.getValue() * (rating - neighborAvg));
                        recommendUserSimilarity.put(movieIdList.indexOf(ratedMovieId), recommendUserSimilarity.getOrDefault(movieIdList.indexOf(ratedMovieId), 0.0) + entry.getValue());
                    }
                }
            }
            for (Map.Entry<Integer, Double> entry : recommendUserSimilarity.entrySet())
                recommendList.put(entry.getKey(), recommendMovie.get(entry.getKey()) / entry.getValue() + userAvg);
            //排序并输出结果
            recommendList = sortMap(recommendList);
            int count = 0;
            System.out.println("-----------------------------为用户" + userId + "推荐的电影列表-----------------------------");
            System.out.printf("%5s\t%-6s\t%-16s\t%s\n", "电影ID", "预测评分", "电影类型", "电影名称");
            for (Map.Entry<Integer, Double> entry : recommendList.entrySet()) {
                System.out.printf("%6d\t%.6f\t%-16s\t%s\n", movieIdList.get(entry.getKey()), entry.getValue(), movieInfoList.get(entry.getKey()).getGenres(), movieInfoList.get(entry.getKey()).getTitle());
                if ((++count) >= N) break;
            }
        }
    }
}
