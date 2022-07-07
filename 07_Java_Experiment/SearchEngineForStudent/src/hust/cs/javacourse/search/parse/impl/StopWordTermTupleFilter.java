/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.StopWords;

import java.util.Arrays;
import java.util.List;

/**
 * <pre>
 *     StopWordTermTupleFilter类是AbstractTermTupleFilter的具体子类.
 *     功能: 完成停用词过滤功能.
 * </pre>
 */
public class StopWordTermTupleFilter extends AbstractTermTupleFilter {
    public StopWordTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
    }

    @Override
    public AbstractTermTuple next() {
        List<String> STOP_WORDS = Arrays.asList(StopWords.STOP_WORDS);
        AbstractTermTuple termTuple;
        while ((termTuple = input.next()) != null) {
            if (!STOP_WORDS.contains(termTuple.term.getContent()))
                return termTuple;
        }
        return null;
    }
}
