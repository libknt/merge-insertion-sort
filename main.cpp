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
    if (v.size() <= (pairSize + start))
        return -1;
    std::cout << v[start] << "<" << v[pairSize + start] << std::endl;
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
    size_t size = v.size() - 1;

    for (int i = 0; i < pairSize; ++i) {
        if (start + pairSize > size)
            return true;
        ++start;
    }
    return false;
}

void pairwiseComparison(int pairSize, std::vector < int > & v, int start, int end) {

    std::cout << std::endl << "pairsize: " << pairSize << std::endl;
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

void insertAtTheStart(std::vector < int > & v, std::vector < int > & s, v_itr begin, v_itr end) {
    v.insert(v.begin(), begin, end);
    // s.erase(begin, end);
}

void insert(std::vector < int > & v, v_itr position, int key) {
    v.insert(position, key);
}

// void insert(std::vector<int> & v, v_itr position, std::vector<int> & s, v_itr begin, v_itr end) {
//     if(begin == end){
//         v.insert(position, *begin);
//         // s.erase(begin);
//         return;
//     }
//     v.insert(position, begin, end);
//     // s.erase(begin, end);
// }

// bool isKey(std::vector<v_itr> iterators, int index, int key) {
//     if (*(iterators[index]) >= key) return true;
//     else return false;
// }

// v_itr lower_bound(std::vector<v_itr>& iterators, vi_itr begin, vi_itr end, int key, int right) {
//     int left = -1;
//     while (right - left > 1) {
//         int mid = left + (right - left) / 2;

//         if (isKey(iterators, mid, key)) right = mid;
//         else left = mid;
//     }

//     return *(iterators.begin() + right);
// }

// v_itr   binarySearch(std::vector<int> & v, int key, int pairSize, int keyPosition) {
//     std::vector<v_itr> iterators;

//     for (v_itr itr = v.begin(); itr != v.end(); itr += pairSize) {
//         iterators.push_back(itr);
//     }
//     vi_itr begin = iterators.begin();
//     vi_itr end = iterators.begin() + keyPosition;
//     return lower_bound(iterators,begin, end, key, iterators.size());
// }

bool isKey(std::vector < int > & v, int index, int key) {
    if (v[index] >= key) return true;
    else return false;
}

// int binarySearch(std::vector<int> & v, int key, int right) {
//     int left = -1;

//     std::cout << std::endl << "right   " << v[right] << std::endl;
//     while (right - left > 1) {
//         int mid = left + (right - left) / 2;

//         if (isKey(v, mid, key)) right = mid;
//         else left = mid;
//     }

//     return right;
// }

v_itr binarySearch(std::vector < int > & v, int key, int right) {
    // int left = -1;

    // std::cout << std::endl << "right   " << v[right] << std::endl;
    // while (right - left > 1) {
    //     int mid = left + (right - left) / 2;

    //     if (isKey(v, mid, key)) right = mid;
    //     else left = mid;
    // }
    // v_itr it = v.begin();
    // for ( int i=0; i <= right; ++i ) {
    //     ++it;
    // }
    std::cout << std::endl << "key " << key << "  it   " << * (v.begin() + right + 1) << std::endl;

    return std::lower_bound(v.begin(), v.begin() + right + 1, key);
    // return std::upper_bound(v.begin(), it, key);

    // return right;
}

void insertionFromSubIntoMain(std::vector < int > & v, std::vector < int > & s, int pairSize) {
    int n = 3;
    int jac;
    v_itr itr;
    int insertNum = 0;
    int i = 0;
    while (1) {
        jac = jacobsthalNumber(n);

        v_itr s_begin = s.begin();
        v_itr s_end = s.begin();
        for (int i = 0; i < pairSize; ++i) {
            ++s_end;
            if (s_end == s.end()) {
                break;
            }
        }
        int index = jac;
        if (s.size() < jac)
            index = s.size();
        std::cout << std::endl;
        for (; jacobsthalNumber(n - 1) < index;) {

            std::cout << std::endl << "vector" << std::endl;
            i = 0;
            for (v_itr it = v.begin(); it != v.end(); ++it) {
                if ((i % pairSize) == 0)
                    std::cout << "[";
                std::cout << * it;
                if ((i % pairSize) == 0)
                    std::cout << "]";
                std::cout << " ";
                i++;
            }
            itr = binarySearch(v, s[index - 1], insertNum + index - 1);
            std::cout << "^" << s[index - 1] << " " << * itr << "^";
            insert(v, itr, s[index - 1]);
            ++insertNum;
            --index;
        }
        std::cout << std::endl;
        ++n;
        if (s.size() < jac) break;
    }

}

void mergeInsertionSort(std::vector < int > & v, int start, int end, int pairSize) {
    if (v.size() / pairSize <= 2) return;

    pairwiseComparison(pairSize, v, start, end);

    // mergeInsertionSort(v, 0, v.size(), pairSize * 2);
    // if(pairSize < 4)
    //     return;
    std::cout << "size " << v.size() << std::endl;

    std::vector < int > s;
    int i = 0;
    // std::cout << std::endl <<  "=========================" << std::endl;
    //     std::cout << std::endl <<  "vector" << std::endl;
    //     i = 0;
    //     for ( v_itr it = v.begin(); it != v.end(); ++it) {
    //         if((i % pairSize) == 0)
    //             std::cout << "[";
    //         std::cout << *it;
    //         if((i % pairSize) == 0)
    //             std::cout << "]";
    //         std::cout << " ";
    //         i++;
    //     }
    separateMainChainAndSubChain(v, s, pairSize);
    std::cout << std::endl << "vector" << std::endl;
    i = 0;
    for (v_itr it = v.begin(); it != v.end(); ++it) {
        if ((i % pairSize) == 0)
            std::cout << "[";
        std::cout << * it;
        if ((i % pairSize) == 0)
            std::cout << "]";
        std::cout << " ";
        i++;
    }
    std::cout << std::endl << "small" << std::endl;
    i = 0;
    for (v_itr it = s.begin(); it != s.end(); ++it) {
        if ((i % pairSize) == 0)
            std::cout << "[";
        std::cout << * it;
        if ((i % pairSize) == 0)
            std::cout << "]";
        std::cout << " ";
        i++;
    }
    std::cout << std::endl << "=========================" << std::endl;
    insertAtTheStart(v, s, s.begin(), s.begin() + pairSize);
    std::cout << std::endl << "=========================" << std::endl;
    std::cout << "                                      pairSize: " << pairSize << std::endl;
    std::cout << std::endl << "[][][][][][][][][][][][]]" << std::endl;
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
    std::cout << "size " << v.size() << std::endl;
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
    int pairSize = 8;
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