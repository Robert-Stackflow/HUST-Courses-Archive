import recommendation.ContentBasedRecommendation;
import recommendation.UserCFRecommendation;

import java.util.Scanner;

public class RecommendSystem {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("输入推荐算法类型(输入0表示UserCF，输入1表示ContentBased):");
        int choice = scanner.nextInt();
        if (choice == 0) {
            UserCFRecommendation.run();
        } else if (choice == 1) {
            ContentBasedRecommendation.run();
        }
    }
}
