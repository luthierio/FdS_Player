#include <algorithm>
#include <vector>
#include <functional>

template <class DATATYPE, unsigned char SIZE>
class Array {
  private:
    std::vector<DATATYPE> values;

  public:
    DATATYPE Array[SIZE];

    std::vector<DATATYPE> getValues() const {
        return values;
    }

    void clean() {
        values.clear();
    }

    bool canPush() const {
        return true; // Vous pouvez ajuster cette logique si nécessaire
    }

    bool isEmpty() const {
        return values.empty();
    }

    bool exist(const DATATYPE& value) const {
        return std::find(values.begin(), values.end(), value) != values.end();
    }

    void push(const DATATYPE& value) {
        if (!exist(value) && canPush()) {
            values.push_back(value);                
            std::sort(values.begin(), values.end());
        }
    }

    DATATYPE getPreviousFrom(const DATATYPE& value) const {
        auto it = std::upper_bound(values.begin(), values.end(), value, std::less<DATATYPE>());
        if (it != values.begin()) {
            return *(--it);
        } else {
            // Aucune valeur strictement inférieure à 'value' n'a été trouvée,
            // dans ce cas, vous pouvez choisir comment traiter cette situation.
            // Ici, je retourne la dernière valeur du vecteur.
            return values.back();
        }
    }

    void printAll() const {
      for (const auto& marker : values) {
          Serial.print(marker);
          Serial.print(":");
      }
    }

    void pop() {
      if (!values.empty()) {
        values.pop_back();
        std::sort(values.begin(), values.end());
      }
    }

    void popPrevious(const DATATYPE& value) {
        const DATATYPE previous = getPreviousFrom(value);
        values.erase(std::remove(values.begin(), values.end(), previous), values.end());
        std::sort(values.begin(), values.end());
    }
};
