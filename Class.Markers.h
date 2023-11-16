#include <algorithm>
#include <vector>

template <class DATATYPE>
class MarkerArray {
private:
    std::vector<DATATYPE> markers;

    static bool compareMarkers(const DATATYPE& a, const DATATYPE& b) {
        return a > b;
    }

public:
    MarkerArray() {}

    void clean() {
        markers.clear();
    }

    bool canPush() const {
        return true; // Vous pouvez ajuster cette logique si nécessaire
    }

    bool isEmpty() const {
        return markers.empty();
    }

    bool exist(const DATATYPE& value) const {
        return std::find(markers.begin(), markers.end(), value) != markers.end();
    }

    void push(const DATATYPE& value) {
        if (!exist(value) && canPush()) {
            markers.push_back(value);
            std::sort(markers.begin(), markers.end(), compareMarkers);
        }
    }

    DATATYPE getPreviousFrom(const DATATYPE& value) const {
        for (const auto& marker : markers) {
            if (marker >= value) {
                return (marker == markers.front()) ? markers.back() : *(std::prev(std::find(markers.begin(), markers.end(), marker)));
            }
        }
        return markers.back();
    }

    void printAll() const {
        for (const auto& marker : markers) {
            Serial.print(marker);
            Serial.print(":");
        }
    }

    void pop() {
        if (!markers.empty()) {
            markers.pop_back();
        }
    }

    void popPrevious(const DATATYPE& value) {
        const DATATYPE previous = getPreviousFrom(value);
        markers.erase(std::remove(markers.begin(), markers.end(), previous), markers.end());
    }
};
