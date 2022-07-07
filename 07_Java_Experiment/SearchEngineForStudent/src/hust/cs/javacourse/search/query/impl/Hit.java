/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;

import java.util.Map;

/**
 * <pre>
 *     Hit是AbstractHit的具体子类.
 *     功能: 表示一个命中结果.
 * </pre>
 */
public class Hit extends AbstractHit {
    public Hit() {
    }

    public Hit(int docId, String docPath) {
        super(docId, docPath);
    }

    public Hit(int docId, String docPath, Map<AbstractTerm, AbstractPosting> termPostingMapping) {
        super(docId, docPath, termPostingMapping);
    }

    @Override
    public int getDocId() {
        return docId;
    }

    @Override
    public String getDocPath() {
        return docPath;
    }

    @Override
    public String getContent() {
        return content;
    }

    @Override
    public void setContent(String content) {
        this.content = content;
    }

    @Override
    public double getScore() {
        return score;
    }

    @Override
    public void setScore(double score) {
        this.score = score;
    }

    @Override
    public Map<AbstractTerm, AbstractPosting> getTermPostingMapping() {
        return termPostingMapping;
    }

    @Override
    public String toString() {
        return "----------------------------------------------\n" +
                "docId:" + docId +
                "\nscore:" + score +
                "\ndocPath:" + docPath +
                "\ntermPostingMapping:\n" + termPostingMapping +
                "\ncontent:\n" + content + "\n";
    }

    @Override
    public int compareTo(AbstractHit o) {
        //根据score进行比较
        double subValue = getScore() - o.getScore();
        if (subValue != 0)
            return (int) subValue;
        else
            return o.getDocId() - getDocId();
    }
}
