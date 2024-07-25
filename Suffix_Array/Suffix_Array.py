def create_suffix_array(word : str):
    # word += chr(0) # uncomment to use a string termination character
    suffix_arr = [(word[i:], i) for i in range(len(word))]
    suffix_arr.sort()
    '''[('I', 10), ('IPPI', 7), ('ISSIPPI', 4), ('ISSISSIPPI', 1), 
        ('MISSISSIPPI', 0), ('PI', 9), ('PPI', 8), ('SIPPI', 6), 
        ('SISSIPPI', 3), ('SSIPPI', 5), ('SSISSIPPI', 2)]'''
    
    return [index for substring, index in suffix_arr]


if __name__ == "__main__":
    word = "MISSISSIPPI"
    result = create_suffix_array(word)

    print("Suffix Array of '{}':".format(word), result)