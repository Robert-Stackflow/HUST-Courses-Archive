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

方法一：递归
最直观的方法是使用递归。在递归遍历二叉树时，需要考虑当前的节点和它的孩子节点。
如果当前的节点不是叶子节点，则在当前的路径末尾添加该节点，并递归遍历该节点的每一个孩子节点。
如果当前的节点是叶子节点，则在当前的路径末尾添加该节点后，就得到了一条从根节点到叶子节点的路径，可以把该路径加入到答案中。

class Solution {
    public void construct_paths(TreeNode root, String path, LinkedList<String> paths) {
        if (root != null) {
            path += Integer.toString(root.val);
            if ((root.left == null) && (root.right == null))  // 当前节点是叶子节点
                paths.add(path);  // 把路径加入到答案中
            else {
                path += "->";  // 当前节点不是叶子节点，继续递归遍历
                construct_paths(root.left, path, paths);
                construct_paths(root.right, path, paths);
            }
        }
    }

    public List<String> binaryTreePaths(TreeNode root) {
        LinkedList<String> paths = new LinkedList();
        construct_paths(root, "", paths);
        return paths;
    }
}
复杂度分析:
时间复杂度：每个节点只会被访问一次，因此时间复杂度为 O(N)，其中 N 表示节点数目。
空间复杂度：O(N)。这里不考虑存储答案 paths 使用的空间，仅考虑额外的空间复杂度。
额外的空间复杂度为递归时使用的栈空间，
在最坏情况下，当二叉树中每个节点只有一个孩子节点时，递归的层数为 N，此时空间复杂度为 O(N)。
在最好情况下，当二叉树为平衡二叉树时，它的高度为 log(N)，此时空间复杂度为O(log(N))。
