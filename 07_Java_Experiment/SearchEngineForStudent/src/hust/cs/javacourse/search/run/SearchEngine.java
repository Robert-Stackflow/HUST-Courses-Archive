/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.DocumentBuilder;
import hust.cs.javacourse.search.index.impl.Index;
import hust.cs.javacourse.search.index.impl.IndexBuilder;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.impl.IndexSearcher;
import hust.cs.javacourse.search.query.impl.SimpleSorter;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StopWords;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

/**
 * <pre>
 *     主测试引擎，提供控制台中简单的用户交互界面.
 * </pre>
 */
public class SearchEngine {
    /**
     * 程序的入口
     *
     * @param args 命令数组
     */
    public static void main(String[] args) {
        clearConsole(1);
        AbstractIndexBuilder indexBuilder;
        AbstractIndexSearcher indexSearcher = null;
        int option = 1;
        while (option != 0) {
            System.out.println("**************************************************");
            System.out.println("**           Welcome To Search Engine           **");
            System.out.println("**************************************************");
            System.out.println("** 0. Exit The Engine                           **");
            System.out.println("** 1. Build Index From Existing Text Files      **");
            System.out.println("** 2. Build Index From Existing Index File      **");
            System.out.println("** 3. Search Certain Term(s)                    **");
            System.out.println("** 4. Save Index into text file and display     **");
            System.out.println("**************************************************");
            System.out.println("Please Input Your Choice: ");
            Scanner choiceScanner = new Scanner(System.in);
            option = choiceScanner.nextInt();
            switch (option) {
                case 1:
                    AbstractDocumentBuilder documentBuilder = new DocumentBuilder();
                    indexBuilder = new IndexBuilder(documentBuilder);
                    indexBuilder.buildIndex(Config.DOC_DIR);
                    if ((new File(Config.INDEX_DIR + "index.dat")).exists()) {
                        indexSearcher = new IndexSearcher();
                        indexSearcher.open(Config.INDEX_DIR + "index.dat");
                        System.out.println("Index build successfully!");
                    } else
                        System.out.println("Searcher build failed ! (Index doesn't exist)");
                    clearConsole(3);
                    break;
                case 2:
                    if ((new File(Config.INDEX_DIR + "index.dat")).exists()) {
                        indexSearcher = new IndexSearcher();
                        indexSearcher.open(Config.INDEX_DIR + "index.dat");
                        System.out.println("Index build successfully!");
                    } else
                        System.out.println("Searcher build failed ! (Index doesn't exist)");
                    clearConsole(3);
                    break;
                case 3:
                    if (indexSearcher == null) {
                        System.out.println("Searcher build failed ! (build index first)");
                        clearConsole(3);
                    }
                    else
                        searchFunction(indexSearcher);
                    break;
                case 4:
                    if (indexSearcher == null)
                        System.out.println("Save index failed ! (build index first)");
                    else {
                        Index index = new Index();
                        index.load(new File(Config.INDEX_DIR + "index.dat"));
                        index.print(Config.INDEX_DIR + "index.txt");
                        System.out.println(index);
                    }
                    clearConsole(3);
                    break;
                case 0:
                default:
                    clearConsole(1);
            }
        }
    }

