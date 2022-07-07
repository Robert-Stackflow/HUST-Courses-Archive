/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;

/**
 * <pre>
 *      TermTuple是AbstractTermTuple的具体子类.
 *      功能: 表示一个三元组(单词，出现频率，出现的当前位置).
 * </pre>
 */
public class TermTuple extends AbstractTermTuple {

    public TermTuple() {
    }

    public TermTuple(Term term, int curPos) {
        this.term = term;
        this.curPos = curPos;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof TermTuple) {
            return ((TermTuple) obj).curPos == curPos && ((TermTuple) obj).term.equals(term);
        }
        return false;
    }

    @Override
    public String toString() {
        return "TermTuple{" +
                "term=" + term +
                ", freq=" + freq +
                ", curPos=" + curPos +
                '}';
    }
}
