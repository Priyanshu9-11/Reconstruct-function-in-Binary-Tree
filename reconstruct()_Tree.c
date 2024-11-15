#include<stdio.h>
#include<stdlib.h>

struct bintree {
    char info;  // Changed from int to char
    struct bintree *left, *right;
};
typedef struct bintree node;

node *insert(node *, char);
void inorderTraversal(node *);
void preorderTraversal(node *);
node *reconstruct(char [], char [], int);

node *insert(node *s, char n) {     //insert() int n -> char n
    node *nn;
    nn = (node *)malloc(sizeof(node));
    nn->info = n;
    nn->left = NULL;
    nn->right = NULL;
    if (s == NULL) {
        return nn;
    } else {
        node *S = s;
        while (1) {
            if (n < S->info) {
                if (S->left == NULL) {
                    S->left = nn;
                    break;
                } else {
                    S = S->left;
                }
            }
            else {
                if (S->right == NULL) {
                    S->right = nn;
                    break;
                } else {
                    S = S->right;
                }
            }
        }
    }
    return s;
}

void inorderTraversal(node *s) {
    if (s != NULL) {
        inorderTraversal(s->left);
        printf("%c ", s->info);  // Print as char
        inorderTraversal(s->right);
    }
}

void preorderTraversal(node *s) {
    if (s != NULL) {
        printf("%c ", s->info);
        preorderTraversal(s->left);
        preorderTraversal(s->right);
    }
}

node *reconstruct(char inorder[100], char preorder[100], int nfn) {
    node *nn;
    char tmpinorder[100], tmppreorder[100];
    int i, pos;
    if (nfn == 0) {
        return NULL;
    }
    nn = (node *)malloc(sizeof(node));
    nn->info = preorder[0];  // Directly using char
    nn->left = nn->right = NULL;
    if (nfn == 1) {
        return nn;
    }
    for (i = 0; i <= nfn - 1; i++) {
        if (inorder[i] == preorder[0]) {
            break;
        }
    }
    pos = i;
    for (i = 0; i <= pos - 1; i++) {
        tmpinorder[i] = inorder[i];
        tmppreorder[i] = preorder[i + 1];
    }
    nn->left = reconstruct(tmpinorder, tmppreorder, pos);
    for (i = pos + 1; i < nfn; i++) {
        tmpinorder[i - pos - 1] = inorder[i];
        tmppreorder[i - pos - 1] = preorder[i];
    }
    nn->right = reconstruct(tmpinorder, tmppreorder, nfn - pos - 1);
    return nn;
}

main() {
    node *s = NULL;
    int n, i;
    char inorderArr[100], preorderArr[100];

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the Inorder traversal (as a sequence of characters without spaces): ");
    scanf("%s", inorderArr);

    printf("Enter the Preorder traversal (as a sequence of characters without spaces): ");
    scanf("%s", preorderArr);


    s = reconstruct(inorderArr, preorderArr, n);


    printf("Inorder Traversal of reconstructed tree: ");
    inorderTraversal(s);
    printf("\n");

    printf("Preorder Traversal of reconstructed tree: ");
    preorderTraversal(s);
    printf("\n");

}
