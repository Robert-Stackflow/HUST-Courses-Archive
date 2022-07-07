/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;

import java.util.Comparator;
import java.util.List;

public class SimpleSorter implements hust.cs.javacourse.search.query.Sort {

    @Override
    public void sort(List<AbstractHit> hits) {
        hits.sort(Comparator.reverseOrder());
    }

    @Override
    public double score(AbstractHit hit) {
        double score = 0.0;
        for (AbstractTerm key : hit.getTermPostingMapping().keySet()) {
            score += hit.getTermPostingMapping().get(key).getFreq();
        }
        return score;
    }
}
