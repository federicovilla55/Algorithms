# Using a defined standard number of bits
NUM_BITS = 1024

def zero_encoding(num):
    bin_num = (bin(num)[2:]).zfill(NUM_BITS)
    zero_enc = set()
    for i in range(len(bin_num)):
        if bin_num[i] == '0':
            zero_enc.add(bin_num[:i] + '1')
    return zero_enc

def one_encoding(num):
    bin_num = (bin(num)[2:]).zfill(NUM_BITS)
    one_enc = set()
    for i in range(len(bin_num)):
        if bin_num[i] == '1':
            one_enc.add(bin_num[:i+1])
    return one_enc

def private_set_intersection(set1, set2):
    return set1 & set2


a = 50
b = 25

if len(private_set_intersection(one_encoding(a), zero_encoding(b))) > 0:
    print("A > B")
else:
    print("B >= A")