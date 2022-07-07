/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

/**
 * <pre>
 *     PatternTermTupleFilter类是AbstractTermTupleFilter的具体子类.
 *     功能: 完成单词正则表达式过滤功能.
 * </pre>
 */
public class PatternTermTupleFilter extends AbstractTermTupleFilter {

    public PatternTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
    }

    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple termTuple;
        while ((termTuple = input.next()) != null) {
            if (termTuple.term.getContent().matches(Config.TERM_FILTER_PATTERN))
                return termTuple;
        }
        return null;
    }
}
