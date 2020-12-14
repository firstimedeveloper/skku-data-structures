#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define MAX 100000

typedef enum
{
    false,
    true
} bool;
typedef int Key;
typedef int Data;
typedef struct _BSTNode
{
    Data count;
    Data lChildren;
    Data rChildren;
    Key key;
    struct _BSTNode *lc;
    struct _BSTNode *rc;
} BSTNode;

BSTNode *CreateNode(Key key, Data count);
void DestroyNode(BSTNode *n);
bool CreateLeftSubTree(BSTNode *root, Key key, Data count);
bool CreateRightSubTree(BSTNode *root, Key key, Data count);

BSTNode *Search(BSTNode *root, Key key);
void Insert(BSTNode *root, Key key, Data count);
void Delete(BSTNode *root, Key key, Data count);
void Traverse(BSTNode *root);
void ClearTree(BSTNode *root);
void Inorder(BSTNode *root);

int Count(BSTNode *root, Key key);

int Top(BSTNode *root, Data rank);
int RangeCount(BSTNode *root, Data r1, Data r2);


int main() {
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    if (!node) printf("node is null");
    else printf("%d", node);
}


BSTNode *CreateNode(Key key, Data count)
{
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    node->key = key;
    node->count = count;
    node->lChildren = 0;
    node->rChildren = 0;
    node->lc = NULL;
    node->rc = NULL;

    return node;
}

void DestroyNode(BSTNode *n)
{
    free(n);
}
bool CreateLeftSubTree(BSTNode *root, Key key, Data count)
{
    BSTNode *node = CreateNode(key, count);
    if (root->lc != NULL)
        return false;
    root->lChildren += node->count;
    root->lc = node;
    return true;
}
bool CreateRightSubTree(BSTNode *root, Key key, Data count)
{
    BSTNode *node = CreateNode(key, count);
    if (root->rc != NULL)
        return false;
    root->rChildren += node->count;
    root->rc = node;
    return true;
}

void Inorder(BSTNode *root)
{
    if (root != NULL)
    {
        
        Inorder(root->lc);
        printf("k:%d c:%d lc:%d rc:%d\n", root->key, root->count, root->lChildren, root->rChildren);
        Inorder(root->rc);
    }
}

int Top(BSTNode *root, Data rank)
{
    int total = root->lChildren + root->rChildren + root->count;

    if (total < rank)
    {
        // printf("%d\n", -1);
        return -1;
    }

    int current = 0;
    while (root->lChildren != 0 || root->rChildren != 0)
    {
        // printf("k:%d curr:%d lc:%d c:%d rc:%d\n", root->key, current, root->lChildren, root->count, root->rChildren);
        // lc
        if (rank <= current + root->lChildren)
        {
            root = root->lc;
        }
        // rc
        else if (current + root->count + root->lChildren < rank)
        {
            current += root->count + root->lChildren;
            root = root->rc;
        }
        // middle
        else
        {
            // printf("%d\n", root->key);
            return root->key;
        }
    }
    // printf("%d\n", root->key);
    return root->key;
}

int RangeCount(BSTNode *root, Data r1, Data r2) {
    if (root == NULL)
        return 0;
    else if (root->key < r1) {
        return RangeCount(root->rc, r1, r2);
    } else if (root->key > r2) {
        return RangeCount(root->lc, r1, r2);
    }

    return root->count + RangeCount(root->lc, r1, r2) + RangeCount(root->rc, r1, r2);
}

BSTNode* Search(BSTNode* root, Key key)
{
    if (root == NULL || root->key == key) return root;
    else if (root->key > key)
        return Search(root->lc, key);
    else
        return Search(root->rc, key);
}

BSTNode *DSearch(BSTNode *root, Key key)
{
    BSTNode *cur = root;
    while (cur != NULL)
    {
        if (cur->key == key)
            break;
        else if (cur->key > key)
            cur = cur->lc;
        else
            cur = cur->rc;
    }
    return cur;
}

int Count(BSTNode *root, Key key)
{
    int count;
    BSTNode *node = Search(root, key);
    if (node == NULL || node->key == 0)
        count = -1;
    else
        count = node->count;
    // printf("%d\n", count);
    return count;
}

void fInsert(BSTNode* root, Key key, Data count)
{
    if (root->key == key) 
        root->count += count;
    
    else if (root->key > key) {
        // Insert a new node for a left child.
        if (root->lc == NULL)
            CreateLeftSubTree(root, key, count);
        else {
            root->lChildren += count;
            Insert(root->lc, key, count);
        }
    }
    else {
        // Insert a new node for a right child.
        if (root->rc == NULL)
            CreateRightSubTree(root, key, count);
        else {
            root->rChildren += count;
            Insert(root->rc, key, count);
        }

    }
}

