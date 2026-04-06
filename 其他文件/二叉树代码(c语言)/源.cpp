#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// 1. 定义二叉树节点结构
typedef struct TreeNode {
    int data;                    // 数据域，这里假设存储整数
    struct TreeNode* left;       // 左孩子指针
    struct TreeNode* right;      // 右孩子指针
} TreeNode;

// 2. 队列节点结构 (用于层序遍历)
typedef struct QueueNode {
    TreeNode* node;             //层序遍历节点
    struct QueueNode* next;     //下一个节点,形成链表
} QueueNode;



/*   Queue(层序)
   简单二叉树
        3
       / \
      4   5
     / \
    6   7
  
  第一次操作:将 3 分配至队首,4 和 5 分配至队尾
  //队伍 3            4 5
  
  第二次操作:将 4 分配至队首,6 和 7 分配至队尾
  //队伍 3 4            5           6 7
  
  第三次操作:将 5 分配至队首, NULL 分配至队尾
  //队伍 3 4  5                     6 7
  
  第四次操作:将 6 分配至队首, NULL 分配至队尾
  第五次操作:将 7 分配至队首, NULL 分配至队尾
 
 层序: 3 4 5 6 7 
*/
typedef struct Queue {          //结构体:分配前后层
    QueueNode* front;           //队首钥匙
    QueueNode* rear;            //队尾钥匙
} Queue;                        //根节点分配至队首,根节点的子节点分配至队尾

// 队列操作函数声明
Queue* createQueue();                               //开辟空间
void enqueue(Queue* q, TreeNode* node);             //排队进入
TreeNode* dequeue(Queue* q);                        //排队输出
int isQueueEmpty(Queue* q);                         //判断是否为空
// 3. 二叉树操作函数声明
TreeNode* createNode(int value);                    // 创建新节点
void preorderTraversal(TreeNode* root);             // 前序遍历
void inorderTraversal(TreeNode* root);              // 中序遍历
void postorderTraversal(TreeNode* root);            // 后序遍历
void levelOrderTraversal(TreeNode* root);           // 层序遍历

int main() {
    // 4. 构建示例二叉树
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5

    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    // 5. 执行各种遍历
    printf("前序遍历: ");
    preorderTraversal(root);
    printf("\n");

    printf("中序遍历: ");
    inorderTraversal(root);
    printf("\n");

    printf("后序遍历: ");
    postorderTraversal(root);
    printf("\n");

    printf("层序遍历: ");
    levelOrderTraversal(root);
    printf("\n");

    return 0;
}

// ==========================================
// 队列相关函数实现 (辅助层序遍历)
// ==========================================

Queue* createQueue() {                              //函数:开辟空间
    Queue* q = (Queue*)malloc(sizeof(Queue));       //分配空间
    q->front = q->rear = NULL;                      //清理空间
    return q;                                       //返回打开空间的钥匙p
}
//            空间钥匙    二叉树钥匙
void enqueue(Queue* q, TreeNode* node) {                            //函数:排队进入
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));     //分配空间
    newNode->node = node;                                           //为新空间分配二叉树节点的值
    newNode->next = NULL;                                           //清空下一个节点的指针,防止报错
    if (isQueueEmpty(q)) {                                          //判断队列是否为空
                                                //这里的链表只支持队头删除和队尾接入,当前一个为空时,链表只能首尾相接  
        q->front = q->rear = newNode;                               //链表首尾相接
    }
    else {
                                                //使用空间钥匙p,指向其队尾rear,rear指向下一个节点及新队首
        q->rear->next = newNode;                                    //新队首跟在旧队尾后面
        q->rear = newNode;                                          //更新队尾位置
    }
}

TreeNode* dequeue(Queue* q) {                                       //函数:排队输出
    if (isQueueEmpty(q)) return NULL;                               //判断链表是否为空
    QueueNode* temp = q->front;                                     //使temp成为指向链表队首的钥匙
    TreeNode* node = temp->node;                                    //通过temp找出它指向的node,并将其赋值
    q->front = q->front->next;                                      //更新队首
    if (q->front == NULL) q->rear = NULL;                           //如果队首为空,那么队尾为空
    free(temp);                                                     //清空
    return node;                                                    //返回赋值的值
}

int isQueueEmpty(Queue* q) {                                        //函数:判断是否为空
    return q->front == NULL;                                        
}

// ==========================================
// 二叉树函数实现
// ==========================================

// 创建新节点
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        printf("内存分配失败!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 前序遍历：根 -> 左 -> 右
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);          // 访问根节点
        preorderTraversal(root->left);      // 遍历左子树
        preorderTraversal(root->right);     // 遍历右子树
    }
}

// 中序遍历：左 -> 根 -> 右
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);       // 遍历左子树
        printf("%d ", root->data);          // 访问根节点
        inorderTraversal(root->right);      // 遍历右子树
    }
}

// 后序遍历：左 -> 右 -> 根
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);     // 遍历左子树
        postorderTraversal(root->right);    // 遍历右子树
        printf("%d ", root->data);          // 访问根节点
    }
}

// 层序遍历 (使用队列)
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) return;

    Queue* q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        TreeNode* current = dequeue(q);
        printf("%d ", current->data);

        // 将左右孩子入队（如果存在）
        if (current->left != NULL) {
            enqueue(q, current->left);
        }
        if (current->right != NULL) {
            enqueue(q, current->right);
        }
    }

    free(q);
}