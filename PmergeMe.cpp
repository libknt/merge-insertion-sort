#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {};

PmergeMe::PmergeMe(const PmergeMe & r): input_(r.input_), List_mainChain_(r.List_mainChain_), Vector_mainChain_(r.Vector_mainChain_), sorted_(r.sorted_) {};

PmergeMe::~PmergeMe() {};

PmergeMe & PmergeMe::operator= (const PmergeMe &other) {
    if( this != &other ) {
        this->input_ = other.input_;
        this->List_mainChain_ = other.List_mainChain_;
        this->Vector_mainChain_ = other.Vector_mainChain_;
        this->sorted_ = other.sorted_;
    }
    return *this;
}
std::list<int> PmergeMe::getList() const { return this->List_mainChain_; }
std::vector<int> PmergeMe::getVector() const { return this->Vector_mainChain_; }

void PmergeMe::printClock(std::clock_t start, std::clock_t end, E_Type type) {
    std::string t;
    if(type == LIST) t = "  List  ";
    else if(type == VECTOR) t = " Vector ";
    double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    double microseconds = elapsed_time * 1e6;
    std::cout << \
    "Time to process a range of " << \
    this->size_ << \
    " elements with std::[" << \
    t << \
    "] : " << \
    std::fixed << std::setprecision(5) << microseconds << \
    " us" << \
    std::endl;
}

int PmergeMe::stoi(const std::string& str) {
    std::istringstream iss(str);
    int value;
    iss >> value;

    if (iss.fail() || !iss.eof()) {
        throw std::runtime_error("Invalid integer string");
    }

    return value;
}

void    PmergeMe::initContainer(int size, int numbers[]) {
    for (int i = 0; i < size; ++i) { 
        if(numbers[i] < 0) throw std::invalid_argument("Received a negative number");
        if(sorted_.find(numbers[i]) != sorted_.end()) throw std::runtime_error("The number already exists in the sorted container.");
        input_.push_back(numbers[i]);
        sorted_.insert(numbers[i]);
        List_mainChain_.push_back(numbers[i]);
        Vector_mainChain_.push_back(numbers[i]);
    }
}

void    PmergeMe::initContainer(int size, char* numbers) {
    (void)size;
    std::stringstream ss(numbers);
    std::string number;
    int n;
    while (std::getline(ss, number, ' ')) {
        if (!number.empty()) {
            n = stoi(number);
            if(n < 0) throw std::invalid_argument("Received a negative number");
            if(sorted_.find(n) != sorted_.end()) throw std::runtime_error("The number already exists in the sorted container.");
                input_.push_back(n);
                sorted_.insert(n);
                List_mainChain_.push_back(n);
                Vector_mainChain_.push_back(n);
        }
    }
}
void    PmergeMe::initContainer(int size, char* numbers[]) {
    int n;
    for (int i=0; i < size ; ++i) {
        n = stoi(numbers[i]);
        if(n < 0) throw std::invalid_argument("Received a negative number");
        if(sorted_.find(n) != sorted_.end()) throw std::runtime_error("The number already exists in the sorted container.");
        input_.push_back(n);
        sorted_.insert(n);
        List_mainChain_.push_back(n);
        Vector_mainChain_.push_back(n);
    }
}

void    PmergeMe::initContainer(int size, std::string numbers) {
    (void)size;
    std::stringstream ss(numbers);
    std::string number;
    int n;
    while (std::getline(ss, number, ' ')) {
        if (!number.empty()) {
            n = stoi(number);
            if(n < 0) throw std::invalid_argument("Received a negative number");
            if(sorted_.find(n) != sorted_.end()) throw std::runtime_error("The number already exists in the sorted container.");
                input_.push_back(n);
                sorted_.insert(n);
                List_mainChain_.push_back(n);
                Vector_mainChain_.push_back(n);
        }
    }
}
void    PmergeMe::initContainer(int size, std::string numbers[]) {
    int n;
    for (int i=0; i < size ; ++i) {
        n = stoi(numbers[i]);
        if(n < 0) throw std::invalid_argument("Received a negative number");
        if(sorted_.find(n) != sorted_.end()) throw std::runtime_error("The number already exists in the sorted container.");
        input_.push_back(n);
        sorted_.insert(n);
        List_mainChain_.push_back(n);
        Vector_mainChain_.push_back(n);
    }
}

int PmergeMe::calculateJacobsthalNumber(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return calculateJacobsthalNumber(n - 1) + (2 * calculateJacobsthalNumber(n - 2));
}

