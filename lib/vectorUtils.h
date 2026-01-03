#include <vector>
namespace vectorUtils {
template <typename T>

std::vector<T> flatten(std::vector<std::vector<T>> &unflattened_vector) {
    std::vector<T> flattened_vector;
    for (std::vector<T> &row : unflattened_vector) {
        for (T object : row) {
            flattened_vector.push_back(object);
        }
    }
    return flattened_vector;
}

template <typename T>
std::vector<T> flatten(std::vector<std::vector<T>> *unflattened_vector) {
    std::vector<T> flattened_vector;
    for (std::vector<T>& row : *unflattened_vector) {
        for (T object : row) {
            flattened_vector.push_back(object);
        }
    }
    return flattened_vector;
}
}; // namespace vectorUtils
