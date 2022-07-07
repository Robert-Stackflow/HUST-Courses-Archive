/**
 * @Author Ruida
 * @date 2022/4/20
 */
package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.FileSerializable;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 * <pre>
 *      Term是AbstractTerm的具体子类.
 *      功能: 表示文本文档里的一个单词.
 *   </pre>
 */
public class Term extends AbstractTerm implements Comparable<AbstractTerm>, FileSerializable {
    public Term() {
    }

    public Term(String content) {
        this.content = content;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Term) {
            return ((Term) obj).content.equals(content);
        }
        return false;
    }

    @Override
    public String toString() {
        return content;
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
    public int compareTo(AbstractTerm o) {
        return getContent().compareTo(o.getContent());
    }

    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(content);
        } catch (IOException err) {
            err.printStackTrace();
        }
    }

    @Override
    public void readObject(ObjectInputStream in) {
        try {
            content = (String) in.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