    /**
     * <pre>
     * 根据不同模式清空控制台.
     * mode为1时立即清空控制台.
     * mode为2时提示用户按任意键继续.
     * mode为其他值时提示用户按任意键继续后清空控制台.
     *
     * @param mode 清空控制台的模式
     * </pre>
     */
    public static void clearConsole(int mode) {
        try {
            if (System.getProperty("os.name").contains("Windows")) {
                if (mode != 1)
                    new ProcessBuilder("cmd", "/c", "pause").inheritIO().start().waitFor();
                if (mode != 2)
                    new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            } else
                Runtime.getRuntime().exec("clear");
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    /**
     * <pre>
     * 判断单词是否合法.
     * 如果单词在停用词中提示之并输出停用词列表.
     * 否则,如果单词长度不合法提示之并输出单词长度限制.
     * 否则,如果单词不符合正则表达式提示之并输出正则限制.
     * 否则,说明单词合法则返回0表示合法.
     *
     * @param term 待判断的单词
     * @return 返回错误类型(1 - 3)或者合法标志(0)
     * </pre>
     */
    public static int isIllegalTerm(AbstractTerm term) {
        ArrayList<String> STOP_WORDS = new ArrayList<>(Arrays.asList(StopWords.STOP_WORDS));
        if (STOP_WORDS.contains(term.getContent())) {
            System.out.println("INPUT ERROR:the term " + term.getContent() + " is in STOP_WORDS!\n" + "STOP_WORDS:\n" + STOP_WORDS);
            return 1;
        } else if (term.getContent().length() > Config.TERM_FILTER_MAXLENGTH || term.getContent().length() < Config.TERM_FILTER_MINLENGTH) {
            System.out.println("INPUT ERROR:the length of term " + term.getContent() + " is beyond the limit!\n" + "TERM_MINLENGTH:" + Config.TERM_FILTER_MINLENGTH + "\nTERM_MAXLENGTH:" + Config.TERM_FILTER_MAXLENGTH);
            return 2;
        } else if (!term.getContent().matches(Config.TERM_FILTER_PATTERN)) {
            System.out.println("INPUT ERROR:the term " + term.getContent() + " does not match the pattern!\n" + "TERM_PATTERN:" + Config.TERM_FILTER_PATTERN);
            return 3;
        }
        return 0;
    }

    /**
     * 打印输出用于查询单词的副菜单，并根据用户选择进行操作.
     *
     * @param indexSearcher 用于检索的AbstractIndexSearcher对象
     */
    public static void searchFunction(AbstractIndexSearcher indexSearcher) {
        clearConsole(1);
        while (true) {
            System.out.println("**************************************************");
            System.out.println("**           Welcome To Search Engine           **");
            System.out.println("**************************************************");
            System.out.println("** 0. Exit The Search                           **");
            System.out.println("** 1. Search articles with one word             **");
            System.out.println("** 2. Search articles with two words(AND)       **");
            System.out.println("** 3. Search articles with two words(OR)        **");
            System.out.println("** 4. Search articles with two words(NEIGHBOR)  **");
            System.out.println("**************************************************");
            System.out.println("Please Input Your Option: ");
            SimpleSorter sorter = new SimpleSorter();
            Scanner optionScanner = new Scanner(System.in);
            int option = optionScanner.nextInt();
            AbstractHit[] result;
            AbstractTerm queryTerm1;
            AbstractTerm queryTerm2;
            Scanner queryTermScanner = new Scanner(System.in);
            switch (option) {
                case 0:
                    clearConsole(3);
                    return;
                case 1:
                    System.out.print("Input The Word: ");
                    queryTerm1 = new Term(queryTermScanner.next());
                    if (isIllegalTerm(queryTerm1) == 0) {
                        result = indexSearcher.search(queryTerm1, sorter);
                        System.out.println(IndexSearcher.printQuery(queryTerm1, result, Config.INDEX_DIR + "query.txt"));
                    }
                    clearConsole(3);
                    break;
                case 2:
                    System.out.print("Input The Two Words(A B): ");
                    String[] terms = queryTermScanner.nextLine().split(" ");
                    queryTerm1 = new Term(terms[0]);
                    queryTerm2 = new Term(terms[1]);
                    if (isIllegalTerm(queryTerm1) == 0 && isIllegalTerm(queryTerm2) == 0) {
                        result = indexSearcher.search(queryTerm1, queryTerm2, sorter, AbstractIndexSearcher.LogicalCombination.AND);
                        System.out.println(IndexSearcher.printQuery(queryTerm1, queryTerm2, AbstractIndexSearcher.LogicalCombination.AND, result, Config.INDEX_DIR + "query.txt"));
                    }
                    clearConsole(3);
                    break;
                case 3:
                    System.out.print("Input The Two Words(A B): ");
                    String buf = queryTermScanner.nextLine();
                    queryTerm1 = new Term(buf.split(" ")[0]);
                    queryTerm2 = new Term(buf.split(" ")[1]);
                    if (isIllegalTerm(queryTerm1) == 0 && isIllegalTerm(queryTerm2) == 0) {
                        result = indexSearcher.search(queryTerm1, queryTerm2, sorter, AbstractIndexSearcher.LogicalCombination.OR);
                        System.out.println(IndexSearcher.printQuery(queryTerm1, queryTerm2, AbstractIndexSearcher.LogicalCombination.OR, result, Config.INDEX_DIR + "query.txt"));
                    }
                    clearConsole(3);
                    break;
                case 4:
                    System.out.print("Input The Two Words(A B): ");
                    String buf1 = queryTermScanner.nextLine();
                    queryTerm1 = new Term(buf1.split(" ")[0]);
                    queryTerm2 = new Term(buf1.split(" ")[1]);
                    if (isIllegalTerm(queryTerm1) == 0 && isIllegalTerm(queryTerm2) == 0) {
                        result = indexSearcher.search(queryTerm1, queryTerm2, sorter, null);
                        System.out.println(IndexSearcher.printQuery(queryTerm1, queryTerm2, null, result, Config.INDEX_DIR + "query.txt"));
                    }
                    clearConsole(3);
                    break;
                default:
                    clearConsole(1);
            }
        }
    }
}