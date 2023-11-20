#include <algorithm>
#include <functional>  // Include this line

template <class DATATYPE, unsigned char SIZE>
class Array {
private:
    DATATYPE values[SIZE];

public:
    unsigned char count;
    Array() : count(0) {}

    DATATYPE get() { return values; }

    DATATYPE* getValues() {
        return values;
    }

    void clean() {
        count = 0;
    }

    bool canPush() const {
        return count < SIZE;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool exist(const DATATYPE& value) const {
        return std::find(values, values + count, value) != values + count;
    }

    void push(const DATATYPE& value) {
        if (!exist(value) && canPush()) {
            values[count++] = value;
            std::sort(values, values + count);
        }
    }

    DATATYPE getPreviousFrom(const DATATYPE& value) const {
        auto it = std::upper_bound(values, values + count, value, std::less<DATATYPE>());
        if (it != values) {
            return *(--it);
        } else {
            return values[count - 1];
        }
    }

    void pop() {
        if (count > 0) {
            --count;
            std::sort(values, values + count);
        }
    }

    void popPrevious(const DATATYPE& value) {
        const DATATYPE previous = getPreviousFrom(value);
        auto newEnd = std::remove(values, values + count, previous);
        count = static_cast<unsigned char>(newEnd - values);
        std::sort(values, values + count);
    }
};