/**
 * list
*/
//pair comparison
bool PmergeMe::shouldSwapPairs(const std::list<int>& lst, int pairSize, int startIndex) {
    return getElementAtIndex(lst, startIndex) < getElementAtIndex(lst, startIndex + pairSize);
}

void PmergeMe::swapPairs(std::list<int>& lst, int pairSize, int startIndex) {
    std::list<int>::iterator leftStart = getIteratorAt(lst, startIndex);
    std::list<int>::iterator leftEnd = getIteratorAt(lst, startIndex + pairSize);
    std::list<int>::iterator rightStart = leftEnd;
    std::list<int>::iterator rightEnd = getIteratorAt(lst, startIndex + 2 * pairSize);

    lst.splice(leftStart, lst, rightStart, rightEnd);
    lst.splice(rightStart, lst, leftStart, leftEnd);
}

bool PmergeMe::isPairPresent(const std::list<int>& lst, int pairSize, size_t startIndex) {
    return getConstIteratorAt(lst, startIndex + 2*pairSize - 1) != lst.end();
}

void PmergeMe::processPairs(std::list<int>& lst, std::list<int>& subChain, int pairSize, UnpairedElemenat & unpairedData) {
    for (size_t i = 0; i < lst.size();) {
        if (!isPairPresent(lst, pairSize, i)) {
            std::list<int>::iterator iter = getIteratorAt(lst, i);
            if (iter != lst.end())
                subChain.splice(subChain.begin(), lst, iter, lst.end());
            break;
        }

        if (shouldSwapPairs(lst, pairSize, i)) {
            swapPairs(lst, pairSize, i);
        }

        i += 2 * pairSize;
    }

    unpairedData.length = subChain.size();
    unpairedData.value = *(subChain.begin());
    unpairedData.position = -1;
}

//separate mainChain SubChain
void PmergeMe::splitIntoMainAndSubChains(std::list<int>& mainChain, std::list<int>& subChain, int pairSize) {

    int segmentIndex = 1;

    while (true) {
        std::list<int>::iterator segmentStart = getIteratorAt(mainChain, segmentIndex * pairSize);
        
        if (segmentStart == mainChain.end()) {
            break;
        }

        std::list<int>::iterator segmentEnd = getIteratorAt(mainChain, (segmentIndex + 1) * pairSize);
        std::list<int>::iterator subChainInsertPosition = getIteratorAt(subChain, (segmentIndex - 1) * pairSize);
        
        subChain.splice(subChainInsertPosition, mainChain, segmentStart, segmentEnd);
        
        ++segmentIndex;
    }
}

//insert first subPair
void PmergeMe::prependSubchainToMain(std::list<int>& mainChain, std::list<int>& subChain, int pairSize) {
    std::list<int>::iterator subStart = subChain.begin();
    std::list<int>::iterator subEnd = getIteratorAt(subChain, pairSize);
    mainChain.insert(mainChain.begin(), subStart, subEnd);
}

//insert

bool PmergeMe::elementExceedsKey(std::list<int>& lst, int index, int key) {
    return getElementAtIndex(lst, index) >= key;
}

int PmergeMe::find_lower_bound(std::list<int> & lst, int key) {
    int left = -1;
    int right = lst.size();

    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (elementExceedsKey(lst, mid, key)) right = mid;
        else left = mid;
    }
    return right;
}

void PmergeMe::createComparisonListFromMainChain(std::list<int>& lst, std::list<int>& mainChain, int pairSize, UnpairedElemenat& unpairedData, int endpoint) {
    int point=0;
    if(unpairedData.position == -1 || unpairedData.length == 0 ) {
        for(ConstIntListIterator it=mainChain.begin(); it != mainChain.end(); ) {
            lst.push_back(*it);
            if(point == endpoint)
                break;
            ++point;
        it = advanceTo(mainChain, it, pairSize);
        }
    } else {
        int index = 0;
        for(ConstIntListIterator it=mainChain.begin(); it != mainChain.end(); ){
            if(unpairedData.position == index) {
                lst.push_back(*it);
                it = advanceTo(mainChain, it, unpairedData.length);
                ++index;
                ++point;
                continue;
            }
            lst.push_back(*it);
            std::advance(it, pairSize);
            if(point == endpoint)
                break;
            ++point;
            ++index;
        }
    }
}

int  PmergeMe::lower_bound(std::list<int> & mainChain, int key, int pairSize, UnpairedElemenat& unpairedData, int endpoint) { 
    std::list<int> lst;
    createComparisonListFromMainChain(lst, mainChain, pairSize, unpairedData, endpoint);
    return find_lower_bound(lst, key);
}

