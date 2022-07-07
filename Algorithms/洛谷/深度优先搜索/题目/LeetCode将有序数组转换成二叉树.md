108. 将有序数组转换为二叉搜索树
将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。

本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

示例:
给定有序数组: [-10,-3,0,5,9],
一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：

      0
     / \
   -3   9
   /   /
 -10  5
 
遍历树的方法。DFS：先序遍历，中序遍历，后序遍历；BFS。

遍历树的两种通用策略：

深度优先遍历（DFS）
这种方法以深度 depth 优先为策略，从根节点开始一直遍历到某个叶子节点，然后回到根节点，在遍历另外一个分支。
根据根节点，左孩子节点和右孩子节点的访问顺序又可以将 DFS 细分为先序遍历 preorder，中序遍历 inorder 和后序遍历 postorder。

广度优先遍历（BFS）
按照高度顺序，从上往下逐层遍历节点。
先遍历上层节点再遍历下层节点。


中序遍历：始终选择中间位置左边元素作为根节点
算法
方法 helper(left, right) 使用数组 numsnums 中索引从 left 到 right 的元素创建 BST：
如果 left > right，子树中不存在元素，返回空。
找出中间元素：p = (left + right) // 2。
创建根节点：root = TreeNode(nums[p])。
递归创建左子树 root.left = helper(left, p - 1) 和右子树 root.right = helper(p + 1, right)。
返回 helper(0, len(nums) - 1)。

class Solution {
  int[] nums;

  public TreeNode helper(int left, int right) {
    if (left > right) return null;

    // always choose left middle node as a root
    int p = (left + right) / 2;

    // inorder traversal: left -> node -> right
    TreeNode root = new TreeNode(nums[p]);
    root.left = helper(left, p - 1);
    root.right = helper(p + 1, right);
    return root;
  }

  public TreeNode sortedArrayToBST(int[] nums) {
    this.nums = nums;
    return helper(0, nums.length - 1);
  }
}

复杂度分析:
时间复杂度：O(N)，每个元素只访问一次。
空间复杂度：O(N)，二叉搜索树空间 O(N)，递归栈深度 O(logN)。


