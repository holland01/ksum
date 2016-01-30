**What I would have done with more time**

    * Definitely would have studied the algorithm in more depth, and looked around for one which was more efficient.
    * I would have considered the possibility that there may be some useful number theory which would come in handy for generating useful unit test
      files within the python script
    * I would have paid  more attention to areas where move semantics or copy elision would be considered useful, in addition to any other language specific features.
    * I would have generated more input files and figured out some more thorough testing methods.

**Running time complexity of the combinations function**
   We early out as soon as we've exceeded the target length of the tuple list, and the nature of the function
   prevents duplicate groups from being evaluated (irrespective of order). Given these two properties,
   we have a strict O(n!/r!(n - r)!), which is basically O(nCr).
   
