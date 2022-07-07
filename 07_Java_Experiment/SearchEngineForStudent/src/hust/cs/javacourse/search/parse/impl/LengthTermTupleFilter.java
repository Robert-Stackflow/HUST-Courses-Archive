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
 *     LengthTermTupleFilter类是AbstractTermTupleFilter的具体子类.
 *     功能: 完成单词长度过滤功能.
 * </pre>
 */
public class LengthTermTupleFilter extends AbstractTermTupleFilter {
    public LengthTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
    }

    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple termTuple;
        while ((termTuple = input.next()) != null) {
            if (termTuple.term.getContent().length() <= Config.TERM_FILTER_MAXLENGTH && termTuple.term.getContent().length() >= Config.TERM_FILTER_MINLENGTH)
                return termTuple;
        }
        return null;
    }
}
