import java.util.Arrays;

public class Matrix {

    private final int M;
    private final int N;
    double[][] data;

    /**
     * 含维度构造
     *
     * @param M 行
     * @param N 列
     */
    public Matrix(int M, int N) {
        this.M = M;
        this.N = N;
        this.data = new double[M][N];
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                data[i][j] = 0;
    }

    /**
     * 使用二维浮点型数组构造矩阵
     *
     * @param data 浮点型数组
     */
    public Matrix(double[][] data) {
        M = data.length;
        N = data[0].length;
        this.data = new double[M][N];
        for (int i = 0; i < M; i++) {
            System.arraycopy(data[i], 0, this.data[i], 0, N);
        }
    }

    /**
     * 使用二维浮点型数组构造矩阵
     *
     * @param data 浮点型数组
     */
    public Matrix(Double[][] data) {
        M = data.length;
        N = data[0].length;
        this.data = new double[M][N];
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                this.data[i][j] = data[i][j];
    }

    /**
     * 使用二维数组构造矩阵
     *
     * @param data 整型数组
     */
    public Matrix(int[][] data) {
        M = data.length;
        N = data[0].length;
        this.data = new double[M][N];
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                this.data[i][j] = data[i][j];
    }

    /**
     * 初始化矩阵为相同的数
     *
     * @param M 行数
     * @param N 列数
     * @param v 特定浮点型数值
     */
    public Matrix(int M, int N, double v) {
        this.M = M;
        this.N = N;
        double[][] tmp = new double[M][N];
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                tmp[i][j] = v;
        data = tmp;
    }

    /**
     * 返回矩阵行数
     *
     * @return 行数
     */
    public int getRowCount() {
        return this.M;
    }

    /**
     * 返回矩阵列数
     *
     * @return 列数
     */
    public int getColumnCount() {
        return this.N;
    }

    /**
     * 返回特定索引的元素值
     *
     * @param row    行索引
     * @param column 列索引
     * @return 元素
     */
    public double getElement(int row, int column) {
        return this.data[row][column];
    }

    /**
     * 设定指定索引元素为特定值
     *
     * @param row    行索引
     * @param column 列索引
     * @param e      值
     */
    public void setElement(int row, int column, double e) {
        this.data[row][column] = e;
    }

    /**
     * 设定指定行所有元素为特定值
     *
     * @param row 行索引
     * @param e   值
     * @return 设定后的矩阵
     */
    public Matrix setRow(int row, double e) {
        for (int j = 0; j < N; j++)
            this.data[row][j] = e;
        return this;
    }

    /**
     * 设定指定列所有元素为特定值
     *
     * @param column 列索引
     * @param e      值
     * @return 设定后的矩阵
     */
    public Matrix setColumn(int column, double e) {
        for (int i = 0; i < M; i++)
            this.data[i][column] = e;
        return this;
    }

    /**
     * 矩阵转置
     *
     * @return 转置后的矩阵
     */
    public Matrix transpose() {
        Matrix A = new Matrix(N, M);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                A.data[j][i] = this.data[i][j];
        return A;
    }

    /**
     * 两个矩阵相加
     *
     * @param B 指定矩阵
     * @return 原矩阵与指定矩阵的相加
     */
    public Matrix plus(Matrix B) {
        Matrix A = this;
        if (B.M != A.M || B.N != A.N) throw new RuntimeException("矩阵相加时两个矩阵的维度必须一致");
        Matrix C = new Matrix(M, N);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                C.data[i][j] = A.data[i][j] + B.data[i][j];
        return C;
    }

    /**
     * 两个矩阵相减
     *
     * @param B 指定矩阵
     * @return 原矩阵与指定矩阵的相减
     */
    public Matrix minus(Matrix B) {
        Matrix A = this;
        if (B.M != A.M || B.N != A.N) throw new RuntimeException("矩阵相减时两个矩阵的维度必须一致");
        Matrix C = new Matrix(M, N);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                C.data[i][j] = A.data[i][j] - B.data[i][j];
        return C;
    }

