/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.util.Config;

import java.io.File;

import static hust.cs.javacourse.search.util.FileUtil.list;

/**
 * <pre>
 *      IndexBuilder是AbstractIndexBuilder的具体子类.
 *      功能: 由指定目录下的所有文本文件，产生Index对象.
 * </pre>
 */
public class IndexBuilder extends AbstractIndexBuilder {
    public IndexBuilder(AbstractDocumentBuilder docBuilder) {
        super(docBuilder);
    }

    @Override
    public AbstractIndex buildIndex(String rootDirectory) {
        AbstractIndex index = new Index();
        for (String docPath : list(rootDirectory)) {
            //遍历rootDirectory下的文件，构建document对象并添加到index索引中
            AbstractDocument document = docBuilder.build(docId++, docPath, new File(docPath));
            index.addDocument(document);
        }
        //序列化至index.dat文件中
        index.save(new File(Config.INDEX_DIR + "index.dat"));
        return index;
    }
}
