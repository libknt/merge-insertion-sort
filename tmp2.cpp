# include <iostream>
# include <string>
# include <vector>
# include <list>
# include <exception> 
# include <algorithm>

typedef std::vector < int > ::const_iterator cv_itr;
typedef std::vector < int > ::iterator v_itr;
typedef std::vector < v_itr > ::iterator vi_itr;

typedef std::list < int > ::const_iterator cl_itr;
typedef std::list < int > ::iterator l_itr;

int jacobsthalNumber(int n) {

    if (n == 0) return 0;
    if (n == 1) return 1;

    return jacobsthalNumber(n - 1) + (2 * (jacobsthalNumber(n - 2)));
}

void mergeInsertionSort(std::vector < int > & v, int start, int end, int pairSize);

int comparison(int pairSize, std::vector < int > & v, int start) {
    if ((int)v.size() <= (pairSize + start))
        return -1;
    // std::cout << v[start] << "<" << v[pairSize + start] << std::endl;
    if (v[start] < v[pairSize + start])
        return 1;
    return 0;
}

void swap(int pairSize, std::vector < int > & v, int start) {
    for (int i = 0; i < pairSize; ++i) {
        std::iter_swap(v.begin() + start, v.begin() + start + pairSize);
        ++start;
    }
}

int checkOverflow(int pairSize, std::vector < int > & v, int start) {
    int size = v.size() - 1;

    for (int i = 0; i < pairSize; ++i) {
        if (start + pairSize > size)
            return true;
        ++start;
    }
    return false;
}

void pairwiseComparison(int pairSize, std::vector < int > & v, int start, int end) {

    (void)start;
    for (int i = 0; i < end;) {
        if (checkOverflow(pairSize, v, i))
            break;
        if (comparison(pairSize, v, i)) {
            swap(pairSize, v, i);
        }
        i += pairSize;
        i += pairSize;
    }
}

void separateMainChainAndSubChain(std::vector < int > & v, std::vector < int > & s, int pairSize) {
    int end = v.size();

    int over;
    for (int i = 0; i < end;) {
        if (checkOverflow(pairSize, v, i)) {
            over = i;
            for (int k = i; k < end; ++k) {
                s.push_back(v[k]);
            }
            break;
        }
        i += pairSize;
        for (int k = 0; k < pairSize; ++k) {
            s.push_back(v[i + k]);
        }
        i += pairSize;
    }

    int ep = 0;
    v_itr it = v.begin();
    for (; it != v.end(); ++it) {
        if (ep == over)
            break;
        ep++;
    }
    v.erase(it, v.end());

    int beginPostion = pairSize;
    for (;;) {
        v.erase(v.begin() + beginPostion, v.begin() + beginPostion + pairSize);
        if (v.begin() + beginPostion == v.end()) {
            break;
        }
        beginPostion += pairSize;
    }
}

void insertAtTheStart(std::vector < int > & v,v_itr firstKey) {
    v.insert(v.begin(), *firstKey);
}

void insert(std::vector < int > & v, v_itr position, int key) {
    v.insert(position, key);
}

bool isKey(std::vector < int > & v, int index, int key) {
    if (v[index] >= key) return true;
    else return false;
}

v_itr binarySearch(std::vector < int > & v, int key, int right) {
    return std::lower_bound(v.begin(), v.begin() + right + 1, key);
}

void insertionFromSubIntoMain(std::vector < int > & v, std::vector < int > & s, int pairSize) {
    int n = 3;
    int jac;
    v_itr itr;
    int insertNum = 0;
    while (1) {
        jac = jacobsthalNumber(n);

        // v_itr s_begin = s.begin();
        v_itr s_end = s.begin();
        for (int i = 0; i < pairSize; ++i) {
            ++s_end;
            if (s_end == s.end()) {
                break;
            }
        }
        int index = jac;
        if ((int)s.size() < jac)
            index = s.size();
        for (; jacobsthalNumber(n - 1) < index;) {
            itr = binarySearch(v, s[index - 1], insertNum + index - 1);
            insert(v, itr, s[index - 1]);
            ++insertNum;
            --index;
        }
        ++n;
        if ((int)s.size() < jac) break;
    }

}

