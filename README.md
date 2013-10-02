In-place transposition of rectangular matrices
==================

Transposing a rectangular matrix without creating a copy in memory is not a trivial task.

1) Change the matrix dimensions :
    
    This can usually be done in unit time by changing the value of two integers.

2) Move the elements to their correct position in the transposed matrix:
    
    When the matrix is resized, the elements are placed in the resized matrix in column order. 
    
    0  4  8                             0 3 6 9
    1  5  9           becomes           1 4 7 10
    2  6  10                            2 5 8 11
    3  7  11
    
    Note that the position of each element is not the expected position in the transposed matrix. Each element must
    be moved to the correct position, although one cannot simply swap elements. Each element must be moved to its
    correct location, thus replacing the element that is currently in this place. Next, the replaced element must be
    moved and so on. The problem is that elements move along disjoint cycles. Therefore, one cannot simply swap all
    the elements of the resized matrix in a loop.
    
    The algorithm that I implemented uses a bitset to mark matrix elements that have been moved. This uses a little bit of
    additional memory, although the complexity of the algorithm is O(n) where n is the number of elements of the matrix.
    
    Algorithms that do not use additional memory exist, although they run in O(n log n) time.
    
For more information on in-place transposition of rectangular matrices, see:

    Gustavson, F. G., & Swirszcz, T. (2007). In-place transposition of rectangular matrices.In Applied Parallel Computing. 
    State of the Art in Scientific Computing (pp. 560-569). Springer Berlin Heidelberg.
