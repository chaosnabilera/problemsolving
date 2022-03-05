class Solution:
    def kidsWithCandies(self, candies: List[int], extraCandies: int) -> List[bool]:
        cmax = max(candies)
        return [ci+extraCandies >= cmax for ci in candies]