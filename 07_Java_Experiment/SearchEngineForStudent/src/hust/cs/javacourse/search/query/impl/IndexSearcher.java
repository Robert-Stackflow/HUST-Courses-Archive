/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.Posting;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.*;

/**
 * <pre>
 *     IndexSearcher是AbstractIndexSearcher的具体子类.
 *     功能: 具体实现检索功能.
 * </pre>
 */
public class IndexSearcher extends AbstractIndexSearcher {

    public IndexSearcher() {
    }

    @Override
    public void open(String indexFile) {
        try {
            index.load(new File(indexFile));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter) {
        //查找该检索词对应的postingList
        AbstractPostingList postingList = index.search(queryTerm);
        if (postingList != null) {
            //postingList不为空说明查找到该检索词，根据postingList创建hits数组
            Map<AbstractTerm, AbstractPosting> termPostingMapping = new HashMap<>();
            AbstractHit[] hits = new AbstractHit[postingList.size()];
            for (int i = 0; i < postingList.size(); i++) {
                AbstractPosting posting = postingList.get(i);
                termPostingMapping.put(queryTerm, posting);
                hits[i] = new Hit(posting.getDocId(), index.getDocName(posting.getDocId()), termPostingMapping);
                hits[i].setScore(sorter.score(hits[i]));
                termPostingMapping.clear();
            }
            sorter.sort(Arrays.asList(hits));
            return hits;
        } else
            return null;
    }

    @Override
    public AbstractHit[] search(AbstractTerm queryTerm1, AbstractTerm queryTerm2, Sort sorter, LogicalCombination logicalCombination) {
        //查找两个检索词对应的postingList
        AbstractPostingList postingList1 = index.search(queryTerm1);
        AbstractPostingList postingList2 = index.search(queryTerm2);
        Map<AbstractTerm, AbstractPosting> termPostingMapping = new HashMap<>();
        ArrayList<AbstractHit> hits = new ArrayList<>();
        int mode = -1;
        //logicalCombination为null时，查找相邻的两个单词
        if (logicalCombination == null)
            mode = 2;
        //logicalCombination为null时，模式为OR
        else if (logicalCombination == LogicalCombination.OR)
            mode = 0;
        //logicalCombination为null时，模式为AND
        else if (logicalCombination == LogicalCombination.AND)
            mode = 1;
        switch (mode) {
            case 0:
                //模式为OR时，合并两个postingList
                if (postingList1 != null) {
                    for (int i = 0; i < postingList1.size(); i++) {
                        AbstractPosting posting = postingList1.get(i);
                        termPostingMapping.put(queryTerm1, posting);
                        hits.add(new Hit(posting.getDocId(), index.getDocName(posting.getDocId()), termPostingMapping));
                        hits.get(i).setScore(sorter.score(hits.get(i)));
                        termPostingMapping.clear();
                    }
                }
                if (postingList2 != null) {
                    for (int i = 0; i < postingList2.size(); i++) {
                        boolean flag = true;
                        AbstractPosting posting = postingList2.get(i);
                        for (AbstractHit item : hits) {
                            if (item.getDocId() == posting.getDocId()) {
                                item.getTermPostingMapping().put(queryTerm2, posting);
                                item.setScore(sorter.score(item));
                                flag = false;
                            }
                        }
                        if (flag) {
                            termPostingMapping.put(queryTerm2, posting);
                            hits.add(new Hit(posting.getDocId(), index.getDocName(posting.getDocId()), termPostingMapping));
                            hits.get(hits.size() - 1).setScore(sorter.score(hits.get(hits.size() - 1)));
                            termPostingMapping.clear();
                        }
                    }
                }
                break;
            case 1:
                //模式为AND时，按照docId得到两个postingList的交集
                if (postingList1 != null && postingList2 != null) {
                    for (int i = 0; i < postingList1.size(); i++) {
                        AbstractPosting posting1 = postingList1.get(i);
                        for (int j = 0; j < postingList2.size(); j++) {
                            AbstractPosting posting2 = postingList2.get(j);
                            if (posting1.getDocId() == posting2.getDocId()) {
                                termPostingMapping.put(queryTerm1, posting1);
                                termPostingMapping.put(queryTerm2, posting2);
                                hits.add(new Hit(posting1.getDocId(), index.getDocName(posting1.getDocId()), termPostingMapping));
                                hits.get(hits.size() - 1).setScore(sorter.score(hits.get(hits.size() - 1)));
                                termPostingMapping.clear();
                            }
                        }
                    }
                }
                break;
            case 2:
                //查找两个相邻的单词时，还需要在AND模式的基础上比较位置是否相差1来确定是否相邻
                if (postingList1 != null && postingList2 != null) {
                    for (int i = 0; i < postingList1.size(); i++) {
                        AbstractPosting posting1 = postingList1.get(i);
                        for (int j = 0; j < postingList2.size(); j++) {
                            AbstractPosting posting2 = postingList2.get(j);
                            if (posting1.getDocId() == posting2.getDocId()) {
                                List<Integer> position1 = posting1.getPositions();
                                List<Integer> position2 = posting2.getPositions();
                                List<Integer> positions = new ArrayList<>();
                                int i1 = 0, i2 = 0;
                                while (i1 < position1.size() && i2 < position2.size()) {
                                    int p1 = position1.get(i1);
                                    int p2 = position2.get(i2);
                                    if (p1 == p2 - 1 || p2 == p1 - 1) {
                                        positions.add(p1);
                                        i1++;
                                        i2++;
                                    } else if (p1 < p2 - 1) {
                                        i1++;
                                    } else {
                                        i2++;
                                    }
                                }
                                if (positions.size() > 0) {
                                    termPostingMapping.put(new Term(queryTerm1.getContent() + " " + queryTerm2.getContent()),
                                            new Posting(posting1.getDocId(), positions.size(), positions));
                                    hits.add(new Hit(posting1.getDocId(), index.getDocName(posting1.getDocId()), termPostingMapping));
                                    hits.get(hits.size() - 1).setScore(sorter.score(hits.get(hits.size() - 1)));
                                    termPostingMapping.clear();
                                }
                            }
                        }
                    }
                }
                break;
        }
        sorter.sort(hits);
        return hits.toArray(new AbstractHit[0]);
    }

    /**
     * 输出单个检索词的检索结果到文本文件中
     *
     * @param queryTerm 检索词
     * @param result    检索命中结果数组
     * @param filePath  输出的文件路径
     * @return 返回输出到文件中的字符串
     */
    public static String printQuery(AbstractTerm queryTerm, AbstractHit[] result, String filePath) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("[yyyy-MM-dd hh:mm:ss]  ");
        StringBuilder str = new StringBuilder("********************************************************************************************************\n");
        str.append(dateFormat.format(new Date()));
        str.append("Search \"").append(queryTerm).append("\"\n");
        if (result != null && result.length != 0) {
            for (AbstractHit hit : result)
                str.append(hit);
            str.append("\n");
        } else {
            str.append("Not Found!\n");
        }
        try {
            FileWriter writer = new FileWriter(filePath, true);
            writer.write(String.valueOf(str));
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return String.valueOf(str);
    }

    /**
     * 输出两个检索词的检索结果到文本文件中
     *
     * @param queryTerm1         检索词1
     * @param queryTerm2         检索词2
     * @param logicalCombination 逻辑组合词
     * @param result             检索命中结果数组
     * @param filePath           输出的文件路径
     * @return 返回输出到文件中的字符串
     */
    public static String printQuery(AbstractTerm queryTerm1, AbstractTerm queryTerm2, LogicalCombination logicalCombination, AbstractHit[] result, String filePath) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("[yyyy-MM-dd hh:mm:ss]  ");
        StringBuilder str = new StringBuilder("********************************************************************************************************\n");
        str.append(dateFormat.format(new Date()));
        if (logicalCombination == null)
            str.append("Search two words with NEIGHBOR: \"").append(queryTerm1).append("\" NEIGHBOR \"").append(queryTerm2).append("\"\n");
        else if (logicalCombination == LogicalCombination.AND)
            str.append("Search two words with AND: \"").append(queryTerm1).append("\" AND \"").append(queryTerm2).append("\"\n");
        else if (logicalCombination == LogicalCombination.OR)
            str.append("Search two words with OR: \"").append(queryTerm1).append("\" OR \"").append(queryTerm2).append("\"\n");
        if (result != null && result.length != 0) {
            for (AbstractHit hit : result)
                str.append(hit);
            str.append("\n");
        } else {
            str.append("Not Found!\n");
        }
        try {
            FileWriter writer = new FileWriter(filePath, true);
            writer.write(String.valueOf(str));
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return String.valueOf(str);
    }
}
