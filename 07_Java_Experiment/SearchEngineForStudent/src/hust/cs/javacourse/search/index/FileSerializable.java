package hust.cs.javacourse.search.index;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 * 定义文件序列化接口
 */
public interface FileSerializable extends java.io.Serializable {
    /**
     * 写到二进制文件
     *
     * @param out :输出流对象
     */
    void writeObject(ObjectOutputStream out);

    /**
     * 从二进制文件读
     *
     * @param in :输入流对象
     */
    void readObject(ObjectInputStream in);
}
