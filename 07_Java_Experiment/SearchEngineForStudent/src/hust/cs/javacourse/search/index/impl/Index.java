/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.*;

import java.io.*;
import java.util.*;

import static hust.cs.javacourse.search.util.FileUtil.write;

/**
 * <pre>
 *      Index是AbstractIndex的具体子类.
 *      功能: 存储一个文档集合的倒排索引
 * </pre>
 */
public class Index extends AbstractIndex implements FileSerializable {
    public Index() {
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        //输出字典
        str.append("dictionary:").append(getDictionary());
        //输出文档编号-文档路径索引
        str.append("\ndocId-----docPath mapping:\n");
        for (Integer i : docIdToDocPathMapping.keySet())
            str.append(i).append("   ---->   ").append(docIdToDocPathMapping.get(i)).append("\n");
        //输出单词-统计表索引
        str.append("term-----postingList mapping:\n");
        for (AbstractTerm t : getDictionary())
            str.append(t).append("   ---->   ").append(termToPostingListMapping.get(t)).append("\n");
        return String.valueOf(str);
    }

    @Override
    public void addDocument(AbstractDocument document) {
        docIdToDocPathMapping.put(document.getDocId(), document.getDocPath());
        Map<AbstractTerm, Posting> termPostingMap = new TreeMap<>();
        for (AbstractTermTuple tuple : document.getTuples()) {
            if (!termPostingMap.containsKey(tuple.term)) {
                //如果不包含该单词，则创建新的posting
                List<Integer> positons = new ArrayList<>();
                positons.add(tuple.curPos);
                termPostingMap.put(tuple.term, new Posting(document.getDocId(), 1, positons));
            } else {
                //如果该单词已经包含在termPostingMap中，则直接添加信息到对应posting中
                Posting posting = termPostingMap.get(tuple.term);
                posting.setFreq(posting.getFreq() + 1);
                List<Integer> positions = posting.getPositions();
                positions.add(tuple.curPos);
                posting.setPositions(positions);
            }
        }
        termPostingMap.forEach(
                (key, value) -> {
                    //对于termPostingMap中的每个键值对，如果termToPostingListMapping已经包含key，则直接添加
                    if (termToPostingListMapping.containsKey(key))
                        termToPostingListMapping.get(key).add(value);
                    else {
                        //如果不包含则使用put方法添加即可
                        AbstractPostingList postingList = new PostingList();
                        postingList.add(value);
                        termToPostingListMapping.put(key, postingList);
                    }
                }
        );
    }

    @Override
    public void load(File file) {
        try {
            ObjectInputStream in = new ObjectInputStream(new FileInputStream(file));
            readObject(in);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void save(File file) {
        try {
            ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(file));
            writeObject(out);
        } catch (IOException err) {
            err.printStackTrace();
        }
    }

    @Override
    public AbstractPostingList search(AbstractTerm term) {
        return termToPostingListMapping.get(term);
    }

    @Override
    public Set<AbstractTerm> getDictionary() {
        return termToPostingListMapping.keySet();
    }

    @Override
    public void optimize() {
        //对 PostingList进行排序
        for (AbstractPostingList list : termToPostingListMapping.values()) {
            list.sort();
            //对每个Posting进行排序
            for (int i = 0; i < list.size(); i++) {
                list.get(i).sort();
            }
        }
        //对字典进行排序
        for (AbstractTerm t : getDictionary()) {
            termToPostingListMapping.get(t).sort();
        }
    }

    @Override
    public String getDocName(int docId) {
        return docIdToDocPathMapping.get(docId);
    }

    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(termToPostingListMapping);
            out.writeObject(docIdToDocPathMapping);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void readObject(ObjectInputStream in) {
        try {
            termToPostingListMapping = (Map<AbstractTerm, AbstractPostingList>) in.readObject();
            docIdToDocPathMapping = (Map<Integer, String>) in.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * 将索引输出到filePath对应的文本文件中
     *
     * @param filePath 文本文件路径
     */
    public void print(String filePath) {
        write(toString(), filePath);
    }
}