    /**
     * 两个矩阵相乘
     *
     * @param B 指定矩阵
     * @return 原矩阵与指定矩阵的相乘
     */
    public Matrix multiply(Matrix B) {
        Matrix A = this;
        if (A.N != B.M)
            throw new RuntimeException("矩阵相乘时第一个矩阵的列数必须等于第二个矩阵的行数:第一个矩阵的列数为" + A.N + ",第二个矩阵的行数为" + B.M);
        Matrix C = new Matrix(A.M, B.N);
        for (int i = 0; i < C.M; i++)
            for (int j = 0; j < C.N; j++)
                for (int k = 0; k < A.N; k++)
                    C.data[i][j] = C.data[i][j] + A.data[i][k] * B.data[k][j];
        return C;
    }

    /**
     * 两个矩阵相除
     *
     * @param B 指定矩阵
     * @return 原矩阵与指定矩阵的相除
     */
    public Matrix divide(Matrix B) {
        Matrix C = new Matrix(M, N);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (B.data[i][j] == 0) throw new RuntimeException("矩阵相除时被除数不能为0");
                C.data[i][j] = data[i][j] / B.data[i][j];
            }
        }
        return C;
    }

    /**
     * 两个矩阵点乘
     *
     * @param B 指定矩阵
     * @return 原矩阵与指定矩阵的点乘
     */
    public Matrix dot(Matrix B) {
        Matrix C = new Matrix(M, N);
        for (int i = 0; i < C.M; i++) {
            for (int j = 0; j < C.N; j++) {
                C.data[i][j] = data[i][j] * B.data[i][j];
            }
        }
        return C;
    }

    /**
     * 矩阵加上一个数
     *
     * @param e 数
     * @return 结果矩阵
     */
    public Matrix plus(double e) {
        Matrix C = new Matrix(M, N, e);
        return this.plus(C);
    }

    /**
     * 矩阵减去一个数
     *
     * @param e 数
     * @return 结果矩阵
     */
    public Matrix minus(double e) {
        Matrix C = new Matrix(M, N, e);
        return this.minus(C);
    }

    /**
     * 矩阵乘以一个数
     *
     * @param e 数
     * @return 结果矩阵
     */
    public Matrix multiply(double e) {
        Matrix C = new Matrix(M, N, 1);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                C.setElement(i, j, getElement(i, j) * e);
        return C;
    }

    /**
     * 矩阵除以一个数
     *
     * @param e 数
     * @return 结果矩阵
     */
    public Matrix divide(double e) {
        Matrix C = new Matrix(M, N, e);
        return this.divide(C);
    }

    /**
     * 判断两个矩阵是否相等
     *
     * @param t 待比较矩阵
     * @return 布尔矩阵
     */
    public boolean equalTo(Matrix t) {
        if (this.M != t.M || this.N != t.N) throw new RuntimeException("矩阵比较时两个矩阵的维度必须一致");
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                if (data[i][j] != t.data[i][j]) return false;
        return true;
    }

    /**
     * 打印到控制台
     */
    public void print() {
        for (double[] a : data) {
            for (double b : a)
                System.out.printf("%9.4f ", b);
            System.out.println();
        }
    }

    /**
     * 对矩阵每个数取绝对值
     *
     * @return 矩阵
     */
    public Matrix abs() {
        Matrix C = new Matrix(M, N);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                C.data[i][j] = Math.abs(data[i][j]);
        return C;
    }

    /**
     * 对矩阵的每个数向上取整
     *
     * @return 矩阵
     */
    public Matrix ceil() {
        Matrix C = new Matrix(M, N);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                C.data[i][j] = Math.ceil(data[i][j]);
        return C;
    }

    /**
     * 对矩阵的每个数四舍五入
     *
     * @return 矩阵
     */
    public Matrix round() {
        Matrix C = new Matrix(M, N);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                C.data[i][j] = Math.round(data[i][j]);
        return C;
    }

    /**
     * 向下取整
     *
     * @return 矩阵
     */
    public Matrix floor() {
        Matrix C = new Matrix(M, N);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                C.data[i][j] = Math.floor(data[i][j]);
        return C;
    }

    /**
     * 转换为数组
     *
     * @return 二维数组
     */
    public double[][] toArray() {
        return this.data;
    }

    /**
     * 找出矩阵的最大值
     *
     * @return 最大值
     */
    public double max() {
        double max = data[0][0];
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                if (max < data[i][j]) max = data[i][j];
        return max;
    }

    /**
     * 找出矩阵的最小值
     *
     * @return 最小值
     */
    public double min() {
        double min = data[0][0];
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                if (min > data[i][j]) min = data[i][j];
        return min;
    }

    /**
     * 返回矩阵每一行的最大值
     *
     * @return 最大值数组
     */
    public double[] maxOfEachRow() {
        double[] result = new double[M];
        double[][] tmp = data;
        for (int i = 0; i < M; i++) {
            Arrays.parallelSort(tmp[i]);
            result[i] = tmp[i][N - 1];
        }
        return result;
    }

    /**
     * 返回矩阵每一列的最大值
     *
     * @return 最大值数组
     */
    public double[] maxOfEachColumn() {
        double[] result = new double[N];
        double[] col = new double[M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                col[j] = data[j][i];
            }
            Arrays.parallelSort(col);
            result[i] = col[M - 1];
        }
        return result;
    }

    /**
     * 返回矩阵每一行的最小值
     *
     * @return 最小值数组
     */
    public double[] minOfEachRow() {
        double[] result = new double[M];
        double[][] tmp = data;
        for (int i = 0; i < M; i++) {
            Arrays.parallelSort(tmp[i]);
            result[i] = tmp[i][0];
        }
        return result;
    }

    /**
     * 返回矩阵每一列的最小值
     *
     * @return 最小值数组
     */
    public double[] minOfEachColumn() {
        double[] result = new double[N];
        double[] col = new double[M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                col[j] = data[j][i];
            }
            Arrays.parallelSort(col);
            result[i] = col[0];
        }
        return result;
    }

    /**
     * 返回和
     *
     * @return 和数组
     */
    public double sum() {
        double sum = 0;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                sum += data[i][j];
        return sum;
    }

    /**
     * 返回每一行的和
     *
     * @return 和数组
     */
    public double[] sumOfEachRow() {
        if (M == 1) {
            throw new RuntimeException("矩阵行数必须大于1");
        }
        double[] sum = new double[M];
        for (int i = 0; i < M; i++) {
            double s = 0;
            for (int j = 0; j < N; j++) {
                s += data[i][j];
            }
            sum[i] = s;
        }
        return sum;
    }

    /**
     * 返回每一列的和
     *
     * @return 和数组
     */
    public double[] sumOfEachColumn() {
        double[] sum = new double[N];
        for (int i = 0; i < N; i++) {
            double s = 0;
            for (int j = 0; j < M; j++) {
                s += data[j][i];
            }
            sum[i] = s;
        }
        return sum;
    }

    /**
     * 取得特定的行
     *
     * @param index 行索引
     * @return 行矩阵
     */
    public Matrix getRow(int index) {
        Matrix C = new Matrix(1, N);
        if (N >= 0) System.arraycopy(data[index], 0, C.data[0], 0, N);
        return C;
    }

    /**
     * 取得特定的列
     *
     * @param index 列索引
     * @return 列矩阵
     */
    public Matrix getColumn(int index) {
        Matrix C = new Matrix(M, 1);
        for (int i = 0; i < M; i++) {
            C.data[i][0] = data[i][index];
        }
        return C;
    }

    /**
     * 取得特定的列
     *
     * @param index 列索引
     * @return 列矩阵
     */
    public Double[] getColumnArray(int index) {
        Double[] C = new Double[M];
        for (int i = 0; i < M; i++) {
            C[i] = data[i][index];
        }
        return C;
    }

    public Matrix normalization() {
        Matrix C = this;
        double[] sum = sumOfEachColumn();
        for (int j = 0; j < N; j++)
            for (int i = 0; i < M; i++)
                if (getElement(i, j) != 0) setElement(i, j, getElement(i, j) / sum[j]);
        return C;
    }

    public String info() {
        return "矩阵行数:" + M + "\n" + "矩阵列数:" + N;
    }
}
