def bwt_transform(text : str):
    text += chr(0) # Insert the ending character
    rotations = sorted([text[i:] + text[:i] for i in range(len(text))])
    bwt = ''.join(rot[-1] for rot in rotations) # last character of sorted rotations

    original_index = rotations.index(text)
    return bwt, original_index

def inverse_bwt(bwt : str, index : int) -> str:
    rotations = [''] * len(bwt)

    for i in range(len(bwt)): 
        # Reconstruct the orginal matrix with all possible rotations
        rotations = sorted(bwt[i] + rotations[i] for i in range(len(bwt)))

    for rot in rotations:
        if rot[-1] == chr(0):
            return rot

text = "BANANA"
bwt, index = bwt_transform(text)
print("Burrows-Wheeler Transformation: ", bwt)
original_text = inverse_bwt(bwt, index)
print("Original text:", original_text)
