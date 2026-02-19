"""
Python (Object-Oriented): Mean, Median, Mode for a list of integers.
- Reads one line of space-separated integers from stdin.
- Encapsulates statistical logic inside a class.
- Prints "None" if no value repeats (no mode).
"""

class StatisticsCalculator:
    def __init__(self, data):
        # Store the list of integers
        self.data = data

    def mean(self):
        return sum(self.data) / len(self.data)

    def median(self):
        sorted_data = sorted(self.data)
        n = len(sorted_data)

        if n % 2 == 1:
            return float(sorted_data[n // 2])
        else:
            a = sorted_data[n // 2 - 1]
            b = sorted_data[n // 2]
            return (a + b) / 2.0

    def mode(self):
        # Count frequencies using a dictionary
        freq = {}
        for value in self.data:
            freq[value] = freq.get(value, 0) + 1

        max_freq = max(freq.values())

        # If all values occur once, there is no mode
        if max_freq == 1:
            return []

        # Return all values with maximum frequency (sorted for consistency)
        return sorted([k for k, v in freq.items() if v == max_freq])


def parse_input():
    line = input("Enter integers separated by spaces:\n").strip()
    if not line:
        return None

    tokens = line.split()
    try:
        return [int(token) for token in tokens]
    except ValueError:
        return None


if __name__ == "__main__":
    numbers = parse_input()

    if not numbers:
        print("Error: please enter at least one integer.")
    else:
        calculator = StatisticsCalculator(numbers)

        mu = calculator.mean()
        med = calculator.median()
        modes = calculator.mode()

        print(f"Count: {len(numbers)}")
        print(f"Mean: {mu:.2f}")

        # Print median as integer if whole number
        if med.is_integer():
            print(f"Median: {int(med)}")
        else:
            print(f"Median: {med:.2f}")

        if not modes:
            print("Mode: None")
        else:
            print("Mode:", *modes)
