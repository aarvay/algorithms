/* An RMQ implementation using Segment Tree */
/* Author : Vignesh Rajagopalan */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define INF 1<<29 //Taking 2^29 as an infinite value

vector<int> tree(100, 0); //initializing a segment tree of size 100 with zeros
int a[100]; //Given array

/*
 * create() takes the node index, lower limit, upper limit as the params and constructs a tree from the given array.
 * Calling create(1,1,n); will convert the entire array into the segment tree and store the min value of ranges in node k.
 *
 */
void create(int k, int low, int high) {
    
    if(low == high) {
        tree[k] = a[low];
        return;
    }
    int mid = (low + high) / 2; //midpoint of the range (low, high)
    
    create(2*k, low, mid); //Recursively build the left sub-tree
    create((2*k)+1, mid+1, high); //Recursively build the right sub-tree
    
    tree[k] = min(tree[2*k], tree[(2*k)+1]); // Value of the tree at index k is min of it's childrens
}

/*
 * query() takes the node index, lower limit, upper limit and also the query-low and query-highas the params and constructs a tree from 
 * the given array. Calling quey(1,1,n,i,j); will return the lowest element in the range i to j.
 *
 */
int query(int k, int low, int high, int qlow, int qhigh) {
    
    /* If the query limits are within the range don't break it further and return the value at node k */
    if(low >= qlow && high <= qhigh) return tree[k];
    
    /* If the query limits totally fall out of the range neglect that range by returning an infinite value */
    if(high < qlow || qhigh < low) return INF;
    
    int mid = (low + high) / 2;
    
    /* Search the left and the right sub-trees recursively and return the minimum of them */
    int r1 = query(2*k, low, mid, qlow, qhigh); 
    int r2 = query((2*k)+1, mid+1, high, qlow, qhigh);
    return min(r1, r2);
}

/*
 * Sample Input :
 *  9
 *  1 2 3 4 5 6 7 8 9
 *  2
 *  1 9
 *  3 5
 * Sample Output :
 *  1
 *  3
 */
int main () {
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n; i++) {
        scanf("%d", &a[i]);
    }
    create(1, 1, n); //creates a segment tree of the array a
    int t; scanf("%d", &t);
    while(t--){
        int l, h;
        scanf("%d%d", &l, &h);
        cout << query(1, 1, n, l, h) << endl;
    }
    return 0;
}
