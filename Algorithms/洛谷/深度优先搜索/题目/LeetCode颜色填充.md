编写函数，实现许多图片编辑软件都支持的「颜色填充」功能。
待填充的图像用二维数组 image 表示，元素为初始颜色值。初始坐标点的横坐标为 sr 纵坐标为 sc。需要填充的新颜色为 newColor 。
「周围区域」是指颜色相同且在上、下、左、右四个方向上存在相连情况的若干元素。
请用新颜色填充初始坐标点的周围区域，并返回填充后的图像。

示例：
输入：
image = [[1,1,1],[1,1,0],[1,0,1]] 
sr = 1, sc = 1, newColor = 2
输出：[[2,2,2],[2,2,0],[2,0,1]]
解释: 
初始坐标点位于图像的正中间，坐标 (sr,sc)=(1,1) 。
初始坐标点周围区域上所有符合条件的像素点的颜色都被更改成 2 。
注意，右下角的像素没有更改为 2 ，因为它不属于初始坐标点的周围区域。
 
提示：
image 和 image[0] 的长度均在范围 [1, 50] 内。
初始坐标点 (sr,sc) 满足 0 <= sr < image.length 和 0 <= sc < image[0].length 。
image[i][j] 和 newColor 表示的颜色值在范围 [0, 65535] 内。

class Solution {
    private int[][] global_image;
    private int ori_color, new_color, global_row, global_col;

    public int[][] floodFill(int[][] image, int sr, int sc, int newColor) {
        global_row = image.length;
        global_col = image[0].length;
        if (image[sr][sc] == newColor) return image;
        ori_color = image[sr][sc];
        new_color = newColor;
        global_image = image;
        dfs(sr, sc);
        return image;
    }

    private void dfs(int row, int col) {
        global_image[row][col] = new_color;
        if (row > 0 && global_image[row - 1][col] == ori_color)
            dfs(row - 1, col);
        if (col > 0 && global_image[row][col - 1] == ori_color)
            dfs(row, col - 1);
        if (row + 1 < global_row && global_image[row + 1][col] == ori_color)
            dfs(row + 1, col);
        if (col + 1 < global_col && global_image[row][col + 1] == ori_color)
            dfs(row, col + 1);
    }
}

作者：gfu
链接：https://leetcode-cn.com/problems/color-fill-lcci/solution/yuan-di-xiu-gai-dfs-by-gfu/

