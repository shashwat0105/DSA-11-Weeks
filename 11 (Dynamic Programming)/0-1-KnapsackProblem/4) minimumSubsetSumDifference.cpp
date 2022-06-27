// https://www.geeksforgeeks.org/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum/
// Problem Statement arr[] : {1, 2, 7}, To split array into to parts such that absolute(Sum2 - Sum1) = min
// Here Output = 4
// This problem is most similar to equal sum partition ques where Sum2 - Sum1 = 0, say S2 & S1
// S1, S2 belongs to [0, sum of all array elements(range)] // We found the extreme values of S1 & S2 ie when subset is empty and completely fill
// Here S1, S2 belongs to [0, 10] ie {1,2,3,4,5,6,7,8,9,10}
// Since S1 + S2 = range -> S2 = range - S1 -> Problem reduces to (Range - 2*S1) = min
// Assuming S2>S1 -> S1 < (Range/2) , to make overall positive difference
// Hence S1 belongs to [0, 5] ie {1,2,3,4,5} , Now we filter out the sums which are not possible to make with given array
// How to filter? Ans: by using subset sum problem for example sum = 4 will exist or not for given {1,2,7} array
// Hence S1 belongs to {1,2,3}
//   0  1 2 3   4 5 6 7 8 9 10  -> j(Sum)
// 0 T  F F F   F F F F F F  F   
// 1 T
// 2 T
// 3 T  T T (T) F F F T T T  T   // This last row represents(smaller problems) when size of array is 3 & sum varies from 0 to 10 (which we want)
// i(n)

// ******* IMP *****
// for minimizing difference between two sets, we need to know a number that is just less than sum/2 (sum is sum of all elements in array) 
// and can be generated by addition of elements from array. 

// The idea is, sum of S1 is j and it should be closest to sum/2, i.e., 2*j should be closest to sum.  (T) shown in table
// So, we move from S/2 to 0 and as soon as we find a T we break the loop and calculate diff with the index of that T value.

// code

int findMin(int arr[], int n){
    int Range=0;
    for(int i=0; i<n; i++){
        Range+=arr[i];
    }

    // Subset Sum making bottom up table
    bool t[n+1][Range+1];

    // base condition
    for(int i=0;i<=n;i++)
        t[i][0]=true;

    for(int j=1;j<=Range;j++)
        t[0][j]=false;

    // choice diagram
    for(int i=1;i<=n;i++){
        for(int j=1;j<=Range; j++){
            if(arr[i-1] <= j){
                t[i][j] = t[i-1][j-arr[i-1]] || t[i-1][j];
            }
            else{
                t[i][j] = t[i-1][j];
            }
        }
    }

    // Calculating the difference
    int diff = INT_MAX;

    for(int j = Range/2; j>=0; j--){
        if(t[n][j]==true){
            diff=Range-2*j;
            break;                               // no need to check on other T values
        }
    }
    return diff;
}