void PmergeMe::insertSubChain(std::list<int> & mainChain,int  insertPosition, ConstIntListIterator begin, ConstIntListIterator end) {
    mainChain.insert(getIteratorAt(mainChain, insertPosition), begin, end);
}

void PmergeMe::insertSegmentToMainChain(std::list<int>& mainChain, std::list<int>& subChain, int segmentStart, int segmentEnd, int insertionPoint, int pairSize) {
    std::list<int>::iterator startIter = getIteratorAt(subChain, segmentStart * pairSize);
    std::list<int>::iterator endIter = (segmentEnd == -1) ? subChain.end() : getIteratorAt(subChain, segmentEnd * pairSize);
    mainChain.insert(getIteratorAt(mainChain, pairSize * insertionPoint), startIter, endIter);
}


void PmergeMe::mergeSubIntoMain(std::list<int>& mainChain, std::list<int>& subChain, int pairSize, UnpairedElemenat& unpairedData) {
    int maxSegments = subChain.size() / pairSize;
    int insertSize = 0;

    for (int n = 3;; ++n) {
        for (int i = calculateJacobsthalNumber(n); i > calculateJacobsthalNumber(n - 1); --i) {
            if (i > maxSegments) {
                i = maxSegments;
                if (i == calculateJacobsthalNumber(n - 1)) break;
            }

            int key = getElementAtIndex(subChain, (i - 1) * pairSize);
            int insertionPoint = lower_bound(mainChain, key, pairSize, unpairedData, insertSize + i - 1);

            if (i == maxSegments) {
                insertSegmentToMainChain(mainChain, subChain, i - 1, -1, insertionPoint, pairSize);
                unpairedData.position = insertionPoint - 1;
            } else {
                insertSegmentToMainChain(mainChain, subChain, i - 1, i, insertionPoint, pairSize);
                if (unpairedData.position != -1 && unpairedData.value > key) {
                    unpairedData.position++;
                }
            }

            insertSize++;
        }
        if (calculateJacobsthalNumber(n) > maxSegments) break;
    }

    subChain.clear();
}



/**
 * vector
*/

//pair comparison
bool PmergeMe::shouldSwapPairs(const std::vector<int>& vec, int pairSize, int startIndex) {
    return getElementAtIndex(vec, startIndex) < getElementAtIndex(vec, startIndex + pairSize);
}

void PmergeMe::swapPairs(std::vector<int>& vec, int pairSize, int startIndex) {
    IntVecIterator leftStart = vec.begin() + startIndex;
    IntVecIterator leftEnd = leftStart + pairSize;
    IntVecIterator rightStart = leftEnd;

    std::swap_ranges(leftStart, leftEnd, rightStart);
}

bool PmergeMe::isPairPresent(const std::vector<int>& vec, int pairSize, size_t startIndex) {
    return getConstIteratorAt(vec, startIndex + 2*pairSize - 1) != vec.end();
}

void PmergeMe::processPairs(std::vector<int>& vec, std::vector<int>& subChain, int pairSize, UnpairedElemenat & unpairedData) {
    for (size_t i = 0; i < vec.size();) {
        if (!isPairPresent(vec, pairSize, i)) {
            std::vector<int>::iterator iter = getIteratorAt(vec, i);
            if (iter != vec.end()) {
                subChain.insert(subChain.begin(), iter, vec.end());
                vec.erase(iter, vec.end());
            }
            break;
        }

        if (shouldSwapPairs(vec, pairSize, i)) {
            swapPairs(vec, pairSize, i);
        }

        i += 2 * pairSize;
    }

    if(subChain.size() > 0)
        unpairedData.value = *(subChain.begin());

    unpairedData.length = subChain.size();
    unpairedData.position = -1;

}

/**
 * separate mainChain SubChain
*/
void PmergeMe::splitIntoMainAndSubChains(std::vector<int>& mainChain, std::vector<int>& subChain, int pairSize) {

    int segmentIndex = 1;
    std::vector<int> copy(subChain);
    subChain.clear();

    while (true) {
        std::vector<int>::iterator segmentStart = getIteratorAt(mainChain, segmentIndex * pairSize);
        
        if (segmentStart == mainChain.end()) {
            break;
        }

        std::vector<int>::iterator segmentEnd = getIteratorAt(mainChain, (segmentIndex + 1) * pairSize);
        
        subChain.insert(subChain.end(), segmentStart, segmentEnd);
        mainChain.erase(segmentStart, segmentEnd);
        
        ++segmentIndex;
    }
    
    subChain.insert(subChain.end(), copy.begin(), copy.end());
    copy.clear();
}

