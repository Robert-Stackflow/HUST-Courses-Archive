package recommendation;

import util.Matrix;
import util.Movie;
import util.Record;

import java.util.*;

import static util.FileUtil.*;
import static util.MapUtil.sortMap;

public class ContentBasedRecommendation {
    static private final Map<Integer, Set<String>> userRatingMap = new TreeMap<>();
    static private final Map<Integer, Set<Integer>> userMovieMap = new TreeMap<>();
    static private final Map<Integer, Set<Integer>> movieUserMap = new TreeMap<>();
    static private final int N = 5;
    static private List<Integer> movieIdList;
    static private List<Movie> movieInfoList;
    static private List<Record> testSet;
    static private List<Record> trainSet;
    static private Matrix tf_idf;
    static private Matrix cosineSimilarity;

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
        //计算TF_IDF
        tf_idf = TF_IDF();
        //计算余弦相似度
        cosineSimilarity = calCosineSimilarity(tf_idf);
        //处理用户输入
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("[ContentBased]输入用户ID(输入-1退出程序,输入0运行测试集):");
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
     * 计算各个电影的TF*IDF值
     *
     * @return TF-IDF矩阵
     */
    static public Matrix TF_IDF() {
        Set<String> tags = new TreeSet<>();
        for (Movie movie : movieInfoList)
            Collections.addAll(tags, movie.getTags());
        Matrix tf = new Matrix(movieIdList.size(), tags.size());
        Matrix idf = new Matrix(movieIdList.size(), tags.size());
        Matrix tf_idf = new Matrix(movieIdList.size(), tags.size());
        for (Movie movie : movieInfoList) {
            for (String tag : movie.getTags()) {
                tf.setElement(movieIdList.indexOf(movie.getMovieId()), tags.stream().toList().indexOf(tag), 1);
                idf.setElement(movieIdList.indexOf(movie.getMovieId()), tags.stream().toList().indexOf(tag), 1);
            }
        }
        for (int i = 0; i < tf.getRowCount(); i++) {
            double sum = tf.sumOfRow(i);
            for (int j = 0; j < tf.getColumnCount(); j++)
                tf.setElement(i, j, tf.getElement(i, j) / sum);
        }
        for (int j = 0; j < idf.getColumnCount(); j++) {
            double sum = idf.sumOfColumn(j);
            for (int i = 0; i < idf.getRowCount(); i++)
                idf.setElement(i, j, Math.log(movieIdList.size() / sum));
        }
        for (int i = 0; i < tf_idf.getRowCount(); i++)
            for (int j = 0; j < tf_idf.getColumnCount(); j++)
                tf_idf.setElement(i, j, tf.getElement(i, j) * idf.getElement(i, j));
        return tf_idf;
    }

    /**
     * 计算电影间的余弦相似度
     *
     * @param tf_idf 电影的TF-IDF矩阵
     * @return 电影间的相似度矩阵
     */
    static public Matrix calCosineSimilarity(Matrix tf_idf) {
        Matrix cosineSimilarity = new Matrix(tf_idf.getRowCount(), tf_idf.getRowCount());
        for (int i = 0; i < tf_idf.getRowCount(); i++) {
            for (int j = 0; j < tf_idf.getRowCount(); j++) {
                double cosine = 0.0, iMod = 0.0, jMod = 0.0;
                if (i != j) {
                    for (int k = 0; k < tf_idf.getColumnCount(); k++) {
                        cosine += tf_idf.getElement(i, k) * tf_idf.getElement(j, k);
                        iMod += tf_idf.getElement(i, k);
                        jMod += tf_idf.getElement(j, k);
                    }
                    cosine /= Math.sqrt(iMod);
                    cosine /= Math.sqrt(jMod);
                } else cosine = 1.0;
                cosineSimilarity.setElement(i, j, cosine);
            }
        }
        return cosineSimilarity;
    }

    /**
     * 运行测试集并计算SSE
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
     *
     * @param userId  用户ID
     * @param movieId 电影ID
     * @return 预期评分
     */
    static public double getPrediction(int userId, int movieId) {
        double prediction, sumSimilarity = 0.0, sumRating = 0.0, sumWeight = 0.0;
        for (String str : userRatingMap.get(userId)) {
            int ratedMovieId = Integer.parseInt(str.split("_")[0]);
            double rating = Double.parseDouble(str.split("_")[1]);
            double similarity = movieIdList.indexOf(movieId) > movieIdList.indexOf(ratedMovieId) ? cosineSimilarity.getElement(movieIdList.indexOf(ratedMovieId), movieIdList.indexOf(movieId)) : cosineSimilarity.getElement(movieIdList.indexOf(movieId), movieIdList.indexOf(ratedMovieId));
            if (similarity > 0) {
                sumRating += rating;
                sumSimilarity += similarity;
                sumWeight += similarity * rating;
            }
        }
        if (sumSimilarity == 0) prediction = sumRating / userMovieMap.get(userId).size();
        else prediction = sumWeight / sumSimilarity;
        return prediction;
    }

    /**
     * 向某个用户推荐N部电影
     *
     * @param userId 用户ID
     */
    static public void recommendation(int userId) {
        if (!userMovieMap.containsKey(userId)) {
            System.out.println("用户" + userId + "不存在");
        } else {
            Map<Integer, Double> recommendList = new TreeMap<>();
            //计算每部电影的预期评分
            for (int i = 0; i < movieIdList.size(); i++)
                if (!userMovieMap.get(userId).contains(movieIdList.get(i)))
                    recommendList.put(i, getPrediction(userId, movieIdList.get(i)));
            //排序并输出
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
