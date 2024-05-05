class Node:
    def __init__(self):
        self.child = {}
        self.is_end = False

class Trie:
    def __init__(self):
        self.root = Node()

    def insert(self, word):
        node = self.root
        for char in word:
            if char not in node.child:
                node.child[char] = Node()
            node = node.child[char]
        node.is_end = True

    def search(self, word):
        node = self.root
        for char in word:
            if char not in node.child:
                return False
            node = node.child[char]
        return node.is_end

    def checkPrefix(self, prefix):
        node = self.root
        for char in prefix:
            if char not in node.child:
                return False
            node = node.child[char]
        return True

    def _delete_node(node, word, depth):
        if depth == len(word):
            if not node.is_end:
                return False
            
            node.is_end = False
            return (len(node.child) == 0)
        
        lastChar = word[depth]
        if lastChar not in node.child:
            return False
        
        if Trie._delete_node(node.child[lastChar], word, depth + 1):
            del node.child[lastChar]
            return len(node.child) == 0
        
        return False


    def delete(self, word):
        Trie._delete_node(self.root, word, 0)


if __name__ == "__main__":
    trie = Trie()
    trie.insert("laptop")
    trie.insert("lambda")
    trie.insert("function")
    trie.insert("fiction")
    print(trie.search("laptop"))    # True
    print(trie.search("lapto"))    # False
    print(trie.checkPrefix("lap"))  # True
    trie.delete("lambda")
    print(trie.search("lambda"))    # False
