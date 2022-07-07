/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.parse.impl.LengthTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.PatternTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.StopWordTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.TermTupleScanner;

import java.io.*;

/**
 * <pre>
 *      DocumentBuilder是AbstractDocumentBuilder的具体子类.
 *      功能: 由解析文本文档得到的TermTupleStream，产生Document对象.
 * </pre>
 */
public class DocumentBuilder extends AbstractDocumentBuilder {
    public DocumentBuilder() {
    }

    @Override
    public AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream) {
        AbstractDocument document = new Document(docId, docPath);
        AbstractTermTuple termTuple = termTupleStream.next();
        while (termTuple != null) {
            //读取下一个termTuple并加入到document中
            document.addTuple(termTuple);
            termTuple = termTupleStream.next();
        }
        return document;
    }

    @Override
    public AbstractDocument build(int docId, String docPath, File file) {
        AbstractTermTupleStream filter = null;
        try {
            //构造过滤器
            filter = new StopWordTermTupleFilter(new LengthTermTupleFilter(new PatternTermTupleFilter(new TermTupleScanner(new BufferedReader(new InputStreamReader(new FileInputStream(file)))))));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        assert filter != null;
        //使用重载的build方法实现
        return build(docId, docPath, filter);
    }
}
