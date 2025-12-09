# INVALID ID's are ID's that have an even length and first half is equal to second half.

def is_invalid_id(n):
    s = str(n)          # Convert to a string
    length = len(s)

    # Needs to be even length
    if length % 2 != 0:
        return False

    half = length // 2
    # Check if ID starts with 0
    if s[0] == '0':
        return False

    # Compare first half with second half
    return s[:half] == s[half:]


# Test
examples = [55, 1212, 123123, 56561, 12312356]

for x in examples:
    print(x, "->", is_invalid_id(x))

