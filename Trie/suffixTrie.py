class Node:
    def __init__(self):
        self.child = {}
        self.is_end = False

class SuffixTrie:
    def __init__(self):
        self.root = Node()

    def insert(self, word):
        for i in range(len(word)):
            self._insert_suffix(word[i:])

    def _insert_suffix(self, suffix):
        node = self.root
        for char in suffix:
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

    def delete(self, word):
        for i in range(len(word)):
            self._delete_suffix(word[i:])

    def _delete_suffix(self, suffix):
        SuffixTrie._delete_helper(self.root, suffix, 0)

    def _delete_helper(node, suffix, depth):
        if depth == len(suffix):
            if not node.is_end:
                return False
            node.is_end = False
            return len(node.child) == 0
        char = suffix[depth]
        if char not in node.child:
            return False
        if SuffixTrie._delete_helper(node.child[char], suffix, depth + 1):
            del node.child[char]
            return len(node.child) == 0
        return False


if __name__ == "__main__":
    trie = SuffixTrie()
    trie.insert("laptop")
    trie.insert("lambda")
    trie.insert("function")
    trie.insert("fiction")
    print(trie.search("laptop"))    # True
    print(trie.search("lap"))       # False
    print(trie.search("top"))       # True