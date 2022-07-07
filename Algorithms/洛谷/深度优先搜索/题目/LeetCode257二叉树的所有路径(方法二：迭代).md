257. 二叉树的所有路径
给定一个二叉树，返回所有从根节点到叶子节点的路径。

说明: 叶子节点是指没有子节点的节点。

示例:

输入:

   1
 /   \
2     3
 \
  5

输出: ["1->2->5", "1->3"]

解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3

方法二：迭代
上面的算法也可以使用迭代（宽度优先搜索）的方法实现。我们维护一个队列，存储节点以及根到该节点的路径。
一开始这个队列里只有根节点。在每一步迭代中，我们取出队列中的首节点，如果它是一个叶子节点，则将它对应的路径加入到答案中。
如果它不是一个叶子节点，则将它的所有孩子节点加入到队列的末尾。当队列为空时，迭代结束。

class Solution {
    public List<String> binaryTreePaths(TreeNode root) {
        LinkedList<String> paths = new LinkedList();
        if (root == null)
            return paths;

        LinkedList<TreeNode> node_stack = new LinkedList();
        LinkedList<String> path_stack = new LinkedList();
        node_stack.add(root);
        path_stack.add(Integer.toString(root.val));
        TreeNode node;
        String path;
        while (!node_stack.isEmpty()) {
            node = node_stack.pollLast();
            path = path_stack.pollLast();
            if ((node.left == null) && (node.right == null))
                paths.add(path);
            if (node.left != null) {
                node_stack.add(node.left);
                path_stack.add(path + "->" + Integer.toString(node.left.val));
            }
            if (node.right != null) {
                node_stack.add(node.right);
                path_stack.add(path + "->" + Integer.toString(node.right.val));
            }
        }
        return paths;
    }
}
复杂度分析:
时间复杂度：O(N)，每个节点只会被访问一次。
空间复杂度：O(N)，在最坏情况下，队列中有 N 个节点。

