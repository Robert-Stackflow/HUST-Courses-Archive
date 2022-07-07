/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * <pre>
 *     TermTupleScanner是AbstractTermTupleScanner的具体子类.
 *     功能: 它利用java.io.BufferedReader去读取文本文件得到一个个三元组TermTuple.
 * </pre>
 */
public class TermTupleScanner extends AbstractTermTupleScanner {
    private final List<TermTuple> tuples = new ArrayList<>();

    public TermTupleScanner(BufferedReader input) {
        super(input);
        //初始化StringSplitter对象
        StringSplitter splitter = new StringSplitter();
        splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
        try {
            int curPos = 0;
            String str = input.readLine();
            while (str != null) {
                //分割读取到的一行文本，并添加到tuples中
                List<String> parts = splitter.splitByRegex(str);
                for (String part : parts)
                    if (!part.equals(""))
                        tuples.add(new TermTuple(new Term(part.toLowerCase()), curPos++));
                str = input.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public AbstractTermTuple next() {
        if (!tuples.isEmpty())
            return tuples.remove(0);
        else
            return null;
    }
}
