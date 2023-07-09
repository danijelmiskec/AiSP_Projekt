#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>

struct Measurement {
    double u_q;
    double coolant;
    double stator_winding;
    double u_d;
    double stator_tooth;
    double motor_speed;
    double i_d;
    double i_q;
    double pm;
    double stator_yoke;
    double ambient;
    double torque;
    double profile_id;
};

void readMeasurements(const std::string& filename, std::map<double, Measurement>& measurements) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // preskoči zaglavlje

    while (std::getline(file, line)) {
        Measurement measurement;
        char delimiter = ',';
        size_t pos = 0;

        // Parsiranje linije i popunjavanje strukture Measurement
        pos = line.find(delimiter);
        measurement.u_q = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.coolant = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.stator_winding = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.u_d = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.stator_tooth = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.motor_speed = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.i_d = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.i_q = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.pm = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.stator_yoke = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.ambient = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(delimiter);
        measurement.torque = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        measurement.profile_id = std::stod(line);

        measurements[measurement.pm] = measurement;
    }

    file.close();
}

template<typename T>
void printMinAndMaxValue(const std::map<double, Measurement>& measurements, T Measurement::*attribute) {
    if (measurements.empty()) {
        std::cout << "No measurements found." << std::endl;
        return;
    }

    T minValue = std::numeric_limits<T>::max();
    T maxValue = std::numeric_limits<T>::lowest();

    for (const auto& pair : measurements) {
        T value = pair.second.*attribute;
        if (value < minValue) {
            minValue = value;
        }
        if (value > maxValue) {
            maxValue = value;
        }
    }

    std::cout << "Min value: " << minValue << std::endl;
    std::cout << "Max value: " << maxValue << std::endl;
}

template<typename T>
void printNMinAndMaxValues(const std::vector<T>& values, int N) {
    if (values.empty()) {
        std::cout << "No measurements found." << std::endl;
        return;
    }

    std::vector<T> sortedValues = values;
    std::sort(sortedValues.begin(), sortedValues.end());

    std::cout << N << " smallest values:" << std::endl;
    for (int i = 0; i < N && i < sortedValues.size(); ++i) {
        std::cout << sortedValues[i] << std::endl;
    }

    std::cout << N << " largest values:" << std::endl;
    int size = sortedValues.size();
    for (int i = size - N; i < size; ++i) {
        if (i >= 0) {
            std::cout << sortedValues[i] << std::endl;
        }
    }
}

int main() {
    std::map<double, Measurement> measurements;
    readMeasurements("measures_v2.csv", measurements);

    std::vector<double> allValues;
    for (const auto& pair : measurements) {
        allValues.push_back(pair.first);
    }

    int N = 5; // Broj najmanjih i najvećih vrijednosti koje želite ispisati

    std::cout << N << " smallest and largest values in the entire dataset:" << std::endl;
    printNMinAndMaxValues(allValues, N);

    std::cout << "u_q:" << std::endl;
    printMinAndMaxValue(measurements, &Measurement::u_q);

    std::cout << "coolant:" << std::endl;
    printMinAndMaxValue(measurements, &Measurement::coolant);

    std::cout << "stator_winding:" << std::endl;
    printMinAndMaxValue(measurements, &Measurement::stator_winding);

    std::cout << "u_d:" << std::endl;
    printMinAndMaxValue(measurements, &Measurement::u_d);

    std::cout << "stator_tooth:" << std::endl;
    printMinAndMaxValue(measurements, &Measurement::stator_tooth);

    std::cout << "motor_speed:" << std::endl;
    printMinAndMaxValue(measurements, &Measurement::motor_speed);

    std::cout << "i_d:" << std::endl;
    printMinAndMaxValue(measurements, &Measurement::i_d);

    std::cout << "i_q:" << std::endl;
    printMinAndMaxValue(measurements,&Measurement::i_q);

    std::cout << "pm:" << std::endl;
printMinAndMaxValue(measurements, &Measurement::pm);

std::cout << "stator_yoke:" << std::endl;
printMinAndMaxValue(measurements, &Measurement::stator_yoke);

std::cout << "ambient:" << std::endl;
printMinAndMaxValue(measurements, &Measurement::ambient);

std::cout << "torque:" << std::endl;
printMinAndMaxValue(measurements, &Measurement::torque);

std::cout << "profile_id:" << std::endl;
printMinAndMaxValue(measurements, &Measurement::profile_id);

return 0;

}