void Insert(BSTNode *root, Key key, Data count)
{
    BSTNode *cur = root;
    if (cur->key == 0 && cur->count == 0)
    {
        cur->key = key;
        cur->count = count;
        return;
    }

    while (cur != NULL)
    {
        if (cur->key == key)
        {
            // printf("adding %d to grade %d dia\n", count, key);
            cur->count += count;
            return;
        }
        else if (cur->key > key)
        {
            // Insert a new node for a left child.
            if (cur->lc == NULL)
            {
                CreateLeftSubTree(cur, key, count);
                break;
            }
            else
            {
                cur->lChildren += count;
                cur = cur->lc;
            }
        }
        else
        {
            // Insert a new node for a right child.
            if (cur->rc == NULL)
            {
                CreateRightSubTree(cur, key, count);
                break;
            }
            else
            {
                cur->rChildren += count;
                cur = cur->rc;
            }
        }
    }
}

void Delete(BSTNode *root, Key key, Data count) {
    BSTNode *cur = root, *parent = NULL;
    // Find the current node and its parent node.

    // if key is not found, no need to carry on,
    // return
    BSTNode *found = Search(root, key);
    if (!found)
        return;
    
    Data found_count = found->count;
    // go through BST and delete lChildren and rChildren accordingly
    // this is okay because we know that the key exists.
    while (cur != NULL && cur->key != key)
    {  
        parent = cur; // Update the parent node.
        if (cur->key > key)
        {
            if (found_count > count)
                cur->lChildren -= count;
            else 
                cur->lChildren -= found_count;
            cur = cur->lc;
        }
        else
        {
            if (found_count > count)
                cur->rChildren -= count;
            else 
                cur->rChildren -= found_count;
            cur = cur->rc;
        }
    }
    if (cur->key == key && cur->count > count)
    {
        cur->count -= count;
    } else {
        cur->count = 0;
    } 

}

// void Delete(BSTNode *root, Key key, Data count)
// {
//     BSTNode *cur = root, *parent = NULL;
//     // Find the current node and its parent node.

//     // if key is not found, no need to carry on,
//     // return
//     BSTNode *found = Search(root, key);
//     if (!found)
//         return;

//     // go through BST and delete lChildren and rChildren accordingly
//     // this is okay because we know that the key exists.
//     while (cur != NULL && cur->key != key)
//     {
//         parent = cur; // Update the parent node.
//         if (cur->key > key)
//         {
//             cur->lChildren -= count;
//             cur = cur->lc;
//         }
//         else
//         {
//             cur->rChildren -= count;
//             cur = cur->rc;
//         }
//     }
//     if (cur->key == key && cur->count >= count)
//     {
//         cur->count -= count;
//         return;
//     } 

//     // The following 3 cases are if count is greater than or equal the node->count
//     // The case where count is smaller than node->count is handled above

//     // 1 if no children
//     if (cur->lc == NULL && cur->rc == NULL)
//     {
//         if (parent != NULL)
//         {
//             // Remove the current node depending on its position.
//             if (parent->lc == cur)
//             {
//                 parent->lc = NULL;
//             }
//             else
//             {
//                 parent->rc = NULL;
//             }
//             // parent->children -= cur->count;
//             // this is if im at root node with no children
//         }
//         else
//         {
//             cur->key = 0;
//             cur->count = 0;
//             return;
//         }
//         // case 2 if there's one children
//     }
//     else if (cur->lc == NULL || cur->rc == NULL)
//     {
//         BSTNode *child;
//         // Replace a node with its child node.
//         if (cur->lc != NULL)
//         {
//             child = cur->lc;
//         }
//         else
//         {
//             child = cur->rc;
//         }
//         // Replace the child node of its parent node.
//         if (parent != NULL)
//         {
//             if (parent->lc == cur)
//             {
//                 parent->lc = child;
//             }
//             else
//             {
//                 parent->rc = child;
//             }
//             // if deleting root node with one child
//         }
//         else
//         {
//             cur->key = child->key;
//             cur->count = child->count;
//             cur->lChildren = count;
//             cur->lc = child->lc;
//             cur->rc = child->rc;
//             DestroyNode(child);
//             return;
//         }
//     }
//     else
//     {
//         BSTNode *succ_parent = cur, *succ = cur->rc;
//         // Find the successor (left-most node of the current node.)
//         Data succ_count;
//         while (succ->lc != NULL)
//         {
//             succ_parent = succ;
//             succ = succ->lc;
//         }
//         succ_count = succ->count;
//         succ_parent = cur;
//         succ = cur->rc;
//         while (succ->lc != NULL)
//         {
//             succ_parent = succ;
//             succ_parent->lChildren -= succ_count;
//             succ = succ->lc;
//         }
//         // If initial succ doesn't have an lc, succ rc becomes the parent's rc
//         // this is okay even if succ rc is NULL, as then parent's rc will also just be NULL
//         if (succ_parent->rc == succ)
//         {
//             succ_parent->rc = succ->rc;
//         }
//         // if we come up to here, it means succ->lc is NULL
//         // so we set succ_parent's lc to whatever was succ's rc
//         else
//         {
//             succ_parent->lc = succ->rc;
//         }
//         cur->key = succ->key;
//         cur->count = succ->count;
//         cur->rChildren -= succ_count;
//         cur = succ; // Remove the successor.
//     }
//     DestroyNode(cur);
// }
