#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import fileinput
import random



# Copypasta stolen from: http://stackoverflow.com/a/4633515
def subset_sum(numbers, target, target_amount, partial=[]):
    s = sum(partial)
    matchCount = 0

    plength = len(partial)

    # check if the partial sum is equal to target
    if s == target and plength == target_amount:
        matchCount += 1

    if s >= target or plength > target_amount:
        return matchCount # if we reach the number why bother to continue

    for i in range(len(numbers)):
        n = numbers[i]
        # unique values only...
        if n in partial:
            continue
        remaining = numbers[i+1:]
        matchCount += subset_sum(remaining, target, target_amount, partial + [n])

    return matchCount

num_test_files = 3

for i in range(0, num_test_files):
    print("Test %i:" % (i))

    with open("input" + str(i) + '.txt', "w") as f:
        target_amount = random.randrange(2, 10)
        target_sum = random.randrange(target_amount, 200)

        is_valid = False
        nums = ''
        nums += str(target_amount) + '\n'
        nums += str(target_sum) + '\n'
        values = []

        n = random.randrange(5, 50)
        while not is_valid:
            values.clear()
            print("\tAttempt Begin: n = %i" % n)
            for i in range(0, n):
                k = random.randrange(1, 200)
                if k not in values:
                    values.append(k)
            is_valid = subset_sum(values, target_sum, target_amount) >= 1
            print("Done: %s" % str(is_valid))

        for k in values:
            nums += str(k) + '\n'

        f.write(nums)
