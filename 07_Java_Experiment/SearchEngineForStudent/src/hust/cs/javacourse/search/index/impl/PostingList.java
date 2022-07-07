/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.FileSerializable;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Comparator;
import java.util.List;

/**
 * <pre>
 *      PostingList是PostingList的抽象子类.
 *      功能: 包含了一个单词的Posting列表.
 * </pre>
 */
public class PostingList extends AbstractPostingList implements FileSerializable {
    public PostingList() {
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (AbstractPosting posting : list) {
            str.append(posting);
            if (list.indexOf(posting) != list.size() - 1)
                str.append("->");
        }
        return String.valueOf(str);
    }

    @Override
    public void add(AbstractPosting posting) {
        if (!contains(posting)) {
            list.add(posting);
        }
    }

    @Override
    public void add(List<AbstractPosting> postings) {
        for (AbstractPosting posting : postings) {
            if (!list.contains(posting)) {
                list.add(posting);
            }
        }
    }

    @Override
    public AbstractPosting get(int index) {
        return list.get(index);
    }

    @Override
    public int indexOf(AbstractPosting posting) {
        return list.indexOf(posting);
    }

    @Override
    public int indexOf(int docId) {
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i).getDocId() == docId) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public boolean contains(AbstractPosting posting) {
        for (AbstractPosting abstractPosting : list) {
            if (abstractPosting.getDocId() == posting.getDocId()) {
                return abstractPosting.equals(posting);
            }
        }
        return false;
    }

    @Override
    public void remove(int index) {
        if (index >= 0 && index < list.size()) {
            list.remove(index);
        }
    }

    @Override
    public void remove(AbstractPosting posting) {
        list.remove(posting);
    }

    @Override
    public int size() {
        return list.size();
    }

    @Override
    public void clear() {
        list.clear();
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    @Override
    public void sort() {
        list.sort(Comparator.naturalOrder());
    }

    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(list);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void readObject(ObjectInputStream in) {
        try {
            list = (List<AbstractPosting>) (in.readObject());
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
