class Solution:
    def canMeasureWater(self, jug1_capacity: int, jug2_capacity: int, target: int) -> bool:
        states_stack = [(0, 0)]
        self.visited_states = set()
        
        while states_stack:
            current_jug1, current_jug2 = states_stack.pop()

            if current_jug1 == target or current_jug2 == target or current_jug1 + current_jug2 == target:
                return True
        
            if (current_jug1, current_jug2) in self.visited_states:
                continue
            self.visited_states.add((current_jug1, current_jug2))
            states_stack.append((jug1_capacity, current_jug2))
            states_stack.append((current_jug1, jug2_capacity))
            states_stack.append((0, current_jug2))
            states_stack.append((current_jug1, 0))

            states_stack.append((current_jug1 - min(current_jug1, jug2_capacity - current_jug2),
                                 current_jug2 + min(current_jug1, jug2_capacity - current_jug2)))
            states_stack.append((current_jug1 + min(current_jug2, jug1_capacity - current_jug1),
                                 current_jug2 - min(current_jug2, jug1_capacity - current_jug1)))
        
        return False
