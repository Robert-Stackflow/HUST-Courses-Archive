/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.FileSerializable;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Comparator;
import java.util.List;

/**
 * <pre>
 *      Posting是AbstractPosting对象的抽象父类.
 *      功能: 代表倒排索引里每一项.
 *  </pre>
 */
public class Posting extends AbstractPosting implements Comparable<AbstractPosting>, FileSerializable {
    public Posting() {
    }

    public Posting(int docId, int freq, List<Integer> positions) {
        super(docId, freq, positions);
        sort();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Posting)
            return ((Posting) obj).docId == docId && ((Posting) obj).freq == freq && ((Posting) obj).positions.equals(positions);
        return false;
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
    public int getFreq() {
        return freq;
    }

    @Override
    public void setFreq(int freq) {
        this.freq = freq;
    }

    @Override
    public List<Integer> getPositions() {
        return positions;
    }


    @Override
    public void setPositions(List<Integer> positions) {
        this.positions = positions;
    }

    @Override
    public int compareTo(AbstractPosting o) {
        return getDocId() - o.getDocId();
    }

    @Override
    public void sort() {
        positions.sort(Comparator.naturalOrder());
    }


    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(docId);
            out.writeObject(freq);
            out.writeObject(positions);
        } catch (IOException err) {
            err.printStackTrace();
        }
    }

    @Override
    public void readObject(ObjectInputStream in) {
        try {
            docId = (int) (in.readObject());
            freq = (int) (in.readObject());
            positions = (List<Integer>) in.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public String toString() {
        return "{\"docId\":" + docId +
                ",\"freq\":" + freq +
                ",\"positions\":" + positions +
                "}";
    }
}
