/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.index.impl.DocumentBuilder;
import hust.cs.javacourse.search.index.impl.Index;
import hust.cs.javacourse.search.index.impl.IndexBuilder;
import hust.cs.javacourse.search.util.Config;

import java.io.File;

/**
 * <pre>
 *     简单测试索引的构建功能.
 * </pre>
 */
public class TestBuildIndex {
    /**
     * 程序入口
     *
     * @param args 命令数组
     */
    public static void main(String[] args) {
        AbstractIndexBuilder indexBuilder = new IndexBuilder(new DocumentBuilder());

        AbstractIndex index = indexBuilder.buildIndex(Config.DOC_DIR);
        System.out.println(index);

        index.save(new File(Config.INDEX_DIR + "index.dat"));
        AbstractIndex loadIndex = new Index();
        loadIndex.load(new File(Config.INDEX_DIR + "index.dat"));
        System.out.println(loadIndex);
    }
}