void mergeInsertionSort(std::vector < int > & v, int start, int end, int pairSize) {
    if (v.size() / pairSize <= 2) return;

    pairwiseComparison(pairSize, v, start, end);

    /**
     * あとここだけー
     * Recursion. The ⌊𝑛2⌋ larger elements, i.e., a1 to 𝑎⌊𝑛2⌋ are sorted recursively. 
     * Then all elements (the ⌊𝑛2⌋ larger ones as well as the corresponding smaller ones) are renamed accordingly such that ai < ai+ 1 and ai > bi still holds.
    */
    // mergeInsertionSort(v, 0, v.size(), pairSize * 2);

    std::vector < int > s;
    separateMainChainAndSubChain(v, s, pairSize);
    // int i = 0;
    // std::cout << std::endl << "vector" << std::endl;
    // i = 0;
    // for (v_itr it = v.begin(); it != v.end(); ++it) {
    //     if ((i % pairSize) == 0)
    //         std::cout << "[";
    //     std::cout << * it;
    //     if ((i % pairSize) == 0)
    //         std::cout << "]";
    //     std::cout << " ";
    //     i++;
    // }
    // std::cout << std::endl << "small" << std::endl;
    // i = 0;
    // for (v_itr it = s.begin(); it != s.end(); ++it) {
    //     if ((i % pairSize) == 0)
    //         std::cout << "[";
    //     std::cout << * it;
    //     if ((i % pairSize) == 0)
    //         std::cout << "]";
    //     std::cout << " ";
    //     i++;
    // }
    insertAtTheStart(v, s.begin());
    insertionFromSubIntoMain(v, s, pairSize);
    // std::cout << std::endl <<  "vector" << std::endl;
    // for ( v_itr it = v.begin(); it != v.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl <<  "small" << std::endl;
    // for ( v_itr it = s.begin(); it != s.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // insertionFromSubIntoMain(v, s, pairSize);
    // std::cout << std::endl <<  "----------------------------" << std::endl;
    // std::cout << std::endl <<  "vector" << std::endl;
    // for ( v_itr it = v.begin(); it != v.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl <<  "small" << std::endl;
    // for ( v_itr it = s.begin(); it != s.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl <<  "----------------------------" << std::endl;
    // insertionFromSubIntoMain(v, s, pairSize);
    // std::cout << std::endl <<  "vector" << std::endl;
    // for ( v_itr it = v.begin(); it != v.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl <<  "small" << std::endl;
    // for ( v_itr it = s.begin(); it != s.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl <<  "=========================" << std::endl;
}

void mergeInsertionSortAlgorithm(std::vector < int > & v) {
    mergeInsertionSort(v, 0, v.size(), 1);
}

int main() {
    // 57 89 73 92 66 50 99 15 80 44 90 52 82 25 77 
    // 21 34 10 46 28 5  23 3  71 12 33 29 18 8  62
    int arr[] = {
        57,
        21,
        89,
        34,
        10,
        73,
        92,
        46,
        28,
        66,
        50,
        5,
        99,
        23,
        3,
        15,
        71,
        80,
        12,
        44,
        33,
        90,
        52,
        29,
        18,
        82,
        25,
        8,
        62,
        77
    };
    std::vector < int > v;
    for (int i = 0; i < 30; i++) {
        v.push_back(arr[i]);
    }
    for (v_itr it = v.begin(); it != v.end(); ++it) {
        std::cout << * it << " ";
    }
    std::cout << std::endl;

    mergeInsertionSortAlgorithm(v);
    // int i= 0;
    // int pairSize = 8;
    for (v_itr it = v.begin(); it != v.end(); ++it) {
        // if((i % pairSize) == 0)
        // std::cout << "[";
        std::cout << * it;
        // if((i % pairSize) == 0)
        // std::cout << "]";
        std::cout << " ";
        // i++;
    }

    return 0;
}