/**
 * insert first subPair
*/
void PmergeMe::prependSubchainToMain(std::vector<int>& mainChain, std::vector<int>& subChain, int pairSize) {
    std::vector<int>::iterator subStart = subChain.begin();
    std::vector<int>::iterator subEnd = getIteratorAt(subChain, pairSize);
    mainChain.insert(mainChain.begin(), subStart, subEnd);
}


/**
 * insert
*/

bool PmergeMe::elementExceedsKey(std::vector<int>& vec, int index, int key) {
    return getElementAtIndex(vec, index) >= key;
}

int PmergeMe::find_lower_bound(std::vector<int> & vec, int key) {
    int left = -1;
    int right = vec.size();

    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (elementExceedsKey(vec, mid, key)) right = mid;
        else left = mid;
    }
    return right;
}

void PmergeMe::createComparisonVectorFromMainChain(std::vector<int>& vec, std::vector<int>& mainChain, int pairSize, UnpairedElemenat& unpairedData, int endpoint) {
    int point=0;
    if(unpairedData.position == -1 || unpairedData.length == 0 ) {
        for(ConstIntVecIterator it=mainChain.begin(); it != mainChain.end(); ) {
            vec.push_back(*it);
            if(point == endpoint)
                break;
            ++point;
        it = advanceTo(mainChain, it, pairSize);
        }
    } else {
        int index = 0;
        for(ConstIntVecIterator it=mainChain.begin(); it != mainChain.end(); ){
            if(unpairedData.position == index) {
                vec.push_back(*it);
                it = advanceTo(mainChain, it, unpairedData.length);
                ++index;
                ++point;
                continue;
            }
            vec.push_back(*it);
            std::advance(it, pairSize);
            if(point == endpoint)
                break;
            ++point;
            ++index;
        }
    }
}

int  PmergeMe::lower_bound(std::vector<int> & mainChain, int key, int pairSize, UnpairedElemenat& unpairedData, int endpoint) { 
    std::vector<int> vec;
    createComparisonVectorFromMainChain(vec, mainChain, pairSize, unpairedData, endpoint);
    return find_lower_bound(vec, key);
}

void PmergeMe::insertSubChain(std::vector<int> & mainChain,int  insertPosition, ConstIntVecIterator begin, ConstIntVecIterator end) {
    mainChain.insert(getIteratorAt(mainChain, insertPosition), begin, end);
}

void PmergeMe::insertSegmentToMainChain(std::vector<int>& mainChain, std::vector<int>& subChain, int segmentStart, int segmentEnd, int insertionPoint, int pairSize) {
    std::vector<int>::iterator startIter = getIteratorAt(subChain, segmentStart * pairSize);
    std::vector<int>::iterator endIter = (segmentEnd == -1) ? subChain.end() : getIteratorAt(subChain, segmentEnd * pairSize);
    mainChain.insert(getIteratorAt(mainChain, pairSize * insertionPoint), startIter, endIter);
}


void PmergeMe::mergeSubIntoMain(std::vector<int>& mainChain, std::vector<int>& subChain, int pairSize, UnpairedElemenat& unpairedData) {
    int maxSegments = subChain.size() / pairSize;
    int insertSize = 0;

    for (int n = 3;; ++n) {
        for (int i = calculateJacobsthalNumber(n); i > calculateJacobsthalNumber(n - 1); --i) {
            if (i > maxSegments) {
                i = maxSegments;
                if (i == calculateJacobsthalNumber(n - 1)) break;
            }

            int key = getElementAtIndex(subChain, (i - 1) * pairSize);
            int insertionPoint = lower_bound(mainChain, key, pairSize, unpairedData, insertSize + i - 1);
            #ifdef INSERT
                #ifdef LISTDEBUG
                    testInsertDebug(mainChain, subChain, pairSize, "Insert", key, i);
                #endif
                #ifdef VECTORDEBUG
                    testInsertDebug(mainChain, subChain, pairSize, "Insert", key, i);
                #endif
            #endif

            if (i == maxSegments) {
                insertSegmentToMainChain(mainChain, subChain, i - 1, -1, insertionPoint, pairSize);
                unpairedData.position = insertionPoint - 1;
            } else {
                insertSegmentToMainChain(mainChain, subChain, i - 1, i, insertionPoint, pairSize);
                if (unpairedData.position != -1 && unpairedData.value > key) {
                    unpairedData.position++;
                }
            }

            insertSize++;
        }
        if (calculateJacobsthalNumber(n) > maxSegments) break;
    }
    #ifdef INSERT
        std::cout << std::endl << std::endl;
    #endif

    subChain.clear();
}




