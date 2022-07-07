/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractTermTuple;

import java.util.List;

/**
 * <pre>
 *     Document是AbstractDocument的具体子类.
 *     功能: 存储某个文档的文档编号、文档路径、文档中的三元组对象列表.
 * </pre>
 */
public class Document extends AbstractDocument {
    public Document() {
    }

    public Document(int docId, String docPath, List<AbstractTermTuple> tuples) {
        super(docId, docPath, tuples);
    }

    public Document(int docId, String docPath) {
        super(docId, docPath);
    }

    @Override
    public int getDocId() {
        return docId;
    }

    @Override
    public void setDocId(int docId) {
        this.docId = docId;
    }

    @Override
    public String getDocPath() {
        return docPath;
    }

    @Override
    public void setDocPath(String docPath) {
        this.docPath = docPath;
    }

    @Override
    public List<AbstractTermTuple> getTuples() {
        return tuples;
    }

    @Override
    public void addTuple(AbstractTermTuple tuple) {
        if (!contains(tuple)) {
            tuples.add(tuple);
        }
    }

    @Override
    public boolean contains(AbstractTermTuple tuple) {
        return tuples.contains(tuple);
    }

    @Override
    public AbstractTermTuple getTuple(int index) {
        return tuples.get(index);
    }

    @Override
    public int getTupleSize() {
        return tuples.size();
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("docId  ").append(docId).append(", docPath  ").append(docPath).append("\nTuples \n");
        for (AbstractTermTuple tuple : tuples)
            str.append(tuple.toString());
        return String.valueOf(str);
    }
}

