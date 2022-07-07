/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.impl.IndexSearcher;
import hust.cs.javacourse.search.query.impl.SimpleSorter;
import hust.cs.javacourse.search.util.Config;

/**
 * <pre>
 *     简单测试索引的查询功能.
 * </pre>
 */
public class TestSearchIndex {
    /**
     * 程序入口
     *
     * @param args 命令数组
     */
    public static void main(String[] args) {
        AbstractIndexSearcher searcher = new IndexSearcher();
        searcher.open(Config.INDEX_DIR + "index.dat");
        AbstractHit[] hits = searcher.search(new Term("coronavirus"), new SimpleSorter());
        if (hits != null) {
            for (AbstractHit hit : hits) {
                System.out.println(hit);
            }
        }
    }
}