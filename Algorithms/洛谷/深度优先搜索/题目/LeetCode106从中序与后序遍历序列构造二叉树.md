106. 从中序与后序遍历序列构造二叉树
根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出

中序遍历 inorder = [9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]
返回如下的二叉树：

    3
   / \
  9  20
    /  \
   15   7
   
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
   public TreeNode buildTree(int[] inorder, int[] postorder) {
        if(inorder.length == 0){
            return null;
        }
        int rootValues = postorder[postorder.length-1];
        TreeNode root = new TreeNode(rootValues);
        int leftCount = 0;
        for(leftCount = 0;leftCount < inorder.length;leftCount++){
            if(inorder[leftCount] == rootValues){
                break;
            }
        }
        //统计出了左子树的节点数后求出左子树中序遍历的数组
        int[] leftInorder = Arrays.copyOfRange(inorder,0,leftCount);
        int[] leftPostorder = Arrays.copyOfRange(postorder,0,leftCount);
        root.left = buildTree(leftInorder,leftPostorder);
        //建右子树
        int[] rightInorder = Arrays.copyOfRange(inorder,leftCount+1,inorder.length);
        int[] rightPostorder = Arrays.copyOfRange(postorder,leftCount,inorder.length-1);
        root.right = buildTree(rightInorder,rightPostorder);
        return root;
    